#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <string>

#include "xmlnode.h"
#include "doctype.h"
#include "../AnalyseurDTD/dtddoc.h"

class Document
{
	Doctype doctype;
	XmlNode root;
	std::string filepath;
	
	public :
                /**
                 * Crée un objet Document à partir de son chemin, son doctype
                 * et sa racine.
                 * @param filepath Chemin associé au document.
                 * @param doctype Doctype associé au document.
                 * @param root Noeud racine du document.
                 */
		Document(std::string & filepath, Doctype & doctype, XmlNode & root);
                
                /**
                 * Crée un objet Document à partir de son chemin.
                 * @param filepath Chemin du document à créer.
                 */
		Document(std::string & filepath);
		
		/**
                 * Lance le parsing du document XML.
                 * @return true si le parsing s'est bien déroulé, false sinon.
                 */
		bool parse();
		
		/**
                 * Définit l'élément racine du document.
                 * @param root Élément sans parent qui deviendra la racine du
                 *             document.
                 * @return true si l'élément a été correctement associé comme
                 * élément racine, false si l'élément indiqué possède un parent
                 * et ne peut donc devenir racine du document.
                 */
		bool setRoot(XmlNode & root);
		
                /**
                 * Retourne l'élément racine du document.
                 * @return Un pointeur vers l'élément racine du document.
                 */
		XmlNode * getRoot();
		
                /**
                 * Associe un Doctype avec le document.
                 * @param doctype Objet doctype qui sera associé au document.
                 */
		void setDoctype(Doctype & doctype);
		
                /**
                 * Valide le document XML par rapport à sa DTD (défini dans le
                 * doctype).
                 * @return true si le document est valide, false sinon.
                 */
		bool isValid();
		
                /**
                 * Crée une chaîne représentant le document au format XML.
                 * @return Une string contenant le document XML.
                 */
		std::string toString();

                /**
                 * TODO: WTF is this ?
                 */
		void toTree(Document * xslDocument);
};
#endif

