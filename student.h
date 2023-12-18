#pragma once
#include "Header.h"

class Student {
	friend ostream& operator << (ostream& os, const Student& dt);
public:
	Student();
	Student(int n, int g, int gs);
	Student(Student* orig);
	~Student();

	char* getName();
	void setName(char* n);
	char* getGroup();
	void setGroup(char* g);
	char* getGrades();
	void setGrades(char* gs);

	void setAverageGrade();
	float getAverageGrade();

	bool operator < (Student& r); // сравнение средних оценок
	Student& operator = (Student& r);
private:
	char* name;
	char* group;
	char* grades;
	float averageGrade;
};
