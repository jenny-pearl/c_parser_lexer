#include <stdio.h>
#include <stdlib.h>

int jcc_lexer_char_str(char curChar, FILE *readFile, FILE *writeFile);
int jcc_lexer_comment(char curChar, FILE *readFile, FILE *writeFile);
int jcc_lexer_num(char curChar, FILE *readFile, FILE *writeFile);
int jcc_lexer_keyword_var_func(char curChar, FILE *readFile, FILE *writeFile);
int jcc_lexer_macro(char curChar, FILE *readFile, FILE *writeFile);

const char *infile = "./test.c";
const char *outfile = "./lexedTest.txt";

int main(void)
{
	char curChar = 0x10;
	FILE *readFile = fopen(infile, "r");
	FILE *writeFile = fopen(outfile, "w");

	while (curChar != EOF) {
		curChar = getc(readFile);
		switch (curChar) {
		case '	':
		case ' ':
		case '\n':
			break;
		case '/':
			jcc_lexer_comment(curChar, readFile, writeFile);
			break;
		case '#':
			fprintf(writeFile, "%c\n", curChar);
			jcc_lexer_macro(curChar, readFile, writeFile);
			break;
		case '\'':
		case '\"':
			fprintf(writeFile, "%c", curChar);
			jcc_lexer_char_str(curChar, readFile, writeFile);
			break;
		case '(': 
		case ')':
		case '{':
		case '}':
		case '[':
		case ']':
			fprintf(writeFile, "%c\n", curChar);
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
			fprintf(writeFile, "%c", curChar);
			jcc_lexer_num(curChar, readFile, writeFile);
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
			fprintf(writeFile, "%c", curChar);
			jcc_lexer_keyword_var_func(curChar, readFile, writeFile);
			break;
		default:
			fprintf(writeFile, "%c\n", curChar);
			break;
		}
	}
	fclose(readFile);
	fclose(writeFile);
	return 0;
}

int jcc_lexer_num(char curChar, FILE *readFile, FILE *writeFile)
{
	while (1) {
		curChar = getc(readFile);
		if (curChar >= 48 && curChar <= 57 || curChar == '.') {
			fprintf(writeFile, "%c", curChar);
		} else if (curChar != EOF && curChar != ' ' && curChar != '\n' && curChar != '	') {
			fprintf(writeFile, "\n%c", curChar);
			break;
		} else {
			break;
		}
	}
	fprintf(writeFile, "\n");
	return 0;
}

int jcc_lexer_keyword_var_func(char curChar, FILE *readFile, FILE *writeFile)
{
	while (1) {
		curChar = getc(readFile);
		if ((curChar >= 'A' && curChar <= 'Z')
					|| (curChar >= 'a' && curChar <= 'z')
					|| curChar == '_') {
			fprintf(writeFile, "%c", curChar);
		} else if (curChar != EOF && curChar != ' ' && curChar != '\n' && curChar != '	') {
			fprintf(writeFile, "\n%c", curChar);
			break;
		} else {
			break;
		}
	}
	fprintf(writeFile, "\n");
	return 0;
}

int jcc_lexer_char_str(char curChar, FILE *readFile, FILE *writeFile)
{
	char anchor = curChar;
	char dummy;
	while (1) {
		curChar = getc(readFile);
		if (curChar == '\\') {
			fprintf(writeFile, "%c", curChar);
			dummy = getc(readFile);
			fprintf(writeFile, "%c", dummy);
		} else if (curChar == anchor) {
			fprintf(writeFile, "%c", curChar);
			fprintf(writeFile, "\n");
			break;
		} else if (curChar == EOF) {
			break;
		} else {
			fprintf(writeFile, "%c", curChar);
		}
	}
	return 0;
}

int jcc_lexer_macro(char curChar, FILE *readFile, FILE *writeFile)
{
	return 0;
}

int jcc_lexer_comment(char curChar, FILE *readFile, FILE *writeFile)
{
	char dummy;
	dummy = getc(readFile);
	if (dummy == '/') {
		while (curChar != '\n') {
			curChar = getc(readFile);
		}
	} else if (dummy == '*') {
		while (dummy != '/') {
			while (curChar != '*') {
				curChar = getc(readFile);
			}
			dummy = getc(readFile);
		}
	} else {
		fprintf(writeFile, "%c\n", curChar);
		if (dummy != EOF && dummy != ' ' && dummy != '\n' && dummy != '	') {
			fprintf(writeFile, "%c", dummy);
		} else {
			return 0;
		}
	}
	return 0;
}
