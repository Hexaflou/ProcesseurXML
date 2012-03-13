#include "doctype.h"

using namespace std;

Doctype::Doctype (string anomRacine, bool aportee, string adtdUrl):nomRacine(anomRacine),portee(aportee),dtdUrl(adtdUrl)
{
	
}

Doctype::Doctype (string anomRacine, string aportee, string adtdUrl):nomRacine(anomRacine),portee(false),dtdUrl(adtdUrl)
{
	if(aportee == "PUBLIC")
	{
		this->portee = true;
	}
}