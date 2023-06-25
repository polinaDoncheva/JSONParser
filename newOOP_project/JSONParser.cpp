#include "JSONParser.h"
#include "SingleValue.h"
#include "NestedValue.h"
#include "ArrayValue.h"
#include <fstream>
#include <iostream>
#include <sstream>


JSONParser::JSONParser(const MyString& fileName)
{
	parse(fileName);
}

void JSONParser::parse(const MyString& fileName)
{
	std::ifstream ifs(fileName.c_str());
	if (!ifs.is_open())
		throw std::exception("Error while opening the file!");
	unsigned currentPosition = ifs.tellg();
	validateFile(ifs);
	ifs.seekg(currentPosition);
	this->fileName = fileName;

	char ch;
	bool isBegin = false;
	while (true)
	{
		ch = ifs.get();
		if (ch == '}')
			break;
		else if (ch == ',' || ch == '{')
			pairs.pushBack(std::move(Pair(ifs)));
	}
	ifs.close();
}

void JSONParser::validateValue(const MyString& value) const
{
	unsigned lenght = value.length();
	for (size_t i = 0; i < lenght; i++)
	{
		if (value[i] == ' ' || value[i] == '\t')
			continue;
	}
}

bool JSONParser::validateQuotes(std::istream& ifs) const
{
	size_t currentPos = ifs.tellg();
	int counter = 0;
	char c;
	while (true)
	{
		c = ifs.get();
		if (ifs.eof())
			break;
		if (c == '\"')
			counter++;
	}
	ifs.clear();
	ifs.seekg(currentPos);
	return counter % 2 == 0;
}
bool JSONParser::validateBrack(std::istream& ifs, const char ch) const
{
	size_t currentPos = ifs.tellg();
	int counter = 0;
	char c;
	if (ch == '{')
	{
		while (!ifs.eof())
		{
			c = ifs.get();
			if (c == '{')
				counter++;
			else if (c == '}')
				counter--;
		}

	}
	else
	{
		while (!ifs.eof())
		{
			c = ifs.get();
			if (c == '[')
				counter++;
			else if (c == ']')
				counter--;
		}
	}
	ifs.clear();
	ifs.seekg(currentPos);
	return counter == 0;
}
void JSONParser::validateLogic(std::istream& ifs, char c) const
{
	size_t currentPos = ifs.tellg();
	switch (c)
	{
	case '\"':
	{
		c = ifs.get();
		while (c != '"') {
			if (c == ':' || c == '{' || c == '}' || c == ']' || c == '[' || c == ',' || c == '\n')
				throw std::exception("Incorrect symbol in key or value!");
			c = ifs.get();
		}
		currentPos = ifs.tellg();
		break;
	}
	case '[':
	{
		c = ifs.get();
		while (c == ' ' || c == '\t' || c == ',' || c == '\n')
			c = ifs.get();

		while (c != ']')
		{
			if (c == '\"')
				validateLogic(ifs, '"');
			if (c == '[')
				validateLogic(ifs, '[');
			if (c == '{')
				validateLogic(ifs, '{');

			if (c == ':')
				throw std::exception("Cannot have key-value pairs in an array");

			//c = ifs.get();
			ifs >> c;
			if (c == ']')
				break;
		}
		currentPos = ifs.tellg();

		break;
	}
	case '{':
	{
		c = ifs.get();
		while (c == ' ' || c == '\t' || c == ',' || c == '\n')
			c = ifs.get();

		while (c != '}')
		{
			if (c == '\"') {

				validateLogic(ifs, '"');
				char ch = ifs.get();

				while (ch == ' ' || ch == '\t')
					ch = ifs.get();
				if (ch != ':')
					throw std::exception("Can't have a value without a key in an object!");
				ch = ifs.get();

				while (ch == ' ' || ch == '\t')
					ch = ifs.get();

				if (ch == '"')
					validateLogic(ifs, '"');
				else if (ch == '[')
					validateLogic(ifs, '[');
				ch = ifs.get();
				while (ch == ' ' || ch == '\t')
					ch = ifs.get();
				if (ch == '}')
					break;
				if (ch != ',' && ch != '\n')
					throw std::exception("Wrong kvp syntax in an object!");


			}
			if (c == '[') {
				ifs.seekg(-1, std::ios::cur);
				char ch = ifs.get();
				while (ch == ' ' || ch == '\t')
					ch = ifs.get();
				if (ch != ':')
					throw std::exception("Can't have an array whitout a key in an object!");
				ch = ifs.get();

				while (ch == ' ' || ch == '\t')
					ch = ifs.get();
				ifs.ignore();
				validateLogic(ifs, '[');
			}
			if (c == '{')
				validateLogic(ifs, '{');

			c = ifs.get();

		}
		currentPos = ifs.tellg();
		break;
	}
	default:
		throw std::exception("Wrong file format!");
		break;
	}
	ifs.clear();
	ifs.seekg(currentPos);
}
void JSONParser::validateFile(std::istream& ifs) const
{
	if (!validateQuotes(ifs))
	{
		throw std::exception("Incorrect placemen of quotes in file!");
		//ifs.close();
	}
	if (!validateBrack(ifs, '['))
		throw std::exception("Incorrect placemen of square brackets in file!");
	if (!validateBrack(ifs, '{'))
		throw std::exception("Incorrect placemen of curly brackets in file!");
	char c;
	ifs >> c;
	if (c != '{')
		throw std::exception("File must start with an open curly bracket!");
	validateLogic(ifs, c);
	//std::cout << "File successfully validated ";
}


