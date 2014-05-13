// salad.h

#ifndef _SALAD_H
#define _SALAD_H

#include <string>
#include <vector>
#include "halfmeal.h"
#include "ingredient.h"

class FoodDatabase;

class Salad : public Halfmeal
{
 public:
  Salad(const FoodDatabase& fdb, const std::vector< std::pair<std::string, size_t> >& used, const std::vector< std::pair<std::string, size_t> >& haveleft, size_t freq);
  virtual void printHalfmeal() const;
  virtual double getCost() const;

 private:
  Ingredient m_green;
  Ingredient m_topping1;
  Ingredient m_topping2;
  Ingredient m_topping3;
  Ingredient m_topping4;
  Ingredient m_dressing;
};

#endif
