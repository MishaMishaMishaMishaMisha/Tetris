#pragma once

#include <fstream>
#include <string>
#include "Globals.h"
#include <vector>

// ����� ��� ������ � ������ �������
class FileManager
{
private:
	std::string path = "";
	std::string filename = "record.txt";
	std::ofstream output_stream; // ������
	std::ifstream input_stream;  // ������

public:
	void setPath(std::string path);
	void setFileName(std::string fileName);

	// ������� ����� � ������ ����� ������
	void writeLine(std::string line);

	// ��������� ������ � ������� ��
	std::string readLine();

	// ������� ������ �� ����� (�����)
	std::vector<unsigned int> splitIntoNumbers(const std::string& str);

	// ����� �� ������ �������������� � �����
	bool isNumber(const std::string& str);


	// ���������� ����� ������ (�� �����������)
	void addNewRecord(GameScore score);

	// ��������� ��� (�� ��������)
	void readAll();
};

