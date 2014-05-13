// halfmeal.h

#ifndef _HALFMEAL_H
#define _HALFMEAL_H

#include <string>
#include <vector>
#include "ingredient.h"

class FoodDatabase;

class Halfmeal
{
 public:
  Halfmeal( size_t m_freq );
  virtual ~Halfmeal() {}
  const std::vector< std::string >& getFoodNames() const;
  virtual void printHalfmeal() const = 0;
  virtual double getCost() const = 0;

 protected:
  size_t m_freq;
  std::vector< std::string > m_foodNames;
  bool findIfItemInHalfmeal( const std::string& item ) const;
  const Ingredient& getIngred( std::string type, const FoodDatabase& fdb, const std::vector< std::pair< std::string, size_t > >& used, const std::vector< std::pair< std::string, size_t > >& haveLeft);

};

#endif
