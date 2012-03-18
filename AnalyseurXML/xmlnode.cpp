#include <string>
#include <list>

#include "xmlelement.h"
#include "commun.h"

using namespace std;

//Constructeurs
XmlNode::XmlNode(ElementName aname, AttMap aattributs, XmlNode::ElementList achilds, XmlNode * parent=0):
XmlElement(parent), name(aname), attributs(aattributs), childs(achilds)
{
	
}

XmlNode::XmlNode(ElementName aname, XmlNode * parent=0):
XmlElement(parent), name(aname), attributs(), childs()
{
	
}

XmlNode::XmlNode(string ns, string aname, XmlNode * parent=0)
XmlElement(parent), name(ns,aname), attributs(), childs()
{
	
}

//Methodes d'ajout
//Ajoute un attribut au noeud, retourne vrai si succes et faux si l'attribut existe déjà.
bool XmlNode::addAttribute(Attribut att)
{
	attributs.insert(att);
}

bool XmlNode::addAttribute(string name, string content)
{
	attributs.insert(Attribut(name,content));
}

//Ajoute un fils au noeud.
void XmlNode::addChild(XmlElement * element)
{
	childs.insert(element);
}


string XmlNode::toString(int level) const
{
	string ret("\n");
	int i;
	for(i = 0; i<level; ++i)
		ret+="\t";
	
	ret+="<"+name+" ";
	
	AttMap::iterator ait;
	for(ait = attributs.begin() ; ait != attributs.end() ; ++ait)
	{
		ret+=ait->first()+"=\""+ait->second()+"\" ";
	}
	
	if(childs.size()>0)
	{
		ret+=">";
		ElementList::iterator eit;
		for(eit = childs.begin(); eit != childs.end(); ++eit)
		{
			ret+=eit->toString(level+1);
		}
		ret+="\n";
		
		for(i = 0; i<level; ++i)
			ret+="\t";
		
		ret+="</"+name+">";
	}
	else
	{
		ret+="/>";
	}
	
	return ret;
	
}

XmlNode::~XmlNode()
{
	ElementList::iterator it;
	for(it = childs.begin(); it != childs.end(); ++it)
	{
		delete (*it);
	}
}