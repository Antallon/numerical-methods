# Имя исполняемого файла
all: prog

# Правило для сборки исполняемого файла
# prog: main.o solve.o
# 	g++  -o prog main.o solve.o
prog: main2.o integration.o
	g++  -o prog main2.o integration.o

# Правило для создания объектного файла main.o
main2.o: main2.cpp integration.hpp
	g++  -O3 -c main2.cpp

# Правило для создания объектного файла solve.o
integration.o: integration.cpp integration.hpp
	g++  -O3 -c integration.cpp

# Правило для очистки сгенерированных файлов
clean:
	rm -f *.o prog