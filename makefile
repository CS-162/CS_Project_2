CC = g++ -std=c++11
exe_file = proj2_app
$(exe_file): Course.o teacher.o University.o util.o main.o
	$(CC) Course.o teacher.o University.o util.o main.o -o $(exe_file)
Course.o: Course.cpp
	$(CC) -c Course.cpp
teacher.o: teacher.cpp
	$(CC) -c teacher.cpp
University.o: University.cpp
	$(CC) -c University.cpp
util.o: util.cpp
	$(CC) -c util.cpp
main.o: main.cpp
	$(CC) -c main.cpp

clean:
	rm -f *.out *.o $(exe_file)