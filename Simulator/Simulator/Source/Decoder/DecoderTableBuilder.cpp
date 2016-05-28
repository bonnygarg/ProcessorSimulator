#include "DecoderTableBuilder.h"

#include <OperationFunction\OperationFunctions.h>
#include <OperationFactory\ByteOperandOperationFactory.h>
#include <OperationFactory\NoOperandOperationFactory.h>
#include <OperationFactory\InOperationFactory.h>
#include <OperationFactory\OutOperationFactory.h>
#include <OperationFactory\WordOperandOperationFactory.h>
#include <OperationFactory\ConditionalCallOperationFactory.h>
#include <OperationFactory\ConditionalJumpOperationFactory.h>
#include <OperationFactory\ConditionalReturnOperationFactory.h>
#include <OperationFactory\UnconditionalCallOperationFactory.h>
#include <OperationFactory\UnconditionalJumpOperationFactory.h>
#include <OperationFactory\UnconditionalReturnOperationFactory.h>
#include <OperationFactory\RestartOperationFactory.h>
#include <OperationFactory\HaltOperationFactory.h>

void AddDataTransferOperations(DecoderTableBuilder::DecoderTable& table)
{
	// MOV R,R --------------------------------------------------------------------------------
	table.insert(
		std::make_pair(
			OperationKey(0x7F), std::make_shared<NoOperandOperationFactory>(
				OperationMetadata("mov_a_a", false, 1), &opfun::mov_a_a
				)));
	table.insert(
		std::make_pair(
			OperationKey(0x78), std::make_shared<NoOperandOperationFactory>(
				OperationMetadata("mov_a_b", false, 1), &opfun::mov_a_b
				)));
	table.insert(
		std::make_pair(
			OperationKey(0x79), std::make_shared<NoOperandOperationFactory>(
				OperationMetadata("mov_a_c", false, 1), &opfun::mov_a_c
				)));
	table.insert(
		std::make_pair(
			OperationKey(0x7A), std::make_shared<NoOperandOperationFactory>(
				OperationMetadata("mov_a_d", false, 1), &opfun::mov_a_d
				)));
	table.insert(
		std::make_pair(
			OperationKey(0x7B), std::make_shared<NoOperandOperationFactory>(
				OperationMetadata("mov_a_e", false, 1), &opfun::mov_a_e
				)));
	table.insert(
		std::make_pair(
			OperationKey(0x7C), std::make_shared<NoOperandOperationFactory>(
				OperationMetadata("mov_a_h", false, 1), &opfun::mov_a_h
				)));
	table.insert(
		std::make_pair(
			OperationKey(0x7D), std::make_shared<NoOperandOperationFactory>(
				OperationMetadata("mov_a_l", false, 1), &opfun::mov_a_l
				)));
	table.insert(
		std::make_pair(
			OperationKey(0x47), std::make_shared<NoOperandOperationFactory>(
				OperationMetadata("mov_b_a", false, 1), &opfun::mov_b_a
				)));
	table.insert(
		std::make_pair(
			OperationKey(0x40), std::make_shared<NoOperandOperationFactory>(
				OperationMetadata("mov_b_b", false, 1), &opfun::mov_b_b
				)));
	table.insert(
		std::make_pair(
			OperationKey(0x41), std::make_shared<NoOperandOperationFactory>(
				OperationMetadata("mov_b_c", false, 1), &opfun::mov_b_c
				)));
	table.insert(
		std::make_pair(
			OperationKey(0x42), std::make_shared<NoOperandOperationFactory>(
				OperationMetadata("mov_b_d", false, 1), &opfun::mov_b_d
				)));
	table.insert(
		std::make_pair(
			OperationKey(0x43), std::make_shared<NoOperandOperationFactory>(
				OperationMetadata("mov_b_e", false, 1), &opfun::mov_b_e
				)));
	table.insert(
		std::make_pair(
			OperationKey(0x44), std::make_shared<NoOperandOperationFactory>(
				OperationMetadata("mov_b_h", false, 1), &opfun::mov_b_h
				)));
	table.insert(
		std::make_pair(
			OperationKey(0x45), std::make_shared<NoOperandOperationFactory>(
				OperationMetadata("mov_b_l", false, 1), &opfun::mov_b_l
				)));
	table.insert(
		std::make_pair(
			OperationKey(0x4F), std::make_shared<NoOperandOperationFactory>(
				OperationMetadata("mov_c_a", false, 1), &opfun::mov_c_a
				)));
	table.insert(
		std::make_pair(
			OperationKey(0x48), std::make_shared<NoOperandOperationFactory>(
				OperationMetadata("mov_c_b", false, 1), &opfun::mov_c_b
				)));
	table.insert(
		std::make_pair(
			OperationKey(0x49), std::make_shared<NoOperandOperationFactory>(
				OperationMetadata("mov_c_c", false, 1), &opfun::mov_c_c
				)));
	table.insert(
		std::make_pair(
			OperationKey(0x4A), std::make_shared<NoOperandOperationFactory>(
				OperationMetadata("mov_c_d", false, 1), &opfun::mov_c_d
				)));
	table.insert(
		std::make_pair(
			OperationKey(0x4B), std::make_shared<NoOperandOperationFactory>(
				OperationMetadata("mov_c_e", false, 1), &opfun::mov_c_e
				)));
	table.insert(
		std::make_pair(
			OperationKey(0x4C), std::make_shared<NoOperandOperationFactory>(
				OperationMetadata("mov_c_h", false, 1), &opfun::mov_c_h
				)));
	table.insert(
		std::make_pair(
			OperationKey(0x4D), std::make_shared<NoOperandOperationFactory>(
				OperationMetadata("mov_c_l", false, 1), &opfun::mov_c_l
				)));
	table.insert(
		std::make_pair(
			OperationKey(0x57), std::make_shared<NoOperandOperationFactory>(
				OperationMetadata("mov_d_a", false, 1), &opfun::mov_d_a
				)));
	table.insert(
		std::make_pair(
			OperationKey(0x50), std::make_shared<NoOperandOperationFactory>(
				OperationMetadata("mov_d_b", false, 1), &opfun::mov_d_b
				)));
	table.insert(
		std::make_pair(
			OperationKey(0x51), std::make_shared<NoOperandOperationFactory>(
				OperationMetadata("mov_d_c", false, 1), &opfun::mov_d_c
				)));
	table.insert(
		std::make_pair(
			OperationKey(0x52), std::make_shared<NoOperandOperationFactory>(
				OperationMetadata("mov_d_d", false, 1), &opfun::mov_d_d
				)));
	table.insert(
		std::make_pair(
			OperationKey(0x53), std::make_shared<NoOperandOperationFactory>(
				OperationMetadata("mov_d_e", false, 1), &opfun::mov_d_e
				)));
	table.insert(
		std::make_pair(
			OperationKey(0x54), std::make_shared<NoOperandOperationFactory>(
				OperationMetadata("mov_d_h", false, 1), &opfun::mov_d_h
				)));
	table.insert(
		std::make_pair(
			OperationKey(0x55), std::make_shared<NoOperandOperationFactory>(
				OperationMetadata("mov_d_l", false, 1), &opfun::mov_d_l
				)));
	table.insert(
		std::make_pair(
			OperationKey(0x5F), std::make_shared<NoOperandOperationFactory>(
				OperationMetadata("mov_e_a", false, 1), &opfun::mov_e_a
				)));
	table.insert(
		std::make_pair(
			OperationKey(0x58), std::make_shared<NoOperandOperationFactory>(
				OperationMetadata("mov_e_b", false, 1), &opfun::mov_e_b
				)));
	table.insert(
		std::make_pair(
			OperationKey(0x59), std::make_shared<NoOperandOperationFactory>(
				OperationMetadata("mov_e_c", false, 1), &opfun::mov_e_c
				)));
	table.insert(
		std::make_pair(
			OperationKey(0x5A), std::make_shared<NoOperandOperationFactory>(
				OperationMetadata("mov_e_d", false, 1), &opfun::mov_e_d
				)));
	table.insert(
		std::make_pair(
			OperationKey(0x5B), std::make_shared<NoOperandOperationFactory>(
				OperationMetadata("mov_e_e", false, 1), &opfun::mov_e_e
				)));
	table.insert(
		std::make_pair(
			OperationKey(0x5C), std::make_shared<NoOperandOperationFactory>(
				OperationMetadata("mov_e_h", false, 1), &opfun::mov_e_h
				)));
	table.insert(
		std::make_pair(
			OperationKey(0x5D), std::make_shared<NoOperandOperationFactory>(
				OperationMetadata("mov_e_l", false, 1), &opfun::mov_e_l
				)));
	table.insert(
		std::make_pair(
			OperationKey(0x67), std::make_shared<NoOperandOperationFactory>(
				OperationMetadata("mov_h_a", false, 1), &opfun::mov_h_a
				)));
	table.insert(
		std::make_pair(
			OperationKey(0x60), std::make_shared<NoOperandOperationFactory>(
				OperationMetadata("mov_h_b", false, 1), &opfun::mov_h_b
				)));
	table.insert(
		std::make_pair(
			OperationKey(0x61), std::make_shared<NoOperandOperationFactory>(
				OperationMetadata("mov_h_c", false, 1), &opfun::mov_h_c
				)));
	table.insert(
		std::make_pair(
			OperationKey(0x62), std::make_shared<NoOperandOperationFactory>(
				OperationMetadata("mov_h_d", false, 1), &opfun::mov_h_d
				)));
	table.insert(
		std::make_pair(
			OperationKey(0x63), std::make_shared<NoOperandOperationFactory>(
				OperationMetadata("mov_h_e", false, 1), &opfun::mov_h_e
				)));
	table.insert(
		std::make_pair(
			OperationKey(0x64), std::make_shared<NoOperandOperationFactory>(
				OperationMetadata("mov_h_h", false, 1), &opfun::mov_h_h
				)));
	table.insert(
		std::make_pair(
			OperationKey(0x65), std::make_shared<NoOperandOperationFactory>(
				OperationMetadata("mov_h_l", false, 1), &opfun::mov_h_l
				)));
	table.insert(
		std::make_pair(
			OperationKey(0x6F), std::make_shared<NoOperandOperationFactory>(
				OperationMetadata("mov_l_a", false, 1), &opfun::mov_l_a
				)));
	table.insert(
		std::make_pair(
			OperationKey(0x68), std::make_shared<NoOperandOperationFactory>(
				OperationMetadata("mov_l_b", false, 1), &opfun::mov_l_b
				)));
	table.insert(
		std::make_pair(
			OperationKey(0x69), std::make_shared<NoOperandOperationFactory>(
				OperationMetadata("mov_l_c", false, 1), &opfun::mov_l_c
				)));
	table.insert(
		std::make_pair(
			OperationKey(0x6A), std::make_shared<NoOperandOperationFactory>(
				OperationMetadata("mov_l_d", false, 1), &opfun::mov_l_d
				)));
	table.insert(
		std::make_pair(
			OperationKey(0x6B), std::make_shared<NoOperandOperationFactory>(
				OperationMetadata("mov_l_e", false, 1), &opfun::mov_l_e
				)));
	table.insert(
		std::make_pair(
			OperationKey(0x6C), std::make_shared<NoOperandOperationFactory>(
				OperationMetadata("mov_l_h", false, 1), &opfun::mov_l_h
				)));
	table.insert(
		std::make_pair(
			OperationKey(0x6D), std::make_shared<NoOperandOperationFactory>(
				OperationMetadata("mov_l_l", false, 1), &opfun::mov_l_l
				)));

	//MOV M,R  ----------------------------------------------------------------------------------------------------
	table.insert(
		std::make_pair(
			OperationKey(0x77), std::make_shared<NoOperandOperationFactory>(
				OperationMetadata("mov_m_a", true, 1), &opfun::mov_m_a
				)));
	table.insert(
		std::make_pair(
			OperationKey(0x70), std::make_shared<NoOperandOperationFactory>(
				OperationMetadata("mov_m_b", true, 1), &opfun::mov_m_b
				)));
	table.insert(
		std::make_pair(
			OperationKey(0x71), std::make_shared<NoOperandOperationFactory>(
				OperationMetadata("mov_m_c", true, 1), &opfun::mov_m_c
				)));
	table.insert(
		std::make_pair(
			OperationKey(0x72), std::make_shared<NoOperandOperationFactory>(
				OperationMetadata("mov_m_d", true, 1), &opfun::mov_m_d
				)));
	table.insert(
		std::make_pair(
			OperationKey(0x73), std::make_shared<NoOperandOperationFactory>(
				OperationMetadata("mov_m_e", true, 1), &opfun::mov_m_e
				)));
	table.insert(
		std::make_pair(
			OperationKey(0x74), std::make_shared<NoOperandOperationFactory>(
				OperationMetadata("mov_m_h", true, 1), &opfun::mov_m_h
				)));
	table.insert(
		std::make_pair(
			OperationKey(0x75), std::make_shared<NoOperandOperationFactory>(
				OperationMetadata("mov_m_l", true, 1), &opfun::mov_m_l
				)));

	// MOV R,M -------------------------------------------------------------------------------------------------
	table.insert(
		std::make_pair(
			OperationKey(0x7E), std::make_shared<NoOperandOperationFactory>(
				OperationMetadata("mov_a_m", false, 1), &opfun::mov_a_m
				)));
	table.insert(
		std::make_pair(
			OperationKey(0x46), std::make_shared<NoOperandOperationFactory>(
				OperationMetadata("mov_b_m", false, 1), &opfun::mov_b_m
				)));
	table.insert(
		std::make_pair(
			OperationKey(0x4E), std::make_shared<NoOperandOperationFactory>(
				OperationMetadata("mov_c_m", false, 1), &opfun::mov_c_m
				)));
	table.insert(
		std::make_pair(
			OperationKey(0x56), std::make_shared<NoOperandOperationFactory>(
				OperationMetadata("mov_d_m", false, 1), &opfun::mov_d_m
				)));
	table.insert(
		std::make_pair(
			OperationKey(0x5E), std::make_shared<NoOperandOperationFactory>(
				OperationMetadata("mov_e_m", false, 1), &opfun::mov_e_m
				)));
	table.insert(
		std::make_pair(
			OperationKey(0x66), std::make_shared<NoOperandOperationFactory>(
				OperationMetadata("mov_h_m", false, 1), &opfun::mov_h_m
				)));
	table.insert(
		std::make_pair(
			OperationKey(0x6E), std::make_shared<NoOperandOperationFactory>(
				OperationMetadata("mov_l_m", false, 1), &opfun::mov_l_m
				)));

	// MVI R/M ----------------------------------------------------------------------------------------------------
	table.insert(
		std::make_pair(
			OperationKey(0x3E), std::make_shared<ByteOperandOperationFactory>(
				OperationMetadata("mvi_a", false, 2), &opfun::mvi_a
				)));
	table.insert(
		std::make_pair(
			OperationKey(0x06), std::make_shared<ByteOperandOperationFactory>(
				OperationMetadata("mvi_b", false, 2), &opfun::mvi_b
				)));
	table.insert(
		std::make_pair(
			OperationKey(0x0E), std::make_shared<ByteOperandOperationFactory>(
				OperationMetadata("mvi_c", false, 2), &opfun::mvi_c
				)));
	table.insert(
		std::make_pair(
			OperationKey(0x16), std::make_shared<ByteOperandOperationFactory>(
				OperationMetadata("mvi_d", false, 2), &opfun::mvi_d
				)));
	table.insert(
		std::make_pair(
			OperationKey(0x1E), std::make_shared<ByteOperandOperationFactory>(
				OperationMetadata("mvi_e", false, 2), &opfun::mvi_e
				)));
	table.insert(
		std::make_pair(
			OperationKey(0x26), std::make_shared<ByteOperandOperationFactory>(
				OperationMetadata("mvi_h", false, 2), &opfun::mvi_h
				)));
	table.insert(
		std::make_pair(
			OperationKey(0x2E), std::make_shared<ByteOperandOperationFactory>(
				OperationMetadata("mvi_l", false, 2), &opfun::mvi_l
				)));
	table.insert(
		std::make_pair(
			OperationKey(0x36), std::make_shared<ByteOperandOperationFactory>(
				OperationMetadata("mvi_m", true, 2), &opfun::mvi_m
				)));
	// LOAD -----------------------------------------------------------------------------------------
	table.insert(
		std::make_pair(
			OperationKey(0x3A), std::make_shared<WordOperandOperationFactory>(
				OperationMetadata("lda", false, 3), &opfun::lda
				)));
	table.insert(
		std::make_pair(
			OperationKey(0x0A), std::make_shared<NoOperandOperationFactory>(
				OperationMetadata("ldax_bc", false, 1), &opfun::ldax_bc
				)));
	table.insert(
		std::make_pair(
			OperationKey(0x1A), std::make_shared<NoOperandOperationFactory>(
				OperationMetadata("ldax_de", false, 1), &opfun::ldax_de
				)));
	table.insert(
		std::make_pair(
			OperationKey(0x2A), std::make_shared<WordOperandOperationFactory>(
				OperationMetadata("lhld", false, 3), &opfun::lhld
				)));
	table.insert(
		std::make_pair(
			OperationKey(0x01), std::make_shared<WordOperandOperationFactory>(
				OperationMetadata("lxi_bc", false, 3), &opfun::lxi_bc
				)));
	table.insert(
		std::make_pair(
			OperationKey(0x11), std::make_shared<WordOperandOperationFactory>(
				OperationMetadata("lxi_de", false, 3), &opfun::lxi_de
				)));
	table.insert(
		std::make_pair(
			OperationKey(0x21), std::make_shared<WordOperandOperationFactory>(
				OperationMetadata("lxi_hl", false, 3), &opfun::lxi_hl
				)));
	table.insert(
		std::make_pair(
			OperationKey(0x31), std::make_shared<WordOperandOperationFactory>(
				OperationMetadata("lxi_sp", false, 3), &opfun::lxi_sp
				)));

	// EXCHANGE ---------------------------------------------------------------------------------
	
	table.insert(
		std::make_pair(
			OperationKey(0xEB), std::make_shared<NoOperandOperationFactory>(
				OperationMetadata("xchg", false, 1), &opfun::xchg
				)));

	// STORE ----------------------------------------------------------------------------------
	table.insert(
		std::make_pair(
			OperationKey(0x02), std::make_shared<NoOperandOperationFactory>(
				OperationMetadata("stax_bc", true, 1), &opfun::stax_bc
				)));
	table.insert(
		std::make_pair(
			OperationKey(0x12), std::make_shared<NoOperandOperationFactory>(
				OperationMetadata("stax_de", true, 1), &opfun::stax_de
				)));
	table.insert(
		std::make_pair(
			OperationKey(0x32), std::make_shared<WordOperandOperationFactory>(
				OperationMetadata("sta", true, 3), &opfun::sta
				)));
	table.insert(
		std::make_pair(
			OperationKey(0x22), std::make_shared<WordOperandOperationFactory>(
				OperationMetadata("shld", true, 3), &opfun::shld
				)));
}

