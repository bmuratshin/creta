/* Copyright 2002 Rene Rivera.
** Distributed under the Boost Software License, Version 1.0.
** (See accompanying file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
*/

/*
# yyacc - yacc wrapper
#
# Allows tokens to be written as `literal` and then automatically
# substituted with #defined tokens.
#
# Usage:
#    yyacc file.y filetab.h file.yy
#
# inputs:
#    file.yy        yacc grammar with ` literals
#
# outputs:
#    file.y        yacc grammar
#    filetab.h    array of string <-> token mappings
#
# 3-13-93
#    Documented and p moved in sed command (for some reason,
#    s/x/y/p doesn't work).
# 10-12-93
#    Take basename as second argument.
# 12-31-96
#    reversed order of args to be compatible with GenFile rule
# 11-20-2002
#    Reimplemented as a C program for portability. (Rene Rivera)
*/


//int cnt = 0;
//https://ru.wikipedia.org/wiki/%D0%A4%D1%83%D0%BD%D0%BA%D1%86%D0%B8%D1%8F_%D0%90%D0%BA%D0%BA%D0%B5%D1%80%D0%BC%D0%B0%D0%BD%D0%B0
int a(int m, int n)
{
  int tmp;
//  double cc = 12.5;
//  print(m);
//  print(n);
//  cnt++;
  if (m == 0)
    {
	return n + 1 + tmp;
    }
  if (n == 0)
    {
	return a(m - 1, 1);
    }
  return a(m - 1, a(m, n - 1));
}

int main()
{
  int r =
    (a(3, 10));//3,10));
  return 0;
}

