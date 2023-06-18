#include "SingleValue.h"
#include <fstream>


SingleValue::SingleValue(std::istream& is)
{
	char ch;
	bool isBegin = false;

	while (true)
	{
		ch = is.get();
		if (ch == '\"' && !isBegin)
		{
			isBegin = true;
			continue;
		}
		else if (ch == '\"' && isBegin)
			return;
		else if (isBegin)
			value += ch;
	}
}
void SingleValue::print(std::ostream& os, unsigned tabsCount) const
{
	os << '\"' << value << '\"';
}

Value* SingleValue::clone() const
{
	return new SingleValue(*this);
}

bool SingleValue::search(const MyString& key) const
{
	return false;
}
Pair* SingleValue::findPath(const Vector<MyString>& path, unsigned currIndex)
{
	return nullptr;
}
bool SingleValue::addValue(const Pair& pair)
{
	return false;
}
bool SingleValue::deleteByKey(const MyString& key)
{
	return false;
}
