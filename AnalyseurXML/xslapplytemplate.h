#ifndef XSLAPPLYTEMPLATE_H
#define XSLAPPLYTEMPLATE_H

#include <string>
#include <list>
#include <fstream>

#include "xmlnode.h"
#include "commun.h"


class XslApplyTemplate : public XmlNode {

	public :
		//Constructeurs
		XslApplyTemplate(ElementName name, AttMap attributs, ElementList childs, XmlNode * parent=0);
		XslApplyTemplate(ElementName name, XmlNode * parent=0);
		XslApplyTemplate(std::string ns="", std::string name="", XmlNode * parent=0);


		//Affichage en html
		virtual void toHtml(XmlNode * p_xslNode, XmlElement * p_xmlNode, FILE file, int level = 0, bool findMatch = false);
};

#endif
