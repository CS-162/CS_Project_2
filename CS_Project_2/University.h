#ifndef UNIVERSITY_H
#define UNIVERSITY_H

#include <string>

#include "teacher.h"
#include "Course.h"

using namespace std;

class University {

	public:

		University();
		University(const University &);

		~University();

		University & operator=(const University &);

		string get_name();
		void set_name(string);
		string get_adress();
		void set_address(string);
		string get_current_term();
		void set_current_term(string);
		int get_num_teachers();
		teacher * get_teachers();
		void set_teachers(teacher *, int);
		int get_num_courses();
		Course * get_courses();
		void set_courses(Course *, int);

		Course * search_courses_by_term(string, int);
		int get_search_by_term_num(string, int);
		Course * search_courses_by_times(string *, int, int);
		void add_to_catalog(Course);
		void remove_from_catalog(int);
		int get_index(string, string);
		static void unenroll_student(string, string, string);

		void load_info(string);

		void print() const;
		void log_info();

	private:

		string name, address, current_term;
		teacher *teachers;
		int num_courses, num_teachers;
		Course *courses;

};

#endif