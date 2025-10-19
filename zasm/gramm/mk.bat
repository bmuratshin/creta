rem #gperf --ignore-case -LC++ -D -aCGptr -Kkeyword -k1,2,3,4,5,6,$ -Nlex_hash_kw sqlwords.gperf >sqlwords.inl 

C:\cygwin64\bin\flex.exe -d -8 -R -Pzasm --yylineno --nounistd --header-file=zasm_scanner.h -ozasm_scanner.cpp zasm.l  

C:\cygwin64\bin\bison zasm.y -pzasm -t -r all -ozasm_parser.cpp --defines=zasm_parser.h
