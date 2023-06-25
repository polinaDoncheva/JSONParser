#pragma once
#include "JSONParser.h"

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

class Command {
public:
	virtual void execute()=0;
	~Command()=default;
};

class OpenCommand : public Command {
	JSONParser* myObject;
	bool isFileOpen = false;
public:
	OpenCommand(JSONParser* obj,bool isOpen):myObject(obj),isFileOpen(isOpen){}
	void execute() override;
};
class CloseCommand : public Command {
	JSONParser* myObject;
	bool isFileOpen = false;
public:
	CloseCommand(JSONParser* obj, bool isOpen) :myObject(obj), isFileOpen(isOpen) {}
	void execute() override;
};
class ValidateCommand : public Command {
	/*JSONParser* myObject;
	bool isFileOpen = false;*/
public:
	//ValidateCommand(JSONParser* obj, bool isOpen) :myObject(obj), isFileOpen(isOpen) {}
	 void execute() override;
};
class PrintCommand : public Command {
	JSONParser* myObject;
	bool isFileOpen = false;
public:
	PrintCommand(JSONParser* obj, bool isOpen) :myObject(obj), isFileOpen(isOpen) {}
	void execute() override;
};
class SearchCommand : public Command {
	JSONParser* myObject;
	bool isFileOpen = false;
public:
	SearchCommand(JSONParser* obj, bool isOpen) :myObject(obj), isFileOpen(isOpen) {}
	void execute() override;
};
class SetCommand : public Command {
	JSONParser* myObject;
	bool isFileOpen = false;
public:
	SetCommand(JSONParser* obj, bool isOpen) :myObject(obj), isFileOpen(isOpen) {}
	void execute() override;
};
class CreateCommand : public Command {
	JSONParser* myObject;
	bool isFileOpen = false;
public:
	CreateCommand(JSONParser* obj, bool isOpen) :myObject(obj), isFileOpen(isOpen) {}
	void execute() override;
};
class DeleteCommand : public Command {
	JSONParser* myObject;
	bool isFileOpen = false;
public:
	DeleteCommand(JSONParser* obj, bool isOpen) :myObject(obj), isFileOpen(isOpen) {}
	void execute() override;
};
class MoveCommand : public Command {
	JSONParser* myObject;
	bool isFileOpen = false;
public:
	MoveCommand(JSONParser* obj, bool isOpen) :myObject(obj), isFileOpen(isOpen) {}
	void execute() override;
};
class SaveCommand : public Command {
	JSONParser* myObject;
	bool isFileOpen = false;
public:
	SaveCommand(JSONParser* obj, bool isOpen) :myObject(obj), isFileOpen(isOpen) {}
	void execute() override;
};
class SavePathCommand : public Command{
	JSONParser* myObject;
	bool isFileOpen = false;
public:
	SavePathCommand(JSONParser* obj, bool isOpen) :myObject(obj), isFileOpen(isOpen) {}
	void execute() override;
};
class SaveAsCommand : public Command {
	JSONParser* myObject;
	bool isFileOpen = false;
public:
	SaveAsCommand(JSONParser* obj, bool isOpen) :myObject(obj), isFileOpen(isOpen) {}
	void execute() override;
};
class SaveAsPathCommand : public Command{
	JSONParser* myObject;
	bool isFileOpen = false;
public:
	SaveAsPathCommand(JSONParser* obj, bool isOpen) :myObject(obj), isFileOpen(isOpen) {}
	void execute() override;
};
class HelpCommand :public Command {
public:
	void execute() override;
};
class DefaultCommand :public Command {
public:
	void execute() {}
};