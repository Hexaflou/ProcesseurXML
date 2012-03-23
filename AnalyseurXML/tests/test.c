int yywrap(void);
void yyerror(Document *d,char *msg);
int yylex(void);

int main(int argc, char **argv)
{
  int err;
  std::string filepath = "blablabla.bla";

  //yydebug = 1; // pour enlever l'affichage de l'éxécution du parser, commenter cette ligne
  Document *doc = new Document(filepath);
  err = yyparse(doc);

  if (err != 0){
    printf("E: Parsing ended with %d error(s).\n", err);
  }else{
  	printf("\nParsed successfully.\n\n", err);
    printf(doc->toString().c_str());
    printf("\n");
  }
  return 0;
}

int xyloxmlwrap(void)
{
	return 1;
}

void xyloxmlerror(Document * d,char *msg)
{
	fprintf(stderr, "%s\n", msg);
}
