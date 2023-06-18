#pragma once
#include "Vector.hpp"
#include "Pair.h"

class JSONParser {
	Vector<Pair> pairs;
	MyString fileName;

	Pair* findPath(const Vector<MyString>& path) ;
	void fillKeysFromPath(const MyString& path, Vector<MyString>& dest) const;
	Value* getNewValue(const MyString& string) const;
	void writeObject(std::ostream& os) const;

	//validate functions from Milica!
	bool validateQuotes(std::istream& ifs) const;
	bool validateBrack(std::istream& ifs, const char ch) const;
	//void validateLogic(std::istream& ifs, char c) const;

public:
	JSONParser() = default;
	JSONParser(const MyString& fileName);
	//validate function from Milica!
	void validateFile(std::istream& ifs) const;
	void parse(const MyString& fiileName);
	void print() const;
	void search(const MyString& key);
	void set(const MyString& path, const MyString& string);
	void set(const MyString& path, Value* value);

	void create(const MyString& path, const MyString& string);
	void create(const MyString& path, Value* value);
	
	void deleteByPath(const MyString& path);
	void move(const MyString& from, const MyString& to);
	void save() const;
	void saveAs(const MyString& newFileName) const;
};