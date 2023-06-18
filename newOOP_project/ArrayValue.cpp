#include "ArrayValue.h"
#include "SingleValue.h"
#include "NestedValue.h"
#include <fstream>

void ArrayValue::copyFrom(const ArrayValue& other)
{
	size = other.size;
	capacity = other.capacity;
	values = new Value * [capacity] {nullptr};
	for (size_t i = 0; i < size; i++)
		values[i] = other.values[i]->clone();
}
void ArrayValue::moveFrom(ArrayValue&& other)
{
	size = other.size;
	capacity = other.capacity;
	values = other.values;
	other.values = nullptr;
}
void ArrayValue::free()
{
	for (size_t i = 0; i < size; i++)
		delete values[i];
	delete[] values;
}
void ArrayValue::resize()
{
	capacity *= 2;
	Value** temp = new Value * [capacity];
	for (size_t i = 0; i < size; i++)
		temp[i] = values[i];
	delete[] values;
	values = temp;
}

ArrayValue::ArrayValue(const ArrayValue& other)
{
	copyFrom(other);
}
ArrayValue& ArrayValue::operator=(const ArrayValue& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}
ArrayValue::ArrayValue(ArrayValue&& other)
{
	moveFrom(std::move(other));
}
ArrayValue& ArrayValue::operator=(ArrayValue&& other)
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

ArrayValue::~ArrayValue()
{
	free();
}

Value* ArrayValue::clone() const 
{
	return new ArrayValue(*this);
}

void ArrayValue::print(std::ostream& os, unsigned tabsCount) const
{
	os << '[' << std::endl;
	for (size_t i = 0; i < size; i++)
	{
		printTabs(os, tabsCount);
		values[i]->print(os, tabsCount+1);
		if (i != size - 1)
			os << ',';
		os << std::endl;
	}
	os << ']';
}

ArrayValue::ArrayValue(std::istream& is)
{
	char ch;
	unsigned currentPosition = 0;
	values = new Value*[capacity];

	while (true)
	{
		is >> ch;
		if (ch == '{')
		{
			currentPosition = is.tellg();
			is.seekg(currentPosition - 1);
			values[size++] = new NestedValue(is);
		}
		else if (ch == '\"')
		{
			currentPosition = is.tellg();
			is.seekg(currentPosition - 1);
			values[size++] = new SingleValue(is);
		}
		else if (ch == ']')
			break;
		/* da ne poddurjam value da e array ot array-ove
		else if (ch == '[')
		{
			currentPosition = ifs.tellg();
			values[size++] = new ArrayValue(ifs);
			break;
		}*/
	}
}

bool ArrayValue::search(const MyString& key) const
{
	bool isFound = false;
	for (size_t i = 0; i < size; i++)
	{
		if (values[i]->search(key))
			isFound = true;
	}
	return isFound;
}

Pair* ArrayValue::findPath(const Vector<MyString>& path, unsigned currIndex)
{
	for (size_t i = 0; i < size; i++)
	{
		if (values[i]->findPath(path, currIndex ) == nullptr)
			continue;
		return values[i]->findPath(path, currIndex );
	}
	return nullptr;
}

bool ArrayValue::addValue(const Pair& pair)
{
	values[size] = new NestedValue();
	return values[size++]->addValue(pair);
}
bool ArrayValue::deleteByKey(const MyString& key)
{
	for (size_t i = 0; i < size; i++) {
		if (values[i]->deleteByKey(key))
			return true;
	}
	return false;
}