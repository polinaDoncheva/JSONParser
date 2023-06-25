#pragma once
#include "JSONParser.h"

class JSONExecutor {

	static bool validateNumber(const MyString& input);
	static unsigned getNumber(const MyString& input);
	static void printMenu();

public:
	static void runProgram();
};