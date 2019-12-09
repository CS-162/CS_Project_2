/**
**	Program: Driver File
**	Author: Austin Chayka
**	Date: 20.27.2019
**	Description: Main driver file
**/

#include <iostream>
#include <fstream>

#include "util.h"
#include "University.h"
#include "teacher.h"

using namespace std;

/**
**	Function: run course enrollment
**	Description: gets student information from user and enrolls them
**		in a course
**	Parameters: university of enrollment
**/
void run_course_enrollment(University &university) {

	string name, term;
	cout << "\nEnter course name:";
	cin >> name;
	cout << "Enter course term:";
	cin >> term;
	int i = university.get_index(name, term);
	if(i == -1) {
		cout << "Error: no class found" << endl;
	} else {
		string first_name, last_name, id;
		cout << "Enter first name:";
		cin >> first_name;
		cout << "Enter last name:";
		cin >> last_name;
		cout << "Enter student ID:";
		cin >> id;
		university.get_courses()[i].enroll_student(id);
		ofstream file;
		file.open("enrollment.txt", ofstream::out | ofstream::app);
		file << first_name  << "_" << last_name << " " << id << " " 
			<< university.get_courses()[i].get_name() << " " 
			<< university.get_courses()[i].get_schedule().term << endl;
		file.close();
	}

}

/**
**	Function: run edit course
**	Description: gets new course information from user and edits 
**		the desired course
**	Parameters: university of enrollment
**/
void run_edit_course(University &university) {

	string name, term;
	cout << "\nEnter course name:";
	cin >> name;
	cout << "Enter course term:";
	cin >> term;
	int i = university.get_index(name, term);
	if(i == -1) cout << "Error: course not found" << endl;
	else {
		string input;
		cout << "Enter \"NA\" in any field to keep entry the same" << endl;
		cout << "Enter new course name:";
		cin >> input;
		if(input != "NA") university.get_courses()[i].set_name(input);
		cout << "Enter new course teacher:";
		cin >> input;
		if(input != "NA") university.get_courses()[i].set_teacher(input);
		schedule s = university.get_courses()[i].get_schedule();
		cout << "Enter new course term:";
		cin >> input;
		if(input != "NA") s.term = input;
		cout << "Enter new course days:";
		cin >> input;
		if(input != "NA") s.days = input;
		cout << "Enter new course start time:";
		cin >> input;
		if(input != "NA") s.start_time = input;
		cout << "Enter new course end time:";
		cin >> input;
		if(input != "NA") s.end_time = input;
		cout << "Enter new course location:";
		cin >> input;
		if(input != "NA") s.location = input;
		university.get_courses()[i].set_schedule(s);
	}

}

/**
**	Function: run course addition
**	Description: gets new course information and adds that course
**		to the university
**	Parameters: university of enrollment
**/
void run_course_addition(University &university) {

	Course course;
	schedule new_schedule;
	string input;
	cout << "\nEnter Course name:";
	cin >> input;
	course.set_name(input);
	cout << "Enter Course teacher:";
	cin >> input;
	course.set_teacher(input);
	cout << "Enter Course term:";
	cin >> input;
	new_schedule.term = input;
	cout << "Enter Course days:";
	cin >> input;
	new_schedule.days = input;
	cout << "Enter Course start time:";
	cin >> input;
	new_schedule.start_time = input;
	cout << "Enter Course end time:";
	cin >> input;
	new_schedule.end_time = input;
	cout << "Enter Course location:";
	cin >> input;
	new_schedule.location = input;
	course.change_course_time(new_schedule);
	university.add_to_catalog(course);

}

/**
**	Function: run course removal
**	Description: finds desired course and removes it
**	Parameters: university of enrollment
**/
void run_course_removal(University &university) {

	string name, term;
	cout << "\nEnter course name:";
	cin >> name;
	cout << "Enter course term:";
	cin >> term;
	int i = university.get_index(name, term);
	if(i == -1) cout << "Error: course not found" << endl;
	else university.remove_from_catalog(i);

}

