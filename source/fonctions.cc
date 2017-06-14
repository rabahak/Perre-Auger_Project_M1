#include "fonctions.h"

#include <iostream>
#include <time.h>
#include <cstdlib>
#include <random>
#include <cmath> //contains the const M_PI
#include <cassert> // for the assert function
#include "gerbe.h"
#include "reseau.h"
#include "maille.h"
#include <fstream>
#include <stdio.h>
#include<cstdlib>
#include<string>
#include"constantes.h"

using namespace std;

void fonctions::OUTPUT_IMPACT_PY(gerbe* GERBE,int n_gerbe,reseau Reseau_1,int n_maille)
{


ofstream python_file;
python_file.open("output.py");

python_file<<"import numpy as np"<<endl;
python_file<<"from mpl_toolkits.mplot3d import Axes3D"<<endl;
python_file<<"import matplotlib.pyplot as plt"<<endl;


for(int m=0;m<n_gerbe;m++) // a chaque gerbe on associe une figure de duree de 1 sec

{
python_file<<"fig = plt.figure()"<<endl;
python_file<<"ax = fig.add_subplot(111, projection='3d')"<<endl;

for(int j=0;j<n_maille;j++)
for(int k=0;k<3;k++)
{if(Reseau_1.maille_numero(j).d(k,m) ==0)
python_file<<"ax.scatter("<<Reseau_1.maille_numero(j).x(k)<<","<<Reseau_1.maille_numero(j).y(k)<<", 0, zdir='z', c='b', marker='o')"<<endl;
else
python_file<<"ax.scatter("<<Reseau_1.maille_numero(j).x(k)<<","<<Reseau_1.maille_numero(j).y(k)<<", 0, zdir='z', c='r', marker='o')"<<endl;}



python_file<<"r=np.linspace(0,10000,10000)"<<endl;
python_file<<"p=np.linspace(-10000,10000,20000)"<<endl;
//for(int m=0;m<n_gerbe;m++) //axes des gerbes
python_file<<"x="<<sin(GERBE[m].phi_i())*cos(GERBE[m].teta_i())<<"*r+"<<GERBE[m].x_i()<<endl;
python_file<<"y="<<sin(GERBE[m].phi_i())*sin(GERBE[m].teta_i())<<"*r+"<<GERBE[m].y_i()<<endl;
python_file<<"z="<<cos(GERBE[m].phi_i())<<"*r"<<endl; // ici phi est comme delta == 
python_file<<"ax.plot(x,y,z)"<<endl;

//la projection de la droite dans 2D:
python_file<<"x="<<sin(GERBE[m].phi_i())*cos(GERBE[m].teta_i())<<"*r+"<<GERBE[m].x_i()<<endl;
python_file<<"y="<<sin(GERBE[m].phi_i())*sin(GERBE[m].teta_i())<<"*r+"<<GERBE[m].y_i()<<endl;
python_file<<"z="<<0<<endl; // ici phi est comme delta == 
python_file<<"ax.plot(x,y,z)"<<endl;

//La limite des detecteurs declenches
python_file<<"x="<<sin(GERBE[m].phi_i())*cos(GERBE[m].teta_i()+M_PI/2)<<"*p+"<<GERBE[m].x_i()<<endl;
python_file<<"y="<<sin(GERBE[m].phi_i())*sin(GERBE[m].teta_i()+M_PI/2)<<"*p+"<<GERBE[m].y_i()<<endl;
python_file<<"z="<<0<<endl; // ici phi est comme delta == 
python_file<<"ax.plot(x,y,z)"<<endl;
//---------------------------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------------------------------------------
// RECONSTRUCTION
//for(int m=0;m<n_gerbe;m++)
if(Reseau_1.reconstruit2_x(m) !=0 && Reseau_1.reconstruit2_y(m) !=0)
python_file<<"ax.scatter("<<Reseau_1.reconstruit2_x(m)<<","<<Reseau_1.reconstruit2_y(m)<<", 0, zdir='z', c='g', marker='o')"<<endl;



python_file<<"ax.set_xlabel('X')"<<endl;
python_file<<"ax.set_ylabel('Y')"<<endl;
python_file<<"ax.set_zlabel('Z')"<<endl;
//python_file<<"ax.set_xlim3d(0, 1)"<<endl;
//python_file<<"ax.set_ylim3d(0, 1)"<<endl;
python_file<<"ax.set_zlim3d(0, 10000)"<<endl;
if(m<n_gerbe-1)
{
python_file<<"plt.pause(1)"<<endl;
python_file<<"plt.clf()"<<endl;
}
}
python_file<<"plt.show()"<<endl;
//python_file<<"Axes3D.plot()"<<endl;
//-----------------------------------------------------------------------------------------------------------------------

python_file.close();
	
}

