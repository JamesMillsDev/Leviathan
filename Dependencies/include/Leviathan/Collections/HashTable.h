#pragma once

#include <Leviathan/Core/Leviathan.h>

#include <string>
#include <vector>
#include <assert.h>

using std::string;
using std::vector;

// Based on ELF Hash method
DLL extern unsigned int DefaultHash(const char* _str);

template<typename T, unsigned int GROW_SIZE = 100, unsigned int(*HASH_FUNC)(const char*) = DefaultHash>
class HashTable
{
public:
	HashTable();
	~HashTable();

	// Remove the ability to copy one table to another
	HashTable(const HashTable&) = delete;
	HashTable& operator=(const HashTable&) = delete;

	// Remove all entries from the table
	void Clear();

	// Return boolean stating if the table is empty
	bool Empty() const;

	// Return number of entries within the table
	unsigned int Count() const;

	// Return the capacity of the table
	unsigned int Capacity() const;

	// Return the current load factor of the table
	float LoadFactor() const;

	// Add a value at the location of the key
	void Insert(const char* _key, const T& _value);

	// Remove first with the matching key
	void Remove(const char* _key);

	// Remove all entries with the matching key
	void RemoveAll(const char* _key);

	// Fill the vector with all the values matching the key
	size_t AllFor(const char* _key, vector<T>& _values) const;

public:
	// Return the value with the matching key (must exist)
	T& operator[](const char* _key);

	// Return the value with the matching key (must exist)
	const T& operator[](const char* _key) const;

private:
	// A Key-Value pair for a linked-list
	class Entry
	{
	public:
		string key;
		T value;
		Entry* next = nullptr;

	public:
		Entry(const char* _key, const T& _value);
	
	};

private:
	// can't be a template parameter unfortunately because of non-integer
	const float LOAD_THRESHOLD = .8f;

	Entry** m_entries;
	unsigned int m_count;
	unsigned int m_capacity;

private:
	void Expand();

};

template<typename T, unsigned int GROW_SIZE, unsigned int(*HASH_FUNC)(const char*)>
inline HashTable<T, GROW_SIZE, HASH_FUNC>::HashTable()
	: m_entries(new Entry*[GROW_SIZE]), m_count(0), m_capacity(GROW_SIZE)
{
	for (unsigned int i = 0; i < m_capacity; ++i)
		m_entries[i] = nullptr;
}

template<typename T, unsigned int GROW_SIZE, unsigned int(*HASH_FUNC)(const char*)>
inline HashTable<T, GROW_SIZE, HASH_FUNC>::~HashTable()
{
	Clear();

	if (m_entries != nullptr)
	{
		delete[] m_entries;
		m_entries = nullptr;
	}
}

template<typename T, unsigned int GROW_SIZE, unsigned int(*HASH_FUNC)(const char*)>
inline void HashTable<T, GROW_SIZE, HASH_FUNC>::Clear()
{
	for (unsigned int i = 0; i < m_capacity; ++i)
	{
		while (m_entries[i] != nullptr)
		{
			auto next = m_entries[i]->next;
			delete m_entries[i];
			m_entries[i] = next;
		}
	}
}

template<typename T, unsigned int GROW_SIZE, unsigned int(*HASH_FUNC)(const char*)>
inline bool HashTable<T, GROW_SIZE, HASH_FUNC>::Empty() const
{
	return m_count == 0;
}

template<typename T, unsigned int GROW_SIZE, unsigned int(*HASH_FUNC)(const char*)>
inline unsigned int HashTable<T, GROW_SIZE, HASH_FUNC>::Count() const
{
	return m_count;
}

template<typename T, unsigned int GROW_SIZE, unsigned int(*HASH_FUNC)(const char*)>
inline unsigned int HashTable<T, GROW_SIZE, HASH_FUNC>::Capacity() const
{
	return m_capacity;
}

template<typename T, unsigned int GROW_SIZE, unsigned int(*HASH_FUNC)(const char*)>
inline float HashTable<T, GROW_SIZE, HASH_FUNC>::LoadFactor() const
{
	return m_count / float(m_capacity);
}

