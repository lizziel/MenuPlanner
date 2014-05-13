// soup.cpp

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include "halfmeal.h"
#include "soup.h"
#include "ingredient.h"
#include "fooddatabase.h"
using std::string;
using std::vector;
using std::pair;
using std::cout;
using std::endl;

Soup::Soup( const FoodDatabase& fdb, const vector< pair< string, size_t > >& used, const vector< pair< string, size_t > >& haveLeft, size_t freq) : Halfmeal( freq )
{
  m_soup = getIngred("soup", fdb, used, haveLeft);
  m_foodNames.push_back(m_soup.getName());
}

void Soup::printHalfmeal() const
{
  cout << "Soup: " << m_soup << endl;
}

double Soup::getCost() const
{
  double cost = m_soup.getCost();
  return cost;
}


