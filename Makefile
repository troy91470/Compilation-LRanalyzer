main.o: main.c arbreAnalyse.c automatePile.c LRGrammar.c read_file.c
	gcc main.c arbreAnalyse.c automatePile.c LRGrammar.c read_file.c -o LRanalyzer -Wall -g -lm
