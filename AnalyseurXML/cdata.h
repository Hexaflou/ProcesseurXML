#ifndef CDATA_H
#define CDATA_H

#include <string>
#include "xmlelement.h"
#include "xmlnode.h"
#include "../AnalyseurDTD/dtddoc.h"

class Cdata : public XmlElement{
	
	std::string content;
	
	public :
	Cdata(std::string content, XmlNode * parent=0);
	
	//Getters
	virtual std::string toString(int level=0) const;
	
	virtual std::string getSemName() const;
	
	virtual bool isValid(DtdDoc & validator);
	
	virtual ~Cdata();
};

#endif
