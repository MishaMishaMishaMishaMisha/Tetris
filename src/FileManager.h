#pragma once

#include <fstream>
#include <string>
#include "Globals.h"
#include <vector>

// класс для записи и чтения рекорда
class FileManager
{
private:
	std::string path = "";
	std::string filename = "record.txt";
	std::ofstream output_stream; // запись
	std::ifstream input_stream;  // чтение

public:
	void setPath(std::string path);
	void setFileName(std::string fileName);

	// очистка файла и запись новой строки
	void writeLine(std::string line);

	// прочитать строку и вернуть ее
	std::string readLine();

	// разбить строку на слова (числа)
	std::vector<unsigned int> splitIntoNumbers(const std::string& str);

	// можно ли строку конвертировать в число
	bool isNumber(const std::string& str);


	// добавление новой записи (не реализовано)
	void addNewRecord(GameScore score);

	// прочитать все (не доделано)
	void readAll();
};