void fonctions::OUTPUT_ENERGIE_PY(gerbe* GERBE,int n_gerbe,reseau Reseau_1,int n_maille)
{
int compteur=0;
ofstream python_file;
//-----------------------------------------------------------------------------------------------
//DIAGRAME D'ENERGIE
python_file.open("Energie.py");
python_file<<"import numpy as np\n";
python_file<<"import matplotlib.pyplot as pl"<<endl;
for(int i=0;i<n_gerbe;i++)
{
for(int j=0;j<n_maille;j++)
{
for(int k=0;k<3;k++)
{
python_file<<"pl.plot("<<compteur<<","<<Reseau_1.maille_numero(j).E_exp(k,i)<<",'ro',color='r')"<<endl;
compteur++;
}
}
compteur=0;
python_file<<"pl.axhline("<<Reseau_1.reconstruit_E_moy(i)<<",color='r')"<<endl;
python_file<<"pl.axhline("<<GERBE[i].E_i()<<",color='b')"<<endl;
if(i<n_gerbe-1)
{
python_file<<"pl.pause(5)"<<endl;
python_file<<"pl.clf()"<<endl;}
}
python_file<<"pl.xlabel('numero_cuve')"<<endl;
python_file<<"pl.ylabel('Energie [eV]')"<<endl;
python_file<<"pl.show()"<<endl;

python_file.close();
//-----------------------------------------------------------------------------------------------
 
}


void fonctions::AFFICHE_RESULTAT(gerbe* GERBE,int n_gerbe,reseau Reseau_1,int n_maille)
{
for(int i=0;i<n_gerbe;i++)
{
cout<<"==========================================================="<<endl;
cout<<"Pour la gerbe numero: "<<i<<" :"<<endl;
cout<<"Le nombre de cuves declenchees est: "<<Reseau_1.nombre_declenchees(i)<<" de "<<n_maille*3<<endl;
cout<<endl;
cout<<"L'energie est:                  E_"<<i<<" = "<<GERBE[i].E_i()<<endl;
cout<<"L'energie reconstruite est: E_exp_"<<i<<" = "<<Reseau_1.reconstruit_E_moy(i)<<endl;
cout<<"L'ecart relatif en %            est = "<<GERBE[i].ecart_energie()*100<<" %"<<endl;
cout<<endl;
cout<<"Les coordonnees               sont: ("<<GERBE[i].x_i()<<","<<GERBE[i].y_i()<<")"<<endl;
cout<<"Les coordonnees reconstruites sont: ("<<Reseau_1.reconstruit2_x(i)<<","<<Reseau_1.reconstruit2_y(i)<<")"<<endl;
cout<<"Les ecarts relatives en %     sont: ("<<GERBE[i].ecart_x()*100<<" %,"<<GERBE[i].ecart_y()*100<<" %)"<<endl;
}
cout<<"==========================================================="<<endl;
cout<<"==========================================================="<<endl;
cout<<"LE PROGRAMME N'EST PAS TERMINE"<<endl;
cout<<"==========================================================="<<endl;
cout<<"==========================================================="<<endl;
}

