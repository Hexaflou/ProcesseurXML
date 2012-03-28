
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

DtdDoc::DtdDoc(std::string afilepath) : filepath(afilepath)
{

}

bool DtdDoc::addElement(DtdElement element)
{
	// On insert le nouvel élément dans notre map d'éléments
	DtdDoc::RetElemInsert ret = elements.insert(
			DtdDoc::MapElem(element.getName(), element));
	return ret.second;
}

bool DtdDoc::addAttributetoElement(std::string const &elementName, std::string const &attribut)
{
	// On recherche l'élément à ajouter dans notre map d'attributs
	map<string, DtdElement>::iterator elementPtr = elements.find(elementName);

	// Il n'y est pas ?
	if (elementPtr == elements.end()) {
		// On crée un DtdElement avec ce nom-là...
		DtdElement elem(elementName);
		
		// ...on ajoute le nouvel attribut...
		elem.addAttribute(attribut);
		
		// Et on l'insert.
		elements.insert(DtdDoc::MapElem(elementName, elem));
		
		return true;
	} else { // L'élément existe bien ?
		// On ajoute l'attribut à l'élément.
		return(elementPtr->second.addAttribute(attribut));
	}
}

string DtdDoc::toString() const
{
	string repr;

	map<string, DtdElement>::const_iterator it;
	for (it = elements.begin(); it != elements.end(); ++it) {
		repr += it->second.toString() + "\n";

		string reprAttrList(it->second.attributeListToString());
		if (reprAttrList.size()) {
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
	// On ouvre le fichier pointé par filepath
	fid = fopen(filepath.c_str(), "r");
	
	// Au cas où on n'arrive pas à le lire...
	if (!fid) {
		// ...on informe en disant pourquoi
		cerr << "[Validation] Dtd file \"" << filepath << "\" can't be read : " << strerror() << endl;
		return false;
	}
	
	// On passe cet identifiant de fichier à Bison
	xylodtdin = fid;
	
	// On lance le parsing, et on récupère le fait qu'il y aie des erreurs ou non
	bool ret = (xylodtdparse(this) == 0);
	
	// Fermeture du fichier
	fclose(fid);
	
	return ret;
}

bool DtdDoc::validate(std::string nodeName, AttMap attributs) const
{
	// On recherche le nom du node dans la liste des éléments connus
	ElemMap::const_iterator it(elements.find(nodeName));
	
	// Introuvable : non valide
	if (it == elements.end()) {
		cerr << "[Validation] \"" << nodeName << "\" est un élément inconnu." << endl;
		return false;
	}
	
	// On valide le nœud trouvé avec les attributs
	return it->second.validate(attributs);
}

bool DtdDoc::validate(std::string parentName, std::string childrenNames) const
{
	// On recherche le nom du node dans la liste des éléments connus
	ElemMap::const_iterator it(elements.find(parentName));
	
	// Introuvable : non valide
	if (it == elements.end()) {
		cerr << "[Validation] \"" << parentName << "\" est un élément inconnu." << endl;
		return false;
	}
	
	// On valide le nœud trouvé avec les noms des enfants
	return it->second.validate(childrenNames);
}
