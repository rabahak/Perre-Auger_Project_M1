#ifndef MAILLE_H
#define MAILLE_H
#include <vector>
#include <iostream>
#include <fstream>
class maille
{
private:
std::vector<double>* c; /* pointeur de cuves (chaque cuve est representee par un vecteur)*/
/* c[i] = (a_i,x_i,y_i,d(i,0),s(i,0),d(i,1),s(i,1),...d(i,n_gerbes-1),s(i,n_gerbes-1)) */
std::vector<double>* c_exp; /* chaque numero de case correspond a numero_cuve*/
/* c_exp[i] = (d_exp(i,0),E_exp(i,0),...d_exp(i,n_gerbe-1),E_exp(i,n_gerbe-1))*/
public:
maille();

void test_py(std::ofstream&);
void test();

void centre(double,double);//fonction pour modifier le centre de la maille (le translater)

void distance(int,double);//fonction pour modifier les datas de la cuve en ajoutant au vecteur c[i] la distance correspondante
//apres quelle soit calculee par la fonction hit(maille) 

void signal(int,double);//fonction pour modifier les datas de la cuve en ajoutant au vecteur c[i] le signal

void distance_exp(int,double);

void energie_exp(int,double);

double a(int); // retourne l'angle de la cuve correspondante selon le repere pris
double x(int); // retourne la coordonne'e x de la cuve correspondante
double y(int); // retourne la coordonne'e y de la cuve correspondante
double d(int,int); // retourne la distance_de_l'axe_de_la_gerbe(numero_cuve,numero_gerbe)
double s(int,int); // retourne le signal en VEM restaure' en (numero_cuve,numero_gerbe)

double d_exp(int,int);
double E_exp(int,int); // retourne l'energie de la gerbe re-calculee par chaque detecteur (numero_cuve,numero_gerbe)

/* s_exp = s */
};
#endif

