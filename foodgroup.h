// foodgroup.h

#ifndef _FOODGROUP_H
#define _FOODGROUP_H

#include <string>
#include <vector>
//#include <iostream>
#include "ingredient.h"

class FoodGroup
{
 public:
  FoodGroup(std::string type);
  virtual ~FoodGroup() {}
  std::string getType() const;
  void addFood(const std::string name, const double cost);
  bool contains( const std::string& s) const; 
  const Ingredient& operator[](const size_t pos) const;
  const Ingredient& getIngred(const std::string& name) const;
  const Ingredient& getRandomIngred() const;  
  const Ingredient& getRandomIngredButNot( const std::vector< std::string >& noList) const;

 private:
  std::string m_type;
  std::vector<Ingredient> m_foodGroupVector;

};

#endif
