//#include "JSONExecutor.h"
//#include "JSONParser.h"
//#include <fstream>
//
//void JSONExecutor::execute()
//{
//	MyString fileName;
//	JSONParser myObject;
//	unsigned inputNum = 0;
//	while (true)
//	{
//		std::cout << "Enter file name: ";
//		std::cin >> fileName;
//		try
//		{
//			myObject.parse(fileName);
//		}
//		catch (const std::exception& exc)
//		{
//			std::cout << exc.what() << "File must be valid JSON value! " << "Try again!" << std::endl;
//			fileName = "";
//			continue;
//		}
//	}
//	while (true)
//	{
//		MyString input;
//		printMenu();
//		std::cin >> input;
//		if (!validateNumber(input))
//		{
//			std::cout << "The number must be between 1 and 10" << std::endl;
//			continue;
//		}
//		inputNum = getNumber(input);
//		switch (inputNum)
//		{
//		case 1:validateCommand(myObject, fileName);
//			break;
//		case 2:
//			break;
//		case 3:
//			break;
//		case 4:
//			break;
//		case 5:
//			break;
//		case 6:
//			break;
//		case 7:
//			break;
//		case 8:
//			break;
//		case 9:
//			break;
//		case 10:
//			break;
//		default:
//			break;
//		}
//	}
//}
//
//void JSONExecutor::validateCommand(const JSONParser& myObject, m)
//{
//	try
//	{
//		myObject.validateFile(ifs);
//	}
//	catch (const std::exception& exc)
//	{
//		std::cout << exc.what() << std::endl;
//	}
//}
//void JSONExecutor::printMenu()
//{
//	std::cout << "Enter one of the following numbers:" << std::endl;
//	std::cout << "1. Validate." << std::endl;
//	std::cout << "2. Print." << std::endl;
//	std::cout << "3. Search." << std::endl;
//	std::cout << "4. Set." << std::endl;
//	std::cout << "5. Create." << std::endl;
//	std::cout << "6. Delete." << std::endl;
//	std::cout << "7. Move." << std::endl;
//	std::cout << "8. Save." << std::endl;
//	std::cout << "9. Save as" << std::endl;
//	std::cout << "10. Exit." << std::endl;
//}
//unsigned JSONExecutor::getNumber(const MyString& input)
//{
//	unsigned number = 0;
//	for (size_t i = 0; i < input.length(); i++)
//		number = number * 10 + input[i];
//	return number;
//}
//bool JSONExecutor::validateNumber(const MyString& input)
//{
//	if (input.length() > 2)
//		return false;
//	else if (input.length() == 1)
//	{
//		if (input[0] <= '9' && input[0] >= '1')
//			return true;
//	}
//	else if (input.length() == 2)
//	{
//		if (input[0] == '1' && input[1] == '0')
//			return true;
//	}
//	return false;
//}