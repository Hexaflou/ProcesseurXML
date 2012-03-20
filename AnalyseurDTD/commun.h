#ifndef COMMUN_H
#define COMMUN_H

using namespace std;
#include <list>
#include <map>
#include <utility>
#include <string>
#include <vector>

#include "dtdelement.h"
#include "dtddoc.h"

typedef pair<string,string> Attribut;
typedef map<string,string> AttMap;
typedef pair<string,string> ElementName;

#ifdef DEBUG
#define debug(x) (x)
#else
#define debug(x) ((void) 0)
#endif


#endif