/**
**	Function: run search
**	Description: gets search criteria and prints matching courses
**	Parameters: array of courses, number of courses
**/
void run_search(Course *searched_courses, int num_courses) {

	cout << "\n(1) Search by term\n(2) Search by time" << endl;
	int choice = get_number_choice(1, 2);

	Course *temp = nullptr;

	switch(choice) {

		case 1:
			{
				string term;
				cout << "Enter term:";
				cin >> term;
				temp = Course::search_courses_by_term(searched_courses, num_courses, term);
				num_courses = Course::get_search_by_term_num(searched_courses, num_courses, term);
			}
			break;

		case 2:
			{
				string time;
				cout << "Enter time:";
				cin >> time;
				temp = Course::search_courses_by_time(searched_courses, num_courses, time);
				num_courses = Course::get_search_by_time_num(searched_courses, num_courses, time);
			}
			break;

	}
	if(temp != nullptr) {
		cout << endl;
		for(int i = 0; i < num_courses; i++)
			temp[i].print();
	}
	else cout << "Error: no courses found" << endl;

}

/**
**	Function: run login
**	Description: gets login information and verifies it
**	Parameters: array of teachers, number of teachers
**/
void run_login(teacher *teachers, int num_teachers) {

	string input;
	cout << "\nEnter ID:";
	cin >> input;
	bool valid = false;
	while(!valid) {
		if(!is_num(input)) {
			cout << "Error: input was not a number. Enter again:";
			cin >> input;
		} else if(find_id(teachers, stoi(input), num_teachers) == -1) {
			cout << "Error: ID not found. Enter again:";
			cin >> input;
		} else valid = true;
	}
	int index = find_id(teachers, stoi(input), num_teachers), id = stoi(input);
	cout << "Enter Password:";
	cin >> input;
	valid = false;
	while(!valid) {
		if(!login_valid(teachers, index, id, input, num_teachers)) {
			cout << "Error: incorrect password. Enter again:";
			cin >> input;
		} else valid = true;
	}
	
}

/**
**	Function:  main
**	Description: driver funtion
**	Parameters: none required
**/
int main(int argc, char *argv[]) {

	int num_teachers = get_num_lines("teachers.txt");
	teacher *teachers = create_teachers("teachers.txt");
	if(teachers == nullptr)  return 1;

	int num_courses = get_num_lines("courses.txt");
	Course *courses = Course::create_courses("courses.txt");
	if(courses == nullptr) return 2;

	University university;
	university.load_info("university.txt");
	university.set_teachers(teachers, num_teachers);
	university.set_courses(courses, num_courses);

	bool running = true;
	while(running) {

		cout << "(1) Student\n(2) Teacher\n(3) Quit" << endl;
		int choice = get_number_choice(1, 3);
		if(choice == 3) {
			running = false;
			break;
		}

		int access_flag = 0;
		if(choice == 2) {
			run_login(teachers, num_teachers);
			access_flag = 1;
		}
		
		bool choosing = true;
		while(choosing) {
			switch(access_flag) {

				case 0:
					cout << "\n(1) View Courses\n(2) Search\n(3) Enroll\n(4) Log Out" << endl;
					choice = get_number_choice(1, 4);
					switch(choice) {
						case 1:
							cout << endl;
							for(int i = 0; i < num_courses; i++) courses[i].print();
							break;
						case 2:
							run_search(university.get_courses(), university.get_num_courses());
							break;
						case 3:
							run_course_enrollment(university);
							break;
						case 4:
							choosing = false;
							break;
					}
					break;

				case 1:
					cout << "\n(1) View Courses\n(2) Search\n(3) Edit Course\n(4) Add Course"
						<< "\n(5) Remove Course\n(6) View Enrollment \n(7) Unenroll Student\n(8) Log Out" << endl;
					choice = get_number_choice(1, 8);
					switch(choice) {
						case 1:
							cout << endl;
							for(int i = 0; i < num_courses; i++) courses[i].print();
							break;
						case 2:
							run_search(university.get_courses(), university.get_num_courses());
							break;
						case 3:
							run_edit_course(university);
							break;
						case 4:
							run_course_addition(university);
							cout << endl;
							Course::print_courses(university.get_courses(), university.get_num_courses());
							cout << endl;
							break;
						case 5:
							run_course_removal(university);
							cout << endl;
							Course::print_courses(university.get_courses(), university.get_num_courses());
							cout << endl;
							break;
						case 6:
							cout << endl;
							print_file_contents("enrollment.txt");
							break;
						case 7:
							{
								string id, course_name, term;
								cout << "Enter student ID:";
								cin >> id;
								cout << "Enter course name:";
								cin >> course_name;
								cout << "Enter course term:";
								cin >> term;
								University::unenroll_student(id, course_name, term);
							}
							break;
						case 8:
							choosing = false;
							break;
					}
					break;

			}
		}

	}

	university.log_info();
	
	return 0;

}