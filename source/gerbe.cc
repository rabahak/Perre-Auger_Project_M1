#include"gerbe.h"
#include"reseau.h"
#include"distribution.h"
#include<iostream>
#include <fstream>
#include<vector>
#include<time.h>
#include<cstdlib>
#include<cmath>
#include"constantes.h"

using namespace std;
using namespace distribution;
//NOMBRE DE GERBE
int gerbe::k=0;

gerbe::gerbe()
{


//ANGLE/DIRECTION
teta=uniforme(0,2*M_PI); //angle sur la surface xi yi
 double q=-1;
 while(q<0)
 q=cosinus(-M_PI/2,M_PI/2);
 phi=q; // phi entre 0 et pi/2 car teta est entre 0 et 2*pi
 //angle depuis l'axe z

//POINT D'IMPACTE
double a;
xi=uniforme(-r,r);
yi=uniforme(-r,r);

/*a=uniforme(0,2*M_PI);
xi=uniforme(-r,r)*cos(a);
yi=uniforme(-r,r)*sin(a);
*/

//xi=uniforme(-r,r); //cercle cadrant la maille triangulaire
//yi=uniforme(-sqrt(pow(r,2)-pow(xi,2)),sqrt(pow(r,2)-pow(xi,2)));

//ENERGIE
E=uniforme(pow(10,18),pow(10,20));

//NUMERO
numero=k;
k++;
}
double gerbe::x_i()
{return xi;}
double gerbe::y_i()
{return yi;}
double gerbe::teta_i()
{return teta;}
double gerbe::phi_i()
{return phi;}
double gerbe::E_i()
{return E;}

void gerbe::ajuster_domaine_des_impacts(reseau R)
{
xi=uniforme(-R.nombre_de_couches()*h,R.nombre_de_couches()*h);
yi=uniforme(-R.nombre_de_couches()*h,R.nombre_de_couches()*h); //h==hauteur du triangle equilateral
}


void gerbe::affiche_numero()
{
cout<<numero<<endl;
}
//AFFICHAGE
void gerbe::affiche()
{
cout<<"La gerbe numero: '"<<numero<<"'"<<" possede:"<<endl;
cout<<"teta = "<<teta<<" rads"<<" (= "<<teta/M_PI<<" PI) "<<" (= "<<teta*180/M_PI<<" deg)"<<endl;
cout<<"phi = "<<phi<<" rads"<<" (= "<<phi/M_PI<<" PI) "<<" (= "<<phi*180/M_PI<<" deg)"<<endl;
cout<<"xi = "<<xi<<" m"<<endl;
cout<<"yi = "<<yi<<" m"<<endl;
cout<<"E = "<<E<<" e.v"<<endl;
cout<<endl;

ofstream file;
file.open("gerbe_caracteristique.txt");
file<<"La gerbe numero: '"<<numero<<"'"<<" possede:"<<endl;
file<<"teta = "<<teta<<" rads"<<" (= "<<teta/M_PI<<" PI) "<<" (= "<<teta*180/M_PI<<" deg)"<<endl;
file<<"phi = "<<phi<<" rads"<<" (= "<<phi/M_PI<<" PI) "<<" (= "<<phi*180/M_PI<<" deg)"<<endl;
file<<"xi = "<<xi<<" m"<<endl;
file<<"yi = "<<yi<<" m"<<endl;
file<<"E = "<<E<<" e.v"<<endl;
file.close();

}
void gerbe::affiche_impact_py(ofstream& file)
{
//pour python
file<<xi<<" "<<yi<<endl;
}

