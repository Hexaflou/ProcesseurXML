#include <string>
#include <list>

#include "xmlelement.h"
#include "xmlnode.h"
#include "commun.h"

using namespace std;

//Constructeurs
XmlNode::XmlNode(ElementName aname, AttMap aattributs, XmlNode::ElementList achilds, XmlNode * parent):
XmlElement(parent), name(aname), attributs(aattributs), childs(achilds)
{
	
}

XmlNode::XmlNode(ElementName aname, XmlNode * parent):
XmlElement(parent), name(aname), attributs(), childs()
{
	
}

XmlNode::XmlNode(string ns, string aname, XmlNode * parent):
XmlElement(parent), name(ns,aname), attributs(), childs()
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
	childs.push_back(element);
}


string XmlNode::toString(int level) const
{
	string ret("\n");
	int i;
	for(i = 0; i<level; ++i)
		ret+="\t";
	
	if(name.first=="")
		ret+="<"+name.second+" ";
	else
		ret+="<"+name.first+":"+name.second+" ";
	
	AttMap::const_iterator ait;
	for(ait = attributs.begin() ; ait != attributs.end() ; ++ait)
	{
		ret+=ait->first+"=\""+ait->second+"\" ";
	}
	
	if(childs.size()>0)
	{
		ret+=">";
		ElementList::const_iterator eit;
		for(eit = childs.begin(); eit != childs.end(); ++eit)
		{
			ret+=(**eit).toString(level+1);
		}
		ret+="\n";
		
		for(i = 0; i<level; ++i)
			ret+="\t";
		
		if(name.first=="")
			ret+="</"+name.second+">";
		else
			ret+="</"+name.first+":"+name.second+">";
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
