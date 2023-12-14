# Usage
#
# make       - build the application
# make test  - test the application and gcc interoperability
# make clean - remove generated files

NAME=generate-sum
CPP_FILES=generate-sum.cpp
TEST_NAME=test-sum

export CFLAGS=`llvm-config --cxxflags`
export LDFLAGS=`llvm-config --cxxflags --ldflags --libs core analysis bitwriter --system-libs`

# Replace the two lines above with the following to explicitely use LLVM 17
#export CFLAGS=`llvm-config-17 --cxxflags`
#export LDFLAGS=`llvm-config-17 --cxxflags --ldflags --libs core analysis bitwriter --system-libs`


$(NAME): $(CPP_FILES)
	g++ -o $@  $(CPP_FILES) $(LDFLAGS)

sum.ll : $(NAME)
	./$(NAME)

%.s : %.ll
	llc $^
# Replace the line above with the following to explicitely use LLVM 17
#	llc-17 $^

$(TEST_NAME)-gcc : testfunc.c testmain.c
	gcc -o $@ $^

$(TEST_NAME) : sum.s testmain.c
	gcc -o $@ $^

test: $(TEST_NAME)-gcc $(TEST_NAME) sum.ll
	./$(TEST_NAME)-gcc > testgcc.result
	@echo
	@echo === TEST GCC ===
	@echo
	@cat testgcc.result
	@echo
	@echo
	@echo === GENERATED CODE ===
	@echo
	@cat sum.ll
	@echo
	./$(TEST_NAME) > testcompiler.result
	@echo
	@echo === TEST COMPILER ===
	@echo
	@cat testcompiler.result
	@echo


clean:
	rm -f $(NAME) $(CPP_FILES:.cpp=.o) $(TEST_NAME) $(TEST_NAME)-gcc testgcc.result sum.ll sum.s testcompiler.result
