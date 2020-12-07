// aoc2020_05.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <string_view>
#include <vector>
#include <assert.h>

int find_row(std::string_view code)
{
   if (code.size() < 7) return 0;   

   int l = 0;
   int r = 127;
   for (int i = 0; i < 7; ++i)
   {
      int m = l + (r - l) / 2;
      if (code[i] == 'F')
      {
         r = m;
      }
      else if (code[i] == 'B')
      {
         l = m + 1;
      }
      else
         return 0;
   }

   assert(l == r);
   return l;
}

int find_col(std::string_view code)
{
   if (code.size() < 3) return 0;

   int l = 0;
   int r = 7;
   for (int i = 0; i < 3; ++i)
   {
      int m = l + (r - l) / 2;
      if (code[i] == 'L')
      {
         r = m;
      }
      else if (code[i] == 'R')
      {
         l = m + 1;
      }
      else
         return 0;
   }

   assert(l == r);
   return l;
}

int find_sid(std::string_view code)
{
   if (code.size() != 10) return 0;

   return find_row(code.substr(0, 7)) * 8 + find_col(code.substr(7, 3));
}

int find_highest_sid(std::string_view filename)
{
   std::ifstream input(filename.data());
   if (!input.is_open())
      return 0;

   int sid = 0;
   std::string line;
   while (std::getline(input, line))
   {
      int id = find_sid(line);
      if (id > sid) sid = id;
   }

   return sid;
}

int find_seat(std::string_view filename, int const maxsid)
{
   std::ifstream input(filename.data());
   if (!input.is_open())
      return 0;

   std::string sids;
   sids.resize(maxsid + 1, 'F');
   std::string line;
   while (std::getline(input, line))
   {
      auto sid = find_sid(line);
      assert(sid <= maxsid);
      sids[sid] = 'T';
   }

   return sids.find("TFT") + 1;
}

int main()
{
   assert(find_row("FBFBBFF") == 44);
   assert(find_row("BFFFBBF") == 70);
   assert(find_row("FFFBBBF") == 14);
   assert(find_row("BBFFBBF") == 102);

   assert(find_col("RLR") == 5);
   assert(find_col("RRR") == 7);
   assert(find_col("RLL") == 4);

   auto maxsid = find_highest_sid(R"(..\data\aoc2020_05_input1.txt)");
   std::cout << maxsid << '\n';

   auto sid = find_seat(R"(..\data\aoc2020_05_input1.txt)", maxsid);
   std::cout << sid << '\n';
}
