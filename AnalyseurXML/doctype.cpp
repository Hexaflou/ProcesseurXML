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

string Doctype::toString() const
{
	string ret("<!DOCTYPE ");
	ret += rootName + " " + ((isPublic) ? "PUBLIC " : "SYSTEM ") + "\"" + dtdDoc.getFilePath() + "\">";
	return ret;
}

string Doctype::getRootName() const
{
	return rootName;
}

DtdDoc & Doctype::getDtd()
{
	return dtdDoc;
}

bool Doctype::parse()
{
	return dtdDoc.parse();
}
