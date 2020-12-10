// aoc2020_10.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <string_view>
#include <vector>
#include <algorithm>

std::vector<int> read_numbers(std::string_view filename)
{
   std::vector<int> numbers;

   std::ifstream input(filename.data());
   if (input.is_open())
   {
      std::string line;
      while (std::getline(input, line))
      {
         numbers.push_back(std::stoi(line));
      }
   }

   return numbers;
}

int find_joltage_factor(std::vector<int> data)
{
   int joltage[3]{0,0,0};

   std::sort(data.begin(), data.end());

   int jolts = 0;
   for (auto const v : data)
   {
      joltage[v - jolts - 1]++;
      jolts = v;
   }

   return joltage[0] * (joltage[2] + 1);
}

int find_distinct_ways(std::vector<int> data)
{
   return 0;
}

int main()
{
   std::vector<std::string> data
   {
      R"(..\data\aoc2020_10_input1_test.txt)",
      R"(..\data\aoc2020_10_input2_test.txt)",
      R"(..\data\aoc2020_10_input1.txt)",
   };

   for (auto const& filename : data)
   {
      auto numbers = read_numbers(filename);

      auto factor = find_joltage_factor(numbers);
      std::cout << factor << '\n';

      auto count = find_distinct_ways(numbers);
      std::cout << count << '\n';
   }
}
