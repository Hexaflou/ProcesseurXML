#ifndef DOCUMENT_XSL_H
#define DOCUMENT_XSL_H

#include <string>

#include "xmlnode.h"
#include "doctype.h"

class DocumentXsl
{
	XmlNode root;
	std::string filepath;

	public :
		Document(std::string & filepath, Doctype & doctype, XmlNode & root);
		Document(std::string & filepath);

		// La racine ne doit pas avoir de parent;
		bool setRoot(XmlNode & root);

		XmlNode * getRoot();

		void setDoctype(Doctype & doctype);

		std::string toString();


};
#endif	/* DOCUMENT_XSL_H */

