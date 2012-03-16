#ifndef XMLELEMENT_H
#define XMLELEMENT_H

#include <string>

class XmlNode;

class XmlElement {

	XmlNode *parent;
	
	public :
		XmlElement(XmlNode * parent = 0);
		
		virtual std::string toString()=0;
}

#endif