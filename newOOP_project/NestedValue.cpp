#include "NestedValue.h"
#include <fstream>

NestedValue::NestedValue(std::istream& is)
{
	char ch;
	unsigned currentPosition = 0;
	while (true)
	{
		is >> ch;
		if (ch == '}')
			break;
		currentPosition = is.tellg();
		is.seekg(currentPosition - 1);
		pairs.pushBack(std::move(Pair(is)));
	}
}

void NestedValue::print(std::ostream& os, unsigned tabsCount) const
{
	printTabs(os, tabsCount);
	os << '{' << std::endl;
	unsigned size = pairs.getSize();
	for (size_t i = 0; i < size; i++)
	{
		pairs[i].print(os, tabsCount + 1);
		if (i != size - 1)
			os << ',';
		os << std::endl;
	}
	printTabs(os, tabsCount);
	os << '}';
}

Value* NestedValue::clone() const
{
	return new NestedValue(*this);
}

bool NestedValue::search(const MyString& key) const
{
	bool isFound = false;
	unsigned size = pairs.getSize();
	for (size_t i = 0; i < size; i++)
	{
		if (pairs[i].search(key))
			isFound = true;
	}
	return isFound;
}

void NestedValue::validateValue(const MyString& value) const
{
	
}
Pair* NestedValue::findPath(const Vector<MyString>& path, unsigned currIndex)
{
	unsigned size = pairs.getSize();
	for (size_t i = 0; i < size; i++)
	{
		if (pairs[i].getKey() == path[currIndex] && currIndex == path.getSize() - 1)
			return &pairs[i];
		else if (pairs[i].getKey() == path[currIndex])
			return pairs[i].findPath(path, currIndex + 1);
	}
	return nullptr;
}
bool NestedValue::addValue(const Pair& pair)
{
	pairs.pushBack(pair);
	return true;
}
bool NestedValue::deleteByKey(const MyString& key)
{
	unsigned size = pairs.getSize();
	for (size_t i = 0; i < size; i++)
	{
		if (pairs[i].getKey() == key)
		{
			pairs.popAt(i);
			return true;
		}
	}
	return false;
}