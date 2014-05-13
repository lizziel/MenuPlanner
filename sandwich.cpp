// bruschetta.cpp                                                                           

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include "halfmeal.h"
#include "sandwich.h"
#include "ingredient.h"
#include "fooddatabase.h"
using std::string;
using std::vector;
using std::pair;
using std::cout;
using std::endl;

Sandwich::Sandwich( const FoodDatabase& fdb, const vector< pair< string, size_t > >& used, const vector< pair< string, size_t > >& haveLeft, size_t freq) : Halfmeal( freq )
{
  m_bread = getIngred( "sandwich bread", fdb, used, haveLeft );
  m_foodNames.push_back(m_bread.getName());

  m_mainfilling = getIngred("sandwich main filling", fdb, used, haveLeft);
  m_foodNames.push_back(m_mainfilling.getName());

  m_topping1 = getIngred("sandwich topping", fdb, used, haveLeft);
  m_foodNames.push_back(m_topping1.getName());

  m_topping2 = getIngred("sandwich topping", fdb, used, haveLeft);
  m_foodNames.push_back(m_topping2.getName());
}

void Sandwich::printHalfmeal() const
{
  cout << "Sandwich: " << m_bread << ", " << m_mainfilling;
  cout << ", " << m_topping1 << ", " << m_topping2;
  cout << endl;
}

double Sandwich::getCost() const
{
  double cost = 0;
  cost += m_bread.getCost();
  cost += m_mainfilling.getCost();
  cost += m_topping1.getCost() + m_topping2.getCost();
  return cost;
}


