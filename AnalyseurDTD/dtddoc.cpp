
#include "dtddoc.h"
#include "dtdattribute.h"
#include "dtdelement.h"

#include <string>
#include <map>

using namespace std;

DtdDoc::DtdDoc(std::string afilepath):filepath(afilepath)
{
	
}
		

bool DtdDoc::addElement(DtdElement element)
{
	DtdDoc::RetElemInsert ret = elements.insert(
					DtdDoc::MapElem(element.getName(),element) );
	return ret.second;
}


bool DtdDoc::addAttributetoElement(std::string const &elementName, std::string const &attribut)
{
	map<string,DtdElement>::iterator elementPtr = elements.find(elementName);
	if(elementPtr == elements.end())
	{
		return false;
	}
	else
	{
		return (elementPtr->second.addAttribute(attribut));
	}
}

string DtdDoc::toString() const
{
	string ret;
	map<string,DtdElement>::const_iterator it;
	for ( it=elements.begin() ; it != elements.end(); ++it )
	{
		ret+=it->second.toString()+"\n";
		ret+=it->second.attributeListToString()+"\n\n";
	}
	return ret;
}
