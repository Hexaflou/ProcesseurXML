#include <iostream>
#include <cstdio>
#include <string>

#include "AnalyseurXML/commun.h"
#include "AnalyseurXML/xyloxml.h"
#include "AnalyseurDTD/xylodtd.h"

#include "AnalyseurXML/document.h"
#include "AnalyseurDTD/dtddoc.h"

using namespace std;

/**
 * Point d'entrée du programme.
 * 
 * @param argc Nombre d'arguments en entrée.
 * @param argv Tableaux des arguments du programmes.
 * @return 0 (SUCCESS) si la validation s'est bien déroulée,
 *		   1 dans les autres cas.
 */
int main(int argc, char *argv[])
{
	int codeRetour = 0; // Code d'erreur
	
	// Assez d'arguments ?
	if (argc == 2) {
		// Construction du document XML
		Document * thedoc = new Document(string(argv[1]));
		// Lancement du parseur XML
		bool hasSyntaxErrors = !(thedoc->parse());

		// Des erreurs de syntaxe ?
		if (hasSyntaxErrors) {			
			cout << "[Xylo] Le document spécifié a des erreurs de syntaxe XML." << endl;
			
			codeRetour = 1;
		}else{
			// Lancement de la validation XML
			if (thedoc->isValid()) {
				cout << "[Xylo] Le document spécifié est valide." << endl;
				Document * thedocxslt = new Document(string(argv[2]));
				thedocxslt->parse();
				Document * newdocxslt = thedocxslt->transformToXsltTree();
				delete thedocxslt;
				thedoc->toTree(newdocxslt);
			} else {
				cout << "[Xylo] La document spécifié n'est pas valide." << endl;
				codeRetour = 0;
			}
		}

		// Libération de la mémoire
		delete thedoc;
	} else {
		// Pas assez d'arguments : expliquons le fonctionnement du programme
		cout << "Xylo XML analyser (0.1b) - 2012, by Hexanet" << endl;
		
		cout << "usage: " << argv[0] << " fichier.xml" << endl;
		cout << "E: Aucun fichier passé en argument : rien à faire." << endl;
	}
	
	return codeRetour;
}

void xyloxmlerror(Document * d, char *msg)
{
	cerr << "[XML parser] " << msg << endl;
}

void xylodtderror(DtdDoc * d, char *msg)
{
	cerr << "[DTD parser] " << msg << endl;
}
