#ifndef DTDATTRIBUTE_H
#define DTDATTRIBUTE_H

#include <string>

class DtdElement;

class DtdAttribute {
    std::string name;
    DtdElement * parent;

public:
    DtdAttribute(std::string name, DtdElement * element);

    //getter
    std::string getName() const;
    std::string toString() const;

};

//surcharge d'opérateur pour utilisation dans un set
bool operator<(DtdAttribute const &a, DtdAttribute const& b);
bool operator<=(DtdAttribute const &a, DtdAttribute const& b);
bool operator>(DtdAttribute const &a, DtdAttribute const& b);
bool operator>=(DtdAttribute const &a, DtdAttribute const& b);
bool operator==(DtdAttribute const &a, DtdAttribute const& b);
bool operator!=(DtdAttribute const &a, DtdAttribute const& b);

#endif
