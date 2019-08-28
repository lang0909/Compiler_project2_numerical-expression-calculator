samLexer: samLexer.l
	flex samLexer.l
	gcc parser.c lex.yy.c -lfl

.PHONY: clean
clean:
	rm -rf *.yy.c ./a.out
