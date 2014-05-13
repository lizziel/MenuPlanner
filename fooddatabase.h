// fooddatabase.h

#ifndef _FOODDATABASE_H
#define _FOODDATABASE_H

#include <string>
#include <vector>

class FoodGroup;
class Ingredient;

class FoodDatabase
{
 public:
  FoodDatabase(const std::string& filename);
  ~FoodDatabase(); 
  const Ingredient& getRandomIngred(const std::string& type, const std::vector< std::string >& unwantedList ) const;
  const Ingredient& getSpecificIngred(const std::string& type, const std::string& ingredName) const;
  bool checkIngredType( const std::string& type, const std::string& ingredName ) const;
  bool checkIngredExistence( const std::string& ingredName ) const;

 private:
  std::vector<FoodGroup*> m_allFoods;

};


#endif
