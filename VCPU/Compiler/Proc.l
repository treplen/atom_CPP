%option c++
%option noyywrap
%x JMPLABLE

%{
#include <map>
#include <vector>
#include <iostream>
#include <fstream>

struct cmp_str
{
	bool operator() (const std::string a,const std::string b)
	{
		return strcmp(a.c_str (),b.c_str ())<0;
	}
};

	unsigned int strno;
	bool errdetected;
	std::map<std::string, int,cmp_str> lables;
	std::vector<std::pair<std::string, int>> jumps;
	std::vector<int> operations;

	char* next(char* text)
	{
		while(*text == ' ')
			++text;
		while(*text != ' ')
			++text;
		while(*text == ' ')
			++text;
		return text;
	}

	std::string form(char* begin)
	{
		char* val;
		while((*begin < 'a' || *begin > 'z')&&(*begin < 'A' || *begin > 'Z')&&(*begin < '0' && *begin > '9'))
			++begin;
		char* end = begin;
		while((*end >= 'a' && *end <= 'z')||(*end >= 'A' && *end <= 'Z')||(*end >= '0' && *end <= '9'))
			++end;
		val = new char[end - begin +1];
		val[end - begin] = 0;
		strncpy(val,begin,end-begin);
		std::string ret(val);
		delete[] val;
		return ret;
	}

	int atoi(char* text)
	{
		int val = 0;
		bool negative = false;
		while((*text < '0' || *text > '9') && *text != '-')
			++text;
		if(*text == '-')
		{
			negative = true;
			++text;
		}
		while(*text >= '0' && *text <= '9')
		{
			val *= 10;
			val += *text - '0';
			++text;
		}
		return negative?-val:val;
	}

%}

%%
<INITIAL>{
	[ \t]*end[ \t]*\n	{
				operations.push_back(0);
				++strno;
	}

	[ \t]*push[ \t]+x[0-9]+[ \t]*\n	{
				operations.push_back(1);
				operations.push_back(atoi(yytext));
				++strno;
	}

	[ \t]*push[ \t]+-?[0-9]+[ \t]*\n	{
				operations.push_back(2);
				operations.push_back(atoi(yytext));
				++strno;
	}

	[ \t]*pop[ \t]+x[0-9]+[ \t]*\n	{
				operations.push_back(3);
				operations.push_back(atoi(yytext));
				++strno;
	}

	[ \t]*pop[ \t]*\n	{
				operations.push_back(4);
				++strno;
	}

	[ \t]*swap[ \t]*\n	{
				operations.push_back(5);
				++strno;
	}

	[ \t]*dupl[ \t]*\n	{
				operations.push_back(6);
				++strno;
	}

	[ \t]*add[ \t]*\n	{
				operations.push_back(7);
				++strno;
	}

	[ \t]*sub[ \t]*\n	{
				operations.push_back(8);
				++strno;
	}

	[ \t]*cmp[ \t]*\n	{
				operations.push_back(9);
				++strno;
	}

	[ \t]*mul[ \t]*\n	{
				operations.push_back(10);
				++strno;
	}

	[ \t]*div[ \t]*\n	{
				operations.push_back(11);
				++strno;
	}

	[ \t]*jmp[ \t]+/[a-zA-Z0-9]+[ \t]*\n	{
				operations.push_back(12);
				BEGIN(JMPLABLE);
	}

	[ \t]*(jz|je)[ \t]+/[a-zA-Z0-9]+[ \t]*\n	{
				operations.push_back(13);
				BEGIN(JMPLABLE);
	}

	[ \t]*(jnz|jne)[ \t]+/[a-zA-Z0-9]+[ \t]*\n	{
				operations.push_back(14);
				BEGIN(JMPLABLE);
	}

	[ \t]*(ja|jnbe)[ \t]+/[a-zA-Z0-9]+[ \t]*\n	{
				operations.push_back(15);
				BEGIN(JMPLABLE);
	}

	[ \t]*(jb|jnae)[ \t]+/[a-zA-Z0-9]+[ \t]*\n	{
				operations.push_back(16);
				BEGIN(JMPLABLE);
	}

	[ \t]*(jae|jnb)[ \t]+/[a-zA-Z0-9]+[ \t]*\n	{
				operations.push_back(17);
				BEGIN(JMPLABLE);
	}

	[ \t]*(jbe|jna)[ \t]+/[a-zA-Z0-9]+[ \t]*\n	{
				operations.push_back(18);
				BEGIN(JMPLABLE);
	}

	[ \t]*call[ \t]+/[a-zA-Z0-9]+[ \t]*\n	{
				operations.push_back(19);
				BEGIN(JMPLABLE);
	}

	[ \t]*ret[ \t]*\n	{
				operations.push_back(20);
				++strno;
	}

	[ \t]*[a-zA-Z][a-zA-Z0-9]*:[ \t]*\n	{
				lables.insert(std::pair<std::string,int>(form(yytext), operations.size()));
				++strno;
	}

	#[^\n]*\n	{
				++strno;
	}

	[ \t]*\n	{
				++strno;
	}

	[^\n]*\n	{
				errdetected=true;
				yyout<<"Error detected in line "<<strno<<": "<<yytext;
				++strno;
	}

}

<JMPLABLE>{
	[0-9]+[ \t]*\n {
		operations.push_back(atoi(yytext));
		BEGIN(INITIAL);
		++strno;
	}

	[a-zA-Z0-9]+[ \t]*\n {
		jumps.push_back(std::pair<std::string,int>(form(yytext),operations.size()));
		operations.push_back(0);
		BEGIN(INITIAL);
		++strno;
	}

	[^\n]*\n {
		++strno;
		BEGIN(INITIAL);
	}

}
%%

int main(int argc, char** argv)
{
	if(argc < 2 || argv[1][0] == '-')
	{
		std::cout << "Input file is not specified\n";
		return 0;
	}
	strno = 1;
	errdetected = false;
	std::ifstream in;
	in.open(argv[1]);
	if(in.fail())
	{
		std::cout << "Can't open file \""<<argv[1]<<"\"\n";
		return 0;
	}
	yyFlexLexer lex(&in,&std::cout);
	lex.yylex();
	in.close();
	for (std::vector<std::pair<std::string, int>>::iterator i = jumps.begin (); i != jumps.end (); i++)
	{
		std::map<std::string,int >::const_iterator lable = lables.find (i->first);
		if(lable!=lables.end ())
		{
			operations[i->second]=lable->second;
		}
		else
		{
			std::cout<<"Lable \""<<i->first<<"\" is not declared\n";
			errdetected= true;
		}
	}
	std::string output = "./procout";
	bool print = false;
	for(int i = 2; i < argc; i++)
	{
		if(strcmp(argv[i],"-o")==0 && i < argc + 1)
		{
			output = argv[++i];
		}
		if(strcmp(argv[i],"-p")==0)
		{
			print = true;
		}
	}
	if(!errdetected)
	{
		std::ofstream out (output.c_str(),std::ofstream::binary);
		for(std::vector<int>::const_iterator i = operations.cbegin ();i!=operations.cend ();i++)
		{
			if(print)
				std::cout<<*i<<(i + 1 == operations.cend()?"":", ");
			out.write((char*)&(*i),4);
		}
		if(print)
			std::cout<<'\n';
		out.close();
	}
	return 0;
}
