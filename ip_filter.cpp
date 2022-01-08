#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
enum what { Less, Equal, More };
void COut(const std::vector<std::vector<std::string>>& line);
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

    r.push_back(str.substr(start));

    return r;
}

what isMore(const std::vector<std::string>& a, const std::vector < std::string>& b)
{

    for (int i=0;i<a.size()-1;++i)
    {
        if (std::stoi(a[i]) > std::stoi(b[i]))
            return More;
        else if (std::stoi(a[i]) < std::stoi(b[i]))
            return Less;
    }
    return Equal;
}

void Ip_sort(std::vector<std::vector<std::string>>& line)
{
    std::vector<std::string> str;

    for (int i = 0; i < line.size() - 1; i++) {
        for (int j = 0; j < line.size() - i-1; j++) {
            what m = isMore(line[j + 1], line[j]);
            if (m == Less)
            {
                str = line[j];
                line[j] = line[j+1];
                line[j+1] = str;
            }
        }
    }
    std::vector<std::vector<std::string>> a;
    for (int i = line.size() - 1; i != -1; i--)
    {
        a.push_back(line[i]);
    }
    line.clear();
    line = a;
}

void filter(std::vector<std::vector<std::string>> line,int i)
{
    std::vector<std::vector<std::string>> a;
    for (const auto& c : line)
    {
       if (std::stoi(c[0]) == i)
       {
           a.push_back(c);
       }
    }
    COut(a);

}
void filter(std::vector<std::vector<std::string>> line, int first, int second)
{
    std::vector<std::vector<std::string>> a;
    for (const auto& c : line)
    {
        if ((std::stoi(c[0]) == first)&&(std::stoi(c[1])==second))
        {
            a.push_back(c);
        }
    }
    COut(a);
}
void filter_any(std::vector<std::vector<std::string>> line, int i)
{
    std::vector<std::vector<std::string>> a;
    for (const auto& c : line)
    {
        for (const auto& m : c)
        {
            if (std::stoi(m) == i)
            {
                a.push_back(c);
                continue;
            }
        }
       
    }
    COut(a);
}

void COut(const std::vector<std::vector<std::string>>& ip_pool)
{
    for (std::vector<std::vector<std::string>>::const_iterator ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip)
    {
        for (std::vector<std::string>::const_iterator ip_part = ip->cbegin(); ip_part != ip->cend(); ++ip_part)
        {
            if (ip_part != ip->cbegin())
            {
                std::cout << ".";

            }
            std::cout << *ip_part;
        }
        std::cout << std::endl;
    }
}

int main(int argc, char const *argv[])
{
    try
    {
        std::vector<std::vector<std::string> > ip_pool;

        for(std::string line; std::getline(std::cin, line);)
        {
            std::vector<std::string> v = split(line, '\t');
            ip_pool.push_back(split(v.at(0), '.'));
        }

        Ip_sort(ip_pool);
        // TODO reverse lexicographically sort

        COut(ip_pool);

        filter(ip_pool, 46);
        filter(ip_pool, 46, 70);
        filter_any(ip_pool, 46);
        
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
