// aoc2020_07.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <string_view>
#include <vector>
#include <regex>
#include <set>
#include <assert.h>

class color_graph_t
{
public:
   bool load_from(std::string_view filename)
   {
      std::ifstream input(filename.data());
      if (!input.is_open())
         return false;

      m_colors.clear();
      m_connections.clear();

      std::vector<std::string> lines;

      std::string line;
      while (std::getline(input, line))
      {
         lines.emplace_back(line);
      }

      m_bagsCount = lines.size();
      m_connections.resize(m_bagsCount * m_bagsCount, 0);

      for (auto const& line : lines)
      {
         parse_line(line);
      }

      return m_colors.size() == m_bagsCount;
   }

   int find_outter_bags(std::string_view color)
   {
      int index = find_color_index(color);
      if (index < 0) return 0;

      std::set<std::string> colors;

      visit_row(index, colors);

      return colors.size();
   }

   int find_total_bags(std::string_view color)
   {
      int index = find_color_index(color);
      if (index < 0) return 0;

      return visit_column(index) - 1;
   }

private:
   void parse_line(std::string line)
   {
      auto index = line.find(" bags contain no other bags");
      if (index != std::string::npos)
      {
         auto color = line.substr(0, index);
         find_or_add(color);
      }
      else
      {
         static std::string pattern{ " bags contain " };
         static std::regex rx{R"((\d+) ([\w\s]+) bag[s]?[,.])"};

         index = line.find(pattern);
         if (index != std::string::npos)
         {
            auto color = line.substr(0, index);
            size_t colorIndex = find_or_add(color);

            auto content = line.substr(index + pattern.size());

            int submatches[] = { 1, 2 };
            std::sregex_token_iterator it(content.begin(), content.end(), rx, submatches);
            std::sregex_token_iterator end;
            while (it != end)
            {
               std::string count = *it; ++it;
               std::string color = *it; ++it;

               int ci = find_or_add(color);

               set_count(colorIndex, ci, std::stoi(count));
            }
         }
      }
   }

   int find_or_add(std::string_view color)
   {
      int index = find_color_index(color);
      if (index >= 0)
         return index;

      m_colors.emplace_back(color);
      return m_colors.size() - 1;
   }

   int find_color_index(std::string_view color)
   {
      for (size_t i = 0; i < m_colors.size(); ++i)
         if (m_colors[i] == color)
            return i;

      return -1;
   }

   void visit_row(size_t const index, std::set<std::string>& colors)
   {
      for (size_t r = 0; r < m_bagsCount; ++r)
      {
         if (get_count(r, index) > 0)
         {
            colors.insert(m_colors[r]);

            visit_row(r, colors);
         }
      }
   }

   int visit_column(size_t const index)
   {
      int total = 1;

      for (size_t c = 0; c < m_bagsCount; ++c)
      {
         int count = get_count(index, c);
         if (count > 0)
         {
            total += count * visit_column(c);
         }
      }

      return total;
   }

   void set_count(size_t const from, size_t const to, int const count)
   {
      m_connections[from * m_bagsCount + to] = count;
   }

   int get_count(size_t const from, size_t const to) const
   {
      return m_connections[from * m_bagsCount + to];
   }

private:
   size_t m_bagsCount;
   std::vector<std::string> m_colors;
   std::vector<short> m_connections;
};

int main()
{
   auto bag = "shiny gold";
   {
      color_graph_t graph;
      if (graph.load_from(R"(..\data\aoc2020_07_input1_test.txt)"))
      {
         int count = graph.find_outter_bags(bag);
         std::cout << count << '\n';

         int total = graph.find_total_bags(bag);
         std::cout << total << '\n';
      }
   }

   {
      color_graph_t graph;
      if (graph.load_from(R"(..\data\aoc2020_07_input2_test.txt)"))
      {
         int count = graph.find_outter_bags(bag);
         std::cout << count << '\n';

         int total = graph.find_total_bags(bag);
         std::cout << total << '\n';
      }
   }

   {
      color_graph_t graph;
      if (graph.load_from(R"(..\data\aoc2020_07_input1.txt)"))
      {
         int count = graph.find_outter_bags(bag);
         std::cout << count << '\n';

         int total = graph.find_total_bags(bag);
         std::cout << total << '\n';
      }
   }
}
