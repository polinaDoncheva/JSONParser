#pragma once
#include "MyString.h"
#include "Vector.hpp"
#include <iostream>

class Pair;

class Value {
public:
	virtual Value* clone() const = 0;
	virtual ~Value() = default;

	virtual void print(std::ostream& os, unsigned tabsCount = 0) const = 0;
	void printTabs(std::ostream& os, unsigned tabsCount) const;

	virtual bool search(const MyString& key) const = 0;

	virtual Pair* findPath(const Vector<MyString>& path, unsigned currIndex) = 0;

	virtual bool addValue(const Pair& pair)=0;
	virtual bool deleteByKey(const MyString& key) = 0;
};