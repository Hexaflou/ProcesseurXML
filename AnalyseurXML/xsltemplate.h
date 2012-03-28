#ifndef XSLTEMPLATE_H
#define XSLTEMPLATE_H

#include <string>
#include <list>
#include <fstream>

#include "xmlnode.h"
#include "commun.h"


class XslTemplate : public XmlNode {

	public :
		//Constructeurs
		XslTemplate(ElementName name, AttMap attributs, ElementList childs, XmlNode * parent=0);
		XslTemplate(ElementName name, XmlNode * parent=0);
		XslTemplate(std::string ns="", std::string name="", XmlNode * parent=0);


		//Affichage en html
		virtual void toHtml(XmlNode * p_xslNode, XmlElement * p_xmlNode, FILE file, int level = 0, bool findMatch = false);
};

#endif
