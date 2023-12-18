#include "Header.h"

char* copyWord(char* orig) {
	int i = 0;
	char* copy = new char[getLength(orig)];
	while ((copy[i] = orig[i++]) != '\0');
	return copy;
}

int getLength(char* line) {
	int i = 0;
	while (line[i++] != '\0');
	return i;
}

void pressEnter() {
	putchar('\n');
	std::cout << "Нажмите <Enter>, чтобы продолжить..." << std::endl;
	while (getchar() != '\n')
		continue;
	std::cin.clear();
	system("CLS");
}

void input(int* num) {
	cout << "\n > ";
	cin >> *num;
	putchar('\n');
	getchar();
}
