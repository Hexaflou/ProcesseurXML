%{

void yyerror(char *msg);
int yywrap(void);
int yylex(void);
%}

%union { 
   char *s; 
   }

%token ELEMENT ATTLIST CLOSE OPENPAR CLOSEPAR COMMA PIPE FIXED EMPTY ANY PCDATA AST QMARK PLUS CDATA
%token <s> IDENT TOKENTYPE DECLARATION STRING
%%

main
: dtd_list_opt
;


dtd_list_opt
: dtd_list_opt dtd_declaration CLOSE
| /* empty */
;

dtd_declaration
: ELEMENT IDENT list
| ATTLIST IDENT att_definition_opt
;

list
: seq
| enumerate
;

seq
: OPENPAR seq_list CLOSEPAR
;

seq_list
: seq_list COMMA cp
| cp
;

cp
: IDENT card_opt
| enumerate card_opt
| seq card_opt
;

card_opt
: QMARK
| PLUS
| AST
| /* empty */
;

att_definition_opt
: att_definition_opt attribute
| /* empty */
;

attribute
: IDENT att_type default_declaration
;

att_type
: CDATA
| TOKENTYPE
| enumerate
;

enumerate
: OPENPAR enum_list_plus CLOSEPAR
;

enum_list_plus
: enum_list PIPE item_enum
;

enum_list
: enum_list PIPE item_enum
| item_enum
| PCDATA
;

item_enum
: IDENT
;

default_declaration
: DECLARATION 
| STRING     
| FIXED STRING 
;
%%
int main(int argc, char **argv)
{
  int err;

  yydebug = 1; // pour désactiver l'affichage de l'exécution du parser LALR, commenter cette ligne

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


