// meal.cpp

#include <vector>
#include <string>
#include <iostream>
#include "meal.h"
#include "fooddatabase.h"
#include "ingredient.h"
using std::vector;
using std::string;
using std::pair;
using std::cout;
using std::endl;


typedef vector< pair< string,size_t > >::const_iterator vpiter;
typedef vector<string>::const_iterator vsiter;

Meal::Meal(size_t ID, size_t freq) 
  : m_ID(ID), m_freq(freq), m_foodInMeal( vector< string >(0) )
{
}

size_t Meal::getID() const
{
  return m_ID;
}

size_t Meal::getFreq() const
{
  return m_freq;
}

const std::vector< std::string >& Meal::getFoodInMeal() const
{
  return m_foodInMeal;
}

bool Meal::findIfItemInVec( const string& item, const vector< pair< string,size_t > >& vec) const
{
  for ( vpiter it = vec.begin(); it != vec.end(); ++it)
    { 
      if (it->first == item)
	  return true;
    }
  return false;
}

const Ingredient& Meal::getIngred(string type, const FoodDatabase& fdb, const vector< pair< string, size_t > >& used, const vector< pair< string, size_t > >& haveLeft)
{

  // Preference is to get ingredient which we already have the needed amount of

  vector<string> haveEnough(0);
  for (vpiter it = haveLeft.begin(); it != haveLeft.end(); ++it)
    {
      if (it->second >= m_freq)
        {
          haveEnough.push_back( it->first );
        }
    }
  if ( !haveEnough.empty() )
    {
      std::random_shuffle(haveEnough.begin(), haveEnough.end());
      for (vsiter it2 = haveEnough.begin(); it2 != haveEnough.end(); ++it2)
        {
          if ( fdb.checkIngredType(type,*it2) )
            {
              return fdb.getSpecificIngred(type,*it2);
            }
        }
    }

  // If this is not possible, then try to get ingredient for which we have some amount

  vector<string> haveSome(0);
  for (vpiter it3 = haveLeft.begin(); it3 != haveLeft.end(); ++it3)
    {
      if (it3->second < m_freq)
        {
          haveSome.push_back( it3->first );
        }
    }
  if ( !haveSome.empty() )
    {
      std::random_shuffle(haveSome.begin(), haveSome.end());
      for (vsiter it4 = haveSome.begin(); it4 != haveSome.end(); ++it4)
	{
	  if ( fdb.checkIngredType(type,*it4) )
	    {
	      return fdb.getSpecificIngred(type,*it4);
	    }
	}
    }

  // If this is also not possible, get a random ingredient trying not to get what's used already
 
  vector<string> usedNames(0);
  for ( vpiter veci = used.begin(); veci != used.end(); ++veci)
    {
      usedNames.push_back( veci->first );
    }
  return fdb.getRandomIngred(type,usedNames);

}
