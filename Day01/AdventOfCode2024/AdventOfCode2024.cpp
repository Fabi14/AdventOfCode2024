// AdventOfCode2024.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <vector>
#include <ranges>
#include <numeric>
#include "Input.h"

int main()
{
    using namespace std::views;

    std::vector<int> input = getInputAsVector<int>("input.txt");

    std::vector<int> listA;
    std::vector<int> listB;
    for (auto pair : input | chunk(2))
    {
        listA.emplace_back(pair.front());
        listB.emplace_back(pair.back());
    }
     
    std::ranges::sort(listA);
    std::ranges::sort(listB);

    // ---------------- P A R T   O N E ------------------------------
    auto abs =  zip_transform(std::minus{}, listA, listB) | transform(combinators::_abs);
    std::cout << std::reduce(abs.begin(), abs.end()) <<'\n';

    // ---------------- P A R T   T W O ------------------------------
    std::cout << std::reduce(listA.begin(), listA.end(),0ll, [&listB](auto sum, auto id)
        {
            return sum + id * std::ranges::count(listB, id);
        }) << '\n';
}

