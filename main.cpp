#include <iostream>
#include "AnalyseurXML/commun.h"
#include "AnalyseurXML/xyloxml.h"

using namespace std;

int main(){
	cout << "[Xylo] Lancement de l'analyseur XML..." << endl;
	xyloxmlparse();
	cout << "[Xylo] Lancement de l'analyseur XML terminé." << endl;
	cout << "[Xylo] Lancement de l'analyseur DTD..." << endl;
	cout << "[Xylo] Lancement de l'analyseur DTD terminé." << endl;
	return 0;
}
