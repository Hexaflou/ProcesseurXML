#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <string>

#include "xmlnode.h"
#include "doctype.h"
#include "../AnalyseurDTD/dtddoc.h"

class Document
{
	Doctype doctype;
	XmlNode root;
	std::string filepath;
	
	public :
		Document(std::string & filepath, Doctype & doctype, XmlNode & root);
		Document(std::string filepath);
		
		//Si construit uniquement avec un filepath.
		bool parse();
		
		// La racine ne doit pas avoir de parent;
		bool setRoot(XmlNode & root);
		
		XmlNode * getRoot();
		
		void setDoctype(Doctype & doctype);
		
		bool isValid();
		
		std::string toString();

		void toTree(Document * p_xslDocument);

		
	
};
#endif

