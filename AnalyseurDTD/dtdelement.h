#ifndef DTDELEMENT_H
#define DTDELEMENT_H

#include <regex.h>
#include <string>
#include <set>
#include <map>

#include  "dtdattribute.h"
typedef std::map<std::string, std::string> AttMap;

/**
 * Représente la spécification d'un élément au sein d'une DTD.
 */
class DtdElement {
	std::string name;

	typedef std::set<DtdAttribute> AttSet;
	AttSet attributs;
	// Pour le retour des insertions dans le set des attributs
	typedef std::pair<AttSet::iterator, bool> RetAttInsert;

	// Motif directement tiré du fichier, avec une syntaxe DTDienne
	std::string regexPattern;

public:
	/**
	 * Construit la spécification d'un élement XML au sein d'une DTD.
     * @param name Le nom de l'élément.
     */
	DtdElement(std::string name);
	
	/**
	 * Ajoute un attribut à l'élément.
     * @param name Nom de l'attribut.
     * @return True si l'attribut a bien été ajouté, false dans le cas
	 * contraire (attribut déjà existant par exemple).
     */
	bool addAttribute(std::string const & name);

	std::string getName() const;

	/**
	 * Retourne une représentation sous forme de chaîne de l'élément DTD.
     * @return Une chaîne représentant l'élément DTD.
     */
	std::string toString() const;
	
	/**
	 * Retourne la liste des attributs sous la forme d'un extrait de DTD.
     * @return Une chaîne représentant les attributs DTD de l'élément.
     */
	std::string attributeListToString() const;

	/**
	 * Ajoute la chaîne r à la fin du motif de conformité des enfants.
     * @param r Chaîne à ajouter à la fin du motif.
     */
	void completeChildPattern(std::string r);

	/**
	 * Valide la conformité entre les attributs passés en paramètres et
	 * ceux que peuvent accepter l'élément.
     * @param attributes Les attributs à valider.
     * @return true si les attributs sont valides, false sinon.
     */
	bool validate(AttMap attributes) const;
	
	/**
	 * Valide la conformité de la liste des enfants passés en paramètre
	 * avec le motif des enfants que peut contenir l'élément.
     * @param childrenNames Une chaîne contenant la liste des enfants
	 * du noeud à vérifier.
     * @return true si c'est valide, false sinon.
     */
	bool validate(std::string childrenNames) const;
};

// Surcharges d'opérateurs diverses, pour l'utilisation dans un set
bool operator<(DtdElement const &a, DtdElement const& b);
bool operator<=(DtdElement const &a, DtdElement const& b);
bool operator>(DtdElement const &a, DtdElement const& b);
bool operator>=(DtdElement const &a, DtdElement const& b);
bool operator==(DtdElement const &a, DtdElement const& b);
bool operator!=(DtdElement const &a, DtdElement const& b);


#endif
