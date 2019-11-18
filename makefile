all: comp run

comp: jacobi.cpp
	clear
	gcc -g jacobi.cpp -o launch -lstdc++
	ctags -R .

run:
	./launch

clean:
	rm *.o comp 
