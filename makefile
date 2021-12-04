main: sha256.h main.cpp
	g++ -o UWUdb main.cpp
	export UWUdb=/home/UWUdb/UWUdb
clear:
	rm UWUdb