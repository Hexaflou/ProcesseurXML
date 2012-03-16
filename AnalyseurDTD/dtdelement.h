#ifndef DTDELEMENT_H
#define DTDELEMENT_H

#include <regex>
#include <string>
#include <set>

class DtdElement {

	std::string name;
	
	//remarque c'est un set d'attributs, dans le cadre 
	//d'une evolutivité il faudrai remplacer ce string 
	//par un objet de type attribut
	std::set<std::string> attributs;
	//represente les fils autorisees sous forme de regex;
	regex_t childs;
	//directement tiree du fichier le patern regex
	std::string regexPattern;
	 
	public :
		DtdElement(std::string name);
		bool addAttribute(std::string name);
		void completeChildPattern(std::string r);//TODO:c'est tout pour le moment
}

#endif