# Run with the following commands: 
# cd "h:\\directory_of_file"
# mingw32-make         <- Run "all"
# mingw32-make clean   <- Run "clean"
# ./main.exe           <- Run the executable

all: main.o Book.o Student.o LibrarySystem.o
	g++ main.o Book.o Student.o LibrarySystem.o -o main.exe

main.o: main.cpp
	g++ -c main.cpp

Book.o: Book.cpp Book.hpp
	g++ -c Book.cpp

Student.o: Student.cpp Student.hpp
	g++ -c Student.cpp

LibrarySystem.o: LibrarySystem.cpp LibrarySystem.hpp
	g++ -c LibrarySystem.cpp

clean:
	rm -f *.o main.exe
