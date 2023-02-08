#include "symtable.h"

namespace DSMud{

SymTableImpt SymTable::singleton;

SymTableImpt &SymTable::instance(void)
{
	return singleton;
}

} // namespace DSMud
