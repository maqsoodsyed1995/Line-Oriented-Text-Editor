#pragma once
#include<iostream>
#include<string>
#include <list>
#include <vector>
using namespace std;
/*
* The Led class is used for the entire functioning of led editor.
* The main method in Led class is the run method which calls all the command functions 
* depending upon the user selection.
* The private data member buffer is used to store the user input line by line.
* The private data member clipboard is used to temporarily store the data from the buffer.
* The private data member nooflines is used to have a count of the number of elements in the buffer.
* The private data member currentline is used to store the position of current line in the buffer.
* The private data member filename is used to store the filename on which the buffer is operating.
*/
class led
{
public:
	led(string fname);
	void run();
private:
	list<string> buffer;
	vector<string> clipboard;
	int currentline;
	string filename;
	int nooflines;
	bool saveorunsaved;
	void commanda(int);
	void commandp(int, int);
	void commandi(int);
	void commandd(int, int);
	void commandr(int, int);
	void commandprintall(int, int);
	void commandminus(int);
	void commandplus(int);
	void commandg(int);
	void commandx(int, int);
	void commandv(int);
	void commandu(int);
	void commandj(int, int);
	void commandc(int, int);
	void replaceAll(string&, const string&, const string&,int&);
	void commandw();
	void commandq();
};