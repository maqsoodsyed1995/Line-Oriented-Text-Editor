#include<iostream>
#include<string>
#include "Command.h"

/*
* Default Constructor for the Command class.
*/
Command::Command():firstlineno(0), secondlineno(0)
{
	
}
/*
* Getter method for the private variable firstlineno.
* @return the private data member firstlineno.
*/
int Command::getfirstlineno()
{
	return firstlineno;
}
/*
* Getter method for the private variable secondlineno .
* @return the private data member secondlineno.
*/
int Command::getsecondlineno()
{
	return secondlineno;
}
/*
* Getter method for the private variable Command.
* @return the private data member Command.
*/
char Command::getcommand()
{
	return command;
}
/*
* Setter method for the private variable firstlineno.
* @param flno the interger variable to set the firstlineno.
*/
void Command::setfirstlineno(int flno)
{
	 firstlineno=flno;
}
/*
* Setter method for the private variable secondlineno.
* @param slno the interger varaible to set the secondlineno.
*/
void Command::setsecondlineno(int slno)
{
     secondlineno=slno;
}
/*
* Setter method for the private variable Command.
* @param c the char variable to set the Command.
*/
void Command::setcommand(char c)
{
	command=c;
}
/*
* Searches the string for the  occurrence of the Command in the string.

* @param  cmdstr the string to search for.

* @return return true if command is present in the string else returns false.
*/
bool Command::iscommandpresent(string cmdstr)
{
	char array[] = { 'a', 'i', 'v', 'u', 'd', 'x', 'r', 'j', 'p', 'c', '-', '+', 'g', 'w', 'q', '*' };
	for (int i = 0; i < cmdstr.length(); i++)
	{
		for (int j = 0; j < 16; j++)
		{
			if (cmdstr[i]== array[j])
			{
				return true;
			}
		}
	}
	return false;
}
/*
* Searches the string for the  occurrence of the Comma i,e(,) in the string.

* @param  cmdstr the string to search for.

* @return return true if comma(,) is present in the string else returns false.
*/
bool Command::iscommapresent(string cmdstr)
{
	
	for (int j= 0; j < cmdstr.length(); j++)
	{
		if (cmdstr[j] ==',')
		{
			return true;
		}
	}
	return false;
}
/*
* Finds the position of the commmand in specified string.

* @param  cmdstr the string to search for.

* @return The position of the command in the string cmdtr.

*/
int Command::commandposition(string cmdstr)
{
	int commandpos;
	char array[] = { 'a', 'i', 'v', 'u', 'd', 'x', 'r', 'j', 'p', 'c', '-', '+', 'g', 'w', 'q', '*' };
	for (int i = 0; i < cmdstr.length(); i++)
	{
		for (int j = 0; j < 16; j++)
		{
			if (cmdstr[i] == array[j])
			{
				command = array[j];
				commandpos = i;
			}
		}
	}
	return commandpos;
}
/*
* Finds the position of the commma in specified string.

* @param  cmdstr the string to search for.

* @return The position of the comma in the string cmdtr.

*/
int Command::commaposition(string cmdstr)
{
	for (int j = 0; j < cmdstr.length(); j++)
	{
		if (cmdstr[j] == ',')
		{
			return j;
		}
	}
}
/*
* this function parse the the given string 
* and gives the command,firstlineno and secondlineno depending
* upon the input string provided.

* @param  cmdstr the string to parse.

* @param  currentln the position of the currentln in the buffer to check the boundary conditions.

* @param  lastline the position of the lastline in the buffer to check the boundary conditions.

* @return returns true if the parsing of the string is succesful ,returns false 
* if not succesful(ex.if the range of firstlineno and secondlineno is not proper).    

*/
bool Command::parse(string cmdstr, int currentln, int lastline)
{
	if (cmdstr.length() == 0)
	{
		firstlineno = 1;
		command = '+';
		return true;
	}
	string temp = cmdstr.substr(2);
	if (iscommapresent(temp) && iscommandpresent(temp))//checks for the command that has both command and comma in it.
	{
		
		if (temp.at(0) == ',')
		{
			int compos = commandposition(temp);
			int tempno = atoi(temp.substr(1, compos).c_str());
			if ((temp.substr(1,compos).at(0) == '$'))
			{
				tempno=lastline;
			}

			if ((currentln >= 1 && currentln <= tempno) && (tempno >= currentln && tempno <= lastline))
			{
				firstlineno = currentln;
				secondlineno = tempno;
				command = temp.at(compos);
				return true;
			}
		}
		else if (temp.at(temp.length() - 2) == ',')//x,z
		{
			int compos = commandposition(temp);
			int tempno = atoi(temp.substr(0, compos - 1).c_str());
			if ((tempno >= 1 && tempno <= currentln) && (currentln >= tempno && currentln <= lastline))
			{
				firstlineno = tempno;
				secondlineno = currentln;
				command = temp[compos];
				return true;
			}

		}
		else if (iscommapresent(temp) && iscommandpresent(temp))//x,yz
		{
			int compos = commandposition(temp);
			int commapos = commaposition(temp);
			int temp1 = atoi(temp.substr(0, commapos).c_str());
			int temp2 = atoi(temp.substr(commapos + 1, compos).c_str());
			if ((temp.substr(commapos + 1, compos).at(0) == '$'))
			{
				temp2 = lastline;
			}
			if ((temp1 >= 1 && temp1 <= temp2) && (temp2 >= temp1 && temp2 <= lastline))
			{
				firstlineno = temp1;
				secondlineno = temp2;
				command = temp[compos];
				return true;
			}

		}

		cout << "Out of range Values" << endl;
		return false;
	}
	if (!iscommapresent(temp) && iscommandpresent(temp)&&temp.length()>1)//checks for the command that has command but not comma in it.
	{
		int compos = commandposition(temp);
		int tempno = atoi(temp.substr(0, compos).c_str());
		if ((temp.substr(0, compos).at(0) == '$'))
		{
			tempno = lastline;
		}
		if (temp[compos] == '+' || temp[compos] == '-')
		{
			firstlineno = tempno;
			secondlineno = tempno;
			command = temp[compos];
			return true;
		}
		if (tempno >= 1 && tempno <= lastline)
		{
			firstlineno = tempno;
			secondlineno = tempno;
			command = temp[compos];
			return true;
		}
		cout << "Out of range Values" << endl;
		return false;
	}
	if (iscommapresent(temp) && !iscommandpresent(temp))//checks for the command that has  comma but not command in it.
	{
		
		if (temp.at(0) == ',')
		{
			int tempno = atoi(temp.substr(1, temp.length()).c_str());
			if ((temp.substr(1, temp.length()).at(0) == '$'))
			{
				tempno = lastline;
			}
		    
			if ((currentln >= 1 && currentln <= tempno) && (tempno >= currentln && tempno <= lastline))
			{
				firstlineno = currentln;
				secondlineno = tempno;
				command = 'p';
				return true;
			}
			cout << "Out of range Values" << endl;
			return false;
		}
		else if (temp.at(temp.length() - 1) == ',')//x,
		{
			int tempno = atoi(temp.substr(0, temp.length() - 1).c_str());
			if ((tempno >= 1 && tempno <= currentln) && (currentln >= tempno && currentln <= lastline))
			{
				firstlineno = tempno;
				secondlineno = currentln;
				command = 'p';
				return true;
			}
			cout << "Out of range Values" << endl;
			return false;
		}
		else if (iscommapresent(temp) && !iscommandpresent(temp))//x,y
		{
			int commapos = commaposition(temp);
			int temp1 = atoi(temp.substr(0, commapos).c_str());
			int temp2 = atoi(temp.substr(commapos + 1, temp.length()).c_str());
			if ((temp.substr(commapos + 1, temp.length()).at(0) == '$'))
			{
				temp2 = lastline;
			}
			if ((temp1 >= 1 && temp1 <= temp2) && (temp2 >= temp1 && temp2 <= lastline))
			{
				firstlineno = temp1;
				secondlineno = temp2;
				command = 'p';
				return true;
			}

			cout << "Out of range Values" << endl;
			return false;
		}

	}
	if (temp.length() == 1)
	{
		if (temp.at(0) == 'q')
		{
			command = 'q';
			return true;
		}
		if (temp.at(0) == 'w')
		{
			command = 'w';
			return true;
		}
		if (temp.at(0) == '+')//+
		{
			firstlineno = 1;
			secondlineno = 1;
			command = '+';
			return true;
		}
		else if (temp.at(0) == '-')//-
		{
			firstlineno = 1;
			secondlineno = 1;
			command = '-';
			return true;
		}
		else if (temp.at(0) == ',')//,
		{
			if (currentln >= 1 && currentln <= lastline)
			{
				firstlineno = currentln;
				secondlineno = currentln;
				command = 'p';
				return true;
			}

		}
		else if (temp.at(0) == '*')//*
		{

			firstlineno =1;
			secondlineno =lastline;
			command = 'p';
			return true;
		}
		else if (temp.at(0) == 'i')//i
		{
			firstlineno = 1;
			secondlineno = 1;
			command ='i';
			return true;
		}
		else if (temp.at(0) == 'p'|| temp.at(0) == '.')
		{
			if (currentln == 0)
			{
				cout << "Empty Buffer" << endl;
				return false;
			}

			firstlineno = currentln;
			secondlineno = currentln;
			command = 'p';
			return true;
		}
	}
	if (!iscommandpresent(temp) && !iscommapresent(temp))//checks for the command that has niether command nor comma in it.
	{
		
		int temp1 = atoi(temp.substr(0,temp.length()).c_str());
		if ((temp.substr(0, temp.length()).at(0) == '$'))
		{
			temp1= lastline;
			if (lastline == 0)
			{
				cout << "Empty Buffer" << endl;
				return false;
			}
		}
		if (lastline == 0)
		{
			cout << "Invalid Range" << endl;
			return false;
		}
		if (temp1 >= 1 && temp1 <= lastline)
		{
			
			firstlineno = temp1;
			secondlineno = temp1;
			command ='g';
			return true;
		}
	}
	return false;
}
