.SUFFIXES: .o .cpp .x

CFLAGS = -ggdb -std=c++17
objects =  ttTree.o main.o trieTree.o

main.out: $(objects)
	g++ $(CFLAGS) -o main.out $(objects)

.cpp.o:
	g++ $(CFLAGS) -c $< -o $@

ttTree.o: ttTree.cpp ttTree.h

trieTree.o: trieTree.cpp trieTree.h

main.o: main.cpp ttTree.h trieTree.h

clean:
	rm -fr *.o *~ *.x
