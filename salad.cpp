// salad.cpp

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include "halfmeal.h"
#include "salad.h"
#include "ingredient.h"
#include "fooddatabase.h"
using std::string;
using std::vector;
using std::pair;
using std::cout;
using std::endl;

Salad::Salad( const FoodDatabase& fdb, const vector< pair< string, size_t > >& used, const vector< pair< string, size_t > >& haveLeft, size_t freq) : Halfmeal( freq )
{

  m_green = getIngred("green", fdb, used, haveLeft);
  m_foodNames.push_back(m_green.getName());

  m_topping1 = getIngred("salad topping", fdb, used, haveLeft);
  m_foodNames.push_back(m_topping1.getName());
 
  m_topping2 = getIngred("salad topping", fdb, used, haveLeft);
  m_foodNames.push_back(m_topping2.getName());

  m_topping3 = getIngred("salad topping", fdb, used, haveLeft);
  m_foodNames.push_back(m_topping3.getName());

  m_topping4 = getIngred("salad topping", fdb, used, haveLeft);
  m_foodNames.push_back(m_topping4.getName());

  m_dressing = getIngred("salad dressing", fdb, used, haveLeft);
  m_foodNames.push_back(m_dressing.getName()); 

}

void Salad::printHalfmeal() const
{
  cout << "Salad: " << m_green << ", " << m_topping1;
  cout << ", " << m_topping2 << ", " << m_topping3;
  cout << ", " << m_topping4 << ", " << m_dressing;
  cout << endl;
}

double Salad::getCost() const
{
  double cost = 0;
  cost += m_green.getCost();
  cost += m_topping1.getCost() + m_topping2.getCost() + m_topping3.getCost();
  cost += m_dressing.getCost();
  return cost;
}
