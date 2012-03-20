#ifndef COMMUN_H
#define COMMUN_H

#include <list>
#include <map>
#include <utility>
#include <string>
#include <vector>

typedef std::pair<std::string,std::string> Attribut;
typedef std::map<std::string,std::string> AttMap;
typedef std::map<std::string,std::string>::iterator AttMapIt;
typedef std::pair<std::string,std::string> ElementName;

#ifdef DEBUG
#define debug(x) (x)
#else
#define debug(x) ((void) 0)
#endif


#endif
