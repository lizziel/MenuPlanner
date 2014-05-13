// foodgroup.cpp

//#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include "foodgroup.h"
#include "ingredient.h"
using std::vector;
using std::string;

typedef vector<Ingredient>::const_iterator iiter;

FoodGroup::FoodGroup(const string name) : m_type(name) 
{
}

std::string FoodGroup::getType() const
{
  return m_type;
}

void FoodGroup::addFood(const string name, const double cost)
{
  Ingredient newFood(name, cost);
  m_foodGroupVector.push_back(newFood);
}

const Ingredient& FoodGroup::getIngred(const string& name) const
{
  for (iiter it = m_foodGroupVector.begin(); it != m_foodGroupVector.end(); ++it)
    {
      if (it->getName() == name)
	return *it;
    }
  std::cout << name << std::endl;
  throw std::logic_error ("Asked foodgroup for an ingredient it does not contain.");
}

bool FoodGroup::contains( const string& name ) const
{
  for (iiter it = m_foodGroupVector.begin(); it != m_foodGroupVector.end(); ++it)
    {
      if (it->getName() == name)
	return true;
    }
  return false;
}

const Ingredient& FoodGroup::getRandomIngred() const
{
  size_t randpos = std::rand() % m_foodGroupVector.size();
  return m_foodGroupVector[randpos];
}

const Ingredient& FoodGroup::getRandomIngredButNot( const vector<string>& noList ) const
{

  vector< size_t > possibleIngredsPos(0);
  size_t counter = 0;
  for( iiter it = m_foodGroupVector.begin(); it != m_foodGroupVector.end(); ++it)
    {
      if ( std::find( noList.begin(), noList.end(), it->getName() ) == noList.end() )
	{
	  possibleIngredsPos.push_back( counter );
	} 
      ++counter;
    }
  if ( possibleIngredsPos.empty() )
    return getRandomIngred();
  else
    {
      size_t randpos = rand() % possibleIngredsPos.size();
      return m_foodGroupVector[ possibleIngredsPos[randpos] ];
    }
}

