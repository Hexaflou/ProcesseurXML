#include <string>

#include "cdata.h"
#include "xmlelement.h"
#include "xmlnode.h"
#include "../AnalyseurDTD/dtddoc.h"

using namespace std;

Cdata::Cdata(string acontent, XmlNode * aparent):XmlElement(aparent),content(acontent)
{
	
}

string Cdata::toString(int level) const
{
	string repr("\n"); // On s'assure de retourner à la ligne avant tout
	
	// On affiche le contenu
	repr += content; 
	// TODO: On devrait ignorer les espaces multiples, et effecuter
	// une indentation agréable en utilisant level.

	return repr;
}

string Cdata::getSemName() const
{
	return string("#PCDATA");
}

bool Cdata::isValid(DtdDoc & validator)
{
	return true;
}


void Cdata::toHtml(XmlNode * p_xslNode, XmlElement * p_xmlNode, FILE file, int level){
	fputs (toString(level).c_str(),&file);
}

XmlNode* Cdata::transformToXsltTree() {
	// Stub.
	return 0;
}

Cdata::~Cdata()
{
	
}
