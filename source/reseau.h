
#ifndef RESEAU_H
#define RESEAU_H
#include"maille.h"

class reseau
{
private:
maille* T;
int couche_indice;
int n_maille;
 public:
  reseau(int);
  void affiche_reseau_py();
  void affiche_E_exp_py(int);
  void affiche_reseau();
  int nombre_de_mailles();
  maille maille_numero(int);
  int nombre_de_couches();
  int nombre_declenchees(int); //(numero_gerbe)
  
  /* reconstruit x et y sont caracteristiques du reseau car c'est a l'aide de
  tous les reseaus qu'on reconstruit le point d'impacte, or la distance et
  l'energie sont caracteristiques de chaque cuve de la maille, on leur trouve donc
  dans la class maille */
  
  /*Methode 1: barycentre de toutes les cuves declenchees */
  double reconstruit1_x(int); /* reconstruit_x(int numero_gerbe)*/
  double reconstruit1_y(int);
  
  /*Methode 2: barycentre des 3 cuves ayant les signals maximales*/
  double reconstruit2_x(int); /* reconstruit_x(int numero_gerbe)*/
  double reconstruit2_y(int);
  
  double reconstruit_E_moy(int);
  
};
#endif
