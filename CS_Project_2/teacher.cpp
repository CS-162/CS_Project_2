/**
**	Program: Teacher Struct Implementation
**	Author: Austin Chayka
**	Date: 20.27.2019
**	Description: Implementation of functions for the teacher struct
**/

#include "teacher.h"

#include <fstream>
#include <iostream>

#include "util.h"

/**
**	Function: create teachers
**	Description: creates array of teacher structs from file information
**	Parameters: path to file
**/
teacher * create_teachers(string info_file_path) {

	if(!check_file_validity(info_file_path)) return nullptr;

	int num_teachers = get_num_lines(info_file_path);
	ifstream file;
	file.open(info_file_path);

	teacher *teachers = new teacher[num_teachers];

	int id;
	string password, first_name, last_name;
	for(int i = 0; i < num_teachers; i++) {
		file >> id >> password >> first_name >> last_name;
		teachers[i].id = id;
		teachers[i].password = password;
		teachers[i].first_name = first_name;
		teachers[i].last_name = last_name;
	}

	file.close();

	return teachers;

}

/**
**	Function: find id
**	Description: finds index of teacher with specified id
**	Parameters: array of teachers, id, number of teachers
**/
int find_id(teacher *teachers, int id, int num_teachers) {

	for(int i = 0; i < num_teachers; i++) if(teachers[i].id == id) return i;

	return -1;

}

/**
**	Function: is login valid
**	Description: checks teacher login info is valid
**	Parameters: array of teachers, index of teacher, id, password, number of teachers
**/
bool login_valid(teacher *teachers, int teacher_index, int id, string password, int num_teachers) {

	if(teacher_index < 0 || teacher_index > num_teachers) return false;

	return teachers[teacher_index].id == id && teachers[teacher_index].password == password;

}

/**
**	Function: print info
**	Description: prints info for each teacher in array
**	Parameters: array of teachers, number of teachers
**/
void print_info(const teacher *teachers, int num_teachers) {

	for(int i = 0; i < num_teachers; i++)
		cout << teachers[i].id << " " << teachers[i].password << " "
			<< teachers[i].first_name << " " << teachers[i].last_name << endl;

}