void JSONParser::writeObject(std::ostream& os) const
{
	os << '{' << std::endl;
	unsigned size = pairs.getSize();
	for (size_t i = 0; i < size; i++)
	{
		pairs[i].print(os, 0);
		if (i != size - 1)
			os << ',' << std::endl;
	}
	os << std::endl << '}';
}
void JSONParser::print() const
{
	writeObject(std::cout);
}

void JSONParser::save(const MyString& path)
{
	saveAs(path, fileName);
}
void JSONParser::saveAs(const MyString& path, const MyString& newFileName)
{
	std::ofstream ofs(newFileName.c_str(), std::ios::trunc);
	if (!ofs.is_open())
		throw std::exception("Error while opening the file!");
	if (path != "")
	{
		Vector<MyString> paths;
		fillKeysFromPath(path, paths);
		findPath(paths)->print(ofs, 0);
	}
	else
		writeObject(ofs);
	ofs.close();
}

void JSONParser::search(const MyString& key)
{
	std::cout << '[' << std::endl;
	bool isFound = false;
	unsigned size = pairs.getSize();
	for (size_t i = 0; i < size; i++)
	{
		if (pairs[i].search(key))
			isFound = true;
	}
	std::cout << ']';
	if (!isFound)
		std::cout << std::endl << "Key \"" << key << "\" does not exist!" << std::endl;
}
Pair* JSONParser::findPath(const Vector<MyString>& path)
{
	unsigned size = pairs.getSize();
	for (size_t i = 0; i < size; i++)
	{
		if (pairs[i].findPath(path, 0) == nullptr)
			continue;
		else
			return pairs[i].findPath(path, 0);
	}
	return nullptr;
}

Value* JSONParser::getNewValue(const MyString& string) const
{
	/*
	char ch;
	unsigned currentPosition = 0;
	unsigned length=string.length();
	unsigned currentIndex = 0;*/
	unsigned size = string.length();
	std::stringstream ss(string.c_str());
	for (size_t i = 0; i < size; i++)
	{
		if (string[i] == '{')
			return new NestedValue(ss);
		else if (string[i] == '\"')
			return new SingleValue(ss);
		else if (string[i] == '[')
			return new ArrayValue(ss);
	}

	/*for (size_t i = 0; i < length; i++)
	{
		if (string[currentIndex] == '{')
			return new NestedValue(string, currentIndex, length);
		else if (string[currentIndex] == '\"')
			return new SingleValue(string, currentIndex, length);
		else if (string[currentIndex] == '[')
			return new ArrayValue(string, currentIndex, length);
	}*/
}
void JSONParser::fillKeysFromPath(const MyString& path, Vector<MyString>& dest) const
{
	unsigned size = path.length();
	MyString current;
	for (size_t i = 0; i < size; i++)
	{
		if (path[i] == '/')
		{
			dest.pushBack(current);
			current = "";
		}
		else
		{
			current += path[i];
			if (i == size - 1)
				dest.pushBack(current);
		}
	}
}

void JSONParser::set(const MyString& path, const MyString& string)
{
	Value* value = getNewValue(string);
	set(path, value);
}
void JSONParser::set(const MyString& path, Value* value)
{
	Vector<MyString> paths;
	fillKeysFromPath(path, paths);

	if (findPath(paths) == nullptr)
		throw std::exception("This path does not exist!");
	findPath(paths)->setValue(value);
}

void JSONParser::create(const MyString& path, const MyString& string)
{
	Value* value = getNewValue(string);
	create(path, value);
}
void JSONParser::create(const MyString& path, Value* value)
{
	Vector<MyString> paths;
	fillKeysFromPath(path, paths);
	if (findPath(paths) != nullptr)
		throw std::exception("This path already exists!");
	MyString key = paths[paths.getSize() - 1];
	paths.popBack();
	if (findPath(paths) == nullptr)
		throw std::exception("This path does not exist!");
	Pair p(key, value);
	if (!findPath(paths)->add(p))
		throw std::exception("Can not add anything! Path leads to Simple Value!");
}

void JSONParser::deleteByPath(const MyString& path)
{
	Vector<MyString> paths;
	fillKeysFromPath(path, paths);
	if (findPath(paths) == nullptr)
		throw std::exception("This path does not exist!");

	MyString key = paths[paths.getSize() - 1];
	paths.popBack();
	unsigned size = pairs.getSize();

	if (paths.getSize() == 0)
	{
		for (size_t i = 0; i < size; i++)
		{
			if (pairs[i].getKey() == key)
			{
				pairs.popAt(i);
				return;
			}
		}
	}
	findPath(paths)->deleteByKey(key);
}
void JSONParser::move(const MyString& from, const MyString& to)
{
	Vector<MyString> fromPaths;
	fillKeysFromPath(from, fromPaths);
	Pair* fromPair = findPath(fromPaths);
	if (fromPair == nullptr)
		throw std::exception("This path does not exist!");
	Value* fromValue = fromPair->getValue()->clone();//get copy of value
	set(to, fromValue);
	fromPair->setNullValue();
}

void JSONParser::close()
{
	unsigned size = pairs.getSize();
	for (size_t i = 0; i < size; i++)
		pairs.popBack();
	fileName = "";
}