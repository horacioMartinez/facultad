common: StringUtils.o Exception.o Socket.o Stock.o Directory.o Communication.o Protocolo.o

Communication.o: Exception.h Socket.h
	g++ -c Communication.cpp -O0 -g3 -pedantic -Wall -Wextra -Wconversion -std=c++98 `pkg-config glibmm-2.4 --cflags --libs`

Stock.o: StringUtils.h Stock.h 
	g++ -c Stock.cpp -O0 -g3 -pedantic -Wall -Wextra -Wconversion -std=c++98 `pkg-config glibmm-2.4 --cflags --libs`

Socket.o: Exception.h Socket.h
	g++ -c Socket.cpp -O0 -g3 -pedantic -Wall -Wextra -Wconversion -std=c++98

Exception.o: Exception.h
	g++ -c Exception.cpp -O0 -g3 -pedantic -Wall -Wextra -Wconversion -std=c++98

StringUtils.o: Constants.h StringUtils.h
	g++ -c StringUtils.cpp -O0 -g3 -pedantic -Wall -Wextra -Wconversion -std=c++98 `pkg-config glibmm-2.4 --cflags --libs`

Protocolo.o: Protocolo.h
	g++ -c Protocolo.cpp -O0 -g3 -pedantic -Wall -Wextra -Wconversion -std=c++98 `pkg-config glibmm-2.4 --cflags --libs`

Directory.o:  Exception.h Directory.h
	g++ -c Directory.cpp -O0 -g3 -pedantic -Wall -Wextra -Wconversion -std=c++98
clean:
	rm -f *.o
