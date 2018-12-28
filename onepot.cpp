// alacarte.cpp

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include "meal.h"
#include "onepot.h"
#include "ingredient.h"
#include "fooddatabase.h"
using std::string;
using std::vector;
using std::pair;
using std::cout;
using std::endl;

typedef vector< pair< string,size_t> >::const_iterator vpiter;
typedef vector<string>::const_iterator vsiter;

Onepot::Onepot( const FoodDatabase& fdb, const vector< pair< string, size_t > >& used, const vector< pair< string, size_t > >& haveLeft, size_t ID, size_t freq) : Meal( ID, freq )
{
  m_onepot = getIngred("onepot", fdb, used, haveLeft);
  m_foodInMeal.push_back(m_onepot.getName());
} 

void Onepot::printMeal() const
{
  cout << "Meal " << m_ID << endl;
  cout << "\tBowl: " << m_onepot.getName() << endl;
  cout << "\tFrequency: " << m_freq << endl;
}

double Onepot::getMealCost() const
{
  double cost = m_onepot.getCost();
  return cost;
}
