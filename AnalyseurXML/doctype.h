#ifndef DOCTYPE_H
#define DOCTYPE_H

#include <string>

class Doctype {
	std::string rootName;
	bool isPublic; // contient l'information de portée (PUBLIC/SYSTEM)
	std::string dtdUrl;
	
	
	public :
	Doctype(std::string rootName, std::string portee, std::string dtdUrl);
	
	Doctype(std::string nomRacine="", bool isPublic=false, std::string dtdUrl="");
	
	bool parse();
	
	// Getter
	std::string toString();
};

#endif
