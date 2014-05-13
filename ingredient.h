// ingredient.h

#ifndef _INGREDIENT_H
#define _INGREDIENT_H

#include <string>

class Ingredient
{  
  friend std::ostream& operator<< (std::ostream& os, const Ingredient& ingred);

 public:
  Ingredient();
  Ingredient(std::string name, double cost);
  virtual ~Ingredient() {}
  Ingredient(const Ingredient& other);
  Ingredient& operator=(const Ingredient& other);
  std::string getName() const;
  double getCost() const;

 private:
  std::string m_name;
  double m_cost;
  // possibilities for future versions: color, season

};

#endif
