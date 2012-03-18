
#include "dtddoc.h"
#include "dtdattribute.h"
#include "dtdelement.h"

#include <string>
#include <set>

using namespace std;

DtdDoc::DtdDoc(std::string afilepath):filepath(afilepath)
{
	
}
		

bool DtdDoc::addElement(DtdElement element)
{
	DtdDoc::RetElemInsert ret = elements.insert(element);
	return ret.second;
}


bool DtdDoc::addAttributetoElement(std::string const &elementName, std::string const &attribut)
{
	set<DtdElement>::iterator elementPtr = elements.find(DtdElement(elementName));
	if(elementPtr == elements.end())
	{
		return false;
	}
	else
	{
		return (elementPtr->addAttribute(attribut));
	}
}

string DtdDoc::toString() const
{
	string ret;
	set<DtdElement>::iterator it;
	for ( it=elements.begin() ; it != elements.end(); ++it )
	{
		ret+=it->toString()+"\n";
		ret+=it->attributeListToString()+"\n\n";
	}
	return ret;
}
