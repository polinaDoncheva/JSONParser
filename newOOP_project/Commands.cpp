#include "Commands.h"
#include <fstream>
#include <iostream>

static bool validateQuotes(std::istream& ifs)
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
static bool validateBrack(std::istream& ifs, const char ch)
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
static void validateLogic(std::istream& ifs, char c)
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
static void validateFile(std::istream& ifs)
{
	if (!validateQuotes(ifs))
		throw std::exception("incorrect placemen of quotes in file!");
	if (!validateBrack(ifs, '['))
		throw std::exception("incorrect placemen of square brackets in file!");
	if (!validateBrack(ifs, '{'))
		throw std::exception("incorrect placemen of curly brackets in file!");
	char c;
	ifs>>c;
	if (c != '{')
		throw std::exception("File must start with an open curly bracket!");
	validateLogic(ifs, c);
	//std::cout << "File successfully validated ";
}

void OpenCommand::execute()
{
	if (isFileOpen)
	{
		std::cout << "File is alredy open!" << std::endl;
		return;
	}
	MyString fileName;
	bool isParsed = false;
	while (!isParsed)
	{
		std::cout << "Enter file name: ";
		std::cin >> fileName;
		try
		{
			myObject->parse(fileName);
		}
		catch (const std::exception& exc)
		{
			std::cout << exc.what() << " Object is not saved! Try again!" << std::endl;
			fileName = "";
			continue;
		}
		isParsed = true;
		isFileOpen = true;
		std::cout << "Data saved successfully!" << std::endl;
		return;
	}
}
void CloseCommand::execute()
{
	if (isFileOpen)
	{
		myObject->close();
		std::cout << "File successfully closed!" << std::endl;
	}
	else
		std::cout << "File has not been opened yet!" << std::endl;
}
void ValidateCommand::execute()
{
	MyString fileName;
	std::cout << "Enter file name: ";
	std::cin >> fileName;
	std::ifstream ifs(fileName.c_str());
	try
	{
		if (!ifs.is_open())
			throw std::exception("Error while opening the file!");
		validateFile(ifs);
	}
	catch (const std::exception& exc)
	{
		std::cout << exc.what() <<"File not validated!" << std::endl;
		ifs.close();
		return;
	}
	std::cout << "File is in the correct format!" << std::endl;
	ifs.close();
}
void PrintCommand::execute()
{
	if (!isFileOpen)
	{
		std::cout << "File has not been opened!" << std::endl;
		return;
	}
	myObject->print();
	std::cout << std::endl;
}
void SetCommand::execute()
{
	if (!isFileOpen)
	{
		std::cout << "File has not been opened!" << std::endl;
		return;
	}
	MyString path;
	MyString value;
	std::cout << "Enter path: ";
	std::cin >> path;
	std::cout << "Enter value in JSON format, on one line:) : ";
	std::cin >> value;
	if (value[0] != '{' && value[0] != '[' && value[0] != '\"')
	{
		std::cout << "Value is not in the right format!" << std::endl;
		return;
	}
	try
	{
		myObject->set(path, value);
	}
	catch (const std::exception& exc)
	{
		std::cout << exc.what()<<"Value has not been changed!" << std::endl;
		return;
	}
	std::cout << "Value has been successfully changed!" << std::endl;

}
void SearchCommand::execute()
{
	if (!isFileOpen)
	{
		std::cout << "File has not been opened!" << std::endl;
		return;
	}
	MyString key;
	std::cout << "Enter key: ";
	std::cin >> key;

	try
	{
		myObject->search(key);
	}
	catch (const std::exception& exc)
	{
		std::cout << exc.what()<<std::endl;
		return;
	}
	std::cout << std::endl;
}
void CreateCommand::execute()
{
	if (!isFileOpen)
	{
		std::cout << "File has not been opened!" << std::endl;
		return;
	}
	MyString path;
	MyString value;
	std::cout << "Enter path: ";
	std::cin >> path;
	std::cout << "Enter value in JSON format, on one line:) : ";
	std::cin >> value;
	if (value[0]!='{'&&value[0] != '['&& value[0] != '\"')
	{
		std::cout << "Value is not in the right format!" << std::endl;
		return;
	}
	try
	{
		myObject->create(path, value);
	}
	catch (const std::exception& exc)
	{
		std::cout << exc.what() << std::endl;
		return;
	}
	std::cout << "Key and value added successfully!" << std::endl;
}
void DeleteCommand::execute()
{
	if (!isFileOpen)
	{
		std::cout << "File has not been opened!" << std::endl;
		return;
	}
	MyString path;
	std::cout << "Enter path: ";
	std::cin >> path;
	try
	{
		myObject->deleteByPath(path);
	}
	catch (const std::exception& exc)
	{
		std::cout << exc.what() << std::endl;
		return;
	}
	std::cout << "Key and value has been successfully deleted!" << std::endl;
}
void MoveCommand::execute()
{
	if (!isFileOpen)
	{
		std::cout << "File has not been opened!" << std::endl;
		return;
	}
	MyString fromPath;
	MyString toPath;
	std::cout << "Enter form path: ";
	std::cin >> fromPath;
	std::cout << "Enter to path: ";
	std::cin >> toPath;
	try
	{
		myObject->move(fromPath, toPath);
	}
	catch (const std::exception& exc)
	{
		std::cout << exc.what() << std::endl;
		return;
	}
	std::cout << "Value successfully moved!" << std::endl;
}
void SaveCommand::execute()
{
	if (!isFileOpen)
	{
		std::cout << "File has not been opened!" << std::endl;
		return;
	}
	try
	{
		myObject->save("");
	}
	catch (const std::exception& exc)
	{
		std::cout << exc.what()<<std::endl;
		return;
	}
	std::cout << "Data successfully saved in same file!" << std::endl;
}
void SavePathCommand::execute()
{
	if (!isFileOpen)
	{
		std::cout << "File has not been opened!" << std::endl;
		return;
	}
	MyString path;
	std::cout << "Enter path: ";
	std::cin >> path;
	try
	{
		myObject->save(path);
	}
	catch (const std::exception& exc)
	{
		std::cout << exc.what()<<std::endl;
		return;
	}
	std::cout << "Path successfully saved in same file!" << std::endl;
}
void SaveAsCommand::execute()
{
	if (!isFileOpen)
	{
		std::cout << "File has not been opened!" << std::endl;
		return;
	}
	MyString fileName;
	MyString toPath;
	std::cout << "Enter file name: ";
	std::cin >> fileName;
	try
	{
		myObject->saveAs("",fileName);
	}
	catch (const std::exception& exc)
	{
		std::cout << exc.what() << std::endl;
		return;
	}
	std::cout << "Data successfully saved in new file with name: \"" << fileName << "\"!" << std::endl;
}
void SaveAsPathCommand::execute()
{
	if (!isFileOpen)
	{
		std::cout << "File has not been opened!" << std::endl;
		return;
	}
	MyString fileName;
	MyString path;
	std::cout << "Enter file name: ";
	std::cin >> fileName;
	std::cout << std::endl << "Enter path: ";
	std::cin >> path;
	try
	{
		myObject->saveAs(path, fileName);
	}
	catch (const std::exception& exc)
	{
		std::cout << exc.what()<<std::endl;
		return;
	}
	std::cout << "Path successfully saved in new file with name: \""<<fileName<<"\"!" << std::endl;
}
void HelpCommand::execute()
{
	std::cout << "1. Open - opens file by given name and saves data in JSON format." << std::endl;
	std::cout << "2. Close - closes file." << std::endl;
	std::cout << "3. Help - prints meny and definitions." << std::endl;
	std::cout << "4. Validate - checks if a file is in a correct JSON format." << std::endl;
	std::cout << "5. Print - prints data form opended file." << std::endl;
	std::cout << "6. Search - prints all the values with the given key." << std::endl;
	std::cout << "7. Set - changes the value by given path and new value." << std::endl;
	std::cout << "8. Create - adds new key on the given path with the given value." << std::endl;
	std::cout << "9. Delete - deletes by given path." << std::endl;
	std::cout << "10. Move - moves value from one path to the other." << std::endl;
	std::cout << "11. Save - saves object in current file." << std::endl;
	std::cout << "12. Save by path - saves the object on the given path in current file." << std::endl;
	std::cout << "13. Save as - saves object in new file." << std::endl;
	std::cout << "14. Save as by path - saves the object on the given path in new file." << std::endl;
	std::cout << "15. Exit - exits the program" << std::endl;
}