
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

    // for (auto &m : ret)
    //     std::cout << m << std::endl;
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
        //std::cout << sign << std::endl;
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

int main (int ac, char **av)
{
    if (ac != 2)
    {
        std::cout << "Error" << std::endl;
        return 1;
    }
    int side  = 0;
    std::vector<double> left;
    std::vector<double> right;
    std::vector<std::string> leftS;
    std::vector<std::string> rightS;
    std::vector<std::string> raw = split(av[1]);
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
    // for (std::vector<double>::iterator it = left.begin(); it != left.end(); it++)
    // {
    //     std::cout << *it << std::endl;
    // }
    std::vector<double> reduce = Reduce(left, right, rightS);
    std::cout << "Reduced form: ";
    for (size_t i = 0; i < reduce.size(); i++)
    {
        std::cout << reduce[i]  << " * X^" << i  << " ";
        if (i < reduce.size() - 1)
            std::cout << leftS[i] << " ";
    }
    std::cout << "= 0"<< std::endl;
    std::cout << "Polynomial degree: " << reduce.size() - 1 << std::endl;
    return 0;
}
