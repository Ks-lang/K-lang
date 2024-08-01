#include<iostream>
#include<windows.h>
using namespace std;

enum tokenCode{
    UNDEF = 0,

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
    TK_UNE,     //!=

    TK_OPENPA,	//(
	TK_CLOSEPA,	//)
	TK_OPENBR,	//[
	TK_CLOSEBR,	//]
	TK_BEGIN,	//{
	TK_END,		//}
	TK_COMMA,	//,
	TK_SEMOCOLOM,	//;
    TK_COLON, //:
    TK_COLONS, //::

    TK_INT,
    TK_DOUBLE,

    TK_IDENT
};

tokenCode code = UNDEF;
const int maxKeyWord = 12;
int row = 1;
string token = "";
char keyword[][12] = {"int","double","loop","return","private","public","class","extends","break","continue","main","for"};

void print(tokenCode code){
    switch (code)
    {
    case UNDEF:
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
        cout<<"Undefined word at line "<<row<<". "<<endl;
        break;
    case KW_INT:
    case KW_DOUBLE:
    case KW_LOOP:
    case KW_RETURN:
    case KW_PRIVATE:
    case KW_PUBLIC:
    case KW_CLASS:
    case KW_EXTENDS:
    case KW_BREAK:
    case KW_CONTINUE:
    case KW_MAIN:
    case KW_FOR:
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);	//关键字为蓝色
		break;

    case TK_PLUS:	//+
	case TK_MINUS:	//-
	case TK_STAR:	//*
	case TK_DIVIDE:	// /
	case TK_ASSIGN:	//=
	case TK_EQ:		//==
	case TK_LT:		//<
	case TK_LEQ:	//<=
	case TK_GT:		//>
	case TK_GEQ:		//>=
    case TK_UNE:

    case TK_OPENPA:	//(
	case TK_CLOSEPA:	//)
	case TK_OPENBR:	//[
	case TK_CLOSEBR:	//]
	case TK_BEGIN:	//{
	case TK_END:	//}
	case TK_COMMA:	//,
	case TK_SEMOCOLOM:	//;
    case TK_COLON:     // :
    case TK_COLONS:   // ::
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);	//运算符和分隔符为绿色
		break;
    
    case TK_INT:	
	case TK_DOUBLE:	
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);	//常量为黄色
		if(token.find('.')==token.npos)
			cout << '(' << code << ',' << atoi(token.c_str()) << ")" << endl;						//单词为整型
		else
			cout << '(' << code << ',' << atof(token.c_str()) << ")" << endl;							//单词为浮点型
		return;
		break;

	case TK_IDENT:
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);	//关键字为灰色
		break;
	default:
		break;
	}
	cout << '(' << code << ',' << token << ")" << endl;
}

bool isKey(string token)
{
	for (int i = 0; i < maxKeyWord; i++)
	{
		if (token.compare(keyword[i]) == 0)
			return true;
	}
	return false;
}

int getKeyID(string token)
{
	for (int i = 0; i < maxKeyWord; i++)
	{	//关键字的内码值为keyWord数组中对应的下标加1
		if (token.compare(keyword[i]) == 0)	
			return i+1;
	}
	return -1;
}
bool isLetter(char letter)
{
	if ((letter >= 'a'&&letter <= 'z') || (letter >= 'A' &&letter <= 'Z'))
		return true;
	return false;

}

bool isDigit(char digit)
{
	if (digit >= '0'&&digit <= '9')
		return true;
	return false;
}

void lexicalAnalysis(FILE *fp)
{
	char ch;			
	while ((ch = fgetc(fp)) != EOF)	
	{
		token = ch;									
		if (ch == ' ' || ch == '\t' || ch == '\n')	
		{
			if (ch == '\n')							
				row++;
			continue;								
		}
		else if (isLetter(ch))			
		{
			token = "";					
			while (isLetter(ch) || isDigit(ch))	
			{
				token.push_back(ch);	
				ch = fgetc(fp);			
			}
			
			fseek(fp, -1L, SEEK_CUR);
			if (isKey(token))	
				code = tokenCode(getKeyID(token));
			else	
				code = TK_IDENT;	
		}
		else if (isDigit(ch))	
		{
			int isdouble = 0;	
			token = "";			
			while (isDigit(ch))	
			{
				token.push_back(ch);	
				ch = fgetc(fp);				
				if (ch == '.'&& isdouble == 0)
				{
					//小数点下一位是数字
					if (isDigit(fgetc(fp)))
					{
						isdouble = 1;		
						fseek(fp, -1L, SEEK_CUR);		
						token.push_back(ch);			
						ch = fgetc(fp);			
					}
				}
			}
			if (isdouble == 1)
				code = TK_DOUBLE;
			else
				code = TK_INT;				
			fseek(fp, -1L, SEEK_CUR);
		}
		else switch (ch)
		{	
		case '+': code = TK_PLUS;		//+		
			break;
		case '-': code = TK_MINUS;		//-
			break;
		case '*': code = TK_STAR;		//*
			break;
		case '/': code = TK_DIVIDE;		// /
			break;
		case '=':
		{
			ch = fgetc(fp);				//超前读取'='后面的字符
			if (ch == '=')				//==等于号
			{
				token.push_back(ch);	//将'='后面的'='存入token中
				code = TK_EQ;			//单词为"=="
			}		
			else {						//=赋值运算符
				code = TK_ASSIGN;		//单词为"="
				fseek(fp, -1L, SEEK_CUR);	//将超前读取的字符重新读取
			}
		}
		break;
		case '<':		
		{
			ch = fgetc(fp);				//超前读取'<'后面的字符
			if (ch == '=')				//<=小于等于号
			{
				token.push_back(ch);	//将'<'后面的'='存入token中
				code = TK_LEQ;			//单词为"<="
			}		
			else {						//<小于号
				code = TK_LT;			//单词为"<"
				fseek(fp, -1L, SEEK_CUR);	//将超前读取的字符重新读取
			}
		}
		break;
		case '>':
		{
			ch = fgetc(fp);				//超前读取'>'后面的字符
			if (ch == '=')				//>=大于等于号
			{
				token.push_back(ch);	//将'>'后面的'='存入token中
				code = TK_GEQ;			//单词为">="
			}	
			else {						//>大于号
				code = TK_GT;			//单词为">"
				fseek(fp, -1L, SEEK_CUR);	//将超前读取的字符重新读取
			}
		}
		break;
        case '!':
		{
			ch = fgetc(fp);				
			if (ch == '=')				
			{
				token.push_back(ch);	
				code = TK_UNE;			
			}	
		}
		break;
		/*分界符*/
		case '(': code = TK_OPENPA;		//(
			break;
		case ')': code = TK_CLOSEPA;	//)
			break;
		case '[': code = TK_OPENBR;		//[
			break;
		case ']': code = TK_CLOSEBR;	//]
			break;
		case '{': code = TK_BEGIN;		//{
			break;
		case '}': code = TK_END;		//}
			break;
		case ',': code = TK_COMMA;		//,
			break;
		case ';': code = TK_SEMOCOLOM;	//;
			break;
        case ':':
		{
			ch = fgetc(fp);				
			if (ch == ':')				
			{
				token.push_back(ch);	
				code = TK_COLONS;			
			}else{
                code = TK_COLON;
                fseek(fp, -1L, SEEK_CUR);
            }
		}
		break;
		default: code = UNDEF;
		}
		print(code);		
	}
}

int main(){
    return 0;
}