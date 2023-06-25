#pragma once
#include "Value.h"
#include "Pair.h"
#include "Vector.hpp"
#include "MyString.h"


class ArrayValue :public Value {
	Value** values;
	unsigned size = 0;
	unsigned capacity = 8;

	void copyFrom(const ArrayValue& other);
	void moveFrom(ArrayValue&& other);
	void free();
	void resize();

public:
	ArrayValue(std::istream& is);

	ArrayValue(const ArrayValue& other);
	ArrayValue& operator=(const ArrayValue& other);

	ArrayValue(ArrayValue&& other);
	ArrayValue& operator=(ArrayValue&& other);

	~ArrayValue();

	Value* clone() const override;

	void print(std::ostream& os, unsigned tabsCount) const override;
	bool search(const MyString& key) const override;

	Pair* findPath(const Vector<MyString>& path, unsigned currIndex) override;
	bool addValue(const Pair& pair) override;
	bool deleteByKey(const MyString& key) override;
};