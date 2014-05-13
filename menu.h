// menu.h

#ifndef _MENU_H
#define _MENU_H

#include <vector>
#include <string>

class Meal;

class Menu
{

 public:
  Menu(size_t numLunches, size_t numDinners);
  virtual ~Menu();
  size_t getNumMeals() const;
  size_t getNumMealsWithFreq( size_t freq ) const;
  void addMeal( Meal* );
  const std::vector< std::string>& getMealIngreds(size_t ID) const;
  void printMenu() const;
  double getMenuCost() const;

 private:
  size_t m_numMeals;
  size_t m_numLunches;
  size_t m_numDinners;
  std::vector< Meal* > m_meals;

};

#endif
