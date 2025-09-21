
#include <string>
#include <iostream>
#include <vector>
#include <utility>
#include <cstdlib>
#include <string>
#include <sstream>
#include <cctype>
#include <map>



std::vector<std::string> split(std::string str)
{
    std::vector<std::string> ret;
    std::string mot;
    std::istringstream iss(str);

    while(iss >> mot)
        ret.push_back(mot);

    return ret;
}

std::string slice_side(std::string str, int side)
{
    size_t pos = str.find('=');
    if (side == 1)
        return str.substr(pos + 1);
    else
        return str.substr(0, pos);
}


std::vector<double> Reduce(std::vector<double> left, std::vector<double> right, std::vector<std::string> rightS)
{
    int sign = -1;
    std::vector<double> ret = left;
    for (size_t i = 0; i < right.size(); i++)
    {
        if (left[i])
        {
            if (sign == -1 || rightS[sign][0] == '+')
            {
                ret[i] = left[i] - right[i];
                sign++;
            }
            else 
            {
                ret[i] = left[i] + right[i];
                sign++;
            }
        }
    }
    return ret;
}
double MySqrt(double n)
{
    double x = n;
    double y = 1;
    double e = 0.000001;

    while (x - y > e)
    {
        x = (x + y) / 2;
        y = n / x;
    }
    return x;
}

int main (int ac, char **av)
{
    if (ac != 2)
    {
        std::cout << "Error: Bad input." << std::endl;
        return 1;
    }
    int side  = 0;
    int i = 1;
    std::vector<double> left;
    std::vector<double> right;
    std::vector<std::string> leftS;
    std::vector<std::string> rightS;
    std::vector<std::string> raw = split(av[1]);
    double tmp;
    for (std::vector<std::string>::iterator it = raw.begin(); it != raw.end(); it++)
    {
        if (it[0][0] == 'X' || it[0][0] == '*')
            continue;
        else if (it[0][0] == '-' || it[0][0] == '+')
        {
            if (side == 0)
                leftS.push_back(*it);
            else
                rightS.push_back(*it);
        }
        else if (it[0][0] == '=')
            side = 1;
        else 
        {
            if (side == 0)
                left.push_back(std::stod(*it));
            else
                right.push_back(std::stod(*it));
        }
    }
    std::vector<double> reduce = Reduce(left, right, rightS);
    std::cout << "Reduced form: ";
    for (size_t i = 0; i < reduce.size(); i++)
    {
        std::cout << reduce[i]  << " * X^" << i  << " ";
        if (i < reduce.size() - 1)
            std::cout << leftS[i] << " ";
    }
    std::cout << "= 0"<< std::endl;
    if (reduce.size() - 1 == 0)
    {
        if (reduce[0] >= 0)
            std::cout << "Any real number is a solution." << std::endl;
        else
            std::cout << "No solution." << std::endl;
        return 0;

    }
    std::cout << "Polynomial degree: " << reduce.size() - 1 << std::endl;
    if (reduce.size() - 1 == 3)
    {
        std::cout << "The polynomial degree is strictly greater than 2, can't solve." << std::endl;
        return 0;
    }
    if (reduce.size() - 1 == 1)
    {
        tmp = reduce[0] / -reduce[1];
        std::cout << "The solution is:\n" << tmp << std::endl;
        return 0;
    }
    if (reduce.size() - 1 == 2)
    {
        while (i > 0)
        {
            if (leftS[i][0] == '-')
                reduce[i - 1] = -reduce[i - 1];
            i--;
        }
        
        double a = reduce[2];
        double b = reduce[1];
        double c = reduce[0];
        double delta = (b * b) - (4 * a * c);
    
        std::cout << "a: " << a << ", b: " << b << ", c: " << c << ", delta: " << delta << std::endl;
        if (delta < 0)
        {
            std::cout << "Discriminant is strictly negative, the two solutions are complex:" << std::endl;
            std::cout << -b / (2 * a) << " + i * " << MySqrt(-delta) / (2 * a) << std::endl;
            std::cout << -b / (2 * a) << " - i * " << MySqrt(-delta) / (2 * a) << std::endl;
            return 0;
        }
        else if (delta == 0)
        {
            std::cout << "Discriminant is null, the solution is:" << std::endl;
            std::cout << -b / (2 * a) << std::endl;
            return 0;
        }
        else
        {
            std::cout << "Discriminant is strictly positive, the two solutions are:" << std::endl;
            std::cout << (b + MySqrt(delta)) / (2 * a) << std::endl;
            std::cout << (b - MySqrt(delta)) / (2 * a) << std::endl;
            return 0;
        }
    }
    return 0;
}
