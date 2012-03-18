#ifndef DTDDOC_H
#define DTDDOC_H

#include <map>
#include <string>
#include "dtdelement.h"

class DtdDoc {
	
	std::string filepath ;
	std::map<std::string,DtdElement> elements ;
	//for the return of an insert in the attribute list.
	typedef std::pair<std::map<std::string,DtdElement>::iterator,bool> RetElemInsert;
	typedef std::pair<std::string,DtdElement> MapElem;
		
	public :
		DtdDoc(std::string filepath);
		
		//renvoi faux si l'élément existe
		bool addElement(DtdElement element);
		//renvoi faux en cas d'erreur ->erreurs possibles :
		// attribut existe déjà
		// element inexistant
		bool addAttributetoElement(std::string const &elementName, std::string const &attribut);
		
		std::string toString() const;
	
};

#endif
