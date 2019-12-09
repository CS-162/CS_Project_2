/**
**	Program: Utility Implementation
**	Author: Austin Chayka
**	Date: 20.27.2019
**	Description: Implementation of several utility functions
**/

#include "util.h"

#include <iostream>
#include <fstream>

/**
**	Function: is number
**	Description: checks if string contains only numeric digits
**	Parameters: string to check
**/
bool is_num(std::string s) {

	for(int i = (s[0] == '-' ? 1 : 0); s[i] != '\0'; i++) if(s[i] < '0' || s[i] > '9') return false;

	return true;

}

/**
**	Function: get number choice
**	Description: gets a number choice from the user
**	Parameters: minimum valid choice, maximum valid choice
**/
int get_number_choice(int min, int max) {

	cout << "Enter choice:";
	string input;
	cin >> input;

	bool valid = false;
	while(!valid) {
		if(!is_num(input)) {
			cout << "Error: input was not a number. Enter again:";
			cin >> input;
		} else if(stoi(input) < min || stoi(input) > max) {
			cout << "Error: not a valid option. Enter again:";
			cin >> input;
		} else valid = true;
	}

	return stoi(input);

}

/**
**	Function: get number of lines
**	Description: gets the number of lines in a file
**	Parameters: path to file
**/
int get_num_lines(string file_path) {

	fstream f;
	f.open(file_path);
	if(!f.is_open()) return -1;

	int lines = 0;
	string line;
	while(getline(f, line)) lines++;

	f.close();

	return lines;

}

/**
**	Function: check file validity
**	Description: checks if file exists and is not empty
**	Parameters: path to file
**/
bool check_file_validity(string file_path) {

	ifstream file;
	file.open(file_path);
	if(!file.is_open()) {
		cout << "Error: could not open file: \"" << file_path << "\"" << endl;
		return false;
	}

	file.close();

	if(get_num_lines(file_path) < 1) {
		cout << "Error: no lines in file: \"" << file_path << "\"" << endl;
		return false;
	}

	return true;

}

/**
**	Function: print file contents
**	Description: prints the contents of a file to the console
**	Parameters: path to file
**/
void print_file_contents(string file_path) {

	ifstream file;
	file.open(file_path);
	if(!file.is_open()) {
		cout << "Error: file not found" << endl;
		return;
	}

	string line;
	int num_lines = get_num_lines(file_path);
	for(int i = 0; i < num_lines; i++) {
		getline(file, line);
		cout << line << endl;
	}

}