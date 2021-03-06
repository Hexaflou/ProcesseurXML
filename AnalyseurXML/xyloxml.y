%{

#include "commun.h"
#include "xmlnode.h"
#include "xmlelement.h"
#include "doctype.h"
#include "document.h"
#include "cdata.h"

void xyloxmlerror(Document *d, char const *msg);
static int yywrap(void);
int xyloxmllex(void);

%}

%parse-param {Document *d}

%error-verbose

%union {
   char * s;
   ElementName * en;  /* le nom d'un element avec son namespace */
   XmlNode * xmln;
   std::list<XmlElement *> * lxmlep;
   AttMap * am;
   Attribut * att;
   Doctype * dt;
}

%token EQ SLASH CLOSE CLOSESPECIAL DOCTYPE
%token <s> ENCODING STRING DATA COMMENT IDENT NSIDENT
%token <en> NSSTART START STARTSPECIAL END NSEND
%type <en> start
%type <xmln> xml_element
%type <lxmlep> empty_or_content close_content_and_end content_opt
%type <att> attribute
%type <am> attributes_opt
%type <dt> dec_doctype

%%

main:
  document { /* Nothing : already initialized by d */ }
;

document
 : declarations_opt xml_element misc_seq_opt { d->setRoot(*$2); }
 ;
misc_seq_opt
 : misc_seq_opt comment
 | /*empty*/ 
 ;
comment
 : COMMENT
 ;

declarations_opt
 : dec_header dec_doctype { d->setDoctype(*$2); }
 | dec_header
 | dec_doctype { d->setDoctype(*$1); }
 | /*empty*/
 ;
 
dec_header
 : STARTSPECIAL attributes_opt CLOSESPECIAL { /* TODO */ }
 ;

dec_doctype /* Doctype */
 : DOCTYPE IDENT IDENT STRING CLOSE 	{ $$= new Doctype($2,$3,$4); }
 ;



xml_element /* XmlNode */
 : start attributes_opt empty_or_content { $$ = new XmlNode(*$1, *$2, *$3); } /* parent ? */
 ;


attributes_opt /* AttMap */
 : attributes_opt attribute		{$$ = $1; (*$1)[$2->first]=$2->second;}
 | /* empty */				{$$ = new AttMap();}
 ;

attribute /* Attribut */
 : IDENT EQ STRING			{ $$ = new Attribut($1, $3); }
 | NSIDENT EQ STRING    { $$ = new Attribut($1, $3); }
 ;

start /* ElementName */
 : START				{ $$ = $1; }
 | NSSTART				{ $$ = $1; }
 ;
empty_or_content /* vector<XmlElement> */
 : SLASH CLOSE				{ $$ = new std::list<XmlElement *>(); }
 | close_content_and_end CLOSE		{ $$=$1; }
 ;
close_content_and_end /* vector<XmlElement> */
 : CLOSE content_opt end 	{ $$=$2; }
 ;

end /* void */ 
 : END
 | NSEND
 ;
 
content_opt /* vector<XmlElement> */
 : content_opt DATA			{ $$ = $1; $$->push_back(new Cdata($2)); }
 | content_opt comment    { $$ = $1; }
 | content_opt xml_element      	{ $$ = $1; $$->push_back($2); }
 | /*empty*/         			{ $$ = new std::list<XmlElement *>(); }
 ;
%%


int yywrap(void)
{
	return 1;
}
