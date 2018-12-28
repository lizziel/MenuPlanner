// ingredient.cpp

#include <stdlib.h>
#include <iostream>
#include <string>
#include "ingredient.h"

Ingredient::Ingredient() : m_name("bad"), m_cost(0) {}

Ingredient::Ingredient(std::string name, double cost)
  : m_name(name), m_cost(cost) {}

Ingredient::Ingredient(const Ingredient& other)
{
  m_name = other.getName();
  m_cost = other.getCost();
}

Ingredient& Ingredient::operator=(const Ingredient& other)
{
  if (this == &other)
    return *this;
  m_name = other.getName();
  m_cost = other.getCost();
  return *this;
}

std::string Ingredient::getName() const
{
  return m_name;
}

double Ingredient::getCost() const
{
  return m_cost;
}

std::ostream& operator<< (std::ostream& os, const Ingredient& ingred)
{
  os << ingred.getName();
  return os;
}
