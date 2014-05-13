// meal.h

#ifndef _MEAL_H
#define _MEAL_H

#include <string>
#include <vector>

class FoodDatabase;
class Ingredient;

class Meal
{
 public:
  Meal( size_t m_ID, size_t m_freq );
  virtual ~Meal() {}
  size_t getID() const;
  size_t getFreq() const;
  const std::vector< std::string >& getFoodInMeal() const;
  virtual void printMeal() const = 0;
  virtual double getMealCost() const = 0;

 protected:
  size_t m_ID;
  size_t m_freq;
  std::vector< std::string > m_foodInMeal;

  bool findIfItemInVec( const std::string& item, const std::vector< std::pair< std::string,size_t> >& vec) const;
  const Ingredient& getIngred( std::string type, const FoodDatabase& fdb, const std::vector< std::pair< std::string, size_t > >& used, const std::vector< std::pair< std::string, size_t > >& haveLeft);

};

#endif
