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

Document::Document(std::string afilepath, Doctype & adoctype, XmlNode & aroot) :
doctype(adoctype), root(aroot), filepath(afilepath)
{
}

Document::Document(std::string afilepath) :
doctype(), root(), filepath(afilepath)
{
}

bool Document::parse()
{
	FILE * fid;
	fid = fopen(filepath.c_str(), "r");
	if (!fid) {
		cerr << "[XML parser] XML file \"" << filepath << "\" can't be read." << endl;
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
	if (newRoot.getParent() == 0) {
		root = newRoot;
		return true;
	} else {
		cerr << "[XML parser] It's impossible to define a root with a parent node." << endl;
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
	// Vérification du nom de la racine
	if (root.getName().second != doctype.getRootName()) {
		cerr << "[Validation] The name root is not conform to doctype declaration." << endl;
		cerr << "[Validation] The document is not valid." << endl;
		return false;
	} else if (!root.isValid(doctype.getDtd())) {
		cerr << "[Validation] The document is not valid." << endl;
		return false;
	} else {
		cerr << "[Validation] The XML document is valid." << endl;
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

void Document::toTree(Document * xslDocument)
{
	FILE * fid;
	fid = fopen("test.html","w");

        if(!fid)  // si l'ouverture a réussi
        {
		cerr << "Erreur à l'ouverture !" << endl;
            	
        }
        else  // sinon
                root.toHtml(xslDocument->getRoot(), &root, *fid, 0, true);
                fclose(fid);
}

Document* Document::transformToXsltTree()
{
	if (root.getName().first == "xsl"){
		XmlNode * newRoot = new XmlNode(root.getName());
		// Copie des attributs
		AttMap::iterator attributIt;
		AttMap attMap = root.getAttMap();
		for (attributIt = attMap.begin(); attributIt != attMap.end(); attributIt++)
		{
			newRoot->addAttribute(*attributIt);
		}
		ElementList::iterator elementIt;
		ElementList xmlChildren = root.getDirectChildren();
		for (elementIt = xmlChildren.begin(); elementIt != xmlChildren.end(); elementIt++)
		{
			newRoot->addChild((*elementIt)->transformToXsltTree());
		}
		Document * newDocument = new Document(filepath);
		newDocument->setRoot(*newRoot);
		return newDocument;
	}else{
		return 0;
	}
}
