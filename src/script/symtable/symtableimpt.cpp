#include "symtable.h"

namespace DSMud{

SymTableImpt::Table SymTableImpt::table;

SymTableImpt::TableEntry SymTableImpt::lookup(const char *key)
{
	return table.find(key);
}

SymTableImpt::TableEntry SymTableImpt::insert(const char *key, const SymTableImpt::TableInfo &info)
{
	table.try_emplace(key, info);
	return lookup(key);
}

SymTableImpt::TableEntry SymTableImpt::insert(const char *key, SymTableImpt::TableInfo &&info)
{
	table.try_emplace(key, std::move(info));
	return lookup(key);
}

SymTableImpt::TableEntry SymTableImpt::empty(void)
{
	return table.end();
}

} // namespace DSMud
