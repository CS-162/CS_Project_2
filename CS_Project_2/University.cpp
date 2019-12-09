/**
**	Program: University Object
**	Author: Austin Chayka
**	Date: 20.27.2019
**	Description: Implementation of the university object
**/

#include "University.h"

#include <iostream>
#include <fstream>

#include "util.h"

/**
**	Function: constructor
**	Description: sets variable defaults
**	Parameters: none
**/
University::University() {

	name = "";
	address = "";
	current_term = "";
	num_courses = 0;
	num_teachers = 0;
	teachers = nullptr;
	courses = nullptr;
	
}

/**
**	Function: copy constructor
**	Description: sets the default variables to the values in another university object
**	Parameters: object to copy from
**/
University::University(const University &university) {
	
	name = university.name;
	address = university.address;
	current_term = university.current_term;
	num_courses = university.num_courses;

	if(university.teachers != nullptr) {
		teachers = new teacher[university.num_teachers];
		for(int i = 0; i < university.num_teachers; i++) if(university.teachers != nullptr) {
			teachers[i].first_name = university.teachers[i].first_name;
			teachers[i].last_name = university.teachers[i].last_name;
			teachers[i].id = university.teachers[i].id;
			teachers[i].password = university.teachers[i].password;
		}
	}

	courses = new Course[num_courses];
	if(university.courses != nullptr) for(int i = 0; i < num_courses; i++) courses[i] = university.courses[i];

}

/**
**	Function: destructor
**	Description: deallocates memory
**	Parameters: none
**/
University::~University() {

	if(teachers != nullptr) delete[] teachers;
	if(courses != nullptr) delete[] courses;

}

/**
**	Function: assignment opperator overload
**	Description: overides default assignment opperator to copy object values
**	Parameters: object to copy from
**/
University & University::operator=(const University &university) {

	name = university.name;
	address = university.address;
	current_term = university.current_term;
	num_courses = university.num_courses;
	num_teachers = university.num_teachers;

	if(teachers != nullptr) delete[] teachers;
	teachers = new teacher[university.num_teachers];
	if(university.teachers != nullptr) for(int i = 0; i < university.num_teachers; i++) {
		teachers[i].first_name = university.teachers[i].first_name;
		teachers[i].last_name = university.teachers[i].last_name;
		teachers[i].id = university.teachers[i].id;
		teachers[i].password = university.teachers[i].password;
	}

	if(courses != nullptr) delete[] courses;
	courses = new Course[num_courses];
	if(university.courses != nullptr) for(int i = 0; i < num_courses; i++) courses[i] = university.courses[i];

	return *this;

}

/**
**	Function: get name
**	Description: returns the name
**	Parameters: none
**/
string University::get_name() {

	return name;

}

/**
**	Function: set name
**	Description: sets the name
**	Parameters: new name
**/
void University::set_name(string name) {

	this->name = name;

}

/**
**	Function: get address
**	Description: returns the address
**	Parameters: none
**/
string University::get_adress() {

	return address;

}

/**
**	Function: set address
**	Description: sets the address
**	Parameters: new address
**/
void University::set_address(string address) {

	this->address = address;

}

/**
**	Function: get current term
**	Description: returns the current term
**	Parameters: none
**/
string University::get_current_term() {

	return current_term;

}

/**
**	Function: set current term
**	Description: sets the current term
**	Parameters: new term
**/
void University::set_current_term(string current_term) {

	this->current_term = current_term;

}

/**
**	Function: get number of teachers
**	Description: returns the number of teacher
**	Parameters: none
**/
int University::get_num_teachers() {

	return num_teachers;

}

/**
**	Function: get teachers
**	Description: returns the array of teachers
**	Parameters: none
**/
teacher * University::get_teachers() {

	return teachers;

}

/**
**	Function: set teachers
**	Description: sets the array of teachers
**	Parameters: new array, number of teachers
**/
void University::set_teachers(teacher *teachers, int num_teachers) {

	if(this->teachers == teachers) return;
	delete[] this->teachers;
	this->teachers = teachers;
	this->num_teachers = num_teachers;

}

/**
**	Function: get number of courses
**	Description: returns the number of courses
**	Parameters: none
**/
int University::get_num_courses() {

	return num_courses;

}

/**
**	Function: get courses
**	Description: returns the array of courses
**	Parameters: none
**/
Course * University::get_courses() {

	return courses;

}

/**
**	Function: set courses
**	Description: sets the array of courses
**	Parameters: new array, number of courses
**/
void University::set_courses(Course *courses, int num_courses) {

	if(this->courses == courses) return;
	delete[] this->courses;
	this->courses = courses;
	this->num_courses = num_courses;

}