template<typename T, unsigned int GROW_SIZE, unsigned int(*HASH_FUNC)(const char*)>
inline void HashTable<T, GROW_SIZE, HASH_FUNC>::Insert(const char* _key, const T& _value)
{
	Entry* newEntry = new Entry(_key, _value);
	auto index = HASH_FUNC(_key) % m_capacity;
	newEntry->next = m_entries[index];
	m_entries[index] = newEntry;
	m_count++;

	if (LoadFactor() > LOAD_THRESHOLD)
		Expand();
}

template<typename T, unsigned int GROW_SIZE, unsigned int(*HASH_FUNC)(const char*)>
inline void HashTable<T, GROW_SIZE, HASH_FUNC>::Remove(const char* _key)
{
	auto index = HASH_FUNC(_key) % m_capacity;

	if (m_entries[index] != nullptr)
	{
		auto temp = m_entries[index]->next;
		delete m_entries[index];
		m_entries[index] = temp;
		m_count--;
	}
}

template<typename T, unsigned int GROW_SIZE, unsigned int(*HASH_FUNC)(const char*)>
inline void HashTable<T, GROW_SIZE, HASH_FUNC>::RemoveAll(const char* _key)
{
	auto index = HASH_FUNC(_key) % m_capacity;
	while (m_entries[index] != nullptr)
	{
		auto temp = m_entries[index]->next;
		delete m_entries[index];
		m_entries[index] = temp;
		m_count--;
	}
}

template<typename T, unsigned int GROW_SIZE, unsigned int(*HASH_FUNC)(const char*)>
inline size_t HashTable<T, GROW_SIZE, HASH_FUNC>::AllFor(const char* _key, vector<T>& _values) const
{
	_values.clear();
	auto index = HASH_FUNC(_key) % m_capacity;
	auto temp = m_entries[index];
	while (temp != nullptr)
	{
		_values.push_back(temp->value);
		temp = temp->next;
	}

	return _values.size();
}

template<typename T, unsigned int GROW_SIZE, unsigned int(*HASH_FUNC)(const char*)>
inline T& HashTable<T, GROW_SIZE, HASH_FUNC>::operator[](const char* _key)
{
	auto index = HASH_FUNC(_key) % m_capacity;
	assert(m_entries[index] != nullptr);
	return m_entries[index]->value;
}

template<typename T, unsigned int GROW_SIZE, unsigned int(*HASH_FUNC)(const char*)>
inline const T& HashTable<T, GROW_SIZE, HASH_FUNC>::operator[](const char* _key) const
{
	auto index = HASH_FUNC(_key) % m_capacity;
	assert(m_entries[index] != nullptr);
	return m_entries[index]->value;
}

template<typename T, unsigned int GROW_SIZE, unsigned int(*HASH_FUNC)(const char*)>
inline void HashTable<T, GROW_SIZE, HASH_FUNC>::Expand()
{
	// create new table
	unsigned int newSize = m_capacity + GROW_SIZE;
	Entry** newTable = new Entry * [newSize];
	for (unsigned int i = 0; i < newSize; ++i)
		newTable[i] = nullptr;

	// copy entries to new table and rehash them
	for (unsigned int i = 0; i < m_capacity; ++i)
	{
		auto entry = m_entries[i];
		while (entry != nullptr) 
		{
			auto next = entry->next;

			auto index = HASH_FUNC(entry->key.c_str()) % newSize;

			entry->next = newTable[index];
			newTable[index] = entry;

			entry = next;
		}
	}

	// replace old table
	delete[] m_entries;
	m_entries = newTable;
	m_capacity = newSize;
}

template<typename T, unsigned int GROW_SIZE, unsigned int(*HASH_FUNC)(const char*)>
inline HashTable<T, GROW_SIZE, HASH_FUNC>::Entry::Entry(const char* _key, const T& _value)
	: key(_key), value(_value)
{
}