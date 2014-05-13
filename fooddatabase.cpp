// fooddatabase.cpp

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <stdexcept>
#include <time.h>
#include "fooddatabase.h"
#include "foodgroup.h"
#include "ingredient.h"
using std::vector;
using std::string;
using std::pair;
using std::cout;
using std::endl;

FoodDatabase::FoodDatabase(const string& filename)
{

  std::ifstream file ( filename.c_str() );
  if ( file.is_open() )
    {
      string txtline;     
      while ( file.good() )
	{
	  while (true)
	    {    
	      std::getline(file,txtline);
	      if (txtline.length() != 0 || file.eof()) 
		break; 
	    }
	  FoodGroup* newGroupPtr = new FoodGroup(txtline);
	  string name, cost_str;
	  double cost;	 
	  while (true)
	    {
	      std::getline(file,txtline,'\n');
	      if (txtline.length() == 0 ) 
		{ 
		  break; 
		}
	      std::istringstream subline( txtline );
	      getline ( subline, name, ',');
	      getline ( subline, cost_str, ';');	     
	      cost = atof ( cost_str.c_str() );
	      newGroupPtr->addFood(name,cost);
	    }
	  m_allFoods.push_back(newGroupPtr);	    
	}
    }
  else
    std::cerr << "Failed to open file: " << filename << std::endl;   
}

FoodDatabase::~FoodDatabase()
{
 for (vector<FoodGroup*>::const_iterator fg_it = m_allFoods.begin(); fg_it != m_allFoods.end(); ++fg_it)
   {
     delete *fg_it;
   }
}

const Ingredient& FoodDatabase::getRandomIngred(const string& type, const vector<string>& unwantedList) const
{
  for (vector<FoodGroup*>::const_iterator fg_it = m_allFoods.begin(); fg_it != m_allFoods.end(); ++fg_it)
    {

      if ( (*fg_it)->getType() == type)
	{
	  if (unwantedList.empty())
	    {
	      return (*fg_it)->getRandomIngred();
	    }	 
	  else
	    {
	      return (*fg_it)->getRandomIngredButNot( unwantedList );	  	    
	    }
	}
    }
  throw std::logic_error ( "Attempted to get an ingredient from a foodgroup that does not exist." );
}

const Ingredient& FoodDatabase::getSpecificIngred( const string& type, const string& Ingredname ) const
{
  for (vector<FoodGroup*>::const_iterator fg_it = m_allFoods.begin(); fg_it != m_allFoods.end(); ++fg_it)
    {
      if ( (*fg_it)->getType() == type)
	{
	  return (*fg_it)->getIngred( Ingredname );
	}
    }
  throw std::logic_error ("Attempted to retrieve specific ingredient from foodgroup it is not in."); 
} 

bool FoodDatabase::checkIngredType( const string& type, const string& ingredName ) const
{
  for (vector<FoodGroup*>::const_iterator fg_it = m_allFoods.begin(); fg_it != m_allFoods.end(); ++fg_it)
    {
      if ( (*fg_it)->getType() == type)
	{
	  return (*fg_it)->contains(ingredName);
	}
    }
  throw std::logic_error ("Invalid foodgroup specified when checking specific ingredient foodgroup.");
}

bool FoodDatabase::checkIngredExistence( const string& ingredName ) const
{
  for (vector<FoodGroup*>::const_iterator fg_it = m_allFoods.begin(); fg_it != m_allFoods.end(); ++fg_it)
    {
      if ( (*fg_it)->contains(ingredName) )
	return true;
    }
  return false;
}






