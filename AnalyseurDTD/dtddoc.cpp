
#include "dtddoc.h"
#include "dtdattribute.h"
#include "dtdelement.h"

DtdDoc::DtdDoc(std::string afilepath):filepath(afilepath)
{
	
}
		

bool DtdDoc::addElement(DtdElement element)
{
	RetType ret = elements.insert(element);
	return ret.second;
}

		
bool DtdDoc::addAttributetoElement(std::string elementName, std::string attribut)
{
	set<Element>::iterator it;
}

string DtdDoc::toString()
{
	
}