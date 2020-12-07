// aoc2020_06.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <string_view>
#include <vector>
#include <algorithm>
#include <numeric>

int count_group(std::string group)
{
   std::sort(group.begin(), group.end());
   group.erase(std::unique(group.begin(), group.end()), group.end());
   return group.size();
}

int get_groups_sum1(std::string_view filename)
{
   std::ifstream input(filename.data());
   if (!input.is_open())
      return 0;

   int sum = 0;

   std::string line;
   std::string group;
   while (std::getline(input, line))
   {
      if (!line.empty())
      {
         group += line;
         continue;
      }

      sum += count_group(group);

      group.clear();
   }

   if (!group.empty())
   {
      sum += count_group(group);
   }

   return sum;
}

int get_groups_sum2(std::string_view filename)
{
   std::ifstream input(filename.data());
   if (!input.is_open())
      return 0;

   int sum = 0;
   std::string line;
   std::vector<int> counts(26);
   int members = 0;

   auto l_sum = [&counts](int const m) {
      return std::accumulate(
         counts.begin(), counts.end(),
         0,
         [m](int const total, int const n) {return total + ((n == m) ? 1 : 0); });
   };

   while (std::getline(input, line))
   {
      if (line.empty())
      {
         sum += l_sum(members);
         std::fill(counts.begin(), counts.end(), 0);
         members = 0;
         continue;
      }

      for (auto const c : line)
         counts[c - 'a']++;
      members++;
   }

   sum += l_sum(members);

   return sum;
}

int main()
{
   std::cout << get_groups_sum1(R"(..\data\aoc2020_06_input1_test.txt)") << '\n';
   std::cout << get_groups_sum1(R"(..\data\aoc2020_06_input1.txt)") << '\n';

   std::cout << get_groups_sum2(R"(..\data\aoc2020_06_input1_test.txt)") << '\n';
   std::cout << get_groups_sum2(R"(..\data\aoc2020_06_input1.txt)") << '\n';
}