void gerbe::Hit(reseau& a)
{  /*il faut qu'on filtre les cuves hors du domaines des muons (du plan
perpendiculaire) et dont on calcul l'angle surfacique de la cuve dans le repere
du point de l'impact, celui ci doit etre entre teta - pi/2 et teta + pi/2 ou ces
deux limites caracterisent le seul de contact du plan de la gerbe avec la
terre*/

double dist; //designant la distance
double sign; //designat le signal
int i=0;

double IC_n; //distance : point d'impact - cuve n
double teta_i_cuve_n; // teta dans le repere du point d'impact de la cuve n 
double delta; // angle entre teta gerbe et teta de la cuve i dans le rep du point d'impact

for(int n=0;n<a.nombre_de_mailles();n++)
{
for(i=0;i<3;i++) // pour les 3 cuves
{
IC_n = sqrt(pow((a.maille_numero(n).x(i)-xi),2)+pow((a.maille_numero(n).y(i)-yi),2));



if(xi>=a.maille_numero(n).x(i) && yi>a.maille_numero(n).y(i)) // quadrant 1
teta_i_cuve_n=M_PI+abs(atan((a.maille_numero(n).y(i)-yi)/(a.maille_numero(n).x(i)-xi)));

if(xi<a.maille_numero(n).x(i) && yi>=a.maille_numero(n).y(i)) // quadrant 2
teta_i_cuve_n=2*M_PI-abs(atan((a.maille_numero(n).y(i)-yi)/(a.maille_numero(n).x(i)-xi)));

if(xi<a.maille_numero(n).x(i) && yi<=a.maille_numero(n).y(i)) //quadrant 3
teta_i_cuve_n=abs(atan((a.maille_numero(n).y(i)-yi)/(a.maille_numero(n).x(i)-xi)));

if(xi>=a.maille_numero(n).x(i) && yi<a.maille_numero(n).y(i)) //quadrant 4
teta_i_cuve_n=M_PI-abs(atan((a.maille_numero(n).y(i)-yi)/(a.maille_numero(n).x(i)-xi)));

if(xi==a.maille_numero(n).x(i) && yi==a.maille_numero(n).y(i))
teta_i_cuve_n==9999;


// YOU SHOULD WORK ON THE BORNS (LIMTITES OF CONDITIONS)



delta = teta - teta_i_cuve_n;
//cout<<"pour la maille numero: "<<n<<" et la cuve: "<<i<<" ,teta_i_cuve_n = "<<teta_i_cuve_n<<endl;
double limite_inf;
double limite_sup;
limite_inf=(teta-M_PI/2);
limite_sup=(teta+M_PI/2);
if(teta<M_PI/2)
{

limite_inf=2*M_PI+limite_inf;
if((teta_i_cuve_n > limite_inf) || (teta_i_cuve_n < limite_sup)) //teta+3*M_PI/2
{//dist=(IC_n*sqrt(pow(sin(delta),2)+pow(cos(delta),2)*pow(sin(M_PI/2-phi),2)));
dist=sqrt(pow((a.maille_numero(n).x(i)-xi)*cos(phi),2)+pow((a.maille_numero(n).y(i)-yi)*cos(phi),2)+pow(((a.maille_numero(n).x(i)-xi)*sin(phi)*sin(teta)-(a.maille_numero(n).y(i)-yi)*sin(phi)*cos(teta)),2));
sign=8*(E/pow(10,18))*pow((dist/1000),-1.3);
}
else
{dist=0;sign=0;}
}

if(teta>3*M_PI/2)
{
limite_sup=limite_sup-2*M_PI;
if((teta_i_cuve_n > limite_inf) || (teta_i_cuve_n < limite_sup)) //teta+3*M_PI/2
{//dist=(IC_n*sqrt(pow(sin(delta),2)+pow(cos(delta),2)*pow(sin(M_PI/2-phi),2)));
dist=sqrt(pow((a.maille_numero(n).x(i)-xi)*cos(phi),2)+pow((a.maille_numero(n).y(i)-yi)*cos(phi),2)+pow(((a.maille_numero(n).x(i)-xi)*sin(phi)*sin(teta)-(a.maille_numero(n).y(i)-yi)*sin(phi)*cos(teta)),2));
sign=8*(E/pow(10,18))*pow((dist/1000),-1.3);
}
else
{dist=0;sign=0;}}

if(teta<3*M_PI/2 && teta>M_PI/2)
{
if((teta_i_cuve_n > limite_inf) && (teta_i_cuve_n < limite_sup)) //teta+3*M_PI/2
{//dist=(IC_n*sqrt(pow(sin(delta),2)+pow(cos(delta),2)*pow(sin(M_PI/2-phi),2)));
dist=sqrt(pow((a.maille_numero(n).x(i)-xi)*cos(phi),2)+pow((a.maille_numero(n).y(i)-yi)*cos(phi),2)+pow(((a.maille_numero(n).x(i)-xi)*sin(phi)*sin(teta)-(a.maille_numero(n).y(i)-yi)*sin(phi)*cos(teta)),2));
sign=8*(E/pow(10,18))*pow((dist/1000),-1.3);
}
else
{dist=0;sign=0;}}

if(teta_i_cuve_n!=9999)
{a.maille_numero(n).distance(i,dist);
a.maille_numero(n).signal(i,sign);}

else
{a.maille_numero(n).distance(i,0);
a.maille_numero(n).signal(i,9999);}
}
}}

