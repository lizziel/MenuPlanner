// MakeMenu.cpp

#include <stdexcept>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include "fooddatabase.h"
#include "menuplanner.h"
using std::cout;
using std::cin;
using std::endl;

int main()
{
  try
    {
      srand( time(NULL) );
      FoodDatabase foodsWeLike("foods.txt");

      bool keepPlanning = true;
      while(keepPlanning)
	{

	  cout << endl << "How many lunches? (0-7)" << endl;
	  std::string lunchstr = "";
	  size_t numLunches;
	  bool lunchPrompt = true;
	  while (lunchPrompt)
	    {	 
	      getline(cin, lunchstr);
	      std::stringstream(lunchstr) >> numLunches;
	      if ( numLunches < 0 || numLunches > 7)
		cout << "Input is not valid.  Try again." << endl;
	      else
		break;
	    }

	  cout << "How many dinners? (0-7)" << endl;
	  std::string dinnerstr = "";
	  size_t numDinners;
	  bool dinnerPrompt = true;
	  while (dinnerPrompt)
	    {
	      getline(cin, dinnerstr);
	      std::stringstream(dinnerstr) >> numDinners;
	      if (numDinners < 0 || numDinners > 7)
		  cout << "Input is not valid.  Try again." << endl;
	      else
		break;
	    }

	  MenuPlanner mymenu(foodsWeLike, "have.txt", numLunches, numDinners);
	  mymenu.makeMenu();

	  cout << "Accept this menu? (y/n)" << endl;
	  std::string answer = "";
	  bool quitPrompt = true;
	  while (quitPrompt)
	    {
	      std::getline(cin, answer);
	      // std::stringstream inputstream(answer);
	      if (answer != "y" && answer != "n")
		cout << "That is not a valid input.  Try again." << endl; 
	      else
		break;
	    }

	  if (answer == "y")
	    {
	      mymenu.printShoppingList();
	      mymenu.printCost();
	      break;
	    }
	}


  // save menu to file?
  // print shopping list? (used - have)
  // print what we have that's not used
  // print estimated cost
 
   }
  catch (std::logic_error& exc)
    {
      std::cerr << "Abnormal terminal due to internal logic error" << std::endl;
      std::cerr << "Details: " << exc.what() << std::endl;
    }
  catch (std::exception& exc)
    {
      std::cerr << "Abnormal termination." << std::endl;
      std::cerr << "Details: " << exc.what() << std::endl;
    }

}
