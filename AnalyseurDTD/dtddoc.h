#ifndef DTDDOC_H
#define DTDDOC_H

#include <map>
#include <string>
#include "dtdelement.h"

/**
 * Représente un document DTD, contenant un ensemble de règles
 * permettant de valider un document XML.
 */
class DtdDoc {
	std::string filepath;

	typedef std::map<std::string, DtdElement> ElemMap;
	ElemMap elements;

	// Typedefs utiles pour les retours d'insertions
	typedef std::pair<ElemMap::iterator, bool> RetElemInsert;
	typedef std::pair<std::string, DtdElement> MapElem;

public:
	DtdDoc(std::string filepath);

	/**
	 * Ajoute un élément à la DTD.
	 * @param element Objet DTDElement représentant l'élément à ajouter.
	 * @return false si l'élément existe déjà, true sinon.
	 */
	bool addElement(DtdElement element);

	/**
	 * Ajoute un attribut associé à un élément.
	 * @param elementName Élément auquel l'attribut est associé.
	 * @param attribut Nom de l'attribut à ajouter.
	 * @return true si tout se passe bien, false si :
	 *   - L'attribut existe déjà ;
	 *   - L'élément est inexistant.
	 * (Le détail des erreurs est affiché sur la sortie d'erreur.)
	 */
	bool addAttributetoElement(std::string const &elementName, std::string const &attribut);

	/**
	 * Valide la conformité d'un nom de noeud et de ses attributs envers
	 * les règles de la DTD.
	 * @param nodeName Nom du noeud XML à valider.
	 * @param attributs Attributs du noeud XML à valider.
	 * @return true si la validation s'est bien déroulé (noeud valide),
	 * false sinon.
	 * (Le détail des erreurs est affiché sur la sortie d'erreur.)
	 */
	bool validate(std::string nodeName, AttMap attributs) const;

	/**
	 * Valide la conformité de l'ordre, du nombre et du nom des enfants
	 * d'un noeud parent.
	 * @param parentName Nom du noeud pour lesquels la validité des
	 * enfants est vérifiée (« noeud parent »).
	 * @param childrenNames Nom des enfants, concaténés par des espaces.
	 * @return true si la validation s'est bien déroulé (nom des enfants
	 * valides), false sinon.
	 * (Le détail des erreurs est affiché sur la sortie d'erreur.)
	 */
	bool validate(std::string parentName, std::string childrenNames) const;

	/**
	 * Retourne une chaîne représentant l'entièreté du document DTD
	 * (au format DTD standard).
	 * @return Une string contenant la représentation.
	 */
	std::string toString() const;

	/**
	 * Retourne le chemin du fichier qui a servi à charger la DTD.
	 * @return Le chemin du fichier (complet).
	 */
	std::string getFilePath() const;

	/**
	 * Lance l'analyse syntaxique et crée le contenu de la DTD à partir
	 * du chemin spécifié lors de la création de l'objet (filePath).
	 * @return true si tout s'est bien passé, false sinon.
	 * (Le détail des erreurs est affiché sur la sortie d'erreur.)
	 */
	bool parse();

};

#endif
