#include "JSONExecutor.h"
#include "Commands.h"
#include "JSONParser.h"
#include <fstream>

void JSONExecutor::runProgram()
{
	bool isOpen = false;
	JSONParser myObject;
	Command* command;
	unsigned inputNum = 0; 
	printMenu();
	while (true)
	{
		std::cout << "Enter a number:" << std::endl;
		MyString input;
		std::cin >> input;
		if (!validateNumber(input))
		{
			std::cout << "The number must be between 1 and 15" << std::endl;
			continue;
		}
		inputNum = getNumber(input);
		switch (inputNum)
		{
		case 1:command = new OpenCommand(&myObject, isOpen);
			isOpen = true;
			break;
		case 2: command = new CloseCommand(&myObject, isOpen);
			isOpen = false;
			break;
		case 3:command = new HelpCommand();
			break;
		case 4:command = new ValidateCommand();
			break;
		case 5:command = new PrintCommand(&myObject, isOpen);
			break;
		case 6:command = new SearchCommand(&myObject, isOpen);
			break;
		case 7:command = new SetCommand(&myObject, isOpen);
			break;
		case 8:command = new CreateCommand(&myObject, isOpen);
			break;
		case 9:command = new DeleteCommand(&myObject, isOpen);
			break;
		case 10:command = new MoveCommand(&myObject, isOpen);
			break;
		case 11:command = new SaveCommand(&myObject, isOpen);
			break;
		case 12:command = new SavePathCommand(&myObject, isOpen);
			break;
		case 13:command = new SaveAsCommand(&myObject, isOpen);
			break;
		case 14:command = new SaveAsPathCommand(&myObject, isOpen);
			break;
		default:
			command = new DefaultCommand();
			return;
			break;
		}
		command->execute();
		delete command;
	}
}

void JSONExecutor::printMenu()
{
	std::cout << "1. Open." << std::endl;
	std::cout << "2. Close." << std::endl;
	std::cout << "3. Help." << std::endl;
	std::cout << "4. Validate." << std::endl;
	std::cout << "5. Print." << std::endl;
	std::cout << "6. Search." << std::endl;
	std::cout << "7. Set." << std::endl;
	std::cout << "8. Create." << std::endl;
	std::cout << "9. Delete." << std::endl;
 	std::cout << "10. Move." << std::endl;
 	std::cout << "11. Save." << std::endl;
 	std::cout << "12. Save by path." << std::endl;
 	std::cout << "13. Save as" << std::endl;
 	std::cout << "14. Save as by path" << std::endl;
 	std::cout << "15. Exit." << std::endl;
}
unsigned JSONExecutor::getNumber(const MyString& input)
{
	unsigned number = 0;
	for (size_t i = 0; i < input.length(); i++)
		number = number * 10 + input[i]-'0';
	return number;
}
bool JSONExecutor::validateNumber(const MyString& input)
{
	unsigned length = input.length();
	if (length > 2)
		return false;
	else if (length == 1)
	{
		if (input[0] <= '9' && input[0] >= '1')
			return true;
	}
	else if (length == 2)
	{
		if (input[0] == '1' && input[1] >= '0' && input[1] <= '5')
			return true;
	}
	return false;
}