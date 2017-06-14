#include "reseau.h"
#include "maille.h" // reseau simplement inclu maille mais ne l'herite pas
#include <iostream>
#include <cmath>
#include "constantes.h"
#include <string>
using namespace std;

reseau::reseau(int n)
{
n_maille=n;
T=new maille[n_maille];

couche_indice=1;
int rec=6*couche_indice;
int temp;
double a=0;

for(int i=1;i<n_maille;i++)
{
if(i<=rec)
{
T[i].centre(couche_indice*h*cos(a),couche_indice*h*sin(a));
a=a+M_PI/(3*couche_indice);
}
else
{a=0;
temp=rec;
couche_indice++;
rec=6*couche_indice;
rec=rec+temp;}
}}


void reseau::affiche_reseau()
{
int couche_indice=1;
int rec=6*couche_indice;
int temp;

cout<<"CENTRE: "<<endl;T[0].test();cout<<endl;
cout<<"COUCHE 1: "<<endl;
for(int i=1;i<n_maille;i++)
{
if(i<=rec)
{
T[i].test();
}
else
{
temp=rec;
couche_indice++;
rec=6*couche_indice;
rec=rec+temp;
cout<<endl;
cout<<"COUCHE "<<couche_indice<<": "<<endl;}
}
}

void reseau::affiche_reseau_py()
{
ofstream file;
file.open("cuves_coordonnees.txt");
for(int i=0;i<n_maille;i++)
T[i].test_py(file);
file.close();
}

void reseau::affiche_E_exp_py(int n_gerbe)
{
ofstream file;
file.open("E_exp.txt");
int k=0;
for(int m=0;m<n_gerbe;m++)
{k=0;
for(int i=0;i<n_maille;i++)
{
for(int j=0;j<3;j++)
{
file<<k<<" "<<T[i].E_exp(j,m)<<endl; // pour chaque gerbe on aura 3*n_maille lignes de donnees
k++;
}}}
file.close();
}



maille reseau::maille_numero(int n)
{
return T[n];
}

int reseau::nombre_de_mailles()
{
return n_maille;
}

int reseau::nombre_de_couches()
{
return couche_indice;
}

int reseau::nombre_declenchees(int numero_gerbe)
{
int k=0;
for(int i=0;i<n_maille;i++)
{
for(int j=0;j<3;j++)
{
if(T[i].d(j,numero_gerbe)!=0)
k++;
}
}
return k;
}

double reseau::reconstruit1_x(int numero_gerbe)
{
double x_G=0; // la coordonnee x du barycentre
double temp=0;
int compteur=0;
//=======================================================
// METHODE 1:
// BARYCENTRE DE TOUTES LES CUVES DECLENCHEES

for(int i=0;i<n_maille;i++)
{

for(int j=0;j<3;j++)
{
if(T[i].d(j,numero_gerbe)!=0) // pour la cuve declenchee
{x_G+=T[i].s(j,numero_gerbe)*T[i].x(j); //somme de Signal*coordonnee
temp+=T[i].s(j,numero_gerbe); //somme des Signal
compteur++;}
}

}
if(compteur!=0)
x_G=x_G/temp;
else
x_G=0; //pas de cuves declenchees
return x_G;}

double reseau::reconstruit2_x(int numero_gerbe)
{
double x_G=0; // la coordonnee x du barycentre
double temp=0;
//=======================================================
// METHODE 2:
// BARYCENTRE DES 3 CUVES EMMAGAZINANT LE PLUS DENERGIE

double max1=0;
int max1_maille_indice=0;
int max1_cuve_indice=0;
double max2=0;
int max2_maille_indice=0;
int max2_cuve_indice=0;
double max3=0;
int max3_maille_indice=0;
int max3_cuve_indice=0;
while(true)
{
//  CUVE MAXIMALE 1
for(int i=0;i<n_maille;i++)
{

for(int j=0;j<3;j++)
{
if(T[i].s(j,numero_gerbe)>max1) // pour la cuve declenchee
{max1=T[i].s(j,numero_gerbe);
max1_maille_indice=i;
max1_cuve_indice=j;}
}
}

// CUVE MAXIMALE 2
for(int i=0;i<n_maille;i++)
{

for(int j=0;j<3;j++)
{

if(T[i].s(j,numero_gerbe)>max2 && T[i].s(j,numero_gerbe)!=max1) // pour la cuve declenchee
{max2=T[i].s(j,numero_gerbe);
max2_maille_indice=i;
max2_cuve_indice=j;}

}
}

//CUVE MAXIMALE 3
for(int i=0;i<n_maille;i++)
{

for(int j=0;j<3;j++)
{

if(T[i].s(j,numero_gerbe)>max3 && T[i].s(j,numero_gerbe)!=max1 && T[i].s(j,numero_gerbe)!=max2) // pour la cuve declenchee
{max3=T[i].s(j,numero_gerbe);
max3_maille_indice=i;
max3_cuve_indice=j;}

}
}
break;
}
if(max1!=0)
{
x_G=max1*T[max1_maille_indice].x(max1_cuve_indice) + max2*T[max2_maille_indice].x(max2_cuve_indice) + max3*T[max3_maille_indice].x(max3_cuve_indice);
temp=max1+max2+max3;
x_G=x_G/temp;}
else
x_G=0;//pas de cuves declenchees
return x_G;
}

