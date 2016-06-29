/*
integral f(x)dx a->b
tabela
(xi,f(xi))
1<=i<=k
k>=10
input: nro de subintervalos
      escolha da regra
output: aproximação da integral de acordo com a regra

regras:
  - ponto medio
  - trapezios
  - simpson (n sempre par)
  - quadratura gaussiana (até caso n=6)
*/

#include <iostream>
#include <utility>
#include <vector>
#include <fstream>
#include <math.h>

#ifdef __linux__
    #define CLEAR "clear"
#elif _WIN64
    #define CLEAR "cls"
#elif __APPLE__
    #define CLEAR "clear"
#endif

using namespace std;

#define B 5
#define A 1

// ASSINATURAS DAS FUNCOES
int intervalMenu();
long double ruleMenu(vector<pair<long double, long double> >);
void clearScreen();

vector<pair<long double, long double> > readTable(string, int);

long double calcFunction(long double);

long double ponto_medio(vector<pair<long double, long double> >);
long double trapezios(vector<pair<long double, long double> >);
long double simpson(vector<pair<long double, long double> >);
long double gaussiana(vector<pair<long double, long double> >);

int main()
{
  int interval, rule;
  vector<pair<long double, long double> > intervalPoints;
  long double result;

  interval = intervalMenu();
  intervalPoints = readTable("table.txt", interval);
  result = ruleMenu(intervalPoints);
  cout << "Resultado final: " << result << endl;
  return 0;
}

long double calcFunction(long double x_value)
{
  return 2*(x_value*x_value*x_value)+3*(x_value*x_value)+6*(x_value)+1;
}

int intervalMenu()
{
  int interval;

  cout << "Escreva a quantidade de subintervalos que gostaria de utilizar:" \
    << endl;
  cin >> interval;

  return interval;
}

vector<pair<long double, long double> > readTable(string filename, int interval)
{
  ifstream file;
  vector<pair<long double, long double> > intervalPoints;
  long double xi, fxi, x;

  file.open(filename, ifstream::in);
  if(file.is_open())
  {
    for(int i=0; i<interval && file.good(); ++i)
    {
      file >> xi;
      file >> fxi;
      if(file.eof()) break;
      intervalPoints.push_back(make_pair(xi, fxi));
    }
  }

  file.close();

  return intervalPoints;
}

// Menu inicial de escolha das regras
long double ruleMenu(vector<pair<long double, long double> > intervalPoints)
{
    int op;
    long double result;

    clearScreen();
    cout << "1- Regra do Ponto Médio\n2 - Regra dos Trapézios \
            \n3 - Regra de Simpson(n sempre par) \
            \n4 - Quadratura Gaussiana(n=6) \
            \n5 - Sair" << endl;
    cin >> op;

    clearScreen();
    switch(op)
    {
        case 1:
            result = ponto_medio(intervalPoints);
            break;
        case 2:
            result = trapezios(intervalPoints);
            break;
        case 3:
            result = simpson(intervalPoints);
            break;
        case 4:
            result = gaussiana(intervalPoints);
            break;
        case 5:
            printf("Saindo..\n");
            break;
        default:
            cin.get();
            cout << "Opção inválida." << endl;
            break;
    }

    return result;
}

void clearScreen()
{
    system(CLEAR);
}

long double ponto_medio(vector<pair<long double, long double> > intervalPoints)
{
  vector<long double> med;
  long double H, sum_fxi_med=0, points_size = intervalPoints.size();

  if(points_size > 1)
  {
    H=(B-A)/(points_size-1);
    for(int i=0; i<points_size-1; ++i)
    {
      med.push_back((intervalPoints[i].first+intervalPoints[i+1].first)/2);
      sum_fxi_med+=calcFunction(med[i]);
    }
  }
  return H*sum_fxi_med;
}

// TODO caso 1 intervalo
long double trapezios(vector<pair<long double, long double> > intervalPoints)
{
  vector<long double> trap;
  long double H, sum_fxi=0, points_size = intervalPoints.size();
  int i=0;

  if(points_size > 1)
  {
    H=(intervalPoints[1].first-intervalPoints[0].first);
    trap.push_back(intervalPoints[i].second);
    sum_fxi+=trap[i];
    for(i=1; i<points_size-1; ++i)
    {
      trap.push_back(2*intervalPoints[i].second);
      sum_fxi+=trap[i];
    }
    trap.push_back(intervalPoints[i].second);
    sum_fxi+=trap[i];
  }

  return (H/2)*sum_fxi;
}

long double simpson(vector<pair<long double, long double> > intervalPoints)
{
  vector<long double> trap;
  long double H, sum_fxi=0, points_size = intervalPoints.size();
  int i=0;

  if(points_size > 1)
  {
    H=(intervalPoints[1].first-intervalPoints[0].first);
    trap.push_back(intervalPoints[i].second);
    sum_fxi+=trap[i];
    for(i=1; i<points_size-1; ++i)
    {
      if(i%2) trap.push_back(4*intervalPoints[i].second);
      else trap.push_back(2*intervalPoints[i].second);
      sum_fxi+=trap[i];
    }
    trap.push_back(intervalPoints[i].second);
    sum_fxi+=trap[i];
  }
  return (H/3)*sum_fxi;
}

long double gaussiana(vector<pair<long double, long double> > intervalPoints)
{
  vector<pair<long double, long double> > newIntervalPoints = readTable("table-gauss.txt", 6);
  long double H, JC, sum_fxi=0, points_size = newIntervalPoints.size();

  if(points_size > 1)
  {
    H=(B-A)/2;
    JC=(B+A)/2;
    for(int i=0; i<points_size-1; ++i)
    {
      sum_fxi+=newIntervalPoints[i].second*JC*calcFunction((JC*newIntervalPoints[i].first)+H);
    }
  }
  return sum_fxi;
}