void AddArithmeticOperations(DecoderTableBuilder::DecoderTable& table)
{
	table.insert(std::make_pair(
		OperationKey(0x87), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("add_a", false, 1), &opfun::add_a
			)));

	table.insert(std::make_pair(
		OperationKey(0x80), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("add_b", false, 1), &opfun::add_b
			)));

	table.insert(std::make_pair(
		OperationKey(0x81), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("add_c", false, 1), &opfun::add_c
			)));

	table.insert(std::make_pair(
		OperationKey(0x82), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("add_d", false, 1), &opfun::add_d
			)));

	table.insert(std::make_pair(
		OperationKey(0x83), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("add_e", false, 1), &opfun::add_e
			)));

	table.insert(std::make_pair(
		OperationKey(0x84), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("add_h", false, 1), &opfun::add_h
			)));

	table.insert(std::make_pair(
		OperationKey(0x85), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("add_l", false, 1), &opfun::add_l
			)));

	table.insert(std::make_pair(
		OperationKey(0x86), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("add_m", false, 1), &opfun::add_m
			)));

	table.insert(std::make_pair(
		OperationKey(0xC6), std::make_shared<ByteOperandOperationFactory>(
			OperationMetadata("adi", false, 2), &opfun::adi
			)));

	table.insert(std::make_pair(
		OperationKey(0x8F), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("adc_a", false, 1), &opfun::adc_a
			)));

	table.insert(std::make_pair(
		OperationKey(0x88), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("adc_b", false, 1), &opfun::adc_b
			)));

	table.insert(std::make_pair(
		OperationKey(0x89), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("adc_c", false, 1), &opfun::adc_c
			)));

	table.insert(std::make_pair(
		OperationKey(0x8A), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("adc_d", false, 1), &opfun::adc_d
			)));

	table.insert(std::make_pair(
		OperationKey(0x8B), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("adc_e", false, 1), &opfun::adc_e
			)));

	table.insert(std::make_pair(
		OperationKey(0x8C), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("adc_h", false, 1), &opfun::adc_h
			)));

	table.insert(std::make_pair(
		OperationKey(0x8D), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("adc_l", false, 1), &opfun::adc_l
			)));

	table.insert(std::make_pair(
		OperationKey(0x8E), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("adc_m", false, 1), &opfun::adc_m
			)));

	table.insert(std::make_pair(
		OperationKey(0xCE), std::make_shared<ByteOperandOperationFactory>(
			OperationMetadata("aci", false, 2), &opfun::aci
			)));

	table.insert(std::make_pair(
		OperationKey(0x97), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("sub_a", false, 1), &opfun::sub_a
			)));

	table.insert(std::make_pair(
		OperationKey(0x90), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("sub_b", false, 1), &opfun::sub_b
			)));

	table.insert(std::make_pair(
		OperationKey(0x91), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("sub_c", false, 1), &opfun::sub_c
			)));

	table.insert(std::make_pair(
		OperationKey(0x92), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("sub_d", false, 1), &opfun::sub_d
			)));

	table.insert(std::make_pair(
		OperationKey(0x93), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("sub_e", false, 1), &opfun::sub_e
			)));

	table.insert(std::make_pair(
		OperationKey(0x94), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("sub_h", false, 1), &opfun::sub_h
			)));

	table.insert(std::make_pair(
		OperationKey(0x95), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("sub_l", false, 1), &opfun::sub_l
			)));

	table.insert(std::make_pair(
		OperationKey(0x96), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("sub_m", false, 1), &opfun::sub_m
			)));

	table.insert(std::make_pair(
		OperationKey(0xD6), std::make_shared<ByteOperandOperationFactory>(
			OperationMetadata("sui", false, 2), &opfun::sui
			)));

	table.insert(std::make_pair(
		OperationKey(0x9F), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("sbb_a", false, 1), &opfun::sbb_a
			)));

	table.insert(std::make_pair(
		OperationKey(0x98), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("sbb_b", false, 1), &opfun::sbb_b
			)));

	table.insert(std::make_pair(
		OperationKey(0x99), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("sbb_c", false, 1), &opfun::sbb_c
			)));

	table.insert(std::make_pair(
		OperationKey(0x9A), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("sbb_d", false, 1), &opfun::sbb_d
			)));

	table.insert(std::make_pair(
		OperationKey(0x9B), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("sbb_e", false, 1), &opfun::sbb_e
			)));

	table.insert(std::make_pair(
		OperationKey(0x9C), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("sbb_h", false, 1), &opfun::sbb_h
			)));

	table.insert(std::make_pair(
		OperationKey(0x9D), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("sbb_l", false, 1), &opfun::sbb_l
			)));

	table.insert(std::make_pair(
		OperationKey(0x9E), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("sbb_m", false, 1), &opfun::sbb_m
			)));

	table.insert(std::make_pair(
		OperationKey(0xDE), std::make_shared<ByteOperandOperationFactory>(
			OperationMetadata("sbi", false, 2), &opfun::sbi
			)));

	table.insert(std::make_pair(
		OperationKey(0x3C), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("inr_a", false, 1), &opfun::inr_a
			)));

	table.insert(std::make_pair(
		OperationKey(0x04), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("inr_b", false, 1), &opfun::inr_b
			)));

	table.insert(std::make_pair(
		OperationKey(0x0C), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("inr_c", false, 1), &opfun::inr_c			
			)));

	table.insert(std::make_pair(
		OperationKey(0x14), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("inr_d", false, 1), &opfun::inr_d
			)));

	table.insert(std::make_pair(
		OperationKey(0x1C), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("inr_e", false, 1), &opfun::inr_e
			)));

	table.insert(std::make_pair(
		OperationKey(0x24), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("inr_h", false, 1), &opfun::inr_h
			)));

	table.insert(std::make_pair(
		OperationKey(0x2C), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("inr_l", false, 1), &opfun::inr_l
			)));

	table.insert(std::make_pair(
		OperationKey(0x34), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("inr_m", false, 1), &opfun::inr_m
			)));

	table.insert(std::make_pair(
		OperationKey(0x3D), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("dcr_a", false, 1), &opfun::dcr_a
			)));

	table.insert(std::make_pair(
		OperationKey(0x05), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("dcr_b", false, 1), &opfun::dcr_b
			)));

	table.insert(std::make_pair(
		OperationKey(0x0D), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("dcr_c", false, 1), &opfun::dcr_c
			)));

	table.insert(std::make_pair(
		OperationKey(0x15), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("dcr_d", false, 1), &opfun::dcr_d
			)));

	table.insert(std::make_pair(
		OperationKey(0x1D), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("dcr_e", false, 1), &opfun::dcr_e
			)));

	table.insert(std::make_pair(
		OperationKey(0x25), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("dcr_h", false, 1), &opfun::dcr_h
			)));

	table.insert(std::make_pair(
		OperationKey(0x2D), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("dcr_l", false, 1), &opfun::dcr_l
			)));

	table.insert(std::make_pair(
		OperationKey(0x35), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("dcr_m", false, 1), &opfun::dcr_m
			)));

	table.insert(std::make_pair(
		OperationKey(0x03), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("inx_bc", false, 1), &opfun::inx_bc
			)));

	table.insert(std::make_pair(
		OperationKey(0x13), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("inx_de", false, 1), &opfun::inx_de
			)));

	table.insert(std::make_pair(
		OperationKey(0x23), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("inx_hl", false, 1), &opfun::inx_hl
			)));

	table.insert(std::make_pair(
		OperationKey(0x33), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("inx_sp", false, 1), &opfun::inx_sp
			)));

	table.insert(std::make_pair(
		OperationKey(0x0B), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("dcx_bc", false, 1), &opfun::dcx_bc
			)));

	table.insert(std::make_pair(
		OperationKey(0x1B), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("dcx_de", false, 1), &opfun::dcx_de
			)));

	table.insert(std::make_pair(
		OperationKey(0x2B), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("dcx_hl", false, 1), &opfun::dcx_hl
			)));

	table.insert(std::make_pair(
		OperationKey(0x3B), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("dcx_sp", false, 1), &opfun::dcx_sp
			)));

	table.insert(std::make_pair(
		OperationKey(0x09), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("dad_bc", false, 1), &opfun::dad_bc
			)));

	table.insert(std::make_pair(
		OperationKey(0x19), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("dad_de", false, 1), &opfun::dad_de
			)));

	table.insert(std::make_pair(
		OperationKey(0x29), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("dad_hl", false, 1), &opfun::dad_hl
			)));

	table.insert(std::make_pair(
		OperationKey(0x39), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("dad_sp", false, 1), &opfun::dad_sp
			)));

	table.insert(std::make_pair(
		OperationKey(0x27), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("daa", false, 1), &opfun::daa
			)));

}

