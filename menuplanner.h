// menuplanner.h

#ifndef _MENUPLANNER_H
#define _MENUPLANNER_H

#include <string>
#include <vector>
#include "menu.h"

class FoodDatabase;

class MenuPlanner
{
 public:
  MenuPlanner(const FoodDatabase& fdb, const std::string foodWeHaveFile, size_t numLunches, size_t numDinners);
  virtual ~MenuPlanner();
  void makeMenu();
  void printShoppingList() const;
  void printCost() const;

 private:
  const FoodDatabase& m_fdb;
  Menu m_menu;
  std::vector< std::pair< std::string, size_t > > m_have;
  std::vector< std::pair< std::string, size_t > > m_haveLeft;
  std::vector< std::pair< std::string, size_t > > m_used;
 
  void updateFoodLists(const std::vector< std::string >& mealIngreds, size_t freq);
  bool checkIfItemInVec ( const std::string& item, const std::vector< std::pair< std::string, size_t> >& vec) const;
  std::vector< std::pair< std::string, size_t> >::iterator findItemInVec( const std::string& item, std::vector< std::pair< std::string, size_t > >& vec) const;
  void printItemsNotInDatabase() const;
  void printListStatus() const;

};

#endif
