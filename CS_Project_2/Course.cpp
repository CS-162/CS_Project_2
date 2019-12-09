/**
**	Program: Course Object
**	Author: Austin Chayka
**	Date: 20.27.2019
**	Description: Implementation of the course object
**/

#include "Course.h"

#include <iostream>
#include <fstream>

#include "util.h"
#include "schedule.h"

/**
**	Function: constructor
**	Description: sets default variable values
**	Parameters: none
**/
Course::Course() {

	name = "";
	teacher = "";
	roster = nullptr;
	current_enrollment = 0;

}

/**
**	Function: copy constructor
**	Description: sets variables to the values of those in another course
**	Parameters: course to copy from
**/
Course::Course(const Course &course) {

	name = course.name;
	teacher = course.teacher;
	current_enrollment = course.current_enrollment;

	roster = new string[current_enrollment];
	if(course.roster != nullptr) for(int i = 0; i < current_enrollment; i++) {
		roster[i] = course.roster[i];
	}

	course_time = course.course_time;

}

/**
**	Function: destructor
**	Description: deallocates memory
**	Parameters: none
**/
Course::~Course() {

	if(roster != nullptr) delete[] roster;

}

/**
**	Function: assignment opperator overload
**	Description: overides default assignment opperator to copy object values
**	Parameters: object to copy from
**/
Course & Course::operator=(const Course &course) {

	name = course.name;
	teacher = course.teacher;
	current_enrollment = course.current_enrollment;

	if(roster != nullptr) delete[] roster;
	roster = new string[current_enrollment];
	if(course.roster != nullptr) for(int i = 0; i < current_enrollment; i++) {
		roster[i] = course.roster[i];
	}

	course_time = course.course_time;

	return *this;

}

/**
**	Function: create courses
**	Description: creates an array of courses from the info in a file
**	Parameters: path to file
**/
Course * Course::create_courses(string info_file_path) {
	
	if(!check_file_validity(info_file_path)) return nullptr;

	int num_courses = get_num_lines(info_file_path);
	ifstream file;
	file.open(info_file_path);

	Course *courses = new Course[num_courses];

	string name, teacher, term, days, start_time, end_time, location, student;
	int current_enrollment;
	for(int i = 0; i < num_courses; i++) {
		file >> name >> teacher >> term >> days >> start_time >> end_time >> location >> current_enrollment;
		courses[i].name = name;
		courses[i].teacher = teacher;
		courses[i].course_time.days = days;
		courses[i].course_time.start_time = start_time;
		courses[i].course_time.end_time = end_time;
		courses[i].course_time.term = term;
		courses[i].course_time.location = location;
		courses[i].current_enrollment = current_enrollment;
		if(current_enrollment < 1) continue;
		courses[i].roster = new string[current_enrollment];
		for(int j = 0; j < current_enrollment; j++) {
			file >> student;
			courses[i].roster[j] = student;
		}
	}

	file.close();

	return courses;

}

/**
**	Function: print courses
**	Description: prints the info of courses in an array
**	Parameters: array of courses, number of courses
**/
void Course::print_courses(Course *courses, int num_courses) {

	for(int i = 0; i < num_courses; i++) courses[i].print();

}

/**
**	Function: get index by name
**	Description: gets the index of a course by its name
**	Parameters: array of courses, number of courses, name to look for
**/
int Course::get_index_by_name(Course *courses, int num_courses, string name) {

	for(int i = 0; i < num_courses; i++) if(courses[i].get_name() == name) return i;

	return -1;

}

