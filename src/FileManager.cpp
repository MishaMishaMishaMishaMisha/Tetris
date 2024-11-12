#include "FileManager.h"

void FileManager::setPath(std::string path)
{
	this->path = path;
}
void FileManager::setFileName(std::string fileName)
{
	this->filename = fileName;
}

void FileManager::writeLine(std::string line)
{
	output_stream.open(path + filename);

	if (!output_stream.is_open())
	{
		//std::cout << "file ne otkrilsya\n";
	}
	else
	{
		output_stream << line;
	}

	output_stream.close();
}

std::string FileManager::readLine()
{
	std::string line = "";

	input_stream.open(path + filename);
	if (!input_stream.is_open())
	{
		//std::cout << "file ne otkrilsya\n";
		return line;
	}
	else
	{
		std::getline(input_stream, line);
	}
	
	input_stream.close();

	return line;
}

bool FileManager::isNumber(const std::string& str) 
{
	try 
	{
		std::size_t pos;
		int temp = std::stoi(str, &pos);
		return pos == str.length(); // Проверка: вся строка была числом
	}
	catch (const std::invalid_argument&) 
	{
		return false; // Не удалось преобразовать, значит это не число
	}
	catch (const std::out_of_range&) 
	{
		return false; // Число выходит за пределы диапазона int
	}
}

std::vector<unsigned int> FileManager::splitIntoNumbers(const std::string& str)
{
	std::vector<unsigned int> numbers;
	size_t start = 0;
	size_t end = str.find(' ');

	while (end != std::string::npos) 
	{
		std::string word = str.substr(start, end - start);
		if (isNumber(word)) 
		{
			numbers.push_back(std::stoi(word)); // Преобразуем в int
		}
		start = end + 1;
		end = str.find(' ', start);
	}

	// Добавляем последнее слово
	std::string lastWord = str.substr(start);
	if (isNumber(lastWord)) 
	{
		numbers.push_back(std::stoi(lastWord));
	}

	return numbers;
}




//!!!!!!
void FileManager::addNewRecord(GameScore score)
{
	output_stream.open(path + filename, std::ofstream::app);

	if (!output_stream.is_open())
	{
		//std::cout << "file ne otkrilsya\n";
	}
	else
	{

	}

	output_stream.close();
}

void FileManager::readAll()
{
	input_stream.open(path + filename);

	if (!input_stream.is_open())
	{
		//std::cout << "file ne otkrilsya\n";
	}
	else
	{
		std::string str;
		int count = 0;
		while (!input_stream.eof())
		{
			str = "";
			input_stream >> str;
			//std::cout << str << " ";

			count++;
			if (count % 3 == 0)
			{
				//std::cout << std::endl;
			}
		}

	}

	input_stream.close();
}

