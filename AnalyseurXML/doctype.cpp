#include <string>
#include "doctype.h"
#include "../AnalyseurDTD/dtddoc.h"

using namespace std;

Doctype::Doctype (string arootName, bool aisPublic, string adtdUrl):
		rootName(arootName),isPublic(aisPublic),dtdDoc(adtdUrl)
{
	parse();
}

Doctype::Doctype (string arootName, string sportee, string adtdUrl):
		rootName(arootName),isPublic(false),dtdDoc(adtdUrl)
{
	if(sportee == "PUBLIC")
	{
		this->isPublic = true;
	}
	parse();
}

string Doctype::toString()
{
	string ret("<!DOCTYPE ");
	ret += rootName + " " + ((isPublic) ? "PUBLIC " : "SYSTEM ") + "\"" + dtdDoc.getFilePath() + "\">";
	return ret;
}

bool Doctype::parse()
{
	return dtdDoc.parse();
}
