#include <string>
#include <list>

#include "xmlelement.h"
#include "xmlnode.h"
#include "commun.h"

using namespace std;

//Constructeurs
XmlNode::XmlNode(ElementName aname, AttMap aattributs, XmlNode::ElementList achilds, XmlNode * parent):
XmlElement(parent), name(aname), attributs(aattributs), childs(achilds)
{
	// Pour des raisons pratiques, on s'assure que les fils aie le bon parent
	ElementList::const_iterator eit;
	for(eit = childs.begin(); eit != childs.end(); ++eit)
	{
		(**eit).setParent(this);
	}
}

XmlNode::XmlNode(ElementName aname, XmlNode * parent):
XmlElement(parent), name(aname), attributs(), childs()
{
	
}

XmlNode::XmlNode(string ns, string aname, XmlNode * parent):
XmlElement(parent), name(ns,aname), attributs(), childs()
{
	
}

//Methodes d'ajout
//Ajoute un attribut au noeud, retourne vrai si succes et faux si l'attribut existe déjà.
bool XmlNode::addAttribute(Attribut att)
{
	pair<AttMap::iterator,bool> ret(attributs.insert(att));
	return ret.second;
}

bool XmlNode::addAttribute(string name, string content)
{
	return addAttribute(Attribut(name,content));
}

//Ajoute un fils au noeud.
void XmlNode::addChild(XmlElement * element)
{
	childs.push_back(element);
}
	
string XmlNode::toString(int level) const
{
	string repr("\n"); // On s'assure d'être sur une nouvelle ligne

	// Indentation agréable (selon le paramètre level)

	int i;
	for(i = 0; i < level; ++i)
		repr += "\t";

	// Affichage du début du tag ("<body", ou "<svg:line")
	
	if(name.first == "") // Sans namespace
		repr += "<" + name.second;
	else                 // Avec namespace
		repr += "<" + name.first + ":" + name.second;
	
	// Affichage des attributs

	AttMap::const_iterator ait;
	for(ait = attributs.begin() ; ait != attributs.end() ; ++ait)
	{
		repr += " " + ait->first + "=\"" + ait->second + "\"";
	}
	
	// Si notre nœud des fils, affichons-les

	if(childs.size() > 0)
	{
		repr += ">"; // Terminons donc le tag ouvert

		// Pour chaque fils...
		ElementList::const_iterator eit;
		for(eit = childs.begin(); eit != childs.end(); ++eit)
		{
			// On appelle sa méthode d'affichage
			repr += (**eit).toString(level + 1);
		}
		repr += "\n";
		
		// Indentation au bon niveau
		for(i = 0; i<level; ++i)
			repr += "\t";
		
		// Affichage du tag fermant
		if(name.first == "")
			repr += "</" + name.second + ">";
		else
			repr += "</" + name.first + ":" + name.second + ">";
	}
	else
	{
		// Pas de fils à afficher ? On auto-ferme.

		// TODO: Ne pas confondre élément vide et élément auto-fermé
		// On devrait gérer le cas d'élément vide non auto-fermé
		// (une sombre histoire de sémantique)

		repr += " />";
	}
	
	return repr;
}

XmlNode::~XmlNode()
{
	ElementList::iterator it;
	for(it = childs.begin(); it != childs.end(); ++it)
	{
		delete (*it);
	}
}
