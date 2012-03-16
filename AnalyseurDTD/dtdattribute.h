#ifndef DTDATTRIBUTE_H
#define DTDATTRIBUTE_H

#include <string>

class DtdElement;

class DtdAttribute {
	
	std::string name;
	DtdElement * parent;
	
	public :
		DtdAttribute(std::string name, DtdElement * element);
		
		//getter
		std::string getName();
		std::string toString();
		
}

#endif