void fonctions::COMPARAISON(gerbe* GERBE,int n_gerbe,int choix)
{
if(choix)
{
int n_fixe;
int n_maille_2;
cout<<"La reconstruction de gerbes avec un nombre different de mailles:"<<endl;
cout<<"-----------------------------------------------------------"<<endl;
cout<<"Preciser le numero de la gerbe: ";cin>>n_fixe;
if(n_fixe<n_gerbe)
{
cout<<"Donner le nouveau nombre de mailles a tester: ";cin>>n_maille_2;
reseau Reseau_2(n_maille_2);
GERBE[n_fixe].Hit(Reseau_2);
GERBE[n_fixe].gerbe_exp_get_impact(Reseau_2.reconstruit2_x(0),Reseau_2.reconstruit2_y(0));
GERBE[n_fixe].Hit_exp(Reseau_2,0);
GERBE[n_fixe].gerbe_exp_get_energie(Reseau_2.reconstruit_E_moy(0));
cout<<"Pour la gergbe numero: "<<n_fixe<<" :"<<endl;
cout<<"Le nombre de cuves declenchees est: "<<Reseau_2.nombre_declenchees(0)<<" de "<<Reseau_2.nombre_de_mailles()*3<<endl;
cout<<endl;
cout<<"L'energie est:                  E_"<<n_fixe<<"' = "<<GERBE[n_fixe].E_i()<<endl;
cout<<"L'energie reconstruite est: E_exp_"<<n_fixe<<"' = "<<Reseau_2.reconstruit_E_moy(0)<<endl;
cout<<"L'ecart relatif en %            est = "<<GERBE[n_fixe].ecart_energie()*100<<" %"<<endl;
cout<<endl;
cout<<"Les coordonnees               sont: ("<<GERBE[n_fixe].x_i()<<","<<GERBE[n_fixe].y_i()<<")"<<endl;
cout<<"Les coordonnees reconstruites sont: ("<<Reseau_2.reconstruit2_x(0)<<","<<Reseau_2.reconstruit2_y(0)<<")"<<endl; //pour la deuxieme methode, les coordonnees construites ne changent pas souvent
cout<<"Les ecarts relatives en %     sont: ("<<GERBE[n_fixe].ecart_x()*100<<" %,"<<GERBE[n_fixe].ecart_y()*100<<" %)"<<endl;
cout<<"-----------------------------------------------------------"<<endl;
//Reseau_2.~reseau();
}
else
cout<<"Vous avez donnez un numero invalide"<<endl;
}
}

void fonctions::ECART_RELATIF_MOYEN_PY(gerbe* GERBE,int n_gerbe,reseau Reseau_1,int n_maille)
{
ofstream python_file;
//-----------------------------------------------------------------------------------------------
//DIAGRAME D'erreurs relatives
python_file.open("Ecarts_relatives_moyennes.py");
python_file<<"import numpy as np\n";
python_file<<"import matplotlib.pyplot as pl"<<endl;
double moy;
for(int i=0;i<n_gerbe;i++)
{
if(GERBE[i].ecart_energie()!=1) // !=1 sans compter les gerbes hors du domaines
{
python_file<<"pl.plot("<<i<<","<<GERBE[i].ecart_energie()*100<<",'ro',color='r')"<<endl;
moy+=GERBE[i].ecart_energie()*100;}
}
moy=moy/n_gerbe;
python_file<<"pl.axhline("<<moy<<",color='b')"<<endl;
python_file<<"pl.xlabel('numero_gerbe')"<<endl;
python_file<<"pl.ylabel('Ecart relative d energie [%]')"<<endl;
python_file<<"pl.show()"<<endl;

python_file.close();

}

void fonctions::ECART_RELATIF_MOYEN_Impactx_PY(gerbe* GERBE,int n_gerbe,reseau Reseau_1,int n_maille)
{
ofstream python_file;
//-----------------------------------------------------------------------------------------------
//DIAGRAME D'erreurs relatives
python_file.open("Ecarts_relatives_moyennes_impactx.py");
python_file<<"import numpy as np"<<endl;
python_file<<"import matplotlib.pyplot as pl"<<endl;
double moy;
for(int i=0;i<n_gerbe;i++)
{
if(GERBE[i].ecart_x()<1)
{
python_file<<"pl.plot("<<i<<","<<GERBE[i].ecart_x()*100<<",'ro',color='r')"<<endl;
moy+=GERBE[i].ecart_x()*100;}
}
moy=moy/n_gerbe;
python_file<<"pl.axhline("<<moy<<",color='b')"<<endl;
python_file<<"pl.xlabel('numero_gerbe')"<<endl;
python_file<<"pl.ylabel('Ecart relative sur x [%]')"<<endl;
python_file<<"pl.show()"<<endl;

python_file.close();

}
