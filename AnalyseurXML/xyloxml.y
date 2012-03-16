%{

using namespace std;
#include "commun.h"

int yywrap(void);
void yyerror(char *msg);
int yylex(void);

%}

%parse-param {Document *d}


%union {
   char * s;
   ElementName * en;  /* le nom d'un element avec son namespace */
}

%token EQ SLASH CLOSE CLOSESPECIAL DOCTYPE
%token <s> ENCODING STRING DATA COMMENT IDENT NSIDENT
%token <en> NSSTART START STARTSPECIAL END NSEND

%%

main:
document
;

document
 : declarations_opt xml_element misc_seq_opt
 ;
misc_seq_opt
 : misc_seq_opt comment
 | /*empty*/ 
 ;
comment
 : COMMENT
 ;

declarations_opt
 : dec_header dec_doctype
 | dec_header
 | dec_doctype
 | /*empty*/
 ;
 
dec_header
 : STARTSPECIAL attributes_opt CLOSESPECIAL
 ;

dec_doctype
 : DOCTYPE IDENT IDENT STRING CLOSE 	{$$= new Doctype($1,$2,$3);}
 ;

xml_element
 : start attributes_opt empty_or_content { $$ = new XmlNode($1, $2, $3);} /* parent ? */
 ;

attributes_opt
 : attributes_opt attribute		{$$ = $1; (*$1)[$2->first]=$2->second;}
 | /* empty */				{$$ = new map<string,string>();}
 ;

attribute
 : IDENT EQ STRING			{$$ = new pair<string,string>($1,$3);}
 ;

start
 : START				{$$=$1;}
 | NSSTART				{$$=$1;}
 ;
empty_or_content
 : SLASH CLOSE				{}
 | close_content_and_end CLOSE		{$$=$1;}
 ;
close_content_and_end
 : CLOSE	content_opt END 	{$$=$2;}
 ;
content_opt 
 : content_opt DATA			{$$=$1; $$->push_back(new Cdata($2));}
 | content_opt comment        
 | content_opt xml_element      	{$$=$1; $$->push_back($2);}
 | /*empty*/         			{$$ = new vector<XmlElement>();}
 ;
%%

int main(int argc, char **argv)
{
  int err;

  yydebug = 1; // pour enlever l'affichage de l'éxécution du parser, commenter cette ligne

  err = yyparse();
  if (err != 0) printf("Parse ended with %d error(s)\n", err);
  	else  printf("Parse ended with success\n", err);
  return 0;
}
int yywrap(void)
{
  return 1;
}

void yyerror(char *msg)
{
  fprintf(stderr, "%s\n", msg);
}

