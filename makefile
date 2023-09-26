#Ricardo Varona
#CPSC 1071
#4/25/2023
#Purpose of file is to work as a functioning makefile

#Compiles needed files uses gcc to compile in c 
compile:
	gcc Quiddler.c Project-4.c -o Project-4.out
#Driver contains the main and needs .out respectively
run:
	./Project-4.out
#clean included to clear terminal when needed
clean:
	rm *.out
