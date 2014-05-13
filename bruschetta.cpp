// bruschetta.cpp

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include "halfmeal.h"
#include "bruschetta.h"
#include "ingredient.h"
#include "fooddatabase.h"
using std::string;
using std::vector;
using std::pair;
using std::cout;
using std::endl;

Bruschetta::Bruschetta( const FoodDatabase& fdb, const vector< pair< string, size_t > >& used, const vector< pair< string, size_t > >& haveLeft, size_t freq) : Halfmeal( freq )
{
  m_bread = fdb.getSpecificIngred( "bruschetta bread", "baguette" );
  m_foodNames.push_back(m_bread.getName());

  m_topping1 = getIngred("bruschetta topping", fdb, used, haveLeft);
  m_foodNames.push_back(m_topping1.getName());

  m_topping2 = getIngred("bruschetta topping", fdb, used, haveLeft);
  m_foodNames.push_back(m_topping2.getName());

  m_topping3 = getIngred("bruschetta topping", fdb, used, haveLeft);
  m_foodNames.push_back(m_topping3.getName());
}

void Bruschetta::printHalfmeal() const
{
  cout << "Bruschetta: " << m_bread.getName() << ", " << m_topping1;
  cout << ", " << m_topping2 << ", " << m_topping3;
  cout << endl;
}

double Bruschetta::getCost() const
{
  double cost = 0;
  cost += m_bread.getCost();
  cost += m_topping1.getCost() + m_topping2.getCost() + m_topping3.getCost();
  return cost;
}
