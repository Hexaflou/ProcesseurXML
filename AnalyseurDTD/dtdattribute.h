#ifndef DTDATTRIBUTE_H
#define DTDATTRIBUTE_H

#include <string>

class DtdElement;

/**
 * Représente un attribut et sa définition au sein d'une DTD.
 */
class DtdAttribute {
    // Nom de l'attribut
    std::string name;
    
    // Pointeur vers l'élément parent
    DtdElement * parent;

public:
    /**
     * Construit la définition d'un attribut name, associé
     * à l'élément indiqué.
     * @param name Nom de l'attribut à créer.
     * @param element Élément auquel associer l'attribut.
     */
    DtdAttribute(std::string name, DtdElement * element);

    /**
     * Retourne le nom de l'attribut.
     * @return Le nom de l'attribut.
     */
    std::string getName() const;
    
    /**
     * Représente l'attribut sous une forme textuelle DTD.
     * @return Une chaîne contenant une représentation valide DTD.
     */
    std::string toString() const;

};

// Surcharges d'opérateurs diverses, pour l'utilisation dans un set
bool operator<(DtdAttribute const &a, DtdAttribute const& b);
bool operator<=(DtdAttribute const &a, DtdAttribute const& b);
bool operator>(DtdAttribute const &a, DtdAttribute const& b);
bool operator>=(DtdAttribute const &a, DtdAttribute const& b);
bool operator==(DtdAttribute const &a, DtdAttribute const& b);
bool operator!=(DtdAttribute const &a, DtdAttribute const& b);

#endif
