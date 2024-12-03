#pragma once

#include <ranges>
#include <sstream>
#include <fstream>
#include <filesystem>
#include <blackbird/combinators.hpp>

struct Line {
    std::string line;

    operator std::string() {
        return line;
    }
};
std::istream& operator>>(std::istream& os, Line& l)
{
    std::getline(os, l.line);
    return os;
}

template<typename iStreamType>
auto getRangeFactoryFromFile(const std::filesystem::path& fileName)
{
    auto getFileStreamCal = [](const std::filesystem::path& fileName) {
        return [=]()mutable ->std::fstream {return std::fstream{ fileName }; };
        };

    auto rangeFactoryRAII = [](auto input) {
        return [i = input()]() mutable {return std::views::istream<iStreamType>(i); };
        };

    return combinators::_b(rangeFactoryRAII, getFileStreamCal)(fileName);
}

template<typename T>
std::vector<T> getInputAsVector(const std::filesystem::path& fileName)
{
    std::vector<T> input;
    auto file = getRangeFactoryFromFile<int>(fileName);
    for (auto a : file())
    {
        input.emplace_back(a);
    }
    return input;
}