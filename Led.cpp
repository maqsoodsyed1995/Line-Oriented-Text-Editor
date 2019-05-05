#include "Led.h"
#include "Command.h"
#include<iostream>
#include<fstream>
using namespace std;
/*
* Constructor for led class.
* Initiazes the buffer with the contents of the file if the given file exists ,
* and make the currentline as the last line in the file.
* @param  fname the string for the filename.
*/
led::led(string fname)
{
	nooflines = 0;
	filename = fname;
	saveorunsaved = false;
	ifstream fin(fname);
	if (!fin)
	{
		return;
	}
	string line;
	while (getline(fin, line))
	{
		buffer.push_back(line);
		nooflines++;
	}
	currentline = nooflines;
}
/*
* This is the public function of the led class which calls the private command functions 
* depending uopn the user's choice.
*/
void led::run()
{
	char choice;
	if (nooflines == 0)
	{
		cout << "\"? \""<< " [New File]" << endl;
		cout << "Entering command mode" << endl;
		
	}
	else
	{
		cout <<"\""<<filename<<"\"" << " " << nooflines << " lines" << endl;
		cout << "Entering command mode" << endl;	
	}
	
	do
	{    
		string input;
		bool check;
		getline(cin, input);//reads the command from the user.
		Command cd;
		check=cd.parse(input,currentline,buffer.size());//parse the command line.
		if (check)
		{
			switch (cd.getcommand())
			{
			case 'a':
			{
				commanda(cd.getfirstlineno());//call for append function
				break;
			}
			case 'p':

			{
				commandp(cd.getfirstlineno(), cd.getsecondlineno());//call for print function
				break;
			}
			case 'i':
			{
				commandi(cd.getfirstlineno());//call for insert function
				break;

			}
			case 'd':
			{
				commandd(cd.getfirstlineno(), cd.getsecondlineno());//call for delete function
				break;

			}
			case 'r':
			{
				commandr(cd.getfirstlineno(), cd.getsecondlineno());//call for replace function
				break;
			}
			case '*':
			{
				commandprintall(1, buffer.size());//call for printfunction function which prints the entire buffer
				break;
			}
			case '-':
			{
				commandminus(cd.getfirstlineno());//call for - command
				break;
			}
			case '+':
			{
				commandplus(cd.getfirstlineno());//call for + command
				break;
			}
			case 'g':
			{
				commandg(cd.getfirstlineno());
				break;
			}
			case 'x':
			{
				commandx(cd.getfirstlineno(), cd.getsecondlineno()); //call for g command
				break;
			}
			case 'u':
			{
				commandu(cd.getfirstlineno());//call for u command
				break;
			}
			case 'v':
			{
				commandv(cd.getfirstlineno());//call for v command
				break;
			}
			
			case 'j':
			{
				commandj(cd.getfirstlineno(), cd.getsecondlineno());
				break;
			}
			case 'c':
			{
				commandc(cd.getfirstlineno(), cd.getsecondlineno());//call for join command
				break;
			}
			case 'w':
			{
				commandw();//call for write command
				break;
			}
			case 'q':
			{
				commandq();//call for quit command
				break;
			}
			default:
				break;
			}
		}
		else
		{
		
		}
	} while (true);//infinite loop breaks only when user quits the led editor.


}
/*
* This function appends text into the buffer after the line specified in the parameter
* and it sets the current line as the line entered into the buffer.

* @param  flno the line number after which the data is to be entered.
*/
void led::commanda(int flno)
{

	string line;
	currentline = flno;
	int count = 0;
	list<string>::iterator it = buffer.begin();
	advance(it, flno);
	while (getline(cin, line))

	{
		if (line == "break")
		{
			break;
		}
		buffer.emplace(it, line);
		count++;
		nooflines++;
	}
	getline(cin, line);
	cin.clear();
	currentline = flno+count;
}
/*
* this function prints the line through the given range without affecting the currentline address.

* @param  flno the integer to indicate starting range of the lines to be printed.

* @param  slno the integer to indicate ending range of the lines to be printed.
*/
void led::commandp(int flno, int slno)
{
	if (buffer.size() == 0)
	{
		cout << "Invalid Range" << endl;
			return;	}
	int j = flno;
	list<string>::iterator it = buffer.begin();

	advance(it, flno-1);
	for (int i = flno; i <= slno; i++)
	{
		cout << i;
		if (i == currentline)
		{
			cout << "> ";
		}
		else
		{
			cout << ": ";
		}
		cout<< *it<<endl;
		it++;
	}
	
}
/*
* This function inserts text into the buffer before the line specified in the parameter
* and it sets the current line as the line entered into the buffer.

* @param  flno the line number before which the data is to be entered.
*/
void led::commandi(int flno)
{
	string line;
	currentline =flno;
	int localcount = 0;
	list<string>::iterator it = buffer.begin();
	advance(it, flno-1);
	while (getline(cin, line))

	{
	  
		if (line == "break")
		{
			break;
		}
		buffer.insert(it, line);
		nooflines++;
		localcount++;
	}
	getline(cin, line);
	cin.clear();
	currentline = currentline +localcount- 1;
}
/*
* this function deletes the line through the given range ,if there is line after the deleted
* line range,then the current line is set to that line. otherwise the current address is set to
* the line before the deleted line range.

* @param  flno the integer to indicate starting range of the lines to be deleted.

* @param  llno the integer to indicate ending range of the lines to be deleted.
*/
void led::commandd(int flno, int llno)
{
	bool flag=false;
	if (buffer.size() > llno)
	{
		flag = true;
	}
	else
	{
		currentline = flno - 1;
	}
	int first = flno-1;
	int last = llno-1;
	list<string>::iterator it = buffer.begin();
	advance(it, first);
	for (int i = first; i <= last; i++)
	{
		it=buffer.erase(it);
		nooflines--;
	}
	if (flag)
	{
		currentline =(llno-(llno-flno));
		if (currentline < 0)
		{
			currentline = -(currentline);
		}
	}

	}
