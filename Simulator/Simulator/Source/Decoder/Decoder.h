#ifndef _DECODER_H_
#define _DECODER_H_

#include <unordered_map>
#include <memory>
#include <Global\Global.h>
#include "DecoderTableBuilder.h"
#include <Operation\Key\OperationKey.h>
#include <Operation\Key\OperationKeyHasher.h>
#include <OperationFactory\OperationFactory.h>
#include <State\State.h>
#include <IO\IoBridge.h>

class Decoder
{
public:
	typedef DecoderTableBuilder::DecoderTable DecoderTable;
	Decoder(State* s, const IoBridge& ioBridge);
	std::unique_ptr<Operation> Decode(Address address);
private:
	OperationKey GetOperationKey_(Address address);
	State* s_;
	const IoBridge& ioBridge_;
	DecoderTable decoderTable_;
};

#endif