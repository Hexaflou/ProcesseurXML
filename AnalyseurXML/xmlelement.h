#ifndef XMLELEMENT_H
#define XMLELEMENT_H

#include <string>
#include <list>
#include "../AnalyseurDTD/dtddoc.h"

class XmlNode;

class XmlElement {

	XmlNode *parent;
	
	public :
		XmlElement(XmlNode * parent = 0);
		
		virtual std::string toString(int level=0) const=0;
		virtual std::string getSemName() const=0;
		
		virtual bool isValid(DtdDoc & validator) = 0;
		
		virtual void setParent(XmlNode * newParent);
		
		XmlNode * getParent();
		
		virtual ~XmlElement();
};

typedef std::list<XmlElement*> ElementList;

#endif


