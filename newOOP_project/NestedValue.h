#pragma once
#include "Value.h"
#include "Pair.h"
#include "Vector.hpp"


class NestedValue :public Value {
	Vector<Pair> pairs;
public:
	NestedValue() = default;
	NestedValue(std::istream& is);
	Value* clone() const override;

	void print(std::ostream& os, unsigned tabsCount) const override;
	bool search(const MyString& key) const override;

	Pair* findPath(const Vector<MyString>& path, unsigned currIndex) override;

	bool addValue(const Pair& pair) override;
	bool deleteByKey(const MyString& key) override;
};