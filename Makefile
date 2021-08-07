all:
	g++ *.cpp -std=c++11 -o webbench -lpthread

clean:
	rm -rf *.o ./webbench