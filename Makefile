.SUFFIXES: .o .cpp .x

CFLAGS = -ggdb -std=c++17
objects =  ttTree.o main.o

main.out: $(objects)
	g++ $(CFLAGS) -o main.out $(objects)

.cpp.o:
	g++ $(CFLAGS) -c $< -o $@

ttTree.o: ttTree.cpp ttTree.h

main.o: main.cpp ttTree.h

clean:
	rm -fr *.o *~ *.x
