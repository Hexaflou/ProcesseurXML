#ifndef DTDDOC_H
#define DTDDOC_H

#include <map>
#include <string>
#include "dtdelement.h"

class DtdDoc {
	
	std::string filepath ;
	
	typedef std::map<std::string,DtdElement> ElemMap;
	ElemMap elements ;
	//for the return of an insert in the attribute list.
	typedef std::pair<ElemMap::iterator,bool> RetElemInsert;
	typedef std::pair<std::string,DtdElement> MapElem;
		
	public:
		DtdDoc(std::string filepath);
		
		//renvoi faux si l'élément existe
		bool addElement(DtdElement element);
		//renvoi faux en cas d'erreur ->erreurs possibles :
		// attribut existe déjà
		// element inexistant
		bool addAttributetoElement(std::string const &elementName, std::string const &attribut);
		
		//validateurs
		bool validate(std::string nodeName, AttMap attributs) const;
		bool validate(std::string parentName, std::string childrenNames) const;
		
		std::string toString() const;
		
		std::string getFilePath() const;
		
		bool parse();
	
};

#endif
