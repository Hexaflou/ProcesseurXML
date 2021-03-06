#include <string>
#include <list>
#include <cstdio>

#include "xmlelement.h"
#include "xmlnode.h"
#include "commun.h"
#include "xsltemplate.h"
#include "xslapplytemplate.h"
#include "../AnalyseurDTD/dtddoc.h"

using namespace std;

//Constructeurs
XmlNode::XmlNode(ElementName aname, AttMap aattributs, ElementList achilds, XmlNode * parent):
XmlElement(parent), name(aname), attributs(aattributs), children(achilds)
{
	// Pour des raisons pratiques, on s'assure que les fils aie le bon parent
	ElementList::const_iterator eit;
	for(eit = children.begin(); eit != children.end(); ++eit)
	{
		(**eit).setParent(this);
	}
}

XmlNode::XmlNode(ElementName aname, XmlNode * parent):
XmlElement(parent), name(aname), attributs(), children()
{
	
}

XmlNode::XmlNode(string ns, string aname, XmlNode * parent):
XmlElement(parent), name(ns,aname), attributs(), children()
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
	children.push_back(element);
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

	if(children.size() > 0)
	{
		repr += ">"; // Terminons donc le tag ouvert

		// Pour chaque fils...
		ElementList::const_iterator eit;
		for(eit = children.begin(); eit != children.end(); ++eit)
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

string XmlNode::toStringNode(int level) const
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

	repr += " />";

	return repr;
}

ElementName XmlNode::getName() const {
	return name;
}

AttMap XmlNode::getAttMap() const{
	return attributs;
}

bool XmlNode::isValid(DtdDoc & validator)
{
	//validation des attributs
	if(!validator.validate(name.second,attributs))
		return false;
	//validation de la liste des fils
	if(!validator.validate(name.second,getDirectChildrenNames()))
		return false;
	//validation des fils
	ElementList::const_iterator eit;
	for(eit = children.begin() ; eit != children.end() ; ++eit)
	{
		if(!(**eit).isValid(validator))
			return false;
	}
	return true;
}

string XmlNode::getSemName() const
{
	return name.second;
}

ElementList XmlNode::getDirectChildren() {
	
	return children;
}

string XmlNode::getDirectChildrenNames() {
	string namelist;

	// Pour chaque fils...
	ElementList::const_iterator eit;
	for(eit = children.begin(); eit != children.end(); ++eit)
	{
			namelist += (**eit).getSemName() + " ";
	}

	/*if(namelist.size() > 0)
	namelist.resize(namelist.size() - 1);*/ // Removing the last space

	return namelist;
}

XmlNode * XmlNode::findXmlNodeByNameByAttr(string firstName, string secondName, Attribut aattribut)
{
	AttMapIt attributXsl;
	attributXsl = attributs.find("match");
	XmlNode * result;
	if (name.first == firstName && name.second == secondName && (attributXsl != attributs.end()) && ((*attributXsl).second == aattribut.second)){
		return this;
	}else
	{
		ElementList::iterator elementIt;
		for (elementIt = children.begin(); elementIt != children.end(); elementIt++)
		{
			result = dynamic_cast<XmlNode*>((*elementIt));
			if (result!=0){
				result = ((XmlNode *)(*elementIt))->findXmlNodeByNameByAttr(firstName, secondName, aattribut);
				if (result != 0)
					return result;
			}
		}
		return 0;
	}
}

void XmlNode::toHtml(XmlNode * p_xslNode, XmlElement * p_xmlNode, FILE file, int level, bool findMatch)
{
	AttMapIt attributXsl;
	XmlNode * result = 0;
	if (findMatch){
		string xsl = "xsl", temp = "template";
		Attribut attr("match",p_xmlNode->getSemName());
		result = p_xslNode->findXmlNodeByNameByAttr(xsl, temp, attr);
	}
	if (result != 0){
			result->toHtml(p_xslNode, this, file, level);
	}else{
		// level == 0 correspond au fait que notre objet est le noeud xml racine
		// donc si aucun template n'a été trouvé, l'affichage ne se fera pas.
		if (level == 0)
		{
		}else{	// Cas du <apply-template />
			ElementList::iterator elementIt;
			for (elementIt = children.begin(); elementIt != children.end(); elementIt++)
			{
				(*elementIt)->toHtml(p_xslNode, (*elementIt), file, level+1);
			}
		}
	}
}

XmlElement* XmlNode::transformToXsltTree(){
	XmlNode * newNode;
	if (name.first == "xsl"){
		if (name.second == "apply-templates")	// On ne prend pas en compte le cas où apply-templates a un paramètre
		{
			newNode = new XslApplyTemplate(name);
		}else if (name.second == "template")
		{
			newNode = new XslTemplate(name);
		}else{
			newNode = new XmlNode(name);
		}
	}else
	{
		newNode = new XmlNode(name);
		
	}

	// Copie des attributs
	AttMap::iterator attributIt;
	for (attributIt = attributs.begin(); attributIt != attributs.end(); attributIt++)
	{
		newNode->addAttribute(*attributIt);
	}

	// On lance la fonction récursivement sur les fils
	ElementList::iterator elementIt;
	for (elementIt = children.begin(); elementIt != children.end(); elementIt++)
	{
		newNode->addChild((*elementIt)->transformToXsltTree());
	}
	//std::cout<<newNode->toString()<<endl;
	return newNode;
}

XmlNode::~XmlNode()
{
	ElementList::iterator it;
	for(it = children.begin(); it != children.end(); ++it)
	{
		delete (*it);
	}
}
