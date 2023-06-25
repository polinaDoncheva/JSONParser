#pragma once
#include "MyString.h"
#include "Value.h"
#include <iostream>

class Pair {
	MyString key;
	Value* value;

	void readKey(std::istream& is);
	void printTabs(std::ostream& os, unsigned tabsCount) const;

	void copyFrom(const Pair& other);
	void moveFrom(Pair&& other);
	void free();

public:
	Pair();
	Pair(std::istream& is);
	Pair(const MyString& key, Value* value);

	Pair(const Pair& other);
	Pair& operator=(const Pair& other);

	Pair(Pair&& other);
	Pair& operator=(Pair&& other);

	~Pair();

	Value* getValue() const;

	void print(std::ostream& os, unsigned tabsCount) const;
	bool search(const MyString& key) const;
	const MyString& getKey() const;
	Pair* findPath(const Vector<MyString>& path, unsigned currIndex);

	void setValue(Value* value);
	void setNullValue();
	bool add(const Pair& pair);
	void deleteByKey(const MyString& key);
};