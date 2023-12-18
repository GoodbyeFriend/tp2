#pragma once
#include "Header.h"

#define CHAR_LIMIT 40
#define SENTENCE_CHAR_LIMIT 200

char* getUserWord();
void findWordInFile(char* word);
bool getWordFromFile(char* word, char* sentence, int* size, ifstream& fin);
char* checkLimit(char* orig, int i, int* limit);
bool endOfSentence(char c);
bool isLetter(char c);
bool compare(char* word1, char* word2);

char* getUserWord() {
	char* buffer = new char[CHAR_LIMIT];
	int i = 0;
	while ((buffer[i] = getchar()) != '\n' && !isLetter(buffer[i]));
	if (buffer[i++] == '\n') { buffer[0] = '\0'; return buffer; }
	for (; (buffer[i] = getchar()) != '\n' && isLetter(buffer[i]) && i < CHAR_LIMIT; i++);
	buffer[i] = '\0';
	return buffer;
}

void findWordInFile(char* word) {
	ifstream fin;
	fin.open("file.txt");
	try {
		if (!fin.is_open()) {
			throw "Возникла ошибка при открытии файла";
		}
		else if (fin.eof()) {
			throw "Ошибка - файл пуст";
			fin.close();
		}
	}
	catch (const char* ex) {
		std::cout << ex << endl;
		return;
	}
	int size = 0;
	int limit = SENTENCE_CHAR_LIMIT + 1;
	char* sentence = new char[limit];
	char* buffer = new char[CHAR_LIMIT + 1];
	buffer[0] = '\0';
	sentence[0] = '\0';
	bool flag = FALSE;
	int numOfSentenses = 0;
	while (1) {
		if (!getWordFromFile(buffer, sentence, &size, fin)) {
			if (fin.eof()) {
				if (numOfSentenses == 0)
					cout << "Предложений с заданным словом нет" << endl;
				break;
			}
			if (compare(buffer, word)) flag = 1;
			if (flag) {
				numOfSentenses++;
				sentence[size] = '\0';
				cout << "Предложение #" << numOfSentenses << "  -  " << sentence << endl;
			}
			sentence[0] = '\0';
			size = 0;
			flag = FALSE;
		}
		else {
			if (compare(buffer, word)) flag = TRUE;
		}
		sentence = checkLimit(sentence, size, &limit);
	}
	fin.close();
	delete[] sentence;
	delete[] buffer;
}

bool getWordFromFile(char* word, char* sentence, int* size, ifstream& fin) {
	char c = '\0';
	while (!fin.eof() && !isLetter(c = fin.get())) {
		sentence[(*size)++] = c;
		if (endOfSentence(c)) {
			word[0] = '\0';
			sentence[(*size)++] = 'с';
			return FALSE;
		}
	};
	if (fin.eof()) {
		word[0] = '\0';
		return FALSE;
	};
	sentence[(*size)++] = c;
	word[0] = c;
	int wc = 1;
	while (!fin.eof() && isLetter(c = fin.get()) && wc < CHAR_LIMIT) {
		sentence[(*size)++] = c;
		word[wc++] = c;
	};
	if (endOfSentence(c)) {
		word[wc] = '\0';
		sentence[(*size)++] = c;
		return FALSE;
	}
	sentence[(*size)++] = c;
	word[wc] = '\0';
	return TRUE;
}


char* checkLimit(char* orig, int i, int* limit) {
	if (i >= (*limit) - CHAR_LIMIT) {
		char* copy = new char[(*limit) + SENTENCE_CHAR_LIMIT];
		(*limit) += SENTENCE_CHAR_LIMIT;
		for (int s = 0; s < i; ++s) {
			copy[s] = orig[s];
		}
		delete[] orig;
		orig = copy;
		copy = nullptr;
	}
	return orig;
}

bool endOfSentence(char c) {
	if (c == '.' || c == '!' || c == '?' || c == '…')
		return 1;
	return 0;
}

bool isLetter(char c) {
	if ((c > 'a' && c < 'z') || (c > 'A' && c < 'Z') || (c >= 'а' && c <= 'я') || (c >= 'А' && c <= 'Я'))
		return TRUE;
	else
		return FALSE;
}

bool compare(char* word1, char* word2) {
	int count = 0;
	while (word1[count] != '\0' && word2[count] != '\0') {
		if (word1[count] != word2[count])
			return 0;
		++count;
	}
	if (word1[count] != word2[count])
		return 0;
	return 1;
}
