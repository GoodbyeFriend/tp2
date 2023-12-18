#include "part2.h"
#include "Archive.h"
#include "Header.h"

void main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Rus");

	while (TRUE) {
		char* userWord;
		cout << "(1) Работа с объектами класса Student " << endl;
		cout << "(2) Поиск предложений в файле с заданным словом " << endl;
		cout << endl;
		cout << "(0) Выход из программы " << endl;
		int choice;
		input(&choice);
		system("CLS");
		switch (choice) {
		case 1: {
			Archive* students = new Archive;
			while (TRUE) {
				cout << "Работа с объектами класса Student" << endl;
				cout << "(1) Добавить студента в список " << endl;
				cout << "(2) Убрать определённого студента " << endl;
				cout << "(3) Вывести список студентов на экран " << endl;
				cout << "(4) Вывести отсортированный по среднему баллу список студентов на экран " << endl;
				cout << "(5) Вывести список студентов имеющих оценки 4 и 5 на экран " << endl;
				cout << "(6) Отсортировать список студентов " << endl;
				cout << endl;
				cout << "(0) Выход из программы " << endl;
				input(&choice);
				system("CLS");
				switch (choice) {
				case 1: {
					++(*students);
					break;
				}
				case 2: {
					cout << "Номер студента в списке?" << endl;
					int num;
					input(&num);
					if (num <= students->getSize() && num > 0) {
						(*students) -= num;
						cout << "Студент успешно убран" << endl;
					}
					else {
						cout << "Некорректный ввод" << endl;
					}
					break;
				}
				case 3: {
					if (students->getSize() == 0) {
						cout << "Список студентов пуст" << endl;
					}
					else {
						cout << (*students) << endl;
					}
					break;
				}
				case 4: {
					if (students->getSize() == 0) {
						cout << "Список студентов пуст" << endl;
					}
					else {
						students->showSortedList();
					}
					break;
				}
				case 5: {
					if (students->getSize() == 0) {
						cout << "Список студентов пуст" << endl;
					}
					else {
						students->showWith4and5();
					}
					break;
				}
				case 6: {
					if (students->getSize()) {
						students->sortByAverageGrade();
						cout << "Список успешно отсортирован" << endl;
					}
					else {
						cout << "Список студентов пуст" << endl;
					}
					break;
				}
				case 0: {
					delete students;
					cout << "Работа программы окончена" << endl;
					return;
				}
				default: {
					cout << "Некорректный ввод" << endl;
					break;
				}
				}
				pressEnter();
			}
		}
		case 2: {
			cout << "Введите слово для поиска:" << endl;
			userWord = getUserWord();
			findWordInFile(userWord);
			delete[] userWord;
			pressEnter();
			break;

		}
		case 0: {
			cout << "Работа программы завершена" << endl;
			return;
		}
		default: {
			cout << "Некорректный ввод" << endl;
			pressEnter();
			break;
		}
		}
	}
	return;
}