void gerbe::gerbe_exp_get_impact(double xx,double yy)
{xi_exp=xx;
yi_exp=yy;
}
void gerbe::gerbe_exp_get_energie(double ee)
{E_exp=ee;}

void gerbe::Hit_exp(reseau& a,int n_gerbe)
{  /*il faut qu'on filtre les cuves hors du domaines des muons (du plan
perpendiculaire) et dont on calcul l'angle surfacique de la cuve dans le repere
du point de l'impact, celui ci doit etre entre teta - pi/2 et teta + pi/2 ou ces
deux limites caracterisent le seul de contact du plan de la gerbe avec la
terre*/

double dist; //designant la distance
double log_e;
double e; //designant l'energie recalculee en utilisant dist_exp ... qui n'est autre ici que dist
//double sign=0; //designat le signal
int i=0;

double IC_n; //distance : point d'impact - cuve n
double teta_i_cuve_n; // teta dans le repere du point d'impact de la cuve n 
double delta; // angle entre teta gerbe et teta de la cuve i dans le rep du point d'impact

for(int n=0;n<a.nombre_de_mailles();n++)
{
for(i=0;i<3;i++) // pour les 3 cuves
{
IC_n = sqrt(pow((a.maille_numero(n).x(i)-xi_exp),2)+pow((a.maille_numero(n).y(i)-yi_exp),2));



if(xi_exp>=a.maille_numero(n).x(i) && yi_exp>a.maille_numero(n).y(i)) // quadrant 1
teta_i_cuve_n=M_PI+abs(atan((a.maille_numero(n).y(i)-yi_exp)/(a.maille_numero(n).x(i)-xi_exp)));

if(xi_exp<a.maille_numero(n).x(i) && yi_exp>=a.maille_numero(n).y(i)) // quadrant 2
teta_i_cuve_n=2*M_PI-abs(atan((a.maille_numero(n).y(i)-yi_exp)/(a.maille_numero(n).x(i)-xi_exp)));

if(xi_exp<a.maille_numero(n).x(i) && yi_exp<=a.maille_numero(n).y(i)) //quadrant 3
teta_i_cuve_n=abs(atan((a.maille_numero(n).y(i)-yi_exp)/(a.maille_numero(n).x(i)-xi_exp)));

if(xi_exp>=a.maille_numero(n).x(i) && yi_exp<a.maille_numero(n).y(i)) //quadrant 4
teta_i_cuve_n=M_PI-abs(atan((a.maille_numero(n).y(i)-yi_exp)/(a.maille_numero(n).x(i)-xi_exp)));

if(xi_exp==a.maille_numero(n).x(i) && yi_exp==a.maille_numero(n).y(i))
teta_i_cuve_n==9999;


// YOU SHOULD WORK ON THE BORNS (LIMTITES OF CONDITIONS)



delta = teta - teta_i_cuve_n;
//cout<<"pour la maille numero: "<<n<<" et la cuve: "<<i<<" ,teta_i_cuve_n = "<<teta_i_cuve_n<<endl;
double limite_inf;
double limite_sup;
limite_inf=(teta-M_PI/2);
limite_sup=(teta+M_PI/2);
if(teta<M_PI/2)
{
limite_inf=2*M_PI+limite_inf;
if((teta_i_cuve_n > limite_inf) || (teta_i_cuve_n < limite_sup)) //teta+3*M_PI/2
{//dist=(IC_n*sqrt(pow(sin(delta),2)+pow(cos(delta),2)*pow(sin(M_PI/2-phi),2)));
dist=sqrt(pow((a.maille_numero(n).x(i)-xi_exp)*cos(phi),2)+pow((a.maille_numero(n).y(i)-yi_exp)*cos(phi),2)+pow(((a.maille_numero(n).x(i)-xi_exp)*sin(phi)*sin(teta)-(a.maille_numero(n).y(i)-yi_exp)*sin(phi)*cos(teta)),2));
log_e= 18+ log10((a.maille_numero(n).s(i,n_gerbe))/8) +1.3*log10(dist/1000);
e=pow(10,log_e);
//sign=8*(E/pow(10,18))*pow((dist/1000),-1.3);
}
else
{dist=0;e=0;/*sign=0;*/}
}

if(teta>3*M_PI/2)
{
limite_sup=limite_sup-2*M_PI;
if((teta_i_cuve_n > limite_inf) || (teta_i_cuve_n < limite_sup)) //teta+3*M_PI/2
{//dist=(IC_n*sqrt(pow(sin(delta),2)+pow(cos(delta),2)*pow(sin(M_PI/2-phi),2)));
dist=sqrt(pow((a.maille_numero(n).x(i)-xi_exp)*cos(phi),2)+pow((a.maille_numero(n).y(i)-yi_exp)*cos(phi),2)+pow(((a.maille_numero(n).x(i)-xi_exp)*sin(phi)*sin(teta)-(a.maille_numero(n).y(i)-yi_exp)*sin(phi)*cos(teta)),2));
log_e= 18+ log10((a.maille_numero(n).s(i,n_gerbe))/8) +1.3*log10(dist/1000);
e=pow(10,log_e);
//sign=8*(E/pow(10,18))*pow((dist/1000),-1.3);
}
else
{dist=0;e=0;/*sign=0;*/}}

if(teta<3*M_PI/2 && teta>M_PI/2)
{
if((teta_i_cuve_n > limite_inf) && (teta_i_cuve_n < limite_sup)) //teta+3*M_PI/2
{//dist=(IC_n*sqrt(pow(sin(delta),2)+pow(cos(delta),2)*pow(sin(M_PI/2-phi),2)));
dist=sqrt(pow((a.maille_numero(n).x(i)-xi_exp)*cos(phi),2)+pow((a.maille_numero(n).y(i)-yi_exp)*cos(phi),2)+pow(((a.maille_numero(n).x(i)-xi_exp)*sin(phi)*sin(teta)-(a.maille_numero(n).y(i)-yi_exp)*sin(phi)*cos(teta)),2));
log_e= 18+ log10((a.maille_numero(n).s(i,n_gerbe))/8) +1.3*log10(dist/1000);
e=pow(10,log_e);
//sign=8*(E/pow(10,18))*pow((dist/1000),-1.3);
}
else
{dist=0;e=0;/*sign=0;*/}}

if(teta_i_cuve_n!=9999)
{a.maille_numero(n).distance_exp(i,dist);
a.maille_numero(n).energie_exp(i,e);
/*a.maille_numero(n).signal_exp(i,sign);*/} //signal_exp=signal pour le moment

else
{a.maille_numero(n).distance_exp(i,0);
a.maille_numero(n).energie_exp(i,0);
/*a.maille_numero(n).signal_exp(i,9999);*/}
}
}}

