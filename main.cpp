#include <iostream>
#include <cstdio>
#include <string>

#include "AnalyseurXML/commun.h"
#include "AnalyseurXML/xyloxml.h"
#include "AnalyseurDTD/xylodtd.h"

#include "AnalyseurXML/document.h"
#include "AnalyseurDTD/dtddoc.h"

using namespace std;

int main(int argc,char *argv[]){
	if(argc == 2)
	{
		Document * thedoc = new Document(string(argv[1]));
		
		cout << "[Xylo] Bienvenue dans l'application" << endl;
		cout << "[Xylo] Lancement de l'analyseur XML..." << endl;
		
		thedoc->parse();
		
		cout << "[Xylo] Lancement de l'analyseur XML terminé." << endl;
		cout << "[Xylo] Lancement de la vérification du document..." << endl;
		if(thedoc->isValid())
		{
			cout << "[Xylo] Vérification terminée." << endl;
			Document * thedocxslt = new Document(string(argv[2]));
			thedocxslt->parse();
			Document * newdocxslt = thedocxslt->transformToXsltTree();
			delete thedocxslt;
			thedoc->toTree(newdocxslt);
		}
		else
		{
			cout << "[Xylo] La validation a échoué" << endl;
		}
		delete thedoc;
	}
	else
	{
		cout << "[Xylo] Merci de préciser un nom de fichier à traiter pour commencer." << endl;
	}
	return 0;
}

void xyloxmlerror(Document * d, char *msg)
{
	fprintf(stderr, "%s\n", msg);
}

void xylodtderror(DtdDoc * d, char *msg)
{
	fprintf(stderr, "%s\n", msg);
}
