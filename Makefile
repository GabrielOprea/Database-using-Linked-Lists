EXE=tema1

build: $(EXE)
run: $(EXE)
	./$(EXE)
$(EXE): database.o console.o functions.o
	gcc -g -Wall -Wextra database.o console.o functions.o -o $(EXE)
database.o: database.c
	gcc -g -Wall -Wextra -c database.c
console.o: console.c
	gcc -g -Wall -Wextra -c console.c
functions.o: functions.c
	gcc -g -Wall -Wextra -c functions.c
clean:
	rm tema1 *.o