double gerbe::ecart_energie() // abs(val_exp - val_th)/val_th
{
return (abs(E_exp-E)/E);
}
double gerbe::ecart_x()
{
return (abs(xi_exp-xi)/abs(xi));
}
double gerbe::ecart_y()
{
return (abs(yi_exp-yi)/abs(yi));
}


// BROUILLON

/*if(xi>a.maille_numero(n).x(i) && yi>a.maille_numero(n).y(i)) // quadrant 1
teta_i_cuve_n=M_PI+atan((a.maille_numero(n).y(i)-yi)/(a.maille_numero(n).x(i)-xi));

if(xi<a.maille_numero(n).x(i) && yi>a.maille_numero(n).y(i)) // quadrant 2
teta_i_cuve_n=-atan((a.maille_numero(n).y(i)-yi)/(a.maille_numero(n).x(i)-xi));

if(xi<a.maille_numero(n).x(i) && yi<a.maille_numero(n).y(i)) //quadrant 3
teta_i_cuve_n=atan((a.maille_numero(n).y(i)-yi)/(a.maille_numero(n).x(i)-xi));

if(xi>a.maille_numero(n).x(i) && yi<a.maille_numero(n).y(i)) //quadrant 4
teta_i_cuve_n=M_PI-atan((a.maille_numero(n).y(i)-yi)/(a.maille_numero(n).x(i)-xi));*/

