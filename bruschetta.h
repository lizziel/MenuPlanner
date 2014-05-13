// bruschetta.h

#ifndef _BRUSCHETTA_H
#define _BRUSCHETTA_H

#include <string>
#include <vector>
#include "halfmeal.h"
#include "ingredient.h"

class FoodDatabase;

class Bruschetta : public Halfmeal
{
 public:
  Bruschetta(const FoodDatabase& fdb, const std::vector< std::pair<std::string, size_t> >& used,const std::vector< std::pair<std::string, size_t> >& haveleft, size_t freq);
  virtual void printHalfmeal() const;
  virtual double getCost() const;

 private:
  Ingredient m_bread;
  Ingredient m_topping1;
  Ingredient m_topping2;
  Ingredient m_topping3;
};

#endif