/**
**	Function: search courses by term
**	Description: gets an array of search results
**	Parameters: array of courses, number of courses, term to search for
**/
Course * Course::search_courses_by_term(Course *courses, int num_courses, string term) {

	if(courses == nullptr) return nullptr;

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
**	Function: get search courses by term number
**	Description: gets number of search results
**	Parameters: array of courses, number of courses, term to search for
**/
int Course::get_search_by_term_num(Course *courses, int num_courses, string term) {

	int counter = 0;
	for(int i = 0; i < num_courses; i++) if(courses[i].get_schedule().term == term) counter++;

	return counter;

}

/**
**	Function: search courses by time
**	Description: gets an array of search results
**	Parameters: array of courses, number of courses, time to search for
**/
Course * Course::search_courses_by_time(Course *courses, int num_courses, string time) {

	if(courses == nullptr) return nullptr;

	int counter = 0, increment = 0;
	for(int i = 0; i < num_courses; i++)
		if(courses[i].get_schedule().start_time == time ||
			courses[i].get_schedule().end_time == time) counter++;
	if(counter == 0) return nullptr;

	Course *searched_courses = new Course[counter];
	for(int i = 0; i < num_courses; i++)
		if(courses[i].get_schedule().start_time == time ||
			courses[i].get_schedule().end_time == time) searched_courses[increment++] = courses[i];

	return searched_courses;

}

/**
**	Function: get search courses by time number
**	Description: gets number of search results
**	Parameters: array of courses, number of courses, time to search for
**/
int Course::get_search_by_time_num(Course *courses, int num_courses, string time) {

	int counter = 0;
	for(int i = 0; i < num_courses; i++) if(courses[i].get_schedule().start_time == time ||
		courses[i].get_schedule().end_time == time) counter++;

	return counter;

}

/**
**	Function: get name
**	Description: returns name of course
**	Parameters: none
**/
string Course::get_name() {

	return name;

}

/**
**	Function: set name
**	Description: sets name of course
**	Parameters: new name
**/
void Course::set_name(string name) {

	this->name = name;

}

/**
**	Function: get teacher
**	Description: returns teacher of course
**	Parameters: none
**/
string Course::get_teacher() {

	return teacher;

}

/**
**	Function: set teacher
**	Description: sets teacher of course
**	Parameters: new teacher
**/
void Course::set_teacher(string teacher) {

	this->teacher = teacher;

}

/**
**	Function: get current enrollment
**	Description: returns current enrollment of course
**	Parameters: none
**/
int Course::get_current_enrollment() {

	return current_enrollment;

}

/**
**	Function: set current enrollment
**	Description: sets current enrollment of course
**	Parameters: new enrollment number
**/
void Course::set_current_enrollment(int enrollment) {

	this->current_enrollment = enrollment;

}

/**
**	Function: get roster
**	Description: returns roster of students
**	Parameters: none
**/
string * Course::get_roster() {

	return roster;

}

/**
**	Function: set roster
**	Description: sets roster of students
**	Parameters: new roster
**/
void Course::set_roster(string *roster) {

	delete[] this->roster;
	this->roster = roster;

}

/**
**	Function: get schedule
**	Description: returns schedule of course
**	Parameters: none
**/
schedule Course::get_schedule() {

	return course_time;

}

/**
**	Function: set schedule
**	Description: sets schedule of course
**	Parameters: new schedule
**/
void Course::set_schedule(schedule course_time) {

	this->course_time = course_time;

}

/**
**	Function: change course time
**	Description: changes current schedule
**	Parameters: schedule to copy from
**/
void Course::change_course_time(schedule course_time) {
		
			this->course_time.days = course_time.days;
			this->course_time.end_time = course_time.end_time;
			this->course_time.location = course_time.location;
			this->course_time.start_time = course_time.start_time;
			this->course_time.term = course_time.term;

}

/**
**	Function: enroll student
**	Description: adds a student to the roster
**	Parameters: student to enroll
**/
void Course::enroll_student(string student) {

	string *temp = new string[current_enrollment + 1];
	int *num_temp = new int[current_enrollment + 1];
	for(int i = 0; i < current_enrollment; i++) temp[i] = roster[i];
	temp[current_enrollment] = student;
	set_roster(temp);

}

/**
**	Function: print
**	Description: prints course info
**	Parameters: none
**/
void Course::print() const {

	cout << name << " " << teacher << " " << course_time.term << " " 
		<< course_time.days << " " << course_time.start_time << " " 
		<< course_time.end_time << endl;

}