/**
**	Function: search courses by term
**	Description: gets an array of search results
**	Parameters: term to search for, number of courses
**/
Course * University::search_courses_by_term(string term, int num_courses) {

	int counter = 0, increment = 0;
	for(int i = 0; i < num_courses; i++)
		if(courses[i].get_schedule().term == term) counter++;
	if(counter == 0) return nullptr;

	Course *searched_courses = new Course[counter];
	for(int i = 0; i < num_courses; i++)
		if(courses[i].get_schedule().term == term) searched_courses[increment++] = courses[i];

	return searched_courses;

}

/**
**	Function: get search by temr num
**	Description: returns the number of search results
**	Parameters: term to search for, number of courses
**/
int University::get_search_by_term_num(string term, int num_courses) {

	int counter = 0;
	for(int i = 0; i < num_courses; i++) if(courses[i].get_schedule().term == term) counter++;

	return counter;

}

/**
**	Function: search courses by times
**	Description: gets an array of search results
**	Parameters: times to search for, number of courses
**/
Course * University::search_courses_by_times(string *times, int num_times, int num_courses) {

	int counter = 0;
	for(int i = 0; i < num_courses; i++) for(int j = 0; j < num_times; j++)
		if(courses[i].get_schedule().start_time == times[j] || 
			courses[i].get_schedule().start_time == times[j]) counter++;
	if(counter == 0) return nullptr;

	Course *searched_courses = new Course[counter];
	counter = 0;
	for(int i = 0; i < num_courses; i++) for(int j = 0; j < num_times; j++)
		if(courses[i].get_schedule().start_time == times[j] ||
			courses[i].get_schedule().start_time == times[j]) searched_courses[counter++] = courses[i];

	return searched_courses;

}

/**
**	Function: add to catalog
**	Description: adds course to catalog
**	Parameters: course to add
**/
void University::add_to_catalog(Course new_course) {

	Course *temp = new Course[num_courses + 1];
	for(int i = 0; i < num_courses; i++) temp[i] = courses[i];
	temp[num_courses] = new_course;
	set_courses(temp, num_courses + 1);

}

/**
**	Function: remove from catalog
**	Description: removes course from catalog
**	Parameters: index of course to remove
**/
void University::remove_from_catalog(int n) {

	Course *temp = new Course[num_courses - 1];
	for(int i = 0; i < num_courses; i++) if(i != n) temp[(i < n ? i : i - 1)] = courses[i];
	set_courses(temp, num_courses - 1);

}

/**
**	Function: get index
**	Description: gets index of course in array
**	Parameters: name of course, term of course
**/
int University::get_index(string name, string term) {

	for(int i = 0; i < num_courses; i++) if(courses[i].get_name() == name 
		&& courses[i].get_schedule().term == term) 
			return i;

	return -1;

}

/**
**	Function: unenroll student
**	Description: removes student from roster
**	Parameters: student id, course name, course term
**/
void University::unenroll_student(string student_id, string course_name, string course_term) {

	fstream file;
	file.open("enrollment.txt");
	if(!file.is_open()) {
		cout << "Error: no enrollment file found" << endl;
		return;
	}

	bool found = false;
	string file_contents = "", name, id, course, term;
	int num_lines = get_num_lines("enrollment.txt");
	for(int i = 0; i < num_lines; i++) {
		file >> name >> id >> course >> term;
		if(id == student_id && course == course_name && term == course_term) found = true;
		else file_contents += (name + " " + id + " " + course + " " + term + "\n");
	}

	file.close();

	file.open("enrollment.txt", fstream::out | fstream::trunc);
	file << file_contents;

	file.close();

	if(!found) cout << "Error: student not found" << endl;

}

/**
**	Function: load info
**	Description: loads university info from file
**	Parameters: path to file
**/
void University::load_info(string info_file_path) {

	if(!check_file_validity(info_file_path)) return;

	ifstream file;
	file.open(info_file_path);

	getline(file, name);
	getline(file, address);
	getline(file, current_term);

}

/**
**	Function: print
**	Description: prints university info
**	Parameters: none
**/
void University::print() const {

	cout << name << " " << address << " " << current_term << endl;

}

/**
**	Function: log info
**	Description: records course information to text file
**	Parameters: none
**/
void University::log_info() {

	ofstream file;
	file.open("courses2.txt");
	file.clear();
	for(int i = 0; i < num_courses; i++) {
		file << courses[i].get_name() << " " << courses[i].get_teacher() << " "
			<< courses[i].get_schedule().term << " " << courses[i].get_schedule().days
			<< " " << courses[i].get_schedule().start_time << " "
			<< courses[i].get_schedule().end_time << " " << courses[i].get_schedule().location
			<< " " << courses[i].get_current_enrollment() << " ";
		for(int j = 0; j < courses[i].get_current_enrollment(); j++) file << courses[i].get_roster()[j] << " ";
		file << endl;
	}

}
