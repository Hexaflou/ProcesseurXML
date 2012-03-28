#include <string>
#include <set>
#include <iostream>
#include <algorithm>

#include "dtdelement.h"
#include "dtdattribute.h"
#include <boost/regex.hpp> 

using namespace std;

DtdElement::DtdElement(string aname) : name(aname)
{

}

bool DtdElement::addAttribute(string const & name)
{
	DtdElement::RetAttInsert ret = attributs.insert(DtdAttribute(name, this));

	return ret.second;
}

string DtdElement::toString() const
{
	if (regexPattern != "") {
		string ret("<!ELEMENT ");
		ret += name + " " + regexPattern + ">";
		return ret;
	} else {
		return string();
	}
}

string DtdElement::attributeListToString() const
{
	if (attributs.size() == 0)
		return string("");

	string ret("<!ATTLIST ");
	ret += name;

	set<DtdAttribute>::iterator it;
	for (it = attributs.begin(); it != attributs.end(); ++it) {
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

	for (ait = xmlAttributes.begin(); ait != xmlAttributes.end(); ++ait) {
		// Si l'attribut n'est pas référencé, il y a une erreur
		if (attributs.find(DtdAttribute(ait->first, 0)) == attributs.end()) {
			cout << ait->first << " is not a valid attribute for ";
			cout << name << " node." << endl;
			return false;
		}
	}
	return true;
}

bool DtdElement::validate(std::string childrenNames) const
{
	// On crée un pattern à partir du motif trouvé dans le fichier DTD
	string patt("^" + regexPattern + "( *)$");

	// On remplace simplement les virgules par des espaces
	replace(patt.begin(), patt.end(), ',', ' ');
	
	// Et on crée la regex avec un moteur classique d'expressions régulières
	// (ici, Boost::Regex)
	boost::regex reg(patt, boost::regex::extended);

	// Si l'expression régulière ne correspond pas, c'est qu'il y a un hic
	if (!boost::regex_match(childrenNames, reg)) {
		cerr << "[Validation] Children of the node " << name << " are not valid." << endl;
		cerr << "[Validation] (pattern is \"" << patt << "\" while children list is \""
				<< childrenNames << "\")" << endl;
		return false;
	}

	// Sinon, c'est que les noms des enfants sont valides 
	return true;
}

std::string DtdElement::getName() const
{
	return name;
}

// Surcharges d'opérateur

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
