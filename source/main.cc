//PROJET DE RABAH ABDUL KHALEK
//=============================

#include <iostream>
#include <fstream>
#include <stdio.h>
#include "gerbe.h"
#include "reseau.h"
#include<cstdlib>
#include<cmath>
#include<vector>
#include<string>
#include"constantes.h"
#include"fonctions.h"
using namespace std;
using namespace fonctions;
//makefile
//chmod a+x compile.exe
//g++ -std=gnu++11 distribution.cc fonctions.cc gerbe.cc maille.cc reseau.cc main.cc -o test.exe

int main()
{
//Initialisation
//---------------
srand(unsigned(time(NULL))); // creation d'une seed
int n_gerbe=1;
int n_maille=1; //la maille est constituee de 3 cuves en triangle equilateral
bool choix;

//Generation des gerbes
//-----------------------
cout<<"Determiner le nombre de gerbes a generer: ";cin>>n_gerbe;
gerbe* GERBE;
GERBE=new gerbe[n_gerbe];

//Construction du reseau
//-----------------------
cout<<"Determiner le nombre de mailles du reseau: ";cin>>n_maille;
reseau Reseau_1(n_maille);

//Ajustement de domaine des points d'impactes selon les dimensions du reseau
//---------------------------------------------------------------------------
for(int i=0;i<n_gerbe;i++)
GERBE[i].ajuster_domaine_des_impacts(n_maille);

//Action
//TOUJOURS LE SUFFIXE _EXP DESIGNE LA RECONSTRUCTION ET DOIT VENIR APRES LA FONCTION HIT
//---------------------------------------------------------------------------------------
for(int i=0;i<n_gerbe;i++)
{GERBE[i].Hit(Reseau_1); // Gerbe i agit sur le reseau
GERBE[i].gerbe_exp_get_impact(Reseau_1.reconstruit2_x(i),Reseau_1.reconstruit2_y(i));} //Reconstruction des gerbes // REMARQUE: gerbe_exp ne doit jamais preceder Hit

for(int i=0;i<n_gerbe;i++) 
{GERBE[i].Hit_exp(Reseau_1,i); //Reconstruction // Hit_exp ne doit jamais preceder Hit
GERBE[i].gerbe_exp_get_energie(Reseau_1.reconstruit_E_moy(i));} // Recontruction d'energie
cout<<endl;

//AFFICHAGE
//----------
AFFICHE_RESULTAT(GERBE,n_gerbe,Reseau_1,n_maille);

//POUR ECRIRE LE PYTHON-SCRIPT
//------------------------------
//REMARQUE: CONSEIL DE NE PAS UTILISER LES METHODES 1) et 2) POUR des milliers de GERBES (PAR CE QUE CA PREND DU TEMPS POUR ECRIRE DES SCRIPTS INDEPENDANT POUR N_GERBE!!!
//1)
OUTPUT_IMPACT_PY(GERBE,n_gerbe,Reseau_1,n_maille); 
//2)
OUTPUT_ENERGIE_PY(GERBE,n_gerbe,Reseau_1,n_maille);
//3)
ECART_RELATIF_MOYEN_PY(GERBE,n_gerbe,Reseau_1,n_maille);
//4)
ECART_RELATIF_MOYEN_Impactx_PY(GERBE,n_gerbe,Reseau_1,n_maille);


//POUR comparer pour une gerbe les valeurs de E et du point d'impact avec un different nombre de mailles (un reseay plus large)
//-----------------------------------------------------------------------------------------------------------------------------
cout<<"Pour reconstruire une des gerbes avec un nombre different de mailles apres la generation, tapez 1(oui) ou 0(non): ";cin>>choix;
COMPARAISON(GERBE,n_gerbe,choix);

cout<<"========================"<<endl;
cout<<"PROGRAME TERMINE"<<endl;
cout<<"========================"<<endl;

}
