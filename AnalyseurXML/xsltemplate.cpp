#include <string>
#include <list>
#include <fstream>

#include "xmlelement.h"
#include "xmlnode.h"
#include "xsltemplate.h"
#include "commun.h"

using namespace std;

//Constructeurs
XslTemplate::XslTemplate(ElementName aname, AttMap aattributs, ElementList achilds, XmlNode * parent):
XmlNode(aname, aattributs, achilds, parent)
{
	// Pour des raisons pratiques, on s'assure que les fils aient le bon parent
	ElementList::const_iterator eit;
	for(eit = children.begin(); eit != children.end(); ++eit)
	{
		(**eit).setParent(this);
	}
}

XslTemplate::XslTemplate(ElementName aname, XmlNode * parent):
XmlNode(aname, parent)
{

}

XslTemplate::XslTemplate(string ns, string aname, XmlNode * parent):
XmlNode(ns, aname, parent)
{

}

void XslTemplate::toHtml(XmlNode * p_xslNode, XmlElement * p_xmlNode, FILE file,int level)
{
	ElementList::iterator elementIt;
	for (elementIt = children.begin(); elementIt != children.end(); elementIt++)
	{
		(*elementIt)->toHtml(p_xslNode, p_xmlNode, file, level+1);
	}
}
