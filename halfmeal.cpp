// halfmeal.cpp

#include <string>
#include <vector>
#include <iostream>
#include "halfmeal.h"
#include "fooddatabase.h"
#include "ingredient.h"
using std::vector;
using std::string;
using std::pair;
using std::cout;
using std::endl;

typedef vector< pair< string,size_t > >::const_iterator vpiter;
typedef vector<string>::const_iterator vsiter;

Halfmeal::Halfmeal(size_t freq) : m_freq(freq), m_foodNames( vector<string>(0) ) 
{
}

const vector<string>& Halfmeal::getFoodNames() const
{
  return m_foodNames;
}

const Ingredient& Halfmeal::getIngred(string type, const FoodDatabase& fdb, const vector< pair< string, size_t > >& used, const vector< pair< string, size_t > >& haveLeft)
{

  // Look for an ingredient that we already have in the amount needed.  

  vector<string> haveEnough(0);
  for (vpiter it = haveLeft.begin(); it != haveLeft.end(); ++it)
    {
      if (it->second >= m_freq && !findIfItemInHalfmeal(it->first) )
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

  // If we don't have enough of anything, see if we have just some of something.

  vector<string> haveSome(0);
  for (vpiter it3 = haveLeft.begin(); it3 != haveLeft.end(); ++it3)
    {
      if (it3->second < m_freq  && !findIfItemInHalfmeal(it3->first))
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

  // If we don't have enough or even some of anything, pick a random ingredient not used in this meal.

  return fdb.getRandomIngred(type,m_foodNames);

}

bool Halfmeal::findIfItemInHalfmeal( const string& item ) const
{
  for (vsiter it = m_foodNames.begin(); it != m_foodNames.end(); ++it)
    {
      if (*it == item)
	return true;
    }
  return false;
}







