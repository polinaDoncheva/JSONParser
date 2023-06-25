#pragma once
#include "MyString.h"
#include "Value.h"
#include "Vector.hpp"

class Pair;

class SingleValue :public Value {
	MyString value;
public:
	SingleValue(const MyString& value);
	SingleValue(std::istream& is);
	Value* clone() const override;

	void print(std::ostream& os, unsigned tabsCount) const override;
	bool search(const MyString& key) const override;

	Pair* findPath(const Vector<MyString>& path, unsigned currIndex) override;
	bool addValue(const Pair& pair) override;
	bool deleteByKey(const MyString& key) override;
	void setValue(const MyString& value);
};