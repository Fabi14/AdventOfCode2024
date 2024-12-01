// AdventOfCode2024.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <vector>
#include <ranges>
#include <numeric>
#include "Input.h"
#include <blackbird/combinators.hpp>

int main()
{
    using namespace std::views;

    std::vector<int> input = getInputAsVector<int>("input.txt");

    std::vector<int> listA;
    std::vector<int> listB;
    for (auto view : input | chunk(2))
    {
        listA.emplace_back(view.front());
        listB.emplace_back(view.back());
    }

    std::ranges::sort(listA);
    std::ranges::sort(listB);

    std::ranges::transform(listA, listB, listA.begin(), std::minus{});
    auto abs = listA | transform(combinators::_abs);
    std::cout << std::abs(std::reduce(abs.begin(), abs.end()));
}

