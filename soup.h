// soup.h
    
#ifndef _SOUP_H
#define _SOUP_H

#include <string>
#include <vector>
#include "halfmeal.h"
#include "ingredient.h"

class FoodDatabase;

class Soup : public Halfmeal
{
 public:
  Soup(const FoodDatabase& fdb, const std::vector< std::pair<std::string, size_t> >& used,const std::vector< std::pair<std::string, size_t> >& haveleft, size_t freq);
  virtual void printHalfmeal() const;
  virtual double getCost() const;

 private:
  Ingredient m_soup;

};

#endif
