#include<iostream>
using namespace std;

enum tokenCode{
    UNDEF = 0

    // keyWord
    KW_INT,
    KW_DOUBLE,
    KW_LOOP,
    KW_RETURN,
    KW_PRIVATE,
    KW_PUBLIC,
    KW_CLASS,
    KW_EXTENDS,
    KW_BREAK,
    KW_CONTINUE,
    KW_MAIN,
    KW_FOR,

    TK_PLUS,	//+
	TK_MINUS,	//-
	TK_STAR,	//*
	TK_DIVIDE,	///
	TK_ASSIGN,	//=
	TK_EQ,		//==
	TK_LT,		//<
	TK_LEQ,		//<=
	TK_GT,		//>
	TK_GEQ,		//>=
    TK_UNE      //!=
};