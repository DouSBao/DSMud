#ifndef MUD_SYMTABLE_H
#define MUD_SYMTABLE_H

#include <unordered_map>
#include <tuple>

#define symtable SymTable::instance()

/*
 * Intro: symbol table of mud script.
 * Date: 2023-2-8
 * Developer: DouSBao
 */

namespace DSMud{

// ====================================================================
// Class Section

/*
 * --------------------------------------------------------------
 * Implement of SymTable.
 * Client only access through SymTable.
 * --------------------------------------------------------------
 */

class SymTableImpt{
	using TableInfo = std::tuple<int>;
	using Table = std::unordered_map<const char *, TableInfo>;
	using TableEntry = Table::iterator;

	friend class SymTable;

public:
	/*
	 * Find entry with key.
	 * Return found entry. When found nothing, result is equal with empty().
	 */
	static TableEntry lookup(const char *key);

	/*
	 * Insert new entry if none exist entry with key found.
	 * Return entry with key.
	 */
	static TableEntry insert(const char *key, const TableInfo &info);
	static TableEntry insert(const char *key, TableInfo &&info);

	/*
	 * Return a empty entry used to compare with lookup().
	 */
	static TableEntry empty(void);

private:
	SymTableImpt(void) = default;
	~SymTableImpt(void) = default;			// rule of five

	SymTableImpt(const SymTableImpt &) = delete;
	SymTableImpt &operator=(const SymTableImpt &) = delete;
	SymTableImpt(SymTableImpt &&) = delete;
	SymTableImpt &operator=(const SymTableImpt &&) = delete;

	static Table table;
};

/*
 * --------------------------------------------------------------
 * Singleton wrapper class of SymTableImpt.
 * --------------------------------------------------------------
 */

class SymTable{
public:
	using TableEntry = SymTableImpt::TableEntry;

	/*
	 * Return the singleton instace of SymTableImpt.
	 */
	static SymTableImpt &instance(void);

private:
	static SymTableImpt singleton;
};

// ====================================================================
// Template Section

/*
 * Extract field from symbol table entry.
 */
template<int I>
inline auto field(const SymTable::TableEntry &entry)
{
	return std::get<I - 1>(entry->second);
}

template<>
inline auto field<0>(const SymTable::TableEntry &entry)
{
	return entry->first;
}

} // namespace DSMud

#endif // MUD_SYMTABLE_H
