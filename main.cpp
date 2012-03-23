#include <iostream>
#include "AnalyseurXML/commun.h"
#include "AnalyseurXML/xyloxml.h"
#include "AnalyseurDTD/xylodtd.h"

#include "AnalyseurXML/document.h"
#include "AnalyseurDTD/dtddoc.h"

using namespace std;

int main(){
	cout << "[Xylo] Lancement de l'analyseur XML..." << endl;
	cout << "[Xylo] Lancement de l'analyseur XML terminé." << endl;
	cout << "[Xylo] Lancement de l'analyseur DTD..." << endl;
	cout << "[Xylo] Lancement de l'analyseur DTD terminé." << endl;
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
