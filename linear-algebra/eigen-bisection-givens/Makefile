all: prog

prog: main.o Matfill.o Matin.o  gauss.o norm.o print.o
	g++ -g main.o Matfill.o Matin.o  gauss.o norm.o print.o -o prog -O3

main.o: main.cpp Matfill.h Matin.h gauss.h norm.h print.h
	g++ -g -Wall -Wextra -Werror -pedantic -c main.cpp -O3

Matfill.o: Matfill.cpp Matfill.h
	g++ -g -Wall -Wextra -Werror -pedantic -c Matfill.cpp -O3

Matin.o: Matin.cpp Matin.h
	g++ -g -Wall -Wextra -Werror -pedantic -c Matin.cpp -O3

gauss.o: gauss.cpp gauss.h norm.h print.h
	g++ -g -Wall -Wextra -Werror -pedantic -c gauss.cpp -O3

norm.o: norm.cpp norm.h Matfill.h
	g++ -g -Wall -Wextra -Werror -pedantic -c norm.cpp -O3
        
print.o: print.cpp print.h
	g++ -g -Wall -Wextra -Werror -pedantic -c print.cpp -O3

clean:
	rm -f *.o *.dat *exe *.stackdump prog
