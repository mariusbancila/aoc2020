// aoc2020_10.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <string_view>
#include <vector>
#include <algorithm>
#include <map>

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

long long find_distinct_ways(std::vector<int> data)
{
   std::map<int, int> clusters;

   std::sort(data.begin(), data.end());

   // find the number of clusters of at least 3 consecutive numbers
   int jumps = 0;
   int jolts = 0;

   for (auto const v : data)
   {
      if (v - jolts == 1)
      {
         jumps++;
      }
      else
      {
         if(jumps > 1)
            clusters[jumps]++;
         jumps = 0;
      }

      jolts = v;
   }

   if (jumps > 1)
      clusters[jumps]++;

   // number of ways a number can be composed from factors of 1, 2, 3
   // ex: 2 = 0 + 2, 1 + 1 (2 ways)
   //     3 = 0 + 3, 1 + 2, 2 + 1, 1 + 1 + 1 (4 ways)
   //     4 = 1 + 3, 3 + 1, 2 + 2, 1 + 1 + 2, 1 + 2 + 1, 2 + 1 + 1, 1 + 1 + 1 + 1 (7 ways)
   int factors[]{2, 4, 7, 13, 24};

   // result is the product of all combinations of all these clusters
   // 2^a * 3^b * 4^c ... where a,b,c is the size of each cluster
   long long prod = 1;
   for (auto const& [k, v] : clusters)
   {
      prod *= std::pow(factors[k - 2], v);
   }

   return prod;
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