void AddLogicalOperations(DecoderTableBuilder::DecoderTable& table)
{
	table.insert(std::make_pair(
		OperationKey(0xa7), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("ana_a", false, 1), &opfun::ana_a)));
	table.insert(std::make_pair(
		OperationKey(0xa0), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("ana_b", false, 1), &opfun::ana_b)));
	table.insert(std::make_pair(
		OperationKey(0xa1), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("ana_c", false, 1), &opfun::ana_c)));
	table.insert(std::make_pair(
		OperationKey(0xa2), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("ana_d", false, 1), &opfun::ana_d)));
	table.insert(std::make_pair(
		OperationKey(0xa3), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("ana_e", false, 1), &opfun::ana_e)));
	table.insert(std::make_pair(
		OperationKey(0xa4), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("ana_h", false, 1), &opfun::ana_h)));
	table.insert(std::make_pair(
		OperationKey(0xa5), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("ana_l", false, 1), &opfun::ana_l)));
	table.insert(std::make_pair(
		OperationKey(0xa6), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("ana_m", false, 1), &opfun::ana_m)));
	table.insert(std::make_pair(
		OperationKey(0xe6), std::make_shared<ByteOperandOperationFactory>(
			OperationMetadata("ani", false, 2), &opfun::ani)));

	table.insert(std::make_pair(
		OperationKey(0xb7), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("ora_a", false, 1), &opfun::ora_a)));
	table.insert(std::make_pair(
		OperationKey(0xb0), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("ora_b", false, 1), &opfun::ora_b)));
	table.insert(std::make_pair(
		OperationKey(0xb1), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("ora_c", false, 1), &opfun::ora_c)));
	table.insert(std::make_pair(
		OperationKey(0xb2), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("ora_d", false, 1), &opfun::ora_d)));
	table.insert(std::make_pair(
		OperationKey(0xb3), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("ora_e", false, 1), &opfun::ora_e)));
	table.insert(std::make_pair(
		OperationKey(0xb4), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("ora_h", false, 1), &opfun::ora_h)));
	table.insert(std::make_pair(
		OperationKey(0xb5), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("ora_l", false, 1), &opfun::ora_l)));
	table.insert(std::make_pair(
		OperationKey(0xb6), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("ora_m", false, 1), &opfun::ora_m)));
	table.insert(std::make_pair(
		OperationKey(0xf6), std::make_shared<ByteOperandOperationFactory>(
			OperationMetadata("ori", false, 2), &opfun::ori)));

	table.insert(std::make_pair(
		OperationKey(0xaf), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("xra_a", false, 1), &opfun::xra_a)));
	table.insert(std::make_pair(
		OperationKey(0xa8), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("xra_a", false, 1), &opfun::xra_b)));
	table.insert(std::make_pair(
		OperationKey(0xa9), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("xra_a", false, 1), &opfun::xra_c)));
	table.insert(std::make_pair(
		OperationKey(0xaa), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("xra_a", false, 1), &opfun::xra_d)));
	table.insert(std::make_pair(
		OperationKey(0xab), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("xra_a", false, 1), &opfun::xra_e)));
	table.insert(std::make_pair(
		OperationKey(0xac), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("xra_a", false, 1), &opfun::xra_h)));
	table.insert(std::make_pair(
		OperationKey(0xad), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("xra_a", false, 1), &opfun::xra_l)));
	table.insert(std::make_pair(
		OperationKey(0xae), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("xra_a", false, 1), &opfun::xra_m)));
	table.insert(std::make_pair(
		OperationKey(0xee), std::make_shared<ByteOperandOperationFactory>(
			OperationMetadata("xri", false, 2), &opfun::xri)));
}

