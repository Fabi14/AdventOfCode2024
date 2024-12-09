// aoc2024_day05.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <ranges>
#include <map>
#include <vector>
#include <numeric>

int main()
{
    using namespace  std::views;
    bool readInRules = true;
    std::ifstream input("input.txt");

    std::map<int, std::vector<int>> rules;
    int sum{ 0 };
    for (std::string line; std::getline(input, line);)
    {
        if (readInRules)
        {
            if (line.empty())
            {
                readInRules = false;
                continue;
            }
            auto pair = line
                | lazy_split('|')
                | transform([](auto&& s)
                    {
                        return std::stoi(s
                            | filter([](const char c)
                                {
                                    return std::isdigit(c);
                                })
                            | std::ranges::to<std::string>());
                    }) 
                |  std::ranges::to <std::vector<int>>() ;
            if (pair.size() == 2) {
                rules[pair[1]].push_back(pair[0]);
            }
        }
        else
        {
            auto update = line
                | lazy_split(',')
                | transform([](auto&& s)
                    {
                        return std::stoi(s
                            | filter([](const char c)
                                {
                                    return std::isdigit(c);
                                })
                            | std::ranges::to<std::string>());
                    })
                | std::ranges::to <std::vector<int>>();

            bool updatePossible{ true };
            std::accumulate(update.begin(), update.end(), std::vector<int>(), [&](std::vector<int>&& activRules, int value)
                {
                    if (std::ranges::find(activRules, value) != activRules.end())
                    {
                        updatePossible = false;
                    }
                    activRules.insert_range(activRules.end(), rules[value]);
                    return activRules;
                });
            if (updatePossible)
            {
                sum += update[update.size() / 2];
            }
        }
    }

    std::cout << sum;
}
