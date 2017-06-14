#ifndef GERBE_H
#define GERBE_H
#include<vector>
#include"maille.h"
#include"reseau.h"
#include <iostream>
#include <fstream>
class gerbe
{
static int k;
private:
double teta,phi,xi,yi;
double xi_exp,yi_exp; /* gerbe exp soeur reconstruite par le reseau */
double E_exp;
double E;
int numero;
public:
gerbe();
void gerbe_exp_get_impact(double,double); /* recoit les nouveaux x et y d'impactes
reconstruits par le reseau */
void gerbe_exp_get_energie(double);
double x_i();
double y_i();
double teta_i();
double phi_i();
double E_i();
void ajuster_domaine_des_impacts(reseau);
void affiche_numero();
void affiche();
void affiche_impact_py(std::ofstream&);
void Hit(reseau&);
void Hit_exp(reseau&,int);/* meme fonction que Hit mais avec l'impact reconstruit*/


double ecart_energie(); /* a multiplier par 100 pour avoir le pourcentage */
double ecart_x(); /* a multiplier par 100 pour avoir le pourcentage */
double ecart_y(); /* a multiplier par 100 pour avoir le pourcentage */
};

#endif