void AddRotateOperations(DecoderTableBuilder::DecoderTable& table)
{
	table.insert(std::make_pair(
		OperationKey(0x17), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("ral", false, 1), &opfun::ral)));
	table.insert(std::make_pair(
		OperationKey(0x1f), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("rar", false, 1), &opfun::rar)));
	table.insert(std::make_pair(
		OperationKey(0x07), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("rlc", false, 1), &opfun::rlc)));
	table.insert(std::make_pair(
		OperationKey(0x0f), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("rrc", false, 1), &opfun::rrc)));
}

void AddComplementAndCarryOperations(DecoderTableBuilder::DecoderTable& table)
{
	table.insert(std::make_pair(
		OperationKey(0x2f), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("cma", false, 1), &opfun::cma)));
	table.insert(std::make_pair(
		OperationKey(0x3f), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("cmc", false, 1), &opfun::cmc)));
	table.insert(std::make_pair(
		OperationKey(0x37), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("stc", false, 1), &opfun::stc)));
}

void AddStackOperations(DecoderTableBuilder::DecoderTable& table)
{
	table.insert(std::make_pair(
		OperationKey(0xc5), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("push_b", false, 1), &opfun::push_b)));
	table.insert(std::make_pair(
		OperationKey(0xd5), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("push_d", false, 1), &opfun::push_d)));
	table.insert(std::make_pair(
		OperationKey(0xe5), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("push_h", false, 1), &opfun::push_h)));
	table.insert(std::make_pair(
		OperationKey(0xf5), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("push_psw", false, 1), &opfun::push_psw)));
	
	table.insert(std::make_pair(
		OperationKey(0xc1), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("pop_b", false, 1), &opfun::pop_b)));
	table.insert(std::make_pair(
		OperationKey(0xd1), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("pop_d", false, 1), &opfun::pop_d)));
	table.insert(std::make_pair(
		OperationKey(0xe1), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("pop_h", false, 1), &opfun::pop_h)));
	table.insert(std::make_pair(
		OperationKey(0xf1), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("pop_psw", false, 1), &opfun::pop_psw)));

	table.insert(std::make_pair(
		OperationKey(0xe3), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("xthl", false, 1), &opfun::xthl)));

	table.insert(std::make_pair(
		OperationKey(0xf9), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("sphl", false, 1), &opfun::sphl)));
}

