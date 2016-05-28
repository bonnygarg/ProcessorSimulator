#ifndef _OPERATION_FACTORY_TABLE_BUILDER_H_
#define _OPERATION_FACTORY_TABLE_BUILDER_H_

#include <unordered_map>
#include <fstream>
#include <Global\Global.h>
#include <IO\IoBridge.h>
#include <Operation\Key\OperationKey.h>
#include <Operation\Key\OperationKeyHasher.h>
#include <OperationFactory\OperationFactory.h>

class DecoderTableBuilder
{
public:
	typedef std::unordered_map<OperationKey, std::shared_ptr<OperationFactory>, OperationKeyHasher> DecoderTable;
	static void Build(DecoderTable& table, const IoBridge& ioBridge);
};

#endif