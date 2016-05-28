#include "CompiledCode.h"

const std::vector<std::shared_ptr<CompilationUnit>>& CompiledCode::GetCompilationUnitTable() const
{
	return compilationUnitTable_;
}

std::vector<std::shared_ptr<CompilationUnit>>& CompiledCode::GetCompilationUnitTable()
{
	return compilationUnitTable_;
}

void CompiledCode::SetCompilationUnitTable(const std::vector<std::shared_ptr<CompilationUnit>>& compilationUnitTable)
{
	compilationUnitTable_ = compilationUnitTable;
}

const std::vector<SideExit>& CompiledCode::GetSideExitTable() const
{
	return sideExitTable_;
}

std::vector<SideExit>& CompiledCode::GetSideExitTable()
{
	return sideExitTable_;
}

void CompiledCode::SetSideExitTable(const std::vector<SideExit>& sideExitTable)
{
	sideExitTable_ = sideExitTable;
}

void CompiledCode::Clear()
{
	compilationUnitTable_.clear();
	sideExitTable_.clear();
}
