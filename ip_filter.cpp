#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <exception>

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]

void COut(const std::vector<std::vector<uint8_t>>& ip_pool);
std::vector<std::string> split(const std::string &str, char d)
{
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }
    //stop = str.find(" ");
    r.push_back(str.substr(start));

    return r;
}



void Ip_sort(std::vector<std::vector<uint8_t>>& line)
{
    std::sort(line.begin(), line.end(), [](std::vector<uint8_t>& a, std::vector<uint8_t>& b) {
        for (int i = 0; i < 4; ++i) {
            if (a[i] < b[i])
                return false;
            else if (a[i] > b[i])
                return true;
            else
                continue;
        }
        return false;
        });
    
    
}

void filter(const std::vector<std::vector<uint8_t>>& line,int i)
{
    std::vector<std::vector<uint8_t>> a;
    for (const auto& c : line)
    {
       if (c[0]== i)
       {
           a.push_back(c);
       }
    }
    COut(a);

}
void filter(const std::vector<std::vector<uint8_t>>& line, int first, int second)
{
    std::vector<std::vector<uint8_t>> a;
    for (const auto& c : line)
    {
        if ((c[0] == first)&&(c[1]==second))
        {
            a.push_back(c);
        }
    }
    COut(a);
}
void filter_any(const std::vector<std::vector<uint8_t>>& line, int i)
{
    std::vector<std::vector<uint8_t>> a;
    for (const auto& c : line)
    {
        for (const auto& m : c)
        {
            if (m == i)
            {
                a.push_back(c);
                break;
            }
        }
       
    }
    COut(a);
}

void COut(const std::vector<std::vector<uint8_t>>& ip_pool)
{
    for (const auto& c : ip_pool) {
        for (int i = 0; i < 3; ++i) {
            std::cout << unsigned(c[i]) << ".";
        }
        std::cout << unsigned(c[3]) << std::endl;
    }
}
std::vector<std::vector<uint8_t>> IPToint(const std::vector<std::vector<std::string>>&  ip) {
    std::vector<uint8_t> num;
    std::vector<std::vector<uint8_t>> ippool;
    for (const auto& c : ip) {
        bool bad = false;
        for (const auto& p : c) {
            if (p == "") {
                bad = true;
                break;
            }
            for (const auto& m : p) {
                if (m < '0' || m>'9') {
                    bad = true;
                    break;
                }
                    
            }
            if (bad)
                break;
            
            num.push_back(std::stoi(p));
        }
        if (bad) {
            std::string str = "Bad ip: ";
            for (int i = 0; i < 3; ++i) {
                str += (c[i] + ".");
            }
            str += c[3];
            throw std::invalid_argument(str.c_str());
        }
        ippool.push_back(num);
        num.clear();
    }
    return ippool;
}

int main(int, char const **)
{
    try
    {
        std::vector<std::vector<std::string> > ip_pool;

        for(std::string line; std::getline(std::cin, line);)
        {
            std::vector<std::string> v = split(line, '\t');
            ip_pool.push_back(split(v.at(0), '.'));
        }
        auto ip = IPToint(ip_pool);
        Ip_sort(ip);
        // TODO reverse lexicographically sort

        COut(ip);

        filter(ip, 1);
        filter(ip, 46, 70);
        filter_any(ip, 46);
        
        // 222.173.235.246
        // 222.130.177.64
        // 222.82.198.61
        // ...
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first byte and output
        // ip = filter(1)

        // 1.231.69.33
        // 1.87.203.225
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first and second bytes and output
        // ip = filter(46, 70)

        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76

        // TODO filter by any byte and output
        // ip = filter_any(46)

        // 186.204.34.46
        // 186.46.222.194
        // 185.46.87.231
        // 185.46.86.132
        // 185.46.86.131
        // 185.46.86.131
        // 185.46.86.22
        // 185.46.85.204
        // 185.46.85.78
        // 68.46.218.208
        // 46.251.197.23
        // 46.223.254.56
        // 46.223.254.56
        // 46.182.19.219
        // 46.161.63.66
        // 46.161.61.51
        // 46.161.60.92
        // 46.161.60.35
        // 46.161.58.202
        // 46.161.56.241
        // 46.161.56.203
        // 46.161.56.174
        // 46.161.56.106
        // 46.161.56.106
        // 46.101.163.119
        // 46.101.127.145
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76
        // 46.55.46.98
        // 46.49.43.85
        // 39.46.86.85
        // 5.189.203.46
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
