#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <string>

#include "xmlnode.h"
#include "doctype.h"

class Document
{
	Doctype doctype;
	XmlNode root;
	std::string filepath;
	
	public :
		Document(std::string & filepath, Doctype & doctype, XmlNode & root);
		Document(std::string & filepath);
		
		//la racine ne doit pas avoir de parent;
		bool setRoot(XmlNode & root);
		
		XmlNode * getRoot();
		
		void setDoctype(Doctype & doctype);
		
		std::string toString();
		
	
};
#endif

