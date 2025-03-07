run: ../target/test
	../target/test

../target/test: *.c ../src/*.c ../inc/*.h
	gcc *.c ../src/*.c -I../inc/ -o ../target/test -g
