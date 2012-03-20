#ifndef DTDELEMENT_H
#define DTDELEMENT_H

#include <regex.h>
#include <string>
#include <set>

#include  "dtdattribute.h"

class DtdElement {

	std::string name;
	
	//remarque c'est un set d'attributs, dans le cadre 
	//d'une evolutivité il faudrai remplacer ce string 
	//par un objet de type attribut
	//TODO: Réfléchir à l'utilisation d'un map au lieu d'un set...
	std::set<DtdAttribute> attributs;
	//for the return of an insert in the attribute list.
	typedef std::pair<std::set<DtdAttribute>::iterator,bool> RetAttInsert;
	
	//represente les fils autorisees sous forme de regex;
	regex_t childs;
	//directement tiree du fichier le pattern regex
	std::string regexPattern;
	 
	public :
		DtdElement(std::string name);
		bool addAttribute(std::string const & name);
		
		std::string getName() const;
		
		//retourne l'élément sous forme de chaine.
		std::string toString() const;
		std::string attributeListToString() const;
		
		void completeChildPattern(std::string r);//TODO:c'est tout pour le moment
		
		
		
		//TODO:implementer les fonctions de verification
		//verifie si la liste de fils (sous forme de string séparé par des virgules)
		//récupéré depuis un xml est conforme à la dtd. retourne vrai si valide.
		//bool checkXMLChildren(std::string liste);
};

//surcharge d'opérateur pour utilisation dans un set
bool operator<(DtdElement const &a, DtdElement const& b);
bool operator<=(DtdElement const &a, DtdElement const& b);
bool operator>(DtdElement const &a, DtdElement const& b);
bool operator>=(DtdElement const &a, DtdElement const& b);
bool operator==(DtdElement const &a, DtdElement const& b);
bool operator!=(DtdElement const &a, DtdElement const& b);


#endif
