#include <string>
#include "doctype.h"

using namespace std;

Doctype::Doctype (string arootName, bool aportee, string adtdUrl):
		rootName(arootName),portee(aportee),dtdUrl(adtdUrl)
{
	
}

Doctype::Doctype (string arootName, string aportee, string adtdUrl):
		rootName(arootName),portee(false),dtdUrl(adtdUrl)
{
	if(aportee == "PUBLIC")
	{
		this->portee = true;
	}
}

string Doctype::toString()
{
	string ret("<!DOCTYPE ");
	ret+=rootName+" ";
	if(portee)
		ret+="PUBLIC ";
	else
		ret+="SYSTEM ";
	ret+="\""+dtdUrl+"\"";
	
	return ret;
}
