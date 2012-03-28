#ifndef XMLELEMENT_H
#define XMLELEMENT_H

#include <string>
#include <list>
#include <cstdio>
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

		virtual void toHtml(XmlNode * p_xslNode, XmlElement * p_xmlNode, FILE file, int level = 0);
		
		XmlNode * getParent();
		
		virtual ~XmlElement();

		virtual XmlNode* transformToXsltTree();
};

typedef std::list<XmlElement*> ElementList;

#endif


