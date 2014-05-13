// burger.h

#ifndef _BURGER_H
#define _BURGER_H

#include <string>
#include <vector>
#include "halfmeal.h"
#include "ingredient.h"

class FoodDatabase;

class Burger : public Halfmeal
{
 public:
  Burger(const FoodDatabase& fdb, const std::vector< std::pair<std::string, size_t> >& used,const std::vector< std::pair<std::string, size_t> >& haveleft, size_t freq);
  virtual void printHalfmeal() const;
  virtual double getCost() const;

 private:
  Ingredient m_burger;
  Ingredient m_bun;
  Ingredient m_topping1;
  Ingredient m_topping2;
};

#endif
