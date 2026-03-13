#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <cmath>

std::vector<std::string> split(std::string str) 
{
    std::vector<std::string> tokens;
    std::string word;
    std::istringstream iss(str);
    while (iss >> word) tokens.push_back(word);
    return tokens;
}

double MySqrt(double n) 
{
    double x = n, y = 1;
    for (int i = 0; i < 1000; i++) 
    { 
        if (x <= 0)
            break;
        x = (x + y) / 2;
        y = n / x;
    }
    return x;
}

int main(int ac, char **av) 
{
    std::string input;
    if (ac == 1)
    {
        while (!std::getline(std::cin, input))
            std::cout << "Please enter an equation: ";
    }
    else if (ac == 2)
        input = av[1];
    else if (ac != 2 || input.empty()) {
        std::cout << "Usage: ./computor \"equation\"" << std::endl;
        return 1;
    }

    std::map<int, double> poly; 
    std::vector<std::string> tokens = split(input);
    if (tokens.empty()) 
    {
        std::cout << "No equation provided." << std::endl;
        return 1;
    }
    double side = 1.0; 
    double sign = 1.0;
    int max_degree = 0;
    
    for (size_t i = 0; i < tokens.size(); ++i) 
    {
        if (tokens[i] == "=") 
        {
            side = -1.0;
            sign = 1.0;
        }
        else if (tokens[i] == "-") 
            sign = -1.0;
        else if (tokens[i] == "+") 
            sign = 1.0;
        else if (isdigit(tokens[i][0]) || (tokens[i].size() > 1 && tokens[i][0] == '-')) 
        {
            double coeff = std::stod(tokens[i]);
            int degree = 0;

            if (i + 2 < tokens.size() && tokens[i+2].find("X^") != std::string::npos) 
            {
                degree = std::stoi(tokens[i+2].substr(2));
                i += 2; 
            }
            poly[degree] += coeff * sign * side;
            sign = 1.0; 
        }
    }
    for (auto it = poly.begin(); it != poly.end(); ++it) 
    {
        if (it->second != 0) 
            max_degree = it->first;
    }
    std::cout << "Reduced form: ";
    bool first = true;
    for (int d = 0; d <= max_degree; ++d) 
    {
        if (poly[d] == 0 && d != 0 && d != max_degree) 
            continue;
        if (!first) std::cout << (poly[d] >= 0 ? " + " : " - ");
            else if (poly[d] < 0) std::cout << "-";
        
        std::cout << (poly[d] < 0 ? -poly[d] : poly[d]) << " * X^" << d;
        first = false;
    }
    std::cout << " = 0" << std::endl;
    std::cout << "Polynomial degree: " << max_degree << std::endl;

    if (max_degree > 2) 
        std::cout << "The polynomial degree is strictly greater than 2, I can't solve." << std::endl;
    else if (max_degree == 2) 
    {
        double a = poly[2], b = poly[1], c = poly[0];
        double delta = (b * b) - (4 * a * c);
        if (delta > 0)
        {
            std::cout << "Discriminant is strictly positive, the two solutions are:" << std::endl;
            std::cout << (-b - MySqrt(delta)) / (2 * a) << std::endl;
            std::cout << (-b + MySqrt(delta)) / (2 * a) << std::endl;
        }
        else if (delta == 0)
            std::cout << "Discriminant is zero, the solution is:\n" << -b / (2 * a) << std::endl;
        else 
        {
            double d_sign = 1.0;
            if (a < 0) 
                d_sign = -1.0;
            std::cout << "Discriminant is negative, the two complex solutions are:" << std::endl;
            std::cout << -b * d_sign << "/" << (2 * a) * d_sign << " + " << MySqrt(-delta) * d_sign << "i/" << (2 * a) * d_sign << std::endl;
            std::cout << -b * d_sign << "/" << (2 * a) * d_sign<< " - " << MySqrt(-delta) * d_sign << "i/" << (2 * a) * d_sign<< std::endl;
        }
    } 
    else if (max_degree == 1) 
        std::cout << "The solution is:\n" << -poly[0] / poly[1] << std::endl;
    else 
    { 
        if (poly[0] == 0)
            std::cout << "All real numbers are solutions." << std::endl;
        else
            std::cout << "No solution." << std::endl;
    }
    return 0;
}