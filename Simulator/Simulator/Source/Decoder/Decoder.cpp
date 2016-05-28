#include "Decoder.h"

Decoder::Decoder(State* s, const IoBridge& ioBridge) :
	s_(s),
	ioBridge_(ioBridge),
	decoderTable_()
{
	DecoderTableBuilder::Build(decoderTable_, ioBridge_);
}

std::unique_ptr<Operation> Decoder::Decode(Address address)
{
	auto key = GetOperationKey_(address);
	auto factory = decoderTable_.find(key);
	if (factory != decoderTable_.end())
	{
		return factory->second->CreateOperation(s_, address);
	}
	else
	{
		return std::unique_ptr<Operation>();
	}
}

OperationKey Decoder::GetOperationKey_(Address address)
{
	return OperationKey(s_->m[address].byte);
}
