gcc -o test testmain.c testfunc.c
./test
 
g++ -o generator generate-sum.cpp `llvm-config --cxxflags --ldflags --libs core analysis bitwriter --system-libs`
./generator
ls sum.ll
 
llc sum.ll
ls sum.s
 
gcc -o test2 testmain.c sum.s
./test2
