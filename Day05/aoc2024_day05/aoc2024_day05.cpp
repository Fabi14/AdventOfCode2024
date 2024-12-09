// aoc2024_day05.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <ranges>
#include <map>
#include <vector>
#include <numeric>
#include <algorithm>

int main()
{
    using namespace  std::views;
    bool readInRules = true;
    std::ifstream input("input.txt");

    std::map<int, std::vector<int>> rules;
    std::map<int, std::vector<int>> rulesForFixing;
    int sum{ 0 };
    std::vector<std::vector<int>> incorrectlyOrderedUpdates{};
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
                rulesForFixing[pair[0]].push_back(pair[1]);
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
            else
            {
                incorrectlyOrderedUpdates.push_back(update);
            }
        }
    }

    std::cout << sum << '\n';
    int sum2{ 0 };
    for (auto& u : incorrectlyOrderedUpdates)
    {
        std::ranges::partial_sort(u,u.begin()+u.size()/2+1, [&](int a, int b)
            {
                return std::ranges::find(rulesForFixing[a], b) != rulesForFixing[a].end();
            });
        sum2 += u[u.size() / 2];
    }
    std::cout << sum2;
}
