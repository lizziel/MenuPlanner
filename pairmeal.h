// pairmeal.h

#ifndef _PAIRMEAL_H
#define _PAIRMEAL_H

#include <string>
#include <vector>
#include "meal.h"

class Halfmeal;
class FoodDatabase;

class Pairmeal : public Meal
{
 public:
  Pairmeal(const FoodDatabase& fdb, const std::vector< std::pair<std::string, size_t> >& used, const std::vector< std::pair<std::string, size_t> >& haveleft, size_t ID, size_t freq);
  virtual ~Pairmeal();
  virtual void printMeal() const;
  virtual double getMealCost() const;

 private:
  Halfmeal* m_first;
  Halfmeal* m_second;
  Halfmeal* getNewHalfmeal( size_t num, const FoodDatabase& fdb, const std::vector< std::pair<std::string, size_t> >& used, const std::vector< std::pair<std::string, size_t> >& haveleft, size_t freq ) const;

};

#endif
