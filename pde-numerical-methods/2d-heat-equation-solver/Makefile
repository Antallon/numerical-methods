# Имя исполняемого файла
all: prog

# Правило для сборки исполняемого файла
prog: main4.o solve4.o
	g++  -o prog main4.o solve4.o

# Правило для создания объектного файла main.o
main4.o: main4.cpp solve4.hpp
	g++  -O3 -c main4.cpp

# Правило для создания объектного файла solve.o
solve4.o: solve4.cpp solve4.hpp
	g++  -O3 -c solve4.cpp

# Правило для очистки сгенерированных файлов
clean:
	rm -f *.o prog

# Имя исполняемого файла
# all: prog

# # Правило для сборки исполняемого файла
# prog: rofl_main.o rofl.o
# 	g++  -o prog rofl_main.o rofl.o

# # Правило для создания объектного файла main.o
# rofl_main.o: rofl_main.cpp rofl.hpp
# 	g++  -O3 -c rofl_main.cpp

# # Правило для создания объектного файла solve.o
# rofl.o: rofl.cpp rofl.hpp
# 	g++  -O3 -c rofl.cpp

# # Правило для очистки сгенерированных файлов
# clean:
# 	rm -f *.o prog