#ifndef COURSE_H
#define Course_H

#include <string>

#include "schedule.h"

using namespace std;

class Course {

	public:

		Course();
		Course(const Course &);

		~Course();

		Course & operator=(const Course &);

		static Course * create_courses(string);
		static void print_courses(Course *, int);
		static int get_index_by_name(Course *, int, string);
		static Course * search_courses_by_term(Course *, int, string);
		static int get_search_by_term_num(Course *, int, string);
		static Course * search_courses_by_time(Course *, int, string);
		static int get_search_by_time_num(Course *, int, string);

		string get_name();
		void set_name(string);
		string get_teacher();
		void set_teacher(string);
		int get_current_enrollment();
		void set_current_enrollment(int);
		string * get_roster();
		void set_roster(string *);
		schedule get_schedule();
		void set_schedule(schedule);

		void change_course_time(schedule);
		void enroll_student(string);

		void print() const;

	private:

		string name, teacher, *roster;
		int current_enrollment;
		schedule course_time;

};

#endif