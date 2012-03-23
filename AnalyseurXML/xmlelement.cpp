#include "xmlelement.h"
#include "xmlnode.h"

#include <string>

using namespace std;

XmlElement::XmlElement(XmlNode * aparent):parent(aparent)
{
	
}

void XmlElement::setParent(XmlNode * newParent)
{
	parent = newParent;
}

XmlElement::~XmlElement()
{
	
}

XmlNode * XmlElement::getParent()
{
	return parent;
}
