#include <string>
#include <iostream>
#include <cstdio>
#include <fstream>

#include "xmlnode.h"
#include "doctype.h"
#include "document.h"
#include "../AnalyseurDTD/dtddoc.h"

using namespace std;
int xyloxmlparse(Document *);
extern FILE * xyloxmlin;

Document::Document(std::string & afilepath, Doctype & adoctype, XmlNode & aroot):
		doctype(adoctype),root(aroot),filepath(afilepath){}

Document::Document(std::string afilepath):
		doctype(),root(),filepath(afilepath){}
		
bool Document::parse()
{
	FILE * fid;
	fid = fopen(filepath.c_str(),"r");
	if(!fid)
	{
		cerr << "E: XML file " << filepath << " can't be read." << endl;
		return false;
	}
	xyloxmlin = fid;
	bool ret = (xyloxmlparse(this) == 0);
	fclose(fid);
	return ret;
}

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
	ofstream file("test.html", ios::out | ios::trunc);  //déclaration du flux et ouverture du fichier

	FILE * fid;
	fid = fopen("test.html","w");

        if(!fid)  // si l'ouverture a réussi
        {
		cerr << "Erreur à l'ouverture !" << endl;
            	
        }
        else  // sinon
                root.toHtml(p_xslDocument->getRoot(), 0, *fid, 0);
                fclose(fid);
}
