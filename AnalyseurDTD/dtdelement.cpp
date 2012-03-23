#include <string>
#include <set>

#include "dtdelement.h"
#include "dtdattribute.h"

using namespace std;


DtdElement::DtdElement(string aname):name(aname)
{
	
}

bool DtdElement::addAttribute(string const & name)
{
	
	DtdElement::RetAttInsert ret = attributs.insert(DtdAttribute(name, this));
	
	return ret.second;
}

string DtdElement::toString() const
{
	if(regexPattern != "")
	{
		string ret("<!ELEMENT ");
		ret += name + " " + regexPattern + ">";
		return ret;
	}
	else
	{
		return string();
	}
}

string DtdElement::attributeListToString() const
{
	if(attributs.size() == 0)
		return string("");

	string ret("<!ATTLIST ");
	ret += name;

	set<DtdAttribute>::iterator it;
	for ( it=attributs.begin() ; it != attributs.end(); ++it )
	{
		ret += "\n\t" + it->toString();
	}

	ret += ">";

	return ret;
	
}

void DtdElement::completeChildPattern(string r)
{
	regexPattern += r;
}

std::string DtdElement::getName() const
{
	return name;
}

//Surcharges d'opérateur

bool operator<=(DtdElement const &a, DtdElement const& b)
{
	return a.getName() <= b.getName();
}

bool operator>(DtdElement const &a, DtdElement const& b)
{
	return a.getName() > b.getName();
}

bool operator>=(DtdElement const &a, DtdElement const& b)
{
	return a.getName() >= b.getName();
}

bool operator!=(DtdElement const &a, DtdElement const& b)
{
	return a.getName() != b.getName();
}

bool operator<(DtdElement const &a, DtdElement const& b)
{
	return a.getName() < b.getName();
}

bool operator==(DtdElement const &a, DtdElement const& b)
{
	return a.getName() == b.getName();
}
