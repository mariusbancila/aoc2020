// aoc2020_01.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>

int find_two_numbers(std::vector<int> const & expenses)
{
   for (size_t i = 0; i < expenses.size() - 1; ++i)
   {
      for (size_t j = i + 1; j < expenses.size(); ++j)
      {
         if (expenses[i] + expenses[j] == 2020)
         {
            return expenses[i] * expenses[j];
         }
      }
   }

   return 0;
}

int find_three_numbers(std::vector<int> const& expenses)
{
   for (size_t i = 0; i < expenses.size() - 2; ++i)
   {
      for (size_t j = i + 1; j < expenses.size()-1; ++j)
      {
         for (size_t k = j + 1; k < expenses.size(); ++k)
         {
            if (expenses[i] + expenses[j] + expenses[k] == 2020)
            {
               return expenses[i] * expenses[j] * expenses[k];
            }
         }
      }
   }

   return 0;
}

int main()
{
   std::ifstream input("..\\data\\aoc2020_01_input1.txt");
   if (!input.is_open()) return -1;

   std::vector<int> expenses;
   std::copy(std::istream_iterator<int>(input),
      std::istream_iterator<int>(),
      std::back_inserter(expenses));

   std::vector<int> expenses_test { 1721,
                                    979,
                                    366,
                                    299,
                                    675,
                                    1456 };

   std::cout << find_two_numbers(expenses_test) << '\n';
   std::cout << find_two_numbers(expenses) << '\n';

   std::cout << find_three_numbers(expenses_test) << '\n';
   std::cout << find_three_numbers(expenses) << '\n';
}
