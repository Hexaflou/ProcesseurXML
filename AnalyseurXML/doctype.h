#ifndef DOCTYPE_H
#define DOCTYPE_H

#include <string>

class Doctype {
	string nomRacine;
	bool portee;//portee = true si PUBLIC et false si SYSTEM
	string dtdUrl;
	
	public :
	Doctype(std::string nomRacine, std::string portee, std::string dtdUrl);
	
	Doctype(std::string nomRacine, bool portee, std::string dtdUrl);
	
	//Getter
	std::string toString();
}

#endif