void AddBranchOperations(DecoderTableBuilder::DecoderTable& table)
{
	table.insert(std::make_pair(
		OperationKey(0xc3), std::make_shared<UnconditionalJumpOperationFactory>(
			OperationMetadata("jmp", false, 3), &opfun::jmp)));
	table.insert(std::make_pair(
		OperationKey(0xda), std::make_shared<ConditionalJumpOperationFactory>(
			OperationMetadata("jc", false, 3), &opfun::jc)));
	table.insert(std::make_pair(
		OperationKey(0xd2), std::make_shared<ConditionalJumpOperationFactory>(
			OperationMetadata("jnc", false, 3), &opfun::jnc)));
	table.insert(std::make_pair(
		OperationKey(0xfa), std::make_shared<ConditionalJumpOperationFactory>(
			OperationMetadata("jm", false, 3), &opfun::jm)));
	table.insert(std::make_pair(
		OperationKey(0xf2), std::make_shared<ConditionalJumpOperationFactory>(
			OperationMetadata("jp", false, 3), &opfun::jp)));
	table.insert(std::make_pair(
		OperationKey(0xca), std::make_shared<ConditionalJumpOperationFactory>(
			OperationMetadata("jz", false, 3), &opfun::jz)));
	table.insert(std::make_pair(
		OperationKey(0xc2), std::make_shared<ConditionalJumpOperationFactory>(
			OperationMetadata("jnz", false, 3), &opfun::jnz)));
	table.insert(std::make_pair(
		OperationKey(0xea), std::make_shared<ConditionalJumpOperationFactory>(
			OperationMetadata("jpe", false, 3), &opfun::jpe)));
	table.insert(std::make_pair(
		OperationKey(0xe2), std::make_shared<ConditionalJumpOperationFactory>(
			OperationMetadata("jpo", false, 3), &opfun::jpo)));

	table.insert(std::make_pair(
		OperationKey(0xcd), std::make_shared<UnconditionalCallOperationFactory>(
			OperationMetadata("call", false, 3), &opfun::call)));
	table.insert(std::make_pair(
		OperationKey(0xdc), std::make_shared<ConditionalCallOperationFactory>(
			OperationMetadata("cc", false, 3), &opfun::cc)));
	table.insert(std::make_pair(
		OperationKey(0xd4), std::make_shared<ConditionalCallOperationFactory>(
			OperationMetadata("cnc", false, 3), &opfun::cnc)));
	table.insert(std::make_pair(
		OperationKey(0xfc), std::make_shared<ConditionalCallOperationFactory>(
			OperationMetadata("cm", false, 3), &opfun::cm)));
	table.insert(std::make_pair(
		OperationKey(0xf4), std::make_shared<ConditionalCallOperationFactory>(
			OperationMetadata("cp", false, 3), &opfun::cp)));
	table.insert(std::make_pair(
		OperationKey(0xcc), std::make_shared<ConditionalCallOperationFactory>(
			OperationMetadata("cz", false, 3), &opfun::cz)));
	table.insert(std::make_pair(
		OperationKey(0xc4), std::make_shared<ConditionalCallOperationFactory>(
			OperationMetadata("cnz", false, 3), &opfun::cnz)));
	table.insert(std::make_pair(
		OperationKey(0xec), std::make_shared<ConditionalCallOperationFactory>(
			OperationMetadata("cpe", false, 3), &opfun::cpe)));
	table.insert(std::make_pair(
		OperationKey(0xe4), std::make_shared<ConditionalCallOperationFactory>(
			OperationMetadata("cpo", false, 3), &opfun::cpo)));

	table.insert(std::make_pair(
		OperationKey(0xc9), std::make_shared<UnconditionalReturnOperationFactory>(
			OperationMetadata("ret", false, 3), &opfun::ret)));
	table.insert(std::make_pair(
		OperationKey(0xd8), std::make_shared<ConditionalReturnOperationFactory>(
			OperationMetadata("rc", false, 3), &opfun::rc)));
	table.insert(std::make_pair(
		OperationKey(0xd0), std::make_shared<ConditionalReturnOperationFactory>(
			OperationMetadata("rnc", false, 3), &opfun::rnc)));
	table.insert(std::make_pair(
		OperationKey(0xf8), std::make_shared<ConditionalReturnOperationFactory>(
			OperationMetadata("rm", false, 3), &opfun::rm)));
	table.insert(std::make_pair(
		OperationKey(0xf0), std::make_shared<ConditionalReturnOperationFactory>(
			OperationMetadata("rp", false, 3), &opfun::rp)));
	table.insert(std::make_pair(
		OperationKey(0xc8), std::make_shared<ConditionalReturnOperationFactory>(
			OperationMetadata("rz", false, 3), &opfun::rz)));
	table.insert(std::make_pair(
		OperationKey(0xc0), std::make_shared<ConditionalReturnOperationFactory>(
			OperationMetadata("rnz", false, 3), &opfun::rnz)));
	table.insert(std::make_pair(
		OperationKey(0xe8), std::make_shared<ConditionalReturnOperationFactory>(
			OperationMetadata("rpe", false, 3), &opfun::rpe)));
	table.insert(std::make_pair(
		OperationKey(0xe0), std::make_shared<ConditionalReturnOperationFactory>(
			OperationMetadata("rpo", false, 3), &opfun::rpo)));

}

