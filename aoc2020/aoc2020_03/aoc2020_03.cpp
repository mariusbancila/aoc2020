// aoc2020_03.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <string_view>
#include <numeric>

struct grid_t
{
   bool load_from(std::string_view filename)
   {
      data.clear();

      std::ifstream input(filename.data());
      if (!input.is_open()) 
         return false;

      height_ = 0;
      width_ = 0;
      std::string line;
      while (std::getline(input, line))
      {
         if (data.empty())
            width_ = line.size();
         height_++;
         data += line;
      }

      return true;
   }

   char at(size_t const row, size_t const col) const
   {
      if (row >= height_ || col >= width_)
         return 0;

      return data[row * width_ + col];
   }

   size_t width() const { return width_; }
   size_t height() const { return height_; }

   constexpr static char empty = '.';
   constexpr static char tree = '#';

private:
   std::string data;
   size_t      width_ = 0;
   size_t      height_ = 0;
};

int count_trees(std::string_view filename, unsigned const rightOffset, unsigned const downOffset)
{
   grid_t grid;
   if (!grid.load_from(filename))
      return 0;

   int count = 0;

   size_t y = 0;
   size_t x = 0;
   while (y < grid.height())
   {
      x += rightOffset;
      x %= grid.width();
      y += downOffset;

      if (grid.at(y, x) == grid_t::tree)
         count++;
   }

   return count;
}

int main()
{
    std::cout << count_trees(R"(..\data\aoc2020_03_input1_test.txt)", 3, 1) << '\n';
    std::cout << count_trees(R"(..\data\aoc2020_03_input1.txt)", 3, 1) << '\n';

    {
       std::vector<int> trees
       {
          count_trees(R"(..\data\aoc2020_03_input1_test.txt)", 1, 1),
          count_trees(R"(..\data\aoc2020_03_input1_test.txt)", 3, 1),
          count_trees(R"(..\data\aoc2020_03_input1_test.txt)", 5, 1),
          count_trees(R"(..\data\aoc2020_03_input1_test.txt)", 7, 1),
          count_trees(R"(..\data\aoc2020_03_input1_test.txt)", 1, 2),
       };

       for (auto const t : trees) std::cout << t << '\n';
       auto p = std::accumulate(trees.begin(), trees.end(), 1, std::multiplies<>());
       std::cout << p << '\n';
    }

    {
       std::vector<int> trees
       {
          count_trees(R"(..\data\aoc2020_03_input1.txt)", 1, 1),
          count_trees(R"(..\data\aoc2020_03_input1.txt)", 3, 1),
          count_trees(R"(..\data\aoc2020_03_input1.txt)", 5, 1),
          count_trees(R"(..\data\aoc2020_03_input1.txt)", 7, 1),
          count_trees(R"(..\data\aoc2020_03_input1.txt)", 1, 2),
       };

       for (auto const t : trees) std::cout << t << '\n';
       auto p = std::accumulate(trees.begin(), trees.end(), 1LL, std::multiplies<long long>());
       std::cout << p << '\n';
    }
}
