// aoc2020_04.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <string_view>
#include <vector>
#include <regex>
#include <set>
#include <algorithm>
#include <functional>

struct passport_t
{
   int year;
   int issue_year;
   int expiration_year;
   int height;
   std::string height_unit;
   std::string hair_color;
   std::string eye_color;
   std::string pid;
   std::string cid;
};

bool is_valid_year(int const year)
{
   return year >= 1920 && year <= 2002;
}

bool is_valid_issue_year(int const year)
{
   return year >= 2010 && year <= 2020;
}

bool is_valid_expiration_year(int const year)
{
   return year >= 2020 && year <= 2030;
}

bool is_valid_height(int const height, std::string unit)
{
   return
      (unit == "cm" && height >= 150 && height <= 193) ||
      (unit == "in" && height >= 59 && height <= 76);
}

bool is_valid_hair_color(std::string color)
{
   if (color.size() != 7 || color[0] != '#')
      return false;
   for (size_t i = 1; i < color.size(); ++i)
   {
      if (!std::isdigit(color[i]) && (color[i] < 'a' || color[i] > 'f'))
         return false;
   }

   return true;
}

bool is_valid_eye_color(std::string color)
{
   static std::set<std::string> colors{ "amb", "blu", "brn", "gry", "grn", "hzl", "oth" };
   return colors.contains(color);
}

bool is_valid_pid(std::string pid)
{
   if (pid.size() != 9) return false;
   return std::all_of(pid.cbegin(), pid.cend(), [](char const c) {return std::isdigit(c); });
}

bool is_valid_passport(passport_t const& p)
{
   return
      is_valid_year(p.year) &&
      is_valid_issue_year(p.issue_year) &&
      is_valid_expiration_year(p.expiration_year) &&
      is_valid_height(p.height, p.height_unit) &&
      is_valid_hair_color(p.hair_color) &&
      is_valid_eye_color(p.eye_color) &&
      is_valid_pid(p.pid);
}

bool is_valid_passport1(std::string passport)
{
   static std::regex rx{ R"((\w{3}):[#\d\w]+)" };
   std::set<std::string> fields{ "byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid", "cid" };

   std::set<std::string> docfields;

   int submatches[] = { 1, 2 };
   std::sregex_token_iterator it(passport.begin(), passport.end(), rx, submatches);
   std::sregex_token_iterator end;
   while (it != end)
   {
      docfields.insert(*it); ++it; ++it;
   }

   std::set<std::string> diff;

   std::set_difference(
      fields.begin(), fields.end(),
      docfields.begin(), docfields.end(),
      std::inserter(diff, diff.begin()));

   return diff.empty() || (diff.size() == 1 && diff.contains("cid"));
}

bool is_valid_passport2(std::string data)
{
   static std::regex rx{ R"((\w{3}):([#\d\w]+))" };

   int submatches[] = { 1, 2 };
   std::sregex_token_iterator it(data.begin(), data.end(), rx, submatches);
   std::sregex_token_iterator end;
   passport_t passport;
   while(it != end)
   {      
      std::string key = *it; ++it;
      std::string value = *it; ++it;

      if (key == "byr")
      {
         try
         {
            passport.year = std::stoi(value);
         }
         catch (...)
         {
            return false;
         }
      }
      else if (key == "iyr")
      {
         try
         {
            passport.issue_year = std::stoi(value);
         }
         catch (...)
         {
            return false;
         }
      }
      else if (key == "eyr")
      {
         try
         {
            passport.expiration_year = std::stoi(value);
         }
         catch (...)
         {
            return false;
         }
      }
      else if (key == "hgt")
      {         
         try
         {
            passport.height = std::stoi(value.substr(0, value.length() - 2));
            passport.height_unit = value.substr(value.length() - 2, 2);
         }
         catch (...)
         {
            return false;
         }
      }
      else if (key == "hcl")
      {
         passport.hair_color = value;
      }
      else if (key == "ecl")
      {
         passport.eye_color = value;
      }
      else if (key == "pid")
      {
         passport.pid = value;
      }
      else if (key == "cid")
      {
         passport.cid = value;
      }
   }

   return is_valid_passport(passport);
}

int count_valid_passports(std::string_view filename, std::function<bool(std::string)> predicate)
{
   std::ifstream input(filename.data());
   if (!input.is_open())
      return 0;

   int count = 0;

   std::string line;
   std::string passport;
   while(std::getline(input, line))
   {
      if (!line.empty())
      {
         if (!passport.empty())
            passport += " ";
         passport += line;
         continue;
      }
      
      if (predicate(passport))
         count++;

      passport.clear();
   }

   if(!passport.empty())
      if (predicate(passport))
         count++;

   return count;
}

int main()
{
   std::cout << count_valid_passports(R"(..\data\aoc2020_04_input1_test.txt)", is_valid_passport1) << '\n';
   std::cout << count_valid_passports(R"(..\data\aoc2020_04_input1.txt)", is_valid_passport1) << '\n';

   std::cout << count_valid_passports(R"(..\data\aoc2020_04_input1.txt)", is_valid_passport2) << '\n';
}
