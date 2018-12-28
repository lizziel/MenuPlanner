// onepot.h

#ifndef _ONEPOT_H
#define _ONEPOT_H

#include <string>
#include <vector>
#include "meal.h"
#include "ingredient.h"

class FoodDatabase;

class Onepot : public Meal
{
 public:
  Onepot(const FoodDatabase& fdb, const std::vector< std::pair<std::string, size_t> >& used, const std::vector< std::pair<std::string, size_t> >& haveleft, size_t ID, size_t freq);
  virtual ~Onepot() {}
  virtual void printMeal() const;
  virtual double getMealCost() const;

 private:
  Ingredient m_onepot;
};

#endif
