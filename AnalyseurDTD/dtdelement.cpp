#include <string>
#include <set>
#include <iostream>
#include <algorithm>

#include "dtdelement.h"
#include "dtdattribute.h"
#include <boost/regex.hpp> 

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

bool DtdElement::validate(AttMap xmlAttributes) const
{
	AttMap::const_iterator ait;
	
	for(ait = xmlAttributes.begin() ; ait != xmlAttributes.end() ; ++ait)
	{
		//Si l'attributs n'est pas référencé il y a une erreur
		if(attributs.find(DtdAttribute(ait->first,0))==attributs.end())
		{
			cout << ait->first << " is not a valid attribute for ";
			cout << name << " node."<< endl;
			return false;
		}
	}
	return true;
}

bool DtdElement::validate(std::string childrenNames) const
{
	string patt("^"+regexPattern+"( *)$");
	replace(patt.begin(),patt.end(),',',' ');
	boost::regex reg(patt, boost::regex::extended);
	if(!boost::regex_match(childrenNames, reg))
	{
		cout << "Children of the node " << name << " are not valid." << endl;
		cout << "Pattern is \" " << patt << " \" and the children list is \" " << childrenNames << " \""<<endl; 
		return false;
	}
	return true;
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
