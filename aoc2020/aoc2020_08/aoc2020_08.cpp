// aoc2020_08.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <string_view>
#include <vector>

enum class instruction_set
{
   nop,
   acc,
   jmp
};

instruction_set instruction_from_string(std::string_view instruction)
{
   if (strcmp(instruction.data(), "nop") == 0)
      return instruction_set::nop;
   else if (strcmp(instruction.data(), "acc") == 0)
      return instruction_set::acc;
   else if (strcmp(instruction.data(), "jmp") == 0)
      return instruction_set::jmp;

   throw std::runtime_error("unknown instruction");
}

struct instruction_t
{
   instruction_set   instruction;
   int               argument;
};

using program_code = std::vector<instruction_t>;

program_code read_code(std::string_view filename)
{
   program_code code;

   std::ifstream input(filename.data());
   if (input.is_open())
   {
      std::string line;
      while (std::getline(input, line))
      {
         auto inst = instruction_from_string(line.substr(0, 3));
         auto value = std::stoi(line.substr(4));

         code.push_back({ inst, value });
      }
   }

   return code;
}

int find_acc_in_loop1(program_code const& code)
{
   int acc = 0;
   int ip = 0;
   std::vector<bool> executed(code.size(), false);

   while (true)
   {
      if (executed[ip])
         break;
      else
         executed[ip] = true;
      
      switch (code[ip].instruction)
      {
      case instruction_set::nop:
         ip++;
         break;
      case instruction_set::acc:
         acc += code[ip].argument;
         ip++;
         break;
      case instruction_set::jmp:
         ip += code[ip].argument;
         break;
      }
   }

   return acc;
}

int find_acc_in_loop2(program_code const& code)
{
   int acc = 0;
   size_t ip = 0;
   std::vector<bool> executed(code.size(), false);

   while (true)
   {
      if (ip >= code.size())
         break;
      else if (executed[ip])
         throw std::runtime_error("loop");
      else
         executed[ip] = true;

      switch (code[ip].instruction)
      {
      case instruction_set::nop:
         ip++;
         break;
      case instruction_set::acc:
         acc += code[ip].argument;
         ip++;
         break;
      case instruction_set::jmp:
         ip += code[ip].argument;
         break;
      }
   }

   return acc;
}


int main()
{
   std::vector<std::string> paths
   {
      R"(..\data\aoc2020_08_input1_test.txt)", 
      R"(..\data\aoc2020_08_input1.txt)" 
   };

   for(auto const & filename : paths)
   {
      auto code = read_code(filename);
      std::cout << find_acc_in_loop1(code) << '\n';

      bool done = false;
      while (!done)
      {
         for (size_t i = 0; i < code.size(); ++i)
         {
            auto copy = code;

            if (copy[i].instruction == instruction_set::jmp)
               copy[i].instruction = instruction_set::nop;
            else
               continue;

            try
            {
               int acc = find_acc_in_loop2(copy);
               std::cout << acc << '\n';
               done = true;
               break;
            }
            catch (...)
            {
               continue;
            }
         }
      }
   }
}
