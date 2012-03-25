#ifndef COMMUN_H
#define COMMUN_H

#include <list>
#include <map>
#include <utility>
#include <string>
#include <vector>

typedef std::pair<std::string,std::string> Attribut;
typedef std::map<std::string,std::string> AttMap;
typedef AttMap::iterator AttMapIt;
typedef std::pair<std::string,std::string> ElementName;

//Je commente parce que ça m'empêche de compiler. Et surtout
//ElementName ne voudra jamais être une clef...
//typedef std::map<ElementName, *xmlnode> XslMap;

#ifdef DEBUG
#define debug(x) (x)
#else
#define debug(x) ((void) 0)
#endif


#endif
