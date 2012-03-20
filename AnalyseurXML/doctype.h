#ifndef DOCTYPE_H
#define DOCTYPE_H

#include <string>
#include 

class Doctype {
	std::string rootName;
	bool portee;//portee = true si PUBLIC et false si SYSTEM
	std::string dtdUrl;
	
	
	public :
	Doctype(std::string rootName, std::string portee, std::string dtdUrl);
	
	Doctype(std::string nomRacine="", bool portee=false, std::string dtdUrl="");
	
	bool parse();
	
	//Getter
	std::string toString();
};

#endif
