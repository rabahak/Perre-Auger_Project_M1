#ifndef FONCTIONS_H
#define FONCTIONS_H
#include "gerbe.h"
#include "reseau.h"

namespace fonctions
{
void OUTPUT_IMPACT_PY(gerbe*,int,reseau,int);
void OUTPUT_ENERGIE_PY(gerbe*,int,reseau,int);
void AFFICHE_RESULTAT(gerbe*,int,reseau,int);
void COMPARAISON(gerbe*,int,int);
void ECART_RELATIF_MOYEN_PY(gerbe*,int,reseau,int);
void ECART_RELATIF_MOYEN_Impactx_PY(gerbe*,int,reseau,int);
}
#endif



//FONCTIONS GLOBALES
/*
#ifndef FONCTIONS_H
#define FONCTIONS_H
#include "gerbe.h"
#include "reseau.h"

void OUTPUT_IMPACT_PY(gerbe*,int,reseau,int);
void OUTPUT_ENERGIE_PY(gerbe*,int,reseau,int);
void AFFICHE_RESULTAT(gerbe*,int,reseau,int);
void COMPARAISON(gerbe*,int,int);
void ECART_RELATIF_MOYEN_PY(gerbe*,int,reseau,int);
void ECART_RELATIF_MOYEN_Impactx_PY(gerbe*,int,reseau,int);
#endif
*/
