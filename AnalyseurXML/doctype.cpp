#include <string>
#include "doctype.h"

using namespace std;

Doctype::Doctype (string arootName, bool aisPublic, string adtdUrl):
		rootName(arootName),isPublic(aisPublic),dtdUrl(adtdUrl){}

Doctype::Doctype (string arootName, string sportee, string adtdUrl):
		rootName(arootName),isPublic(false),dtdUrl(adtdUrl)
{
	if(sportee == "PUBLIC")
	{
		this->isPublic = true;
	}
}

string Doctype::toString()
{
	string ret("<!DOCTYPE ");
	ret += rootName + " " + ((isPublic) ? "PUBLIC " : "SYSTEM ") + "\"" + dtdUrl + "\">";
	return ret;
}

bool Doctype::parse()
{

}
