#include <stdio.h>

int jcc_lexer_comment(char curChar, FILE *fp);
int jcc_lexer_num(char curChar, FILE *fp);
int jcc_lexer_keyword_var_func(char curChar, FILE *fp);
int jcc_lexer_char_str(char curChar, FILE *fp);
int jcc_lexer_macro(char churChar, FILE *fp);

const char *filename = "./test.c";

int main(void)
{
	char curChar = 0x10;
	FILE *fp = fopen(filename, "r");

	while (curChar != EOF) {
		curChar = getc(fp);
		switch (curChar) {
		case '	':
		case ' ':
		case '\n':
			break;
		case '/':
			jcc_lexer_comment(curChar, fp);
			break;
		case '#':
			jcc_lexer_macro(curChar, fp);
			break;
		case '\'':
		case '\"':
			printf("%c", curChar);
			jcc_lexer_char_str(curChar, fp);
			break;
		case '(': 
		case ')':
		case '{':
		case '}':
		case '[':
		case ']':
			printf("%c\n", curChar);
			break;
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			printf("%c", curChar);
			jcc_lexer_num(curChar, fp);
			break;
		case '_':
		case 'a':
		case 'b':
		case 'c':
		case 'd':
		case 'e':
		case 'f':
		case 'g':
		case 'h':
		case 'i':
		case 'j':
		case 'k':
		case 'l':
		case 'm':
		case 'n':
		case 'o':
		case 'p':
		case 'q':
		case 'r':
		case 's':
		case 't':
		case 'u':
		case 'v':
		case 'w':
		case 'x':
		case 'y':
		case 'z':
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
		case 'G':
		case 'H':
		case 'I':
		case 'J':
		case 'K':
		case 'L':
		case 'M':
		case 'N':
		case 'O':
		case 'P':
		case 'Q':
		case 'R':
		case 'S':
		case 'T':
		case 'U':
		case 'V':
		case 'W':
		case 'X':
		case 'Y':
		case 'Z':
			printf("%c", curChar);
			jcc_lexer_keyword_var_func(curChar, fp);
			break;
		default:
			printf("%c\n", curChar);
			break;
		}
	}
	fclose(fp);
	return 0;
}

int jcc_lexer_num(char curChar, FILE *fp)
{
	while (1) {
		curChar = getc(fp);
		if (curChar >= 48 && curChar <= 57) {
			printf("%c", curChar);
		} else if (curChar != EOF && curChar != ' ' && curChar != '\n' && curChar != '	') {
			printf("\n%c", curChar);
			break;
		} else {
			break;
		}
	}
	printf("\n");
	return 0;
}

int jcc_lexer_keyword_var_func(char curChar, FILE *fp)
{
	while (1) {
		curChar = getc(fp);
		if ((curChar >= 'A' && curChar <= 'Z')
					|| (curChar >= 'a' && curChar <= 'z')
					|| curChar == '_') {
			printf("%c", curChar);
		} else if (curChar != EOF && curChar != ' ' && curChar != '\n' && curChar != '	') {
			printf("\n%c", curChar);
			break;
		} else {
			break;
		}
	}
	printf("\n");
	return 0;
}

int jcc_lexer_char_str(char curChar, FILE *fp)
{
	char anchor = curChar;
	char dummy;
	while (1) {
		curChar = getc(fp);
		if (curChar == '\\') {
			printf("%c", curChar);
			dummy = getc(fp);
			printf("%c", dummy);
		} else if (curChar == anchor) {
			printf("%c", curChar);
			printf("\n");
			break;
		} else if (curChar == EOF) {
			return 0;
		} else {
			printf("%c", curChar);
		}
	}
	return 0;
}

int jcc_lexer_macro(char curChar, FILE *fp)
{
	printf("--------------------\n");
	printf("I can't parse macros :\(\n");
	while (curChar != '\n') {
		if (curChar == '\\') {
			return 0;
		} else {
			printf("%c", curChar);
			curChar = getc(fp);
		}
	}
	printf("\n");
	printf("--------------------\n");
	return 0;
}

int jcc_lexer_comment(char curChar, FILE *fp)
{
	char dummy;
	dummy = getc(fp);
	if (dummy == '/') {
		while (curChar != '\n') {
			curChar = getc(fp);
		}
	} else if (dummy == '*') {
		while (dummy != '/') {
			while (curChar != '*') {
				curChar = getc(fp);
			}
			dummy = getc(fp);
		}
	} else {
		printf("%c\n", curChar);
		if (dummy != EOF && dummy != ' ' && dummy != '\n' && dummy != '	') {
			printf("%c", dummy);
		} else {
			return 0;
		}
	}
	return 0;
}