double reseau::reconstruit1_y(int numero_gerbe)
{
double y_G=0; // la coordonnee x du barycentre
double temp=0;
int compteur=0;

//=======================================================
// METHODE 1:
// BARYCENTRE DE TOUTES LES CUVES DECLENCHEES

for(int i=0;i<n_maille;i++)
{

for(int j=0;j<3;j++)
{
if(T[i].d(j,numero_gerbe)!=0) // pour la cuve declenchee
{y_G+=T[i].s(j,numero_gerbe)*T[i].y(j);
temp+=T[i].s(j,numero_gerbe);
compteur++;}}}

if(compteur!=0)
y_G=y_G/temp;
else
y_G=0; //pas de cuves declenchees
return y_G; }
//======================================================


double reseau::reconstruit2_y(int numero_gerbe)
{
double y_G=0; // la coordonnee x du barycentre
double temp=0;
//=======================================================
// METHODE 2:
// BARYCENTRE DES 3 CUVES EMMAGAZINANT LE PLUS DENERGIE
double max1=0;
int max1_maille_indice=0;
int max1_cuve_indice=0;
double max2=0;
int max2_maille_indice=0;
int max2_cuve_indice=0;
double max3=0;
int max3_maille_indice=0;
int max3_cuve_indice=0;
while(true)
{
//  CUVE MAXIMALE 1
for(int i=0;i<n_maille;i++)
{

for(int j=0;j<3;j++)
{
if(T[i].s(j,numero_gerbe)>max1) // pour la cuve declenchee
{max1=T[i].s(j,numero_gerbe);
max1_maille_indice=i;
max1_cuve_indice=j;}
}
}

// CUVE MAXIMALE 2
for(int i=0;i<n_maille;i++)
{

for(int j=0;j<3;j++)
{

if(T[i].s(j,numero_gerbe)>max2 && T[i].s(j,numero_gerbe)!=max1) // pour la cuve declenchee
{max2=T[i].s(j,numero_gerbe);
max2_maille_indice=i;
max2_cuve_indice=j;}

}
}

//CUVE MAXIMALE 3
for(int i=0;i<n_maille;i++)
{

for(int j=0;j<3;j++)
{

if(T[i].s(j,numero_gerbe)>max3 && T[i].s(j,numero_gerbe)!=max1 && T[i].s(j,numero_gerbe)!=max2) // pour la cuve declenchee
{max3=T[i].s(j,numero_gerbe);
max3_maille_indice=i;
max3_cuve_indice=j;}

}
}
break;
}
if(max1!=0)
{
y_G=max1*T[max1_maille_indice].y(max1_cuve_indice) + max2*T[max2_maille_indice].y(max2_cuve_indice) + max3*T[max3_maille_indice].y(max3_cuve_indice);
temp=max1+max2+max3;
y_G=y_G/temp;}
else
y_G=0;//pas de cuves declenchees
return y_G;
}

double reseau::reconstruit_E_moy(int numero_gerbe)
{
double moy=0;
int k=0;
for(int i=0;i<n_maille;i++)
{
for(int j=0;j<3;j++)
{
if(T[i].E_exp(j,numero_gerbe)!=0)
{moy+=T[i].E_exp(j,numero_gerbe);
k++; // juste les cuves declenchees
}
}
}
if(k!=0)
moy=moy/k;
else
moy=0;
return moy;
}

























