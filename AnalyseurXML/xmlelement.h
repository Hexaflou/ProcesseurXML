#ifndef XMLELEMENT_H
#define XMLELEMENT_H

#include <string>
#include <list>
#include <cstdio>
#include "../AnalyseurDTD/dtddoc.h"

class XmlNode;

class XmlElement {

	XmlNode *parent;
	
	public :
		/**
		 * Construit un élément XML. 
		 * @param parent Le parent de l'élément (facultatif).
		 */
		XmlElement(XmlNode * parent = 0);
		
		/**
		 * Retourne une chaîne représentant l'élément en XML.
		 * 
		 * (Ceci est une méthode virtuelle à redéfinir.)
		 * 
         * @param level Niveau d'indentation de l'élément.
         * @return La chaîne de représentation XML.
         */
		virtual std::string toString(int level=0) const=0;
		
		/**
		 * Retourne le nom sémantique de l'élément.
		 * 
		 * (Ceci est une méthode virtuelle à redéfinir).
         * @return Le nom sémantique, dans une chaîne.
         */
		virtual std::string getSemName() const=0;
		
		/**
		 * Valide l'élément XML.
         * @param validator Document DTD utilisé pour la validation.
         * @return true si l'élement est valide, false sinon.
         */
		virtual bool isValid(DtdDoc & validator) = 0;
		
		/**
		 * Associe un nouveau noeud XML parent à l'élément.
         * @param newParent Nouveau noeud parent.
         */
		virtual void setParent(XmlNode * newParent);

		/**
		 * TODO: What does this thing?
         * @param p_xslNode ??
         * @param p_xmlNode ??
         * @param file ??
         * @param level ??
         */
		virtual void toHtml(XmlNode * p_xslNode, XmlElement * p_xmlNode, FILE file, int level = 0, bool findMatch=false) = 0;
		
		/**
		 * 
         * @return 
         */
		XmlNode * getParent();
		
		virtual ~XmlElement();

		virtual XmlElement* transformToXsltTree() = 0;
};

typedef std::list<XmlElement*> ElementList;

#endif


