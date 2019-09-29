flex --outfile=../src/parser/scanner.cpp --case-insensitive --header-file=../include/parser/scanner.h ../include/parser/scanner.l
lemon -T../src/parser/lempar.c ../include/parser/parser.y -s
mv ../include/parser/parser.c ../src/parser/parser.cpp

