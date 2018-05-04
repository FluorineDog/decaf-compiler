SOURCEDIR := ..
LEX_SOURCES := $(shell find $(SOURCEDIR) -name '*.lex') 
CPP_HEADERS := $(shell find $(SOURCEDIR) -name '*.h') 
CPP_SOURCES := $(shell find $(SOURCEDIR) -name '*.cpp') 

all: lex.yy.c

lex.yy.c: $(LEX_SOURCES)
	echo `pwd` > lex.yy.c

.PHONY: clean
clean: 
	rm `ls | grep -v Makefile`
