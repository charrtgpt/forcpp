
#include "BitcoinExchange.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cctype>
#include <stdexcept>

BitcoinExchange::BitcoinExchange()
{
    loadDatabase();
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other)
{
    dataBase = other.dataBase;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
    if (this != &other)
        dataBase = other.dataBase;
    return (*this);
}

BitcoinExchange::~BitcoinExchange()
{
}

static std::string trim(const std::string &str)
{
    size_t start = str.find_first_not_of(" \t\r\n");

    if (start == std::string::npos)
        return "";

    size_t end = str.find_last_not_of(" \t\r\n");

    return str.substr(start, end - start + 1);
}

void BitcoinExchange::loadDatabase()
{
    std::ifstream file("data.csv");

    if (!file.is_open())
        throw std::runtime_error("Could not open data.csv");

    std::string line;

    std::getline(file, line);

    while (std::getline(file, line))
    {
        if (line.empty())
            continue;

        std::stringstream ss(line);
        std::string date;
        std::string rate;

        if (!std::getline(ss, date, ',') ||
            !std::getline(ss, rate))
            continue;

        date = trim(date);
        rate = trim(rate);

        std::stringstream converter(rate);
        double value;

        if (!(converter >> value))
            continue;

        converter >> std::ws;

        if (!converter.eof())
            continue;

        dataBase[date] = value;
    }

    file.close();
}

double BitcoinExchange::getRate(const std::string &date) const
{
    std::map<std::string, double>::const_iterator it;

    it = dataBase.upper_bound(date);

    if (it == dataBase.begin())
        throw std::runtime_error("No earlier exchange rate available");

    --it;
    return it->second;
}

static bool isValidDate(const std::string &date)
{
    if (date.length() != 10)
        return false;

    if (date[4] != '-' || date[7] != '-')
        return false;

    for (size_t i = 0; i < date.length(); i++)
    {
        if (i == 4 || i == 7)
            continue;

        if (!std::isdigit(static_cast<unsigned char>(date[i])))
            return false;
    }

    int year = std::atoi(date.substr(0, 4).c_str());
    int month = std::atoi(date.substr(5, 2).c_str());
    int day = std::atoi(date.substr(8, 2).c_str());

    if (year < 1 || month < 1 || month > 12)
        return false;

    int days[] = {31, 28, 31, 30, 31, 30,
                  31, 31, 30, 31, 30, 31};

    bool leap = (year % 400 == 0 ||
                (year % 4 == 0 && year % 100 != 0));

    if (leap)
        days[1] = 29;

    if (day < 1 || day > days[month - 1])
        return false;

    return true;
}

static bool parseValue(const std::string &str, double &value)
{
    std::stringstream ss(str);

    if (!(ss >> value))
        return false;

    ss >> std::ws;

    if (!ss.eof())
        return false;

    if (value != value)
        return false;

    return true;
}

void BitcoinExchange::processInput(const std::string &filename)
{
    std::ifstream file(filename.c_str());

    if (!file.is_open())
        throw std::runtime_error("Could not open input file");

    std::string line;

    std::getline(file, line);

    while (std::getline(file, line))
    {
        if (line.empty())
            continue;

        size_t separator = line.find('|');

        if (separator == std::string::npos)
        {
            std::cerr << "Error: bad input => "
                      << line << std::endl;
            continue;
        }

        std::string date = trim(line.substr(0, separator));
        std::string valueStr = trim(line.substr(separator + 1));

        if (!isValidDate(date))
        {
            std::cerr << "Error: bad input => "
                      << line << std::endl;
            continue;
        }

        double value;

        if (!parseValue(valueStr, value))
        {
            std::cerr << "Error: bad input => "
                      << line << std::endl;
            continue;
        }

        if (value < 0)
        {
            std::cerr << "Error: not a positive number."
                      << std::endl;
            continue;
        }

        if (value > 1000)
        {
            std::cerr << "Error: too large a number."
                      << std::endl;
            continue;
        }

        try
        {
            double rate = getRate(date);

            std::cout << date << " => "
                      << value << " = "
                      << value * rate << std::endl;
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    file.close();
}
