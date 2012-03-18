#ifndef XMLNODE_H
#define XMLNODE_H

#include <string>
#include <list>

#include "xmlelement.h"
#include "commun.h"


class XmlNode : public XmlElement {
	ElementName name;
	AttMap attributs;
	ElementList childs;
	
	typedef std::list<XmlElement*> ElementList;
	//TODO  : remove if useless
	//typedef std::list<XmlElement*>::iterator ElemListIt;
	
	public :
		//Constructeurs
		XmlNode(ElementName name, AttMap attributs, XmlNode::ElementList childs, XmlNode * parent=0);
		XmlNode(ElementName name, XmlNode * parent=0);
		XmlNode(std::string ns, std::string name, XmlNode * parent=0);
		
		//Methodes d'ajout
		//Ajoute un attribut au noeud, retourne vrai si succes et faux si l'attribut existe déjà.
		bool addAttribute(Attribut att); 
		bool addAttribute(std::string name, std::string content);
		
		//Ajoute un fils au noeud.
		void addChild(XmlElement * element);
		
		//Getters
		virtual std::string toString(int level=0) const;
		
		//destructeur
		virtual ~XmlNode();
		
}

#endif