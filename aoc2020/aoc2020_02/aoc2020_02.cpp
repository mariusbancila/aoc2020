// aoc2020_02.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <string_view>
#include <vector>
#include <algorithm>
#include <ranges>
#include <regex>
#include <optional>
#include <functional>

bool is_valid_password(unsigned const min, unsigned const max, char const letter, std::string_view password)
{
   unsigned n = std::ranges::count_if(password, [letter](char const c) {return c == letter; });
   return min <= n && n <= max;
}

bool is_valid_password2(unsigned const index1, unsigned const index2, char const letter, std::string_view password)
{
   if (!(index1 <= password.size() && index2 <= password.size()))
      return false;

   auto l1 = password[index1 - 1] == letter;
   auto l2 = password[index2 - 1] == letter;

   return (l1 && !l2) || (!l1 == l2);
}

std::optional<std::tuple<unsigned, unsigned,char, std::string>> parse_line(std::string const & line)
{
   static std::regex rx{ R"((\d+)-(\d+) (\w): (\w+))" };

   unsigned min = 0;
   unsigned max = 0;
   char letter = 0;
   std::string password;

   std::smatch match;
   if (std::regex_match(line, match, rx))
   {
      if (match.size() == 5)
      {
         min = std::stoi(match[1].str());
         max = std::stoi(match[2].str());
         letter = match[3].str().at(0);
         password = match[4].str();
      }

      return std::make_tuple(min, max, letter, password);
   }

   return {};
}

int count_valid_password(std::string_view filename, std::function<bool(int, int, char, std::string)> predicate)
{
   std::ifstream input(filename.data());
   if (!input.is_open()) return -1;

   int count = 0;
   std::string line;
   while (std::getline(input, line))
   {
      auto result = parse_line(line);
      if (result.has_value())
      {
         auto [min, max, letter, password] = result.value();

         if (predicate(min, max, letter, password))
            count++;
      }
   }

   return count;
}


int main()
{
   std::cout << count_valid_password(R"(..\data\aoc2020_02_input1_test.txt)", is_valid_password) << '\n';
   std::cout << count_valid_password(R"(..\data\aoc2020_02_input1.txt)", is_valid_password) << '\n';

   std::cout << count_valid_password(R"(..\data\aoc2020_02_input1_test.txt)", is_valid_password2) << '\n';
   std::cout << count_valid_password(R"(..\data\aoc2020_02_input1.txt)", is_valid_password2) << '\n';
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
