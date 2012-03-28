
#include "dtddoc.h"
#include "dtdattribute.h"
#include "dtdelement.h"

#include <string>
#include <map>
#include <iostream>
#include <cstdio>

using namespace std;
int xylodtdparse(DtdDoc *);
extern FILE * xylodtdin;

DtdDoc::DtdDoc(std::string afilepath): filepath(afilepath)
{
	
}
		

bool DtdDoc::addElement(DtdElement element)
{
	
	DtdDoc::RetElemInsert ret = elements.insert(
	DtdDoc::MapElem(element.getName(),element) );
	return ret.second;
}


bool DtdDoc::addAttributetoElement(std::string const &elementName, std::string const &attribut)
{
	map<string,DtdElement>::iterator elementPtr = elements.find(elementName);
	
	if(elementPtr == elements.end())
	{
		DtdElement elem(elementName);
		elem.addAttribute(attribut);
		elements.insert(DtdDoc::MapElem(elementName,elem));
		return true;
	}
	else
	{
		return (elementPtr->second.addAttribute(attribut));
	}
}

string DtdDoc::toString() const
{
	string repr;

	map<string,DtdElement>::const_iterator it;
	for ( it=elements.begin() ; it != elements.end(); ++it )
	{
		repr += it->second.toString() + "\n";

		string reprAttrList(it->second.attributeListToString());
		if(reprAttrList.size()) {
			repr += it->second.attributeListToString() + "\n\n";
		}
	}
	return repr;
}

string DtdDoc::getFilePath() const
{
	return filepath;
}

bool DtdDoc::parse()
{
	FILE * fid;
	fid = fopen(filepath.c_str(),"r");
	if(!fid)
	{
		cerr << "[Validation] Dtd file \"" << filepath << "\" can't be read." << endl;
		return false;
	}
	xylodtdin = fid;
	bool ret = (xylodtdparse(this) == 0);
	fclose(fid);
	return ret;
}

bool DtdDoc::validate(std::string nodeName, AttMap attributs) const
{
	ElemMap::const_iterator it(elements.find(nodeName));
	if(it == elements.end())
	{
		cerr << "[Validation] \"" << nodeName << "\" is an unknown element." << endl;
		return false;
	}
	return it->second.validate(attributs);
}

bool DtdDoc::validate(std::string parentName, std::string childrenNames) const
{
	ElemMap::const_iterator it(elements.find(parentName));
	if(it == elements.end())
	{
		cerr << "[Validation] \"" << parentName << "\" is an unknown element." << endl;
		return false;
	}
	return it->second.validate(childrenNames);
}