void AddIoOperations(DecoderTableBuilder::DecoderTable& table, const IoBridge& ioBridge)
{
	table.insert(std::make_pair(
		OperationKey(0xd3), std::make_shared<OutOperationFactory>(
			OperationMetadata("out_byte", false, 1), ioBridge
			)));
	table.insert(std::make_pair(
		OperationKey(0xdb), std::make_shared<InOperationFactory>(
			OperationMetadata("in_byte", false, 1), ioBridge
			)));
}

void AddProgramCounterOperations(DecoderTableBuilder::DecoderTable& table)
{
	table.insert(std::make_pair(
		OperationKey(0xe9), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("pchl", false, 1), &opfun::pchl)));
	
	table.insert(std::make_pair(
		OperationKey(0xc7), std::make_shared<RestartOperationFactory>(
			OperationMetadata("rst_0", false, 1), &opfun::rst_0, 0x0000)));
	table.insert(std::make_pair(
		OperationKey(0xcf), std::make_shared<RestartOperationFactory>(
			OperationMetadata("rst_1", false, 1), &opfun::rst_1, 0x0008)));
	table.insert(std::make_pair(
		OperationKey(0xd7), std::make_shared<RestartOperationFactory>(
			OperationMetadata("rst_2", false, 1), &opfun::rst_2, 0x0010)));
	table.insert(std::make_pair(
		OperationKey(0xdf), std::make_shared<RestartOperationFactory>(
			OperationMetadata("rst_3", false, 1), &opfun::rst_3, 0x0018)));
	table.insert(std::make_pair(
		OperationKey(0xe7), std::make_shared<RestartOperationFactory>(
			OperationMetadata("rst_4", false, 1), &opfun::rst_4, 0x0020)));
	table.insert(std::make_pair(
		OperationKey(0xef), std::make_shared<RestartOperationFactory>(
			OperationMetadata("rst_5", false, 1), &opfun::rst_5, 0x0028)));
	table.insert(std::make_pair(
		OperationKey(0xf7), std::make_shared<RestartOperationFactory>(
			OperationMetadata("rst_6", false, 1), &opfun::rst_6, 0x0030)));
	table.insert(std::make_pair(
		OperationKey(0xff), std::make_shared<RestartOperationFactory>(
			OperationMetadata("rst_7", false, 1), &opfun::rst_7, 0x0038)));
}

