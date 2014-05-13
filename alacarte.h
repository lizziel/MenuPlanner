// alacarte.h

#ifndef _ALACARTE_H
#define _ALACARTE_H

#include <string>
#include <vector>
#include "meal.h"
#include "ingredient.h"

class FoodDatabase;

class Alacarte : public Meal
{
 public:
  Alacarte(const FoodDatabase& fdb, const std::vector< std::pair<std::string, size_t> >& used, const std::vector< std::pair<std::string, size_t> >& haveleft, size_t ID, size_t freq);
  virtual ~Alacarte() {}
  virtual void printMeal() const;
  virtual double getMealCost() const;

 private:
  Ingredient m_veg;
  Ingredient m_protein;
  Ingredient m_starch;
  Ingredient m_savory;

};

#endif
