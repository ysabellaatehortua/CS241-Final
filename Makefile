all: main dict readin

main: main.cc
	g++ -o main main.cc

dict: dict.cc
	g++ -o dict dict.cc

readin: readin.cc
	g++ -o readin readin.cc

clean: rm -f a.out main dict readin
