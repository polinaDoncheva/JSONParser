#include "Pair.h"
#include "SingleValue.h"
#include "NestedValue.h"
#include "ArrayValue.h"
#include <fstream>

Pair::Pair() {
	value = nullptr;
}
Pair::Pair(std::istream& is)
{
	readKey(is);
	char ch;
	unsigned currentPosition = 0;

	while (true)
	{
		is >> ch;
		if (ch == '{')
		{
			currentPosition = is.tellg();
			is.seekg(currentPosition - 1);
			value = new NestedValue(is);
			break;
		}
		else if (ch == '\"')
		{
			currentPosition = is.tellg();
			is.seekg(currentPosition - 1);
			value = new SingleValue(is);
			break;
		}
		else if (ch == '[')
		{
			currentPosition = is.tellg();
			is.seekg(currentPosition - 1);
			value = new ArrayValue(is);
			break;
		}
	}
}
Pair::Pair(const MyString& key, Value* value)
{
	this->key = key;
	this->value = value;
}

void Pair::copyFrom(const Pair& other)
{
	value = other.value->clone();
	key = other.key;
}
void Pair::moveFrom(Pair&& other)
{
	key = std::move(other.key);
	value = other.value;
	other.value = nullptr;
}
void Pair::free()
{
	if (value != nullptr)
		delete value;

}

Pair::Pair(const Pair& other)
{
	copyFrom(other);
}
Pair& Pair::operator=(const Pair& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}
Pair::Pair(Pair&& other)
{
	moveFrom(std::move(other));
}
Pair& Pair::operator=(Pair&& other)
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

Pair::~Pair()
{
	free();
}

void Pair::readKey(std::istream& is)
{
	bool isBegin = false;
	char ch;
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
		if (isBegin)
			this->key += ch;
	}
}

void Pair::print(std::ostream& os, unsigned tabsCount) const
{
	printTabs(os, tabsCount);
	os << '\"' << key << '\"';
	os << " : ";
	value->print(os, tabsCount + 1);
}
void Pair::printTabs(std::ostream& os, unsigned tabCount) const
{
	for (size_t i = 0; i < tabCount; i++)
		os << "  ";
}

bool Pair::search(const MyString& key) const
{
	if (this->key == key)
	{
		value->print(std::cout, 0);
		std::cout << ',' << std::endl;
		return true;
	}
	else
		return value->search(key);
}

const MyString& Pair::getKey() const
{
	return key;
}
Pair* Pair::findPath(const Vector<MyString>& path, unsigned currIndex) 
{
	if (currIndex==path.getSize()-1&&path[currIndex]==key)
		return this;
	else if (path[currIndex] == key)
		return value->findPath(path, currIndex + 1);
	return value->findPath(path, currIndex);
}
void Pair::setValue(Value* value)
{
	delete this->value;
	this->value = value;
}
bool Pair::add(const Pair& pair)
{
	return value->addValue(pair);
}
void Pair::deleteByKey(const MyString& key)
{
	value->deleteByKey(key);
}
Value* Pair::getValue() const
{
	return value;
}
