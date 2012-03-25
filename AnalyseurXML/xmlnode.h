#ifndef XMLNODE_H
#define XMLNODE_H

#include <string>
#include <list>

#include "xmlelement.h"
#include "commun.h"
#include "../AnalyseurDTD/dtddoc.h"


class XmlNode : public XmlElement {
	
	ElementName name;
	AttMap attributs;
	ElementList children;
	
	public :
		//Constructeurs
		XmlNode(ElementName name, AttMap attributs, ElementList childs, XmlNode * parent=0);
		XmlNode(ElementName name, XmlNode * parent=0);
		XmlNode(std::string ns="", std::string name="", XmlNode * parent=0);
		
		//Methodes d'ajout
		//Ajoute un attribut au noeud, retourne vrai si succes et faux si l'attribut existe déjà.
		bool addAttribute(Attribut att); 
		bool addAttribute(std::string name, std::string content);
		
		//validateur
		virtual bool isValid(DtdDoc & validator);
		
		//Ajoute un fils au noeud.
		void addChild(XmlElement * element);

		ElementName getName() const;
		virtual std::string getSemName() const;
		
		//Getters
		virtual std::string toString(int level=0) const;

		ElementList getDirectChildren();
		std::string getDirectChildrenNames();
		
		//destructeur
		virtual ~XmlNode();
		
};

#endif
