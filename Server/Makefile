# Переменные для компилятора и флагов
CXX = g++
CXXFLAGS = -std=c++17 -Wall
LDFLAGS = -lsfml-system -lsfml-network -lmariadb

# Имя итогового исполняемого файла
TARGET = server

# Все исходные файлы
SRC = main.cpp Server.cpp DataBase.cpp

# Правило для компиляции
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

# Очистка скомпилированных файлов
clean:
	rm -f $(TARGET)
