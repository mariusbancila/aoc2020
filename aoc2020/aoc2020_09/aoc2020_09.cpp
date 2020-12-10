// aoc2020_09.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <string_view>
#include <vector>
#include <span>
#include <algorithm>

using bigint = long long;

std::vector<bigint> read_numbers(std::string_view filename)
{
   std::vector<bigint> numbers;

   std::ifstream input(filename.data());
   if (input.is_open())
   {
      std::string line;
      while(std::getline(input, line))
      {
         numbers.push_back(std::stoll(line));
      }
   }

   return numbers;
}

bool is_valid(std::span<bigint> data, bigint const number)
{
   for (size_t i = 0; i < data.size() - 1; ++i)
   {
      for (size_t j = i+1; j < data.size(); ++j)
      {
         if (data[i] + data[j] == number)
            return true;
      }
   }

   return false;
}

std::pair<bigint, size_t> find_first_invalid(std::vector<bigint> numbers, size_t const preamble)
{  
   if (numbers.size() > preamble)
   {
      for (size_t i = preamble; i < numbers.size(); ++i)
      {
         if (!is_valid(std::span<bigint> {numbers.data() + i - preamble, numbers.data() + i}, 
                        numbers[i]))
         {
            return { numbers[i], i };
         }
      }
   }

   return { 0, -1 };
}

bigint find_weakness(std::vector<bigint> const & numbers, bigint const number, size_t const index)
{
   for (size_t i = 0; i < index - 2; ++i)
   {
      bigint sum = numbers[i];
      for (size_t j = i + 1; j < index; ++j)
      {
         sum += numbers[j];
         if (sum == number)
         {
            auto const [min, max] = std::minmax_element(numbers.begin() + i, numbers.begin() + j + 1);
            return *min + *max;
         }
      }
   }

   return 0;
}

int main()
{
   std::vector<std::pair<std::string, int>> data
   {
      {R"(..\data\aoc2020_09_input1_test.txt)", 5},
      {R"(..\data\aoc2020_09_input1.txt)", 25}
   };

   for (auto const& [filename, preamble] : data)
   {
      auto numbers = read_numbers(filename);

      auto [number, index] = find_first_invalid(numbers, preamble);
      std::cout << number << '\n';

      auto weakness = find_weakness(numbers, number, index);
      std::cout << weakness << '\n';
   }
}