/*if(teta>=0 && teta<=M_PI/2) // quadrant 1
teta_i_cuve_n=M_PI+atan((a.maille_numero(n).y(i)-yi)/(a.maille_numero(n).x(i)-xi));

if(teta>=M_PI/2 && teta<=M_PI) // quadrant 2
teta_i_cuve_n=-atan((a.maille_numero(n).y(i)-yi)/(a.maille_numero(n).x(i)-xi));

if(teta>=M_PI && teta<3*M_PI/2) //quadrant 3
teta_i_cuve_n=atan((a.maille_numero(n).y(i)-yi)/(a.maille_numero(n).x(i)-xi));

if(teta>=3*M_PI/2 && teta<2*M_PI) //quadrant 4
teta_i_cuve_n=M_PI-atan((a.maille_numero(n).y(i)-yi)/(a.maille_numero(n).x(i)-xi));*/



/* if((a.maille_numero(n).y(i)-yi)>0 && (a.maille_numero(n).x(i)-xi)>0) //cas: quadrant 1
teta_i_cuve_n = atan((a.maille_numero(n).y(i)-yi)/(a.maille_numero(n).x(i)-xi));

 if((a.maille_numero(n).y(i)-yi)>0 && (a.maille_numero(n).x(i)-xi)<0) //cas: quadrant 2
teta_i_cuve_n = -M_PI + atan((a.maille_numero(n).y(i)-yi)/(a.maille_numero(n).x(i)-xi));

 if((a.maille_numero(n).y(i)-yi)<0 && (a.maille_numero(n).x(i)-xi)<0) //cas: quadrant 3
teta_i_cuve_n =M_PI+ atan((a.maille_numero(n).y(i)-yi)/(a.maille_numero(n).x(i)-xi));

 if((a.maille_numero(n).y(i)-yi)<0 && (a.maille_numero(n).x(i)-xi)>0) //cas: quadrant 4
teta_i_cuve_n = -atan((a.maille_numero(n).y(i)-yi)/(a.maille_numero(n).x(i)-xi));*/


