//GEOMETRIQUE
#include "maille.h"
#include <cmath>
#include <iostream>
#include <vector>
#include"constantes.h"

#include <iostream>
#include <fstream>

using namespace std;

// c[i] = (a_i,x_i,y_i,d(i,1),s(i,1),d(i,2),s(i,2),...d(i,n_gerbes),s(i,n_gerbes))

maille::maille()
{ // constructeur sans argument cree une maille centree sur 0 automatiquement
c=new vector<double>[3]; // 3 cuves par maille
for(int i=0;i<3;i++)
{
if(i==0)
c[i].push_back(0);
else
c[i].push_back(c[i-1][0]+2*M_PI/3);

c[i].push_back(r*cos(c[i][0]));
c[i].push_back(r*sin(c[i][0]));
}

c_exp=new vector<double>[3]; // pour chaque cuve on aura : d_exp et E_exp pour chaque gerbe

}


//qui n'est autre que faire :
/*
c[0].push_back(0); //a1 (angle depuis l'axe des x)
c[0].push_back(r*cos(c[0][0])); //x1
c[0].push_back(r*sin(c[0][0])); //y1

c[1].push_back(c[0][0]+2*M_PI/3); // = 120 deg
c[1].push_back(r*cos(c[1][0])); //x2
c[1].push_back(r*sin(c[1][0])); //y2

c[2].push_back(c[1][0]+2*M_PI/3); // = 240 degs
c[2].push_back(r*cos(c[2][0])); //x3
c[2].push_back(r*sin(c[2][0])); //y3 */


double maille::a(int n) // n=0 designe la premiere cuve
{
return c[n][0];
}
double maille::x(int n)
{
return c[n][1];
}

double maille::y(int n)
{
return c[n][2];
}
double maille::d(int n,int i)
{
return c[n][3+i*2]; // car les 3 premieres cases sont reservees a: 1-angle, 2-x, 3-y et 2*i car entre deux distance on restore le data de signal
}
double maille::s(int n,int i)
{
return c[n][4+i*2]; // car les 4 premieres cases sont reserves a: 1-angle, 2-x, 3-y, 4-d1 et decalee d'une case de la distance
}
void maille::test_py(ofstream& file)
{
//pour python
//file<<0<<" "<<0<<endl; // le centre
file<<x(0)<<" "<<y(0)<<endl;
file<<x(1)<<" "<<y(1)<<endl;
file<<x(2)<<" "<<y(2)<<endl;
}


void maille::test()
{
cout<<"(x0,y0) = ("<<x(0)<<","<<y(0)<<")"<<endl;
cout<<"(x1,y1) = ("<<x(1)<<","<<y(1)<<")"<<endl;
cout<<"(x2,y2) = ("<<x(2)<<","<<y(2)<<")"<<endl;
}

void maille::centre(double Centre_x,double Centre_y)
{
for(int i=0;i<3;i++) // pour les trois cuves de la maille
{c[i][1]+=Centre_x;//chaque x de la cuve est translatee 
c[i][2]+=Centre_y;//chaque  y de la cuve est translatee
}}

void maille::distance(int numero_cuve, double Dist)
{
c[numero_cuve].push_back(Dist);
}

void maille::signal(int numero_cuve,double Sign)
{
c[numero_cuve].push_back(Sign);
}

void maille::distance_exp(int numero_cuve,double Dist_exp)
{
c_exp[numero_cuve].push_back(Dist_exp);
}

void maille::energie_exp(int numero_cuve,double En_exp)
{
c_exp[numero_cuve].push_back(En_exp);
}
double maille::d_exp(int n,int i)
{
return c_exp[n][i*2];
}
double maille::E_exp(int n,int i)
{
return c_exp[n][i*2+1];
}







/*
#include "maille.h"
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

maille::maille(double o): centre(o)
{

  const int d=1500; // distance fixe entre deux detecteurs en metres (1.5 km)


  //POLAIRES
  r=(sqrt(3)/3)*d; //distance de l'orthocentre a l'une des sommets d'un triangle equilateral
  a1=0;            //l'angle d'une des sommets
  a2=a1+2*M_PI/3;
  a3=a2+2*M_PI/3;
  
  if(centre==0) // c'est preferable car xi=uniforme(-r,r); //cercle cadrant la maille triangulaire , else il faut changer xi et yi
  {
// pour un repere de centre = centre du gravite de la maille triangulaire  // CODE : rose dans le schema
  //CARTESIENNES
  x1=r*cos(a1);
  y1=r*sin(a1);
  x2=r*cos(a2);
  y2=r*sin(a2);
  x3=r*cos(a3);
  y3=r*sin(a3);
  }
 else
  {
// pour un repere de centre = un des sommets du rectangle // CODE: rouge dans le schema

x1=0;
y1=0;

x2=d*cos(0);
y2=d*sin(0);

x3=d*cos(M_PI/3); // = d/2
y3=d*sin(M_PI/3); 

}
}

void maille::test()
{

cout<<"les coordonnees polaires sont: (r,a1,a2,a3) = ("<<r<<","<<a1<<","<<a2<<","<<a3<<")"<<endl;
cout<<"le centre est o == "<<centre<<endl;
cout<<"les coordonnees cartesiennes correspondantes:"<<endl;
cout<<"(x1,y1) = ("<<x1<<","<<y1<<")"<<endl;
cout<<"(x2,y2) = ("<<x2<<","<<y2<<")"<<endl;
cout<<"(x3,y3) = ("<<x3<<","<<y3<<")"<<endl;


//pour python
cout<<0<<" "<<0<<endl; // le centre
cout<<x1<<" "<<y1<<endl;
cout<<x2<<" "<<y2<<endl;
cout<<x3<<" "<<y3<<endl;

}

std::vector<double> maille::d(int n)
{
std::vector<double> a;
if(n==1){
a.push_back(x1);
a.push_back(y1);
return a;
}
if(n==2)
{
a.push_back(x2);
a.push_back(y2);
return a;
}
if(n==3)
{
a.push_back(x3);
a.push_back(y3);
return a;
}

}*/
 

