#ifndef CDATA_H
#define CDATA_H

#include <string>
#include "xmlelement.h"
#include "xmlnode.h"

class Cdata : public XmlElement{
	
	std::string content;
	
	public :
	Cdata(string content, XmlNode * parent);
	
	//Getters
	virtual string toString();
}

#endif