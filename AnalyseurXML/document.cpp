#include <string>
#include <iostream>

#include "xmlnode.h"
#include "doctype.h"
#include "document.h"
#include "../AnalyseurDTD/dtddoc.h"

using namespace std;

Document::Document(std::string & afilepath, Doctype & adoctype, XmlNode & aroot):
		doctype(adoctype),root(aroot),filepath(afilepath){}

Document::Document(std::string & afilepath):
		doctype(),root(),filepath(afilepath){}

// La racine ne doit pas avoir de parent;
bool Document::setRoot(XmlNode & newRoot)
{
	if(newRoot.getParent() == 0)
	{
		root = newRoot;
		return true;
	}
	else
	{
		cerr << "It's impossible to define a root with a parent node." << endl;
		return false;
	}
}

XmlNode * Document::getRoot()
{
	return &root;
}

void Document::setDoctype(Doctype & newDoctype)
{
	doctype = newDoctype;
}

bool Document::isValid()
{
	//vérification du nom de la racine.
	if(root.getName().second != doctype.getRootName())
	{
		cout << "The name root is not conform to doctype declaration" << endl;
		cout << "The document is not valid" << endl;
		return false;
	}
	else if (!root.isValid(doctype.getDtd()))
	{
		cout << "The document is not valid" << endl;
		return false;
	}
	else
	{
		cout << "The XML document is valid." << endl;
	}
	return true;
}

string Document::toString()
{
	string ret("<?xml version=\"1.0\" encoding=\"UTF-8\" ?>\n");
	ret += doctype.toString() + "\n";
	ret += root.toString(0);
	
	return ret;
}

void Document::toTree(Document * p_xslDocument)
{
	root.toHtml(p_xslDocument->getRoot(), &root);
}