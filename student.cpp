#include "student.h"

Student::Student() {
	cout << "Вызван конструктор без параметров Student" << endl;
	name = new char[21];
	name[0] = '\0';
	group = new char[6];
	group[0] = '\0';
	grades = new char[5];
	grades[0] = '\0';
	averageGrade = 0;
};

Student::Student(int n, int g, int gs) {
	cout << "Вызван конструктор с параметрами Student" << endl;
	name = new char[n + 1];
	name[0] = '\0';
	group = new char[g + 1];
	group[0] = '\0';
	grades = new char[gs + 1];
	grades[0] = '\0';
	averageGrade = 0;
};
Student::Student(Student* orig) {
	cout << "Вызван конструктор копирования Student" << endl;
	name = copyWord(orig->name);
	group = copyWord(orig->group);
	grades = copyWord(orig->grades);
	averageGrade = orig->averageGrade;
};
Student::~Student() {
	cout << "Вызван деструктор Student" << endl;
	delete[] name;
	delete[] group;
	delete[] grades;
};



char* Student::getName() {
	return name;
}
void Student::setName(char* n) {
	delete[] name;
	name = copyWord(n);
}
char* Student::getGroup() {
	return group;
}
void Student::setGroup(char* g) {
	delete[] group;
	group = copyWord(g);
}
char* Student::getGrades() {
	return grades;
}
void Student::setGrades(char* gs) {
	delete[] grades;
	grades = copyWord(gs);
}



void Student::setAverageGrade() {
	int i = 0;
	float sum = 0;
	while (grades[i] != '\0') sum += grades[i++] - '0';
	sum /= i;
	averageGrade = sum;
	return;
}
float Student::getAverageGrade() {
	return averageGrade;
};


bool Student::operator < (Student& r) {
	return this->getAverageGrade() < r.getAverageGrade();
}; // сравнение средних оценок

Student& Student::operator = (Student& r) {
	this->setName(copyWord(r.getName()));
	this->setGroup(copyWord(r.getGroup()));
	this->setGrades(copyWord(r.getGrades()));
	this->setAverageGrade();
	return *this;
};

ostream& operator << (ostream& os, const Student& dt) {
	int l = getLength(dt.name);
	os << "Студент         -  ";
	for (int i = 0; i < l - 3; ++i) os << dt.name[i];
	os << " " << dt.name[l - 3] << ". " << dt.name[l - 2] << ". " << endl;
	os << "Группа          -  ";
	os << dt.group << endl;
	os << "Оценки          -  ";
	for (int i = 0; dt.grades[i] != '\0'; i++) os << dt.grades[i] << ' ';
	os << endl;
	os << "Средняя оценка  -  " << dt.averageGrade << endl;
	return os;
};
