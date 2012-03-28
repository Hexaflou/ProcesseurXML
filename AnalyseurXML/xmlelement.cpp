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

void XmlElement::toHtml(XmlNode * p_xslNode, XmlElement * p_xmlNode, FILE file, int level)
{
	// TODO: Remove this stub.
}
