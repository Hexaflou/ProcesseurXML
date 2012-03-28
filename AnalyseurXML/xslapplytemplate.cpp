#include <string>
#include <list>
#include <fstream>

#include "xmlelement.h"
#include "xmlnode.h"
#include "xslapplytemplate.h"
#include "commun.h"

using namespace std;

//Constructeurs
XslApplyTemplate::XslApplyTemplate(ElementName aname, AttMap aattributs, ElementList achilds, XmlNode * parent):
XmlNode(aname, aattributs, achilds, parent)
{
	// Pour des raisons pratiques, on s'assure que les fils aient le bon parent
	ElementList::const_iterator eit;
	for(eit = children.begin(); eit != children.end(); ++eit)
	{
		(**eit).setParent(this);
	}
}

XslApplyTemplate::XslApplyTemplate(ElementName aname, XmlNode * parent):
XmlNode(aname, parent)
{

}

XslApplyTemplate::XslApplyTemplate(string ns, string aname, XmlNode * parent):
XmlNode(ns, aname, parent)
{

}

void XslApplyTemplate::toHtml(XmlNode * p_xslNode, XmlElement * p_xmlNode, FILE file,int level)
{
	ElementList::iterator elementIt;
	ElementList xmlChildren = ((XmlNode*)p_xmlNode)->getDirectChildren();
	for (elementIt = xmlChildren.begin(); elementIt != xmlChildren.end(); elementIt++)
	{
		(*elementIt)->toHtml(p_xslNode, 0, file, level+1);
	}
}
