#pragma once
#include<string>
#include<iostream>
using namespace std;
/*
* The Command class is used to parse the command line,
* It uses the parse method to do parsing,and rest of the methods
* helps the parse function to do its job correctly.
* The private data member firstlineno is used to store the line numbers before the comma,
* The private data member secondlineno is used to store the line numbers after the comma.
* The private data member command is used to store the Command character.
* There are setters and getters for each of the private data member.
*/
class Command
{
public:
	Command();
	bool parse(string,int,int);
	int getfirstlineno();
	int getsecondlineno();
	char getcommand();
	void setfirstlineno(int);
	void setsecondlineno(int);
	void setcommand(char);
private:
	int firstlineno;
	int secondlineno;
	char command;
	bool iscommandpresent(string);
	bool iscommapresent(string);
	int commandposition(string);
	int commaposition(string);
};