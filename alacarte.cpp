// alacarte.cpp

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include "meal.h"
#include "alacarte.h"
#include "ingredient.h"
#include "fooddatabase.h"
using std::string;
using std::vector;
using std::pair;
using std::cout;
using std::endl;

typedef vector< pair< string,size_t> >::const_iterator vpiter;
typedef vector<string>::const_iterator vsiter;

Alacarte::Alacarte( const FoodDatabase& fdb, const vector< pair< string, size_t > >& used, const vector< pair< string, size_t > >& haveLeft, size_t ID, size_t freq) : Meal( ID, freq )
{

  m_veg = getIngred("vegetable", fdb, used, haveLeft);
  m_foodInMeal.push_back(m_veg.getName());

  m_protein = getIngred("protein", fdb, used, haveLeft);
  m_foodInMeal.push_back(m_protein.getName());

  m_starch = getIngred("starch", fdb, used, haveLeft);
  m_foodInMeal.push_back(m_starch.getName());

  //m_savory = getIngred("savory", fdb, used, haveLeft);
  //m_foodInMeal.push_back(m_savory.getName());

} 

void Alacarte::printMeal() const
{
  cout << "Meal " << m_ID << endl;
  cout << "\tPlate: ";
  cout << m_protein.getName();
  cout << ", " << m_starch.getName();
  cout << ", " << m_veg.getName();
  cout << endl;
  //cout << ", " << m_savory.getName();
  cout << "\tFrequency: " << m_freq << endl;
}

double Alacarte::getMealCost() const
{
  //double cost = m_veg.getCost() + m_protein.getCost() + m_starch.getCost() + m_savory.getCost();
  double cost = m_veg.getCost() + m_protein.getCost() + m_starch.getCost();
  return cost;
}
