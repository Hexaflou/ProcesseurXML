#include <string>

#include "cdata.h"
#include "xmlelement.h"
#include "xmlnode.h"

using namespace std;

Cdata::Cdata(string acontent, XmlNode * aparent):XmlElement(aparent),content(acontent)
{
	
}

string Cdata::toString(int level) const
{
	return content;
}

Cdata::~Cdata()
{
	
}