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


    std::vector<int> part01;
    std::ranges::transform(listA, listB, std::back_inserter(part01), std::minus{});
    auto abs = part01 | transform(combinators::_abs);
    std::cout << std::reduce(abs.begin(), abs.end()) <<'\n';

    std::vector<int> part02;
    std::cout << std::reduce(listA.begin(), listA.end(),0ll, [listB](auto sum, auto a)
        {
            return sum + a * std::ranges::count(listB, a);
        }) << '\n';
}