/*
if(teta<M_PI && phi>0)
{if((teta_i_cuve_n > (M_PI/2-teta)) && (teta_i_cuve_n < (teta+M_PI/2))) //teta+3*M_PI/2
{dist=(IC_n*sqrt(pow(sin(delta),2)+pow(cos(delta),2)*pow(sin(M_PI/2-phi),2)));
sign=8*(E/pow(10,18))*pow((dist/1000),-1.3);
cout<<"IF"<<endl;}
else
{dist=0;sign=0;cout<<"ELSE"<<endl;}
cout<<"1111111"<<endl;}

if(teta<M_PI && phi<0)
{if((teta_i_cuve_n > (teta+M_PI/2)) && (teta_i_cuve_n < (M_PI/2-teta))) //teta+3*M_PI/2
{dist=(IC_n*sqrt(pow(sin(delta),2)+pow(cos(delta),2)*pow(sin(M_PI/2-phi),2)));
sign=8*(E/pow(10,18))*pow((dist/1000),-1.3);
cout<<"IF"<<endl;}
else
{dist=0;sign=0;cout<<"ELSE"<<endl;}
cout<<"2222222"<<endl;}

if(teta>M_PI && phi>0)
{if((teta_i_cuve_n > (teta-M_PI/2)) && (teta_i_cuve_n < (teta+M_PI/2)))
{dist=(IC_n*sqrt(pow(sin(delta),2)+pow(cos(delta),2)*pow(sin(M_PI/2-phi),2)));
sign=8*(E/pow(10,18))*pow((dist/1000),-1.3);
cout<<"IF"<<endl;}
else
{dist=0;sign=0;cout<<"ELSE"<<endl;}
cout<<"3333333333"<<endl;}

if(teta>M_PI && phi<0)
{if((teta_i_cuve_n > (teta+M_PI/2)) && (teta_i_cuve_n < (teta-M_PI/2)))
{dist=(IC_n*sqrt(pow(sin(delta),2)+pow(cos(delta),2)*pow(sin(M_PI/2-phi),2)));
sign=8*(E/pow(10,18))*pow((dist/1000),-1.3);
cout<<"IF"<<endl;}
else{dist=0;sign=0;cout<<"ELSE"<<endl;}
cout<<"444444444"<<endl;}
*/




/*if(teta<M_PI && phi>0)
{if((teta_i_cuve_n > (teta+3*M_PI/2)) && (teta_i_cuve_n < (teta+M_PI/2)))
{dist=(IC_n*sqrt(pow(sin(delta),2)+pow(cos(delta),2)*pow(sin(M_PI/2-phi),2)));
sign=8*(E/pow(10,18))*pow((dist/1000),-1.3);}
else
{dist=0;sign=0;}
}
else
{if(teta<M_PI && phi<0)
{if((teta_i_cuve_n > (teta+M_PI/2)) && (teta_i_cuve_n < (teta+3*M_PI/2)))
{dist=(IC_n*sqrt(pow(sin(delta),2)+pow(cos(delta),2)*pow(sin(M_PI/2-phi),2)));
sign=8*(E/pow(10,18))*pow((dist/1000),-1.3);}
else{dist=0;sign=0;}}

if(teta>M_PI && phi>0)
{if((teta_i_cuve_n > (teta-M_PI/2)) && (teta_i_cuve_n < (teta+M_PI/2)))
{dist=(IC_n*sqrt(pow(sin(delta),2)+pow(cos(delta),2)*pow(sin(M_PI/2-phi),2)));
sign=8*(E/pow(10,18))*pow((dist/1000),-1.3);}
else{dist=0;sign=0;}}

if(teta>M_PI && phi<0)
{if((teta_i_cuve_n > (teta+M_PI/2)) && (teta_i_cuve_n < (teta-M_PI/2)))
{dist=(IC_n*sqrt(pow(sin(delta),2)+pow(cos(delta),2)*pow(sin(M_PI/2-phi),2)));
sign=8*(E/pow(10,18))*pow((dist/1000),-1.3);}
else{dist=0;sign=0;}}
}*/
