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
	
	Document(std::string filepath, Doctype doctype, XmlNode racine);
	Document(std::string filepath);
	
	//la racine ne doit pas avoir de parent;
	bool setRoot(XmlNode root);
	
	void setDoctype(Doctype doctype);
	
}
#endif
