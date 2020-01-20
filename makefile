all: comp run

comp: jacobi.cpp
	clear
	gcc -g --coverage jacobi.cpp -o launch -lstdc++
	ctags -R .
	@gcov jacobi.cpp -m

run:
	./launch

clean:
	rm *.o comp 
