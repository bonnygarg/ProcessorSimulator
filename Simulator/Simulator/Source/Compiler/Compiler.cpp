#include "Compiler.h"
#define _INCLUDE_LLVM_SWITCH_
//#define _PRINT_LLVM_OUTPUT_
#define _PERFORM_LLVM_OPTIMIZATIONS_

Compiler::Compiler(State* s) :
	s_(s)
{}

bool Compiler::Compile(std::shared_ptr<Cfg> cfg, CompiledCode& compiledCode)
{
	compiledCode.Clear();

	llvm::LLVMContext* context = new llvm::LLVMContext();

	llvm::InitializeNativeTarget();
	llvm::InitializeNativeTargetAsmPrinter();
	llvm::InitializeNativeTargetAsmParser();

	llvm::SMDiagnostic error;
	auto moduleUnique = llvm::parseIRFile("opcodes.bc", error, *context);
	if (!moduleUnique)
		return false;
	llvm::Module* module = moduleUnique.get();

	for (auto functionIterator = module->begin(); functionIterator != module->end(); ++functionIterator)
		functionIterator->addAttribute(llvm::AttributeSet::FunctionIndex, llvm::Attribute::AlwaysInline);

	llvm::ExecutionEngine* executionEngine = llvm::EngineBuilder(std::move(moduleUnique)).setEngineKind(llvm::EngineKind::JIT).create();

	if (!executionEngine)
		return false;

	llvm::StructType* stateType = module->getTypeByName("class.State");
	llvm::PointerType* statePointerType = llvm::PointerType::get(stateType, 0);

	// create function
	llvm::Function* function = llvm::cast<llvm::Function>(module->getOrInsertFunction(
		cfg->GetKey(),
		llvm::Type::getVoidTy(*context),
		statePointerType,
		nullptr));
	function->setCallingConv(llvm::CallingConv::C);
	llvm::AttributeSet func_foo_PAL;
	{
		llvm::SmallVector<llvm::AttributeSet, 4> Attrs;
		llvm::AttributeSet PAS;
		{
			llvm::AttrBuilder B;
			B.addAttribute(llvm::Attribute::NoCapture);
			PAS = llvm::AttributeSet::get(*context, 1U, B);
		}

		Attrs.push_back(PAS);
		{
			llvm::AttrBuilder B;
			B.addAttribute(llvm::Attribute::NoUnwind);
			PAS = llvm::AttributeSet::get(*context, ~0U, B);
		}

		Attrs.push_back(PAS);
		func_foo_PAL = llvm::AttributeSet::get(*context, Attrs);

	}
	function->setAttributes(func_foo_PAL);

	// fetch the function's argument, State* s
	llvm::Function::arg_iterator args = function->arg_begin();
	llvm::Value* statePointerArgument = &(*args);
	statePointerArgument->setName("s");

	// entry llvm basic block will hold a switch case to direct incoming control
	// (via s->pc) to proper basic block
	llvm::BasicBlock* entryBasicBlock = llvm::BasicBlock::Create(*context, "entry", function);
	
	// create llvm basic block for each basic block in cfg
	// and keep a table <cfg basic block key, llvm basic block>
	std::unordered_map<std::string, llvm::BasicBlock*> llvmBasicBlocks;
	for (auto basicBlockRecord : cfg->GetBasicBlockRecords())
	{
		llvm::BasicBlock* llvmBasicBlock = llvm::BasicBlock::Create(*context, basicBlockRecord.first, function);
		llvmBasicBlocks.insert(std::make_pair(basicBlockRecord.first, llvmBasicBlock));
	}

	// return llvm basic block holds a "return void;"
	llvm::BasicBlock* returnBasicBlock = llvm::BasicBlock::Create(*context, "return", function);

	// IRBuilder object
	// before using, make sure to set its entry point
	// via irb.SetEntryPoint(llvm::BasicBlock*);
	llvm::IRBuilder<> irb(*context);
	
	// now build switch case with cases for each entry basic block
	// and simultaneously add a CompiledOperation for each entry basic block
	
	// constant integers 0 and 7, for reaching s->pc from State* s
	// State.pc begins at 8th byte in memory block of class State 
	std::vector<llvm::Value*> pcIndexVector;
	pcIndexVector.push_back(llvm::ConstantInt::get(*context, llvm::APInt(32, 0)));
	pcIndexVector.push_back(llvm::ConstantInt::get(*context, llvm::APInt(32, 7)));
	llvm::ArrayRef<llvm::Value*> pcIndexArrayRef(pcIndexVector);

	// constant integers 0 and 19, for reaching s->resumeFromRecordIndex from State* s
	// State.resumeFromRecordIndex begins at 20th byte in memory block of class State 
	std::vector<llvm::Value*> resumeFromRecordIndexVector;
	resumeFromRecordIndexVector.push_back(llvm::ConstantInt::get(*context, llvm::APInt(32, 0)));
	resumeFromRecordIndexVector.push_back(llvm::ConstantInt::get(*context, llvm::APInt(32, 19)));
	llvm::ArrayRef<llvm::Value*> resumeFromRecordIndexArrayRef(resumeFromRecordIndexVector);

	// constant integers 0 and 20, for reaching s->sideExitIndex from State* s
	// State.sideExitIndex begins at 21st byte in memory block of class State 
	std::vector<llvm::Value*> sideExitIndexVector;
	sideExitIndexVector.push_back(llvm::ConstantInt::get(*context, llvm::APInt(32, 0)));
	sideExitIndexVector.push_back(llvm::ConstantInt::get(*context, llvm::APInt(32, 20)));
	llvm::ArrayRef<llvm::Value*> sideExitIndexArrayRef(sideExitIndexVector);
	
	irb.SetInsertPoint(entryBasicBlock);
	// int32* resumeFromRecordIndexPtr = s[0] + 19 bytes;
	auto resumeFromRecordIndexPtrInstruction = irb.CreateGEP(stateType, statePointerArgument, resumeFromRecordIndexArrayRef);
	// int32 resumeFromRecordIndex = *resumeFromRecordIndexPtr;
	auto resumeFromRecordIndexLoadInstruction = irb.CreateLoad(resumeFromRecordIndexPtrInstruction, false);
	resumeFromRecordIndexLoadInstruction->setAlignment(4);
	// switch (pcValue), case default: goto returnBasicBlock;	
#ifdef _INCLUDE_LLVM_SWITCH_
	auto resumeFromRecordIndexSwitchInstruction = irb.CreateSwitch(resumeFromRecordIndexLoadInstruction, returnBasicBlock);
#endif

	std::unordered_map<std::string, int> compilationUnitIndexTable;

	// add cases
	for (auto entryLabel : cfg->GetEntryBasicBlockRecords())
	{
		auto entryBasicBlockRecord = cfg->GetBasicBlockRecords().find(entryLabel);
		auto entryLlvmBasicBlock = llvmBasicBlocks.find(entryLabel);
		
		std::shared_ptr<CompilationUnit> compilationUnit = std::make_shared<CompiledFunction>(s_, executionEngine, cfg->GetKey());
		compiledCode.GetCompilationUnitTable().push_back(compilationUnit);
		int index = compiledCode.GetCompilationUnitTable().size() - 1;
		compilationUnitIndexTable.insert(std::make_pair(entryBasicBlockRecord->second->GetKey(), index));
		
		llvm::ConstantInt* llvmConstInt32ForIndex = llvm::ConstantInt::get(*context, llvm::APInt(32, index));
#ifdef _INCLUDE_LLVM_SWITCH_
		resumeFromRecordIndexSwitchInstruction->addCase(llvmConstInt32ForIndex, entryLlvmBasicBlock->second);
#endif
	}
	
	// add InterpretedOperation for each NonCompilableOperationRecord
	for (auto ncor : cfg->GetNonCompilableOperationRecords())
	{
		std::string resumeFromRecordKey = ncor.second.GetResumeFromRecord();
		int resumeFromRecordIndex = -1;
		if (resumeFromRecordKey != "")
		{
			resumeFromRecordIndex = compilationUnitIndexTable.find(resumeFromRecordKey)->second;
		}
		std::shared_ptr<CompilationUnit> compilationUnit = std::make_shared<InterpretedOperation>(s_, ncor.second, resumeFromRecordIndex);
		compiledCode.GetCompilationUnitTable().push_back(compilationUnit);
		int index = compiledCode.GetCompilationUnitTable().size() - 1;
		compilationUnitIndexTable.insert(std::make_pair(ncor.second.GetKey(), index));
	}

	// now for each basic block in cfg, we iterate over all its operations
	// emitting LLVM IR
	for (auto basicBlockRecord : cfg->GetBasicBlockRecords())
	{
		// get llvm basic block and set is as IRBuilder's insert point
		llvm::BasicBlock* llvmBasicBlock = llvmBasicBlocks.find(basicBlockRecord.second->GetKey())->second;
		irb.SetInsertPoint(llvmBasicBlock);

		if (basicBlockRecord.second->GetOperations().size() > 0)
		{
			// emit code for all operations
			for (auto operation : basicBlockRecord.second->GetOperations())
			{
				operation->EmitCompiledCode(irb, statePointerArgument, module);
			}

			// add switch case for jump(s) for outgoing edges (outgoing basic blocks)
			if (basicBlockRecord.second->GetOutgoingEdges().size() > 0)
			{
				// int16* pc = s[0] + 7 bytes;
				auto pcPtrInstruction = irb.CreateGEP(stateType, statePointerArgument,{
					llvm::ConstantInt::get(*context, llvm::APInt(32, 0)),
					llvm::ConstantInt::get(*context, llvm::APInt(32, 7))
				});
				// int16 pcValue16 = *pc;
				auto pcLoadInstruction = irb.CreateLoad(pcPtrInstruction, false);
				pcLoadInstruction->setAlignment(4);
				// int32 pcValue = (int32)pcValue16;
				auto pcCastInstruction = irb.CreateCast(llvm::Instruction::CastOps::ZExt, pcLoadInstruction, llvm::IntegerType::get(*context, 32));
				// switch (pcValue), case default: goto returnBasicBlock;
#ifdef _INCLUDE_LLVM_SWITCH_
				auto pcSwitchInstruction = irb.CreateSwitch(pcCastInstruction, returnBasicBlock);
#endif
				// add cases
				for (auto ogLabel : basicBlockRecord.second->GetOutgoingEdges())
				{
					auto ogBasicBlockRecord = cfg->GetBasicBlockRecords().find(ogLabel);
					auto ogLlvmBasicBlock = llvmBasicBlocks.find(ogLabel);
					
					int address = (int)ogBasicBlockRecord->second->GetStartAddress();
					llvm::ConstantInt* llvmConstantInt32ForAddress = llvm::ConstantInt::get(*context, llvm::APInt(32, address));
#ifdef _INCLUDE_LLVM_SWITCH_
					pcSwitchInstruction->addCase(llvmConstantInt32ForAddress, ogLlvmBasicBlock->second);
#endif
				}
			}
			else
			{
				int resumeFromRecordIndex = -1;
				std::string resumeFromRecordKey = basicBlockRecord.second->GetResumeFromRecord();
				if (resumeFromRecordKey != "")
				{
					resumeFromRecordIndex = compilationUnitIndexTable.find(resumeFromRecordKey)->second;
				}
				// int32* resumeFromRecordIndexPtr = s[0] + 19 bytes;
				auto resumeFromRecordIndexPtrInstruction = irb.CreateGEP(stateType, statePointerArgument, resumeFromRecordIndexArrayRef);
				llvm::ConstantInt* llvmConstInt32ForIndex = llvm::ConstantInt::get(*context, llvm::APInt(32, resumeFromRecordIndex));
				// *resumeFromRecordIndexPtr = resumeFromRecordIndex;
				auto resumeFromRecordIndexStoreInstruction = irb.CreateStore(llvmConstInt32ForIndex, resumeFromRecordIndexPtrInstruction, false);
				resumeFromRecordIndexStoreInstruction->setAlignment(4);
				
				irb.CreateBr(returnBasicBlock);
			}
		}
		else
		{
			// empty block 
			// => we are on a side exit
			
			// add entry to SideExitTable
			Address sideExitAddress = basicBlockRecord.second->GetStartAddress();
			std::string sideExitKey = basicBlockRecord.second->GetKey();
			SideExit sideExit = SideExit(sideExitAddress, sideExitKey);
			compiledCode.GetSideExitTable().push_back(sideExit);

			int resumeFromRecordIndex = -1;
			// int32* resumeFromRecordIndexPtr = s[0] + 19 bytes;
			auto resumeFromRecordIndexPtrInstruction = irb.CreateGEP(stateType, statePointerArgument, resumeFromRecordIndexArrayRef);
			llvm::ConstantInt* llvmConstInt32ForIndex = llvm::ConstantInt::get(*context, llvm::APInt(32, resumeFromRecordIndex));
			// *resumeFromRecordIndexPtr = -1;
			auto resumeFromRecordIndexStoreInstruction = irb.CreateStore(llvmConstInt32ForIndex, resumeFromRecordIndexPtrInstruction, false);
			resumeFromRecordIndexStoreInstruction->setAlignment(4);

			int sideExitIndex = compiledCode.GetSideExitTable().size() - 1;
			// int32* sideExitIndexPtr = s[0] + 20 bytes;
			auto sideExitIndexPtrInstruction = irb.CreateGEP(stateType, statePointerArgument, sideExitIndexArrayRef);
			llvm::ConstantInt* llvmConstInt32ForSideExitIndex = llvm::ConstantInt::get(*context, llvm::APInt(32, sideExitIndex));
			// *sideExitIndexPtr = sideExitIndex;
			auto sideExitIndexStoreInstruction = irb.CreateStore(llvmConstInt32ForSideExitIndex, sideExitIndexPtrInstruction, false);
			sideExitIndexStoreInstruction->setAlignment(4);

			// add a "goto returnBasicBlock;" statement
			irb.CreateBr(returnBasicBlock);
		}
	}

	// add return void to return block
	llvm::ReturnInst::Create(*context, returnBasicBlock);

#ifdef _PRINT_LLVM_OUTPUT_
	// debug only, print function generated
	llvm::outs() << *function;
#endif

	// verify function
	if (llvm::verifyFunction(*function)) {
		// handle error
		return false;
	}

#ifdef _PERFORM_LLVM_OPTIMIZATIONS_
	// inline the function calls
	llvm::legacy::PassManager pm;
	pm.add(llvm::createAlwaysInlinerPass());
	pm.run(*module);

	// optimize the function
	std::unique_ptr<llvm::legacy::FunctionPassManager> fpm(new llvm::legacy::FunctionPassManager(module));
	// Do simple "peephole" optimizations and bit-twiddling optzns.
	fpm->add(llvm::createInstructionCombiningPass());
	// Reassociate expressions.
	fpm->add(llvm::createReassociatePass());
	// Eliminate Common SubExpressions.
	fpm->add(llvm::createGVNPass());
	// Simplify the control flow graph (deleting unreachable blocks, etc).
	fpm->add(llvm::createCFGSimplificationPass());
	fpm->doInitialization();
	fpm->run(*function);
#endif

#ifdef _PRINT_LLVM_OUTPUT_
	// debug only, print function generated
	llvm::outs() << *function;
#endif

	return true;
}

