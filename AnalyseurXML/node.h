#ifndef XMLNODE_H
#define XMLNODE_H

#include "xmlelement.h"
#include "commun.h"

typedef list<XmlElement*> ElementList;

class XmlNode {
	ElementList fils;
	AttMap attributs;
	ElementName name;
}

#endif