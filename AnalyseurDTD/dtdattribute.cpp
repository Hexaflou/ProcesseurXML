#include <string>
#include <set>

#include "dtdattribute.h"

using namespace std;

DtdAttribute::DtdAttribute(string aname, DtdElement * element):name(aname),parent(element)
{
	
}
		
//getter
string DtdAttribute::getName() const
{
	return name;
}

string DtdAttribute::toString() const
{
	return name +" CDATA #IMPLIED";
}

//Surcharges d'opérateur

bool operator<=(DtdAttribute const &a, DtdAttribute const& b)
{
	return a.getName() <= b.getName();
}

bool operator>(DtdAttribute const &a, DtdAttribute const& b)
{
	return a.getName() > b.getName();
}

bool operator>=(DtdAttribute const &a, DtdAttribute const& b)
{
	return a.getName() >= b.getName();
}

bool operator!=(DtdAttribute const &a, DtdAttribute const& b)
{
	return a.getName() != b.getName();
}

bool operator<(DtdAttribute const &a, DtdAttribute const& b)
{
	return a.getName() < b.getName();
}

bool operator==(DtdAttribute const &a, DtdAttribute const& b)
{
	return a.getName() == b.getName();
}
