library: Librarian.o Book.o Member.o LibrarianFunctions.o Main.o
	g++ Librarian.o Book.o Member.o LibrarianFunctions.o Main.o -o library

Main.o: Main.cpp
	g++ -c Main.cpp

Librarian.o: Librarian.cpp Librarian.h
	g++ -c Librarian.cpp

Book.o: Book.cpp Book.h
	g++ -c Book.cpp

Member.o: Member.cpp Member.h
	g++ -c Member.cpp

LibrarianFunctions.o: LibrarianFunctions.cpp LibrarianFunctions.h
	g++ -c LibrarianFunctions.cpp

clean:
	rm -f *.o library.exe

