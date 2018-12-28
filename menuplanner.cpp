// menuplanner.cpp

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <map>
#include "menuplanner.h"
#include "fooddatabase.h"
#include "pairmeal.h"
#include "alacarte.h"
#include "onepot.h"

using std::string;
using std::vector;
using std::pair;
using std::cout;
using std::endl;

typedef vector< pair< string,size_t > >::const_iterator ssiter;
typedef vector< string >::const_iterator siter;

MenuPlanner::MenuPlanner(const FoodDatabase& fdb, const string foodWeHaveFile, size_t numLun, size_t numDin) 
  : m_fdb(fdb), m_menu(numLun,numDin), m_have(vector< pair<string,size_t> >(0)), m_haveLeft(vector< pair<string,size_t> >(0)), m_used(vector< pair<string,size_t> >(0))
{
  pair< string, size_t > tempHave; 
  string name, amount_str;
  size_t amount;

  std::ifstream file (foodWeHaveFile.c_str() );
  if (file.is_open() )
    {
      string txtline;
      while ( !file.eof() )
	{
	  std::getline( file, txtline );
	  if (txtline.length() == 0)
	    continue;
	  std::istringstream subline( txtline );
	  getline( subline, name, ',' );
	  getline( subline, amount_str, ';' );
	  amount = atoi ( amount_str.c_str() );
	  tempHave = make_pair ( name, amount );
	  m_have.push_back( tempHave );
	  m_haveLeft.push_back( tempHave );
	}
    }
  else 
    std::cerr << "Failed to open file: " << foodWeHaveFile << std::endl;
}

MenuPlanner::~MenuPlanner()
{
}

void MenuPlanner::makeMenu()
{
  size_t ID = 0;
  size_t freq = 0;

  while (++ID <= m_menu.getNumMeals() )
    {

      if ( ID <= m_menu.getNumMealsWithFreq(2) )
	{
	  freq = 2;     
	}
      else if ( ID <= m_menu.getNumMealsWithFreq(2) + m_menu.getNumMealsWithFreq(1) )
	{
	  freq = 1;
	}
      else
	{
	  throw std::logic_error ("Meal ID exceeds number of meals planned.");
	}

      // set algorithm for choosing meal type
      size_t randnum = std::rand() % 5;      
      if ( randnum <= 1 ) 
	{
	  Alacarte* newAlaPtr = new Alacarte( m_fdb, m_used, m_haveLeft, ID, freq );
	  m_menu.addMeal( newAlaPtr );
	}
      else if ( randnum <= 3 )
	{    
	  Onepot* newOnepotPtr = new Onepot( m_fdb, m_used, m_haveLeft, ID, freq );
	  m_menu.addMeal( newOnepotPtr );
	} 
      else   
	{    
	  Pairmeal* newPairPtr = new Pairmeal( m_fdb, m_used, m_haveLeft, ID, freq );
	  m_menu.addMeal( newPairPtr );
	} 
      updateFoodLists( m_menu.getMealIngreds(ID), freq );

    }

  m_menu.printMenu();
  printItemsNotInDatabase();
  //printListStatus();
}

void MenuPlanner::updateFoodLists(const vector<string>& mealIngreds, size_t freq)
{

  for (siter it = mealIngreds.begin(); it != mealIngreds.end(); ++it )
    {
      if ( !checkIfItemInVec( *it, m_used ) )
	{
	  pair<string,size_t> newIngredUsed = std::make_pair(*it,freq);
	  m_used.push_back( newIngredUsed );
	}
      else
      {
	vector< pair<string,size_t> >::iterator usedItem = findItemInVec(*it,m_used);
	usedItem->second = usedItem->second + freq;
      }
      
      if ( checkIfItemInVec( *it, m_haveLeft ) )
	{
	  vector< pair<string,size_t> >::iterator haveLeftItem = findItemInVec(*it,m_haveLeft);
	  if (haveLeftItem->second <= freq)
	    {
	      m_haveLeft.erase(haveLeftItem);
	    }
	  else
	    {
	      haveLeftItem->second = haveLeftItem->second - freq;
	    }	
	}
    }
}

bool MenuPlanner::checkIfItemInVec( const string& item, const vector< pair<string,size_t> >& vec) const
{
  for (ssiter it = vec.begin(); it != vec.end(); ++it)
    {
      if (it->first == item)
	return true; 
    }
  return false;
}

vector< pair<string,size_t> >::iterator MenuPlanner::findItemInVec( const string& item, vector< pair<string,size_t> >& vec) const
{  
  for (vector< pair<string,size_t> >::iterator it = vec.begin(); it != vec.end(); ++it)
    {
      if (it->first == item)
	return it; 
    }
  return vec.end();
}

void MenuPlanner::printItemsNotInDatabase() const
{
  vector< string > missingIngred = vector< string >(0);
  for (ssiter it = m_have.begin(); it != m_have.end(); ++it)
    {
      if ( !m_fdb.checkIngredExistence(it->first) )
	{
	  missingIngred.push_back(it->first);
	}
    }
  if (!missingIngred.empty())
    {
      cout << "The following were not found in the food database:" << endl;
      for ( siter it2 = missingIngred.begin(); it2 != missingIngred.end(); ++it2)
	{
	  cout << "\t" << *it2 << endl;
	}
      cout << endl;
    }
}

void MenuPlanner::printShoppingList() const
{

  std::map< string, size_t> shoppingList;
  for ( ssiter it = m_used.begin(); it != m_used.end(); ++it)
    {
      shoppingList.insert( *it );
    }

  for ( ssiter it = m_have.begin(); it != m_have.end(); ++it)
    {

      std::map< string, size_t >::iterator usedItem = shoppingList.find( it->first );
      if ( usedItem != shoppingList.end() )
	{
	  if ( it->second  >= usedItem->second ) 
	    { 
	      shoppingList.erase(usedItem); 
	    }
	  else 
	    {
	      usedItem->second -= it->second;
	    }
	}
    }

  cout << endl << "Shopping List:" << endl;
  if ( shoppingList.empty() )
    {
      cout << "Nothing to buy!" << endl << endl;
    }
  else
    {
      for ( std::map< string, size_t >::const_iterator miter = shoppingList.begin(); miter != shoppingList.end(); ++miter)
	{
	  cout << miter->first << " (" << miter->second << ")" << endl;
	}
      cout << endl;
    }
}

void MenuPlanner::printCost() const
{
  cout << endl;
  cout << "Estimated worth of menu: " << m_menu.getMenuCost() << " dollars" << endl;
  cout << endl;
}

void MenuPlanner::printListStatus() const
{
  typedef vector< pair<string,size_t> >::const_iterator iter;
  cout << "Have left: " << endl;
  if ( m_haveLeft.empty() )
    cout << "Nothing" << endl << endl;
  else
    {
      for (iter it = m_haveLeft.begin(); it != m_haveLeft.end(); ++it)
	{
	  cout << it->first << " (" << it->second << "); ";
	}
      cout << endl << endl;
    }
  cout << "Used: " << endl;
  if ( m_used.empty() )
    cout << "Nothing" << endl << endl;
  else
    {
      for (iter it2 = m_used.begin(); it2 != m_used.end(); ++it2)
	{
	  cout << it2->first << " (" << it2->second << "); ";
	}
      cout << endl << endl; 
    }
}


