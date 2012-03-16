#ifndef DTDDOC_H
#define DTDDOC_H

#include <set>
#include <string>
#include "dtdelement.h"

class DtdDoc {
	
	std::string filepath ;
	std::set<DtdElement> elements ;
	//for the return of an insert in the attribute list.
	typedef pair<set<DtdElement>::iterator,bool> RetType;
		
	public :
		DtdDoc(std::string filepath);
		
		//renvoi faux si l'élément existe
		bool addElement(DtdElement element);
		//renvoi faux en cas d'erreur ->erreurs possibles :
		// attribut existe déjà
		// element inexistant
		bool addAttributetoElement(std::string elementName, std::string attribut);
		
		std::string toString();
	
}

#endif