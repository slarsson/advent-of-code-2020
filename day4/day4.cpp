#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
#include <string>
#include <regex>

int main()
{
    std::ifstream file{"input.txt"};
    std::vector<std::map<std::string, std::string>> passports{};

    std::map<std::string, bool> keys{};
    keys["byr"] = true;
    keys["iyr"] = true;
    keys["eyr"] = true;
    keys["hgt"] = true;
    keys["hcl"] = true;
    keys["ecl"] = true;
    keys["pid"] = true;

    // a
    int n = 0;
    std::string line;
    std::string passport;
    while(std::getline(file, line))
    {
        if (line == "")
        {
            std::cout << passport << std::endl;
            std::string row{};
            std::istringstream ss{passport};
            int a_count = 0;
            while (ss >> row)
            {
                row = row.substr(0, row.find(':'));
                if (keys[row])
                {
                    ++a_count;
                }
            }
            
            if (a_count == 7) ++n;
            passport = "";
        }
        passport += " " + line;
    }

    std::cout << n << std::endl;

    // b
    n = 0;
    std::regex e1{"#[0-9a-z]+"};
    std::regex e2{"\\d+"};
    file.clear();
    file.seekg(0); // meh..
    while(std::getline(file, line))
    {
        if (line == "")
        {
            std::cout << passport << std::endl;
            std::string row{};
            std::istringstream ss{passport};
            int count = 0;
            while (ss >> row)
            {
                std::string key = row.substr(0, 3);
                std::string value = row.substr(4, row.length());

                std::cout << key << " " << value << std::endl;

                if (key == "byr")
                {
                    int val = std::stoi(value);
                    if (val < 1920 || val > 2002) break;
                }
                else if (key == "iyr")
                {
                    int val = std::stoi(value);
                    if (val < 2010 || val > 2020) break;
                }
                else if (key == "eyr")
                {
                    int val = std::stoi(value);
                    if (val < 2020 || val > 2030) break;
                }
                else if (key == "hgt")
                {
                    std::string type = value.substr(value.length() - 2, value.length());
                    if (type != "cm" && type != "in") break;
                    int len = std::stoi(value.substr(0, value.length() - 2));
                    if (type == "cm" && (len < 150 || len > 193)) break;
                    if (type == "in" && (len < 59 || len > 76)) break;
                }
                else if (key == "hcl")
                {
                    if (!std::regex_match(value, e1)) break;
                }
                else if (key == "ecl")
                {
                    if (!(value == "amb" || value == "blu" || value == "brn" || value == "gry" || value == "grn" || value == "hzl" || value == "oth")) break;
                }
                else if (key == "pid")
                {
                    if (!(std::regex_match(value, e2) && value.length() == 9)) break;
                }
                else
                {
                    continue;
                }
                
                ++count;
            }

            if (count == 7) ++n;
            
            passport = "";
        }
        passport += " " + line;
    }

    std::cout << n << std::endl;

    return 0;
}