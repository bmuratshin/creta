rem gperf -I -7 -aCGptr -Httmhash -Kkeyword -k1,2,3,4,5,6,$ -LC++ -Nlex_hash_ttm Tutorial_D.gperf >TTM_keywords.h
C:\cygwin64\bin\flex.exe -d -8 -R --yylineno --nounistd --header-file=c_scanner.h -oc_scanner.cpp c_scanner.l  
rem flex.exe -8 -B --header-file -oc_scanner.cpp c_leh.l 
C:\cygwin64\bin\bison c_gramm.y -t -oc_parser.cpp --defines=c_parser.h
