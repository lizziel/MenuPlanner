// menu.cpp

#include <vector>
#include <iostream>
#include <stdexcept>
#include "meal.h"
#include "menu.h"

typedef std::vector< Meal* >::iterator iter;

Menu::Menu(size_t numLunches, size_t numDinners) 
  : m_numLunches(numLunches), m_numDinners(numDinners), m_meals( std::vector< Meal* >(0) ) 
{
  m_numMeals = getNumMeals();
}

Menu::~Menu()
{
  for (iter it = m_meals.begin(); it != m_meals.end(); ++it)
    {
      delete *it;
    }
}

size_t Menu::getNumMeals() const
{
  if (m_numDinners >= m_numLunches)
    return m_numDinners;
  else 
    return m_numLunches;
}

size_t Menu::getNumMealsWithFreq( size_t freq ) const
{
  size_t numfreq = 0;
  if (freq == 1)
    {
      if (m_numDinners >= m_numLunches)
	numfreq = m_numDinners - m_numLunches;
      else
	numfreq = m_numLunches - m_numDinners;
    }
  else if (freq == 2)
    {
      if (m_numDinners >= m_numLunches)
	numfreq = m_numLunches;
      else
	numfreq = m_numDinners;
    }
  else
    throw std::out_of_range ("Tried to get meal with frequency not 1 or 2.");
  return numfreq;
}

void Menu::addMeal( Meal* mealPtr )
{
  m_meals.push_back(mealPtr);
}

const std::vector< std::string >& Menu::getMealIngreds( size_t ID ) const
{
  if ( ID > m_meals.size() )
    {
      throw std::logic_error ("Change to out of range exception.");
    } 
  return m_meals[ID-1]->getFoodInMeal();
}

void Menu::printMenu() const
{
  std::cout << std::endl;
  std::cout << "**************************************************" << std::endl;
  std::cout << "                      M E N U                     " << std::endl;
  std::cout << "**************************************************" << std::endl << std::endl;;
  for (std::vector< Meal*>::const_iterator it = m_meals.begin(); it != m_meals.end(); ++it)
    {
      (*it)->printMeal();
    }
  std::cout << std::endl << "**************************************************" << std::endl;
  std::cout << std::endl;
}

double Menu::getMenuCost() const
{
  double cost = 0;
  for (std::vector< Meal*>::const_iterator it = m_meals.begin(); it != m_meals.end(); ++it)
    {
      cost += (*it)->getMealCost() * (*it)->getFreq();
    }
  return cost;
}
