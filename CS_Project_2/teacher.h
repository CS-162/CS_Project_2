#ifndef TEACHER_H
#define TEACHER_H

#include <string>

using namespace std;

struct teacher{

	int id;
	string password;
	string first_name;
	string last_name;

};

teacher * create_teachers(string);
int find_id(teacher *, int, int);
bool login_valid(teacher *, int, int, string, int);

void print_info(const teacher *, int);

#endif