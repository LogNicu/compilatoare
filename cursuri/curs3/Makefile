NAME=calc
GENERATED_C_FILES=$(NAME).tab.c $(NAME).yy.c
GENERATED_FILES=$(NAME).tab.c $(NAME).yy.c $(NAME).tab.h

$(NAME): $(GENERATED_FILES)
	gcc -o $@ $(GENERATED_C_FILES)

%.yy.c: %.lex
	flex -o $@ $<

%.tab.c %.tab.h: %.y
	bison -d -o $*.tab.c $<

	
clean:
	rm -f $(NAME) $(GENERATED_FILES)
