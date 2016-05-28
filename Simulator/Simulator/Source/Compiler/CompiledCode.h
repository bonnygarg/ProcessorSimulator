#ifndef _COMPILED_CODE_H_
#define _COMPILED_CODE_H_

#include <unordered_map>
#include <memory>

#include "SideExit.h"
#include <CompilationUnit\CompilationUnit.h>
#include <Global\Global.h>

class CompiledCode
{
public:
	const std::vector<std::shared_ptr<CompilationUnit>>& GetCompilationUnitTable() const;
	std::vector<std::shared_ptr<CompilationUnit>>& GetCompilationUnitTable();
	void SetCompilationUnitTable(const std::vector<std::shared_ptr<CompilationUnit>>& compilationUnitTable);

	const std::vector<SideExit>& GetSideExitTable() const;
	std::vector<SideExit>& GetSideExitTable();
	void SetSideExitTable(const std::vector<SideExit>& sideExitTable);

	void Clear();
private:
	std::vector<std::shared_ptr<CompilationUnit>> compilationUnitTable_;
	std::vector<SideExit> sideExitTable_;
};

#endif