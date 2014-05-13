// pairmeal.cpp

#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>
#include "fooddatabase.h"
#include "meal.h"
#include "pairmeal.h"
#include "halfmeal.h"
#include "bruschetta.h"
#include "sandwich.h"
#include "salad.h"
#include "burger.h"
#include "soup.h"
using std::string;
using std::vector;
using std::pair;
using std::cout;
using std::endl;

typedef vector< pair< string, size_t> >::const_iterator vpiter;
typedef vector<string>::const_iterator vsiter;

Pairmeal::Pairmeal(const FoodDatabase& fdb, const vector< pair<string,size_t> >& used, const vector< pair<string, size_t > >& haveleft, size_t ID, size_t freq) : Meal (ID, freq )
{

  // If we have baguette, automatically make bruschetta or sandwich
  // If instead have hamburger, automatically make burger
  // In either case, pair it with soup or salad
  
  if ( findIfItemInVec( "baguette", haveleft ) ||  findIfItemInVec("veggie burger", haveleft) || findIfItemInVec("salmon burger", haveleft) || findIfItemInVec("hamburger",haveleft) )
    {

      if ( findIfItemInVec( "baguette", haveleft ) )
	{
	  size_t randfirst = rand() % 2;
	  if (randfirst == 0)
	    {
	      m_first = new Bruschetta(fdb, used, haveleft, freq);	  
	    }
	  else
	    {
	      m_first = new Sandwich(fdb, used, haveleft, freq);
	    }
	}
      else 
	{
	  m_first = new Burger(fdb, used, haveleft, freq);
	}
      size_t randsecond = rand() % 2;
      m_second = getNewHalfmeal( randsecond, fdb, used, haveleft, freq );
    }

  // otherwise pick a halfmeal type randomly
  // if we get something with bread, pick soup or salad to go with it
  // else, pick anything to go with it except itself

    else
      {
	size_t randfirst = rand() % 5;
	m_first = getNewHalfmeal( randfirst, fdb, used, haveleft, freq );
	if (randfirst == 2 || randfirst == 3 || randfirst == 4)
	  {
	    size_t randsecond = rand() % 2;
	    m_second = getNewHalfmeal( randsecond, fdb, used, haveleft, freq );
	  }
	else
	  {
	    size_t randsecond = rand() % 4;
	    while (randsecond == randfirst)
	      {
		randsecond = rand() % 4;
	      }
	    m_second = getNewHalfmeal( randsecond, fdb, used, haveleft, freq );
	  }
      }

  // build m_foodinmeal
  vector<string> firstFoods = m_first->getFoodNames();
  vector<string> secondFoods = m_second->getFoodNames();
  for ( vector<string>::const_iterator it = firstFoods.begin(); it != firstFoods.end(); ++it)
    {
      m_foodInMeal.push_back( *it );
    }
  for ( vector<string>::const_iterator it2 = secondFoods.begin(); it2 != secondFoods.end(); ++it2)
    {
      // in future version, add a check that item not in first halfmeal
      m_foodInMeal.push_back( *it2 );
    }
}


Pairmeal::~Pairmeal()
{
  delete m_first;
  delete m_second;
}

void Pairmeal::printMeal() const
{
  cout << "Meal " << m_ID << endl;
  cout << "\tFrequency: " << m_freq << endl;
  cout << "\t";
  m_first->printHalfmeal();
  cout << "\t"; 
  m_second->printHalfmeal();
  cout << endl;
}

Halfmeal* Pairmeal::getNewHalfmeal( size_t num, const FoodDatabase& fdb, const vector< pair<string,size_t> >& used, const vector< pair<string, size_t > >& haveleft, size_t freq ) const
{ 
  Halfmeal* halfptr;
  switch ( num )
    {
    case 0:
      halfptr = new Salad(fdb, used, haveleft, freq);
      return halfptr;
    case 1:
      halfptr = new Soup(fdb, used, haveleft, freq);
      return halfptr;
    case 2:
      halfptr = new Bruschetta(fdb, used, haveleft, freq);
      return halfptr;      
    case 3:
      halfptr = new Sandwich(fdb, used, haveleft, freq);
      return halfptr;
    case 4:
      halfptr = new Burger(fdb, used, haveleft, freq);
      return halfptr;
    default:
      throw std::logic_error ("Change to out of bounds exception");
    }
  return halfptr;
}

double Pairmeal::getMealCost() const
{
  double cost = m_first->getCost() + m_second->getCost();
  return cost;
}
