#ifndef DOCUMENT_XSL_H
#define DOCUMENT_XSL_H

#include <string>
#include <map>

#include "commun.h"

class DocumentXsl
{
	XslMap xslMap;
	std::string filepath;

	public :
		DocumentXsl(std::string & filepath, xslMap);
		DocumentXsl(std::string & filepath);

		// La racine ne doit pas avoir de parent;
		bool setXslMap(XslMap & xslMap);

		XslMap * getXslMap();

		std::string toString();


};
#endif	/* DOCUMENT_XSL_H */

