main.o: main.c ecritureLatex.c arbreAnalyse.c automatePile.c LRGrammar.c read_file.c
	gcc main.c ecritureLatex.c arbreAnalyse.c automatePile.c LRGrammar.c read_file.c -o LRanalyzer -Wall -g -lm
