#include "xmlelement.h"
#include "xmlnode.h"

#include <string>

XmlElement::XmlElement(XmlNode * aparent):parent(aparent)
{
	
}

string XmlElement::setParent(XmlNode * newParent)
{
	parent = newParent;
}

XmlElement::~XmlElement()
{
	
}
