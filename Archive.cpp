#include "Archive.h"

ostream& operator << (ostream& os, const Archive& dt) {
	for (int i = 0; i < dt.size; ++i) os << "#" << i + 1 << endl << *(dt.list[i]) << endl;
	return os;
};

Archive::Archive() {
	cout << "Вызван конструктор без параметров Archive" << endl;
	size = 0;
	limit = 5;
	list = new Student * [limit];
};
Archive::Archive(int count) {
	cout << "Вызван конструктор с параметрами Archive" << endl;
	size = count;
	limit = count + 5;
	list = new Student * [limit];
};
Archive::Archive(Archive* orig) {
	cout << "Вызван конструктор копирования Archive" << endl;
	size = orig->getSize();
	limit = orig->getLimit();
	list = new Student * [limit];
	for (int i = 0; i < size; i++) {
		list[i] = new Student(orig->list[i]);
	}
};
Archive::~Archive() {
	cout << "Вызван деструктор Archive" << endl;
	for (int i = 0; i < size; i++)
		delete list[i];
	delete[] list;
};

void Archive::sortByAverageGrade() {
	Student* t;
	for (int i = 0; i < size - 1; i++) {
		for (int j = 0; j < size - 1 - i; j++) {
			if ((*list[j]) < (*list[j + 1])) {
				t = list[j];
				list[j] = list[j + 1];
				list[j + 1] = t;
			}
		}
	}
};
void Archive::showSortedList() {
	Archive* sorted = new Archive(this);
	sorted->sortByAverageGrade();
	cout << "Отсортированный список студентов" << endl;
	cout << *sorted << endl;
	delete sorted;
};
void Archive::showWith4and5() {
	bool flag4, flag5;
	int num = 0;
	char* buf;
	for (int i = 0; i < size; i++) {
		flag4 = 0;
		flag5 = 0;
		buf = copyWord(list[i]->getGrades());
		for (int j = 0; buf[j] != '\0'; j++) {
			int grade = buf[j] - '0';
			if (grade == 4)
				flag4 = 1;
			if (grade == 5)
				flag5 = 1;
		}
		if (flag4 && flag5) {
			if (num == 0) {
				cout << "Студенты, имеющие 4 и 5:" << endl;
			}
			num++;
			cout << '#' << num << endl;
			cout << *(list[i]) << endl;
		}
	}
	if (num == 0) {
		cout << "Студентов, имеющих 4 и 5, нет в списке" << endl;
	}
};



Student** Archive::getList() {
	return list;
};
void Archive::setList(Student** orig) {
	delete[] list;
	list = orig;
};
int Archive::getSize() {
	return size;
};
void Archive::setSize(int s) {
	size = s;
};
int Archive::getLimit() {
	return limit;
};
void Archive::setLimit(int l) {
	limit = l;
};
void Archive::checkLimit() {
	if (size == limit) {
		limit += 5;
		Student** copy = new Student * [limit];
		for (int i = 0; i < size; ++i) {
			copy[i] = new Student;
			(*copy[i]) = (*list[i]);
		}
		setList(copy);
	}
};

Archive& Archive::operator ++ () {
	list[size++] = new Student;
	int buf_limit = 31;
	char* buffer = new char[buf_limit];
	try {
		cout << "Добавление студента в список" << endl;
		// Запись имени студента
		cout << "Введите фамилию и инициалы студента (Фамилия И. О.)" << endl;
		int i = 0;
		while ((buffer[i] = getchar()) != '\n' && i++ < buf_limit - 1);
		buffer[i] = '\0';
		if (!(('A' <= buffer[0] && 'Z' >= buffer[0]) || ('А' <= buffer[0] && 'Я' >= buffer[0])))
			throw "Ошибка при записи фамилии";
		int j = 1;
		while ((('a' <= buffer[j] && 'z' >= buffer[j]) || ('а' <= buffer[j] && 'я' >= buffer[j]))) j++;
		if (buffer[j] != ' ')
			throw "Ошибка при записи фамилии";
		if (!(('A' <= buffer[j + 1] && 'Z' >= buffer[j + 1]) || ('А' <= buffer[j + 1] && 'Я' >= buffer[j + 1]))
			|| buffer[j + 2] != '.' || buffer[j + 3] != ' ' ||
			!(('A' <= buffer[j + 4] && 'Z' >= buffer[j + 4]) || ('А' <= buffer[j + 4] && 'Я' >= buffer[j + 4]))
			|| buffer[j + 5] != '.' || buffer[j + 6] != '\0')
			throw "Ошибка при записи инициалов";
		buffer[j] = buffer[j + 1];
		buffer[j + 1] = buffer[j + 4];
		buffer[j + 2] = '\0';
		list[size - 1]->setName(buffer);
		// Запись группы
		cout << "Введите группу студента" << endl;
		i = 0;
		while ((buffer[i] = getchar()) != '\n' && i++ < buf_limit - 1);
		buffer[i] = '\0';
		list[size - 1]->setGroup(buffer);
		//Запись оценок
		cout << "Введите оценки студента через пробел" << endl;
		i = 0;
		while ((buffer[i] = getchar()) != '\n' && i++ < buf_limit - 1);
		buffer[i] = '\0';
		j = 0;
		for (;;) {
			if (!('1' <= buffer[j] && '5' >= buffer[j]))
				throw "Ошибка при записи оценок";
			if (buffer[j + 1] != ' ' && buffer[j + 1] != '\0')
				throw "Ошибка при записи оценок";
			buffer[j / 2] = buffer[j];
			if (buffer[j + 1] == '\0')
				break;
			j += 2;
		}
		buffer[(j / 2) + 1] = '\0';
		list[size - 1]->setGrades(buffer);
		list[size - 1]->setAverageGrade();
		cout << "Студент добавлен в список" << endl;
		checkLimit();
	}
	catch (const char* ex) {
		cout << ex << endl;
		cout << "Добавление студента в список отменяется" << endl;
		--size;
		delete list[size];
	}
	delete[] buffer;
	return *this;
};      // добавить студента в архив
Archive& Archive::operator -- () {
	delete list[size--];
	return *this;
};      // убрать последнего добаленного студента из архива
Archive& Archive::operator -= (int a) {
	delete list[a - 1];
	for (int i = a; i < size; i++) {
		list[i - 1] = list[i];
	}
	list[size--] = nullptr;
	return *this;
};      // убрать студента под заданным номером
