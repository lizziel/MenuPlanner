// burger.cpp

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include "halfmeal.h"
#include "burger.h"
#include "ingredient.h"
#include "fooddatabase.h"
using std::string;
using std::vector;
using std::pair;
using std::cout;
using std::endl;

Burger::Burger( const FoodDatabase& fdb, const vector< pair< string, size_t > >& used, const vector< pair< string, size_t > >& haveLeft, size_t freq) : Halfmeal( freq )
{
  m_burger = getIngred( "burger filling", fdb, used, haveLeft );
  m_foodNames.push_back(m_burger.getName());

  m_bun = fdb.getSpecificIngred("burger bread", "hamburger bun");
  m_foodNames.push_back(m_bun.getName());

  m_topping1 = getIngred("burger topping", fdb, used, haveLeft);
  m_foodNames.push_back(m_topping1.getName());

  m_topping2 = getIngred("burger topping", fdb, used, haveLeft);
  m_foodNames.push_back(m_topping2.getName());
}

void Burger::printHalfmeal() const
{
  cout << "Burger: " << m_burger << ", " << m_bun;
  cout << ", " << m_topping1 << ", " << m_topping2;
  cout << endl;
}

double Burger::getCost() const
{
  double cost = 0;
  cost += m_burger.getCost();
  cost += m_bun.getCost();
  cost += m_topping1.getCost() + m_topping2.getCost();
  return cost;
}


