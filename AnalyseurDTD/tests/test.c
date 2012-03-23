#include "xylodtd.tab.h"

void yyerror(DtdDoc *d, char *msg);
int yywrap(void);
int yylex(void);

int main(int argc, char **argv)
{
  int err;

  if(argc < 2 || argc > 2){
    std::cout << "usage: " << argv[0] << " filetoread.dtd" << std::endl;
    return 1;
  }

  //yydebug = 1; // pour désactiver l'affichage de l'exécution du parser LALR, commenter cette ligne
  DtdDoc *doc = new DtdDoc(argv[1]);
  doc->parse();
  std::cout << doc->toString();
  /*err = yyparse(doc);
  if (err != 0) printf("Parse ended with %d error(s)\n", err);
        else  printf("Parse ended with success\n", err);*/
  return 0;
}

int xylodtdwrap(void)
{
	return 1;
}

void xylodtderror(DtdDoc * d, char *msg)
{
	fprintf(stderr, "%s\n", msg);
}