void AddMachineControlOperations(DecoderTableBuilder::DecoderTable& table)
{
	table.insert(std::make_pair(
		OperationKey(0x76), std::make_shared<HaltOperationFactory>(
			OperationMetadata("hlt", true, 1), &opfun::hlt)));
	table.insert(std::make_pair(
		OperationKey(0x00), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("nop", false, 1), &opfun::nop)));
	table.insert(std::make_pair(
		OperationKey(0xfb), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("ei", false, 1), &opfun::ei)));
	table.insert(std::make_pair(
		OperationKey(0xf3), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("di", false, 1), &opfun::di)));
}

void AddCompareOperations(DecoderTableBuilder::DecoderTable& table)
{
	table.insert(std::make_pair(
		OperationKey(0xbf), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("cmp_a", false, 1), &opfun::cmp_a
			)));

	table.insert(std::make_pair(
		OperationKey(0xb8), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("cmp_b", false, 1), &opfun::cmp_b
			)));

	table.insert(std::make_pair(
		OperationKey(0xb9), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("cmp_c", false, 1), &opfun::cmp_c
			)));

	table.insert(std::make_pair(
		OperationKey(0xba), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("cmp_d", false, 1), &opfun::cmp_d
			)));

	table.insert(std::make_pair(
		OperationKey(0xbb), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("cmp_e", false, 1), &opfun::cmp_e
			)));

	table.insert(std::make_pair(
		OperationKey(0xbc), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("cmp_h", false, 1), &opfun::cmp_h
			)));

	table.insert(std::make_pair(
		OperationKey(0xbd), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("cmp_l", false, 1), &opfun::cmp_l
			)));

	table.insert(std::make_pair(
		OperationKey(0xbe), std::make_shared<NoOperandOperationFactory>(
			OperationMetadata("cmp_m", false, 1), &opfun::cmp_m
			)));

	table.insert(std::make_pair(
		OperationKey(0xfe), std::make_shared<ByteOperandOperationFactory>(
			OperationMetadata("cpi", false, 2), &opfun::cpi
			)));
}

void DecoderTableBuilder::Build(DecoderTable& table, const IoBridge& ioBridge) 
{
	AddDataTransferOperations(table);
	AddLogicalOperations(table);
	AddIoOperations(table, ioBridge);
	AddLogicalOperations(table);
	AddRotateOperations(table);
	AddComplementAndCarryOperations(table);
	AddStackOperations(table);
	AddArithmeticOperations(table);
	AddBranchOperations(table);
	AddProgramCounterOperations(table);
	AddMachineControlOperations(table);
	AddCompareOperations(table);
}