/*
* this function replaces the lines through the given range with the new inputs.

* @param  flno the integer to indicate starting range of the lines to be replaced.

* @param  slno the integer to indicate ending range of the lines to be replaced.
*/
void led::commandr(int flno, int llno)
{
	commandd(flno, llno);
	commandi(flno);
}
/*
* this function prints the line through the entire buffer in the order it were inserted.

* @param  flno the integer to indicate first line.

* @param  slno the integer to indicate the last line.
*/
void led::commandprintall(int flno, int llno)
{
	int j = flno;
	list<string>::iterator it = buffer.begin();
	advance(it, flno - 1);
	for (int i = flno; i <= llno; i++)
	{
		cout << i;
		if (i == currentline)
		{
			cout << "> ";
		}
		else
		{
			cout << ": ";
		}
		cout << *it << endl;
		it++;
	}

}
/*
* this function moves the currentline up by the speciified number in the parameter 
* provided there are that many lines above ,otherwise it prints top of file reached.


* @param  lineno the integer to indicate the number of lines the currentline should be moved up.
*/
void led::commandminus(int lineno)
{
	if (currentline - lineno > 0)
	{
		currentline = currentline - lineno;
	}
	else
	{
		currentline = 1;
		cout << "Top of file reached"<<endl;
	}
}
/*
* this function moves the currentline down by the speciified number in the parameter
* provided there are that many lines below ,otherwise it prints end of file reached.


* @param  lineno the integer to indicate the number of lines the currentline should be moved down.
*/
void led::commandplus(int lineno)
{
	if (currentline + lineno > buffer.size())
	{
		cout << "End of file reached"<<endl;
		currentline = buffer.size();
	}
	else
	{
		currentline = currentline +lineno;
	}
}
/*
* this function sets the currentline to the line specified in the parameter.

* @param  lineno the integer to which the currentline address has to be set up.
*/
void led::commandg(int lineno)
{
	
	if (buffer.size() == 0)
	{
		cout << "Invalid range" << endl;
		return;
	}

	if (lineno<0 || lineno>buffer.size()+1)
	{
		cout << "Invalid range" << endl;
		return;
	}
	list<string>::iterator it = buffer.begin();
	advance(it, lineno- 1);
	cout << *it<<endl;
	currentline = lineno;

}
/*
* Cuts the line range through the parameters specified from the buffer into the clipboard
* if there is a line after the cut range then the currentline is set to that line ,
* otherwise the current address is set to the line before the cut line range.

* @param  flno the integer to indicate the starting range for thr cut operation.

* @param  llno the integer to indicate the ending range for thr cut operation.

*/
void led::commandx(int flno, int llno)
{
	clipboard.clear();
	list<string>::iterator it = buffer.begin();
	advance(it, flno - 1);
	for (int i = flno; i <=llno; i++)
	{
		clipboard.emplace_back(*it);
		it++;
	}
	commandd(flno, llno);
}
/*
* this function pastes text from the clipboard into the buffer below the line specified in the parameter
* the last line entered is set as the currentline.

* @param  lineno the integer below which the clipboard has to be pasted.
*/
void led::commandv(int lineno)
{
	list<string>::iterator it = buffer.begin();
	advance(it, lineno);

	for (auto it1 = clipboard.begin(); it1 != clipboard.end(); ++it1)
	{
		buffer.emplace(it, *it1);
		nooflines++;
	}
	currentline = lineno + clipboard.size();
	
}
/*
* this function pastes text from the clipboard into the buffer above the line specified in the parameter
* the last line entered is set as the currentline.

* @param  lineno the integer above which the clipboard has to be pasted.
*/
void led::commandu(int lineno)
{
	list<string>::iterator it = buffer.begin();
	advance(it, lineno- 1);
	
	for (auto it1 = clipboard.begin(); it1 != clipboard.end(); ++it1)
	{
		buffer.insert(it,*it1);
		nooflines++;
	}
	currentline = lineno + clipboard.size() - 1;
	
}
/*
* Joins the line range through the specified parameters together on one line at the address
* of the first parameter ,seperated by a single space. lien number specified in the first parameter becomes 
* the currentline.

* @param  flno the integer line number on which the lines thru flno and flno has to be joined.

* @param  llno the integer which indicates the last line to be joined.

*/
void led::commandj(int flno,int llno)
{
	list<string>::iterator it = buffer.begin();
	advance(it, flno- 1);
	string str;
	for (int i = flno; i <= llno; i++)
	{
		str.append(*it+" ");
		it++;
	}
	commandd(flno, llno);

	list<string>::iterator it1 = buffer.begin();
	advance(it1, flno-1);
		buffer.emplace(it,str);
		nooflines++;
		currentline = flno;
}
/*
* this function replaces the present text with some other user specified text in 
* the range specified in the parameters.

* @param  flno the integer line number which indicates the starting line number from which the text has to be changed.

* @param  llno the integer line number which indicates the ending line number to which the text has to be changed.
*/
void led::commandc(int flno, int llno)
{
	int count=0;
	cout << "Change What? ";
	string input1;
	string output1;
	getline(cin, input1);
	cout<< "    To What? ";
	getline(cin, output1);

	list<string>::iterator it = buffer.begin();
	advance(it, flno - 1);
	for (int i = flno; i <= llno; i++)
	{
		size_t index = 0;
		string temp = *it;
		replaceAll(temp, input1, output1,count);
		it = buffer.erase(it);
		buffer.emplace(it, temp);
	}
	if (count > 1)
	{
		cout << "Changed " << count << " occurences" << endl;
	}
	else
	{
		cout << "Changed " << count << " occurence" << endl;
	}
	
}
/*
* This function writes out the entire buffer to its associated file.
* if the buffer is not associated with a user named file,it prompts
* for and reads the name of the associated file.
*/
void led::commandw()
{
	if (filename.length() == 0)
	{
		cout << "Enter file name " << endl;
		getline(cin, filename);
	}
	ofstream fout;
	fout.open(filename);
	list <string> ::iterator it;
	for (it = buffer.begin(); it != buffer.end(); ++it)
	{
		fout << *it;
		fout << '\n';
	}
		
}
/*
* this functions quits the led. Before quitting,however,it gives the user a last chance to save
* the buffer.if the user takes the chance, it simulates the write command specified above.
*/
void led::commandq()
{
	
	string save;
	cout << "Save changes to " << filename << " (y/n)?";
	while (true)
	{
		getline(cin, save);
		if (save.at(0) == 'y')
		{
			commandw();
			cout << endl;
			cout << buffer.size() << " lines written to file :" << filename << endl;
			cout << "Bye" << endl;
			exit(0);
		}
		else if (save.at(0) == 'n')
		{
			cout << "Bye" << endl;
			exit(0);
		}
		else
		{
			cout << "Bad answer :" << save.at(0)<<endl;
			cout << "Enter y for yes and n for no" << endl;
		}
	}
}
/*
* This function searches and replaces the string that has to be changed to a specified string 
* given by the user.
* 
* @param  s the String that has to be changed.

* @param  search the substring which has to be replaced.

* @param  replace the substring with which the search string has to be replaced.

* @param  count the integer which counts the number of changes made.

*/
void led::replaceAll(string &s, const string &search, const string &replace,int& count) {
	for (size_t pos = 0; ; pos += replace.length()) {
		pos = s.find(search, pos);
		if (pos == string::npos) break;
		count++;
		s.erase(pos, search.length());
		s.insert(pos, replace);
	}
	
}