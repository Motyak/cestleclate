#include <iostream>
#include <vector>
#include <variant>
#include <sstream>
#include <regex>
#include <algorithm>

#include <cctype>

/* overload pattern for in-place visitation */
template<class... Ts> struct overload : Ts... { using Ts::operator()...; };
template<class... Ts> overload(Ts...) -> overload<Ts...>;

// returns most significant bit
int msb(int n)
{
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    ++n;
    return n >> 1;
}

using Arg = std::variant<double,long long,char,bool,std::string>;
using Args = std::vector<Arg>;

// split all separated elements as substrings
Args split(const std::string& str)
{
    std::stringstream ss(str);
    std::istream_iterator<std::string> begin(ss), end;
    return Args(begin, end);
}

bool regexMatch(const std::string& str, const std::string& re)
{
    std::regex regex(re);
    std::smatch m;
    return std::regex_search(str, m, regex);
}

// case insensitive
bool regexMatchI(const std::string& str, const std::string& re)
{
    std::regex regex(re, std::regex::icase);
    std::smatch m;
    return std::regex_search(str, m, regex);
}

enum ArgType
{
    DOUBLE =    0b10000,
    LONG_LONG = 0b01000,
    CHAR =      0b00100,
    BOOL =      0b00010,
    STRING =    0b00001
};

// map qui associe chaque converter de string vers x, pour x dans ArgType
const std::map<ArgType,std::function<Arg(const std::string&)>> converter {
    { ArgType::DOUBLE, [](const std::string& str)->Arg{return stod(str);} },
    { ArgType::LONG_LONG, [](const std::string& str)->Arg{return stoll(str);} },
    { ArgType::CHAR, [](const std::string& str)->Arg{return str.at(0);} },
    { ArgType::BOOL, [](const std::string& str)->Arg{return toupper(str[0])=='T'?true:false;} },
    { ArgType::STRING, [](const std::string& str)->Arg{return str;} }
};

unsigned char nextArgType(const std::string& args)
{
    // double|long long|char|bool|std::string
    unsigned char res = 0b00000;

    res |= regexMatch(args, R"(^\d+\.\d+(\ |$))")?ArgType::DOUBLE:0;
    res |= regexMatch(args, R"(^\d+(\ |$))")?ArgType::LONG_LONG:0;
    res |= regexMatch(args, R"(^.{1}(\ |$))")?ArgType::CHAR:0;
    res |= regexMatchI(args, R"(^(true|false)(\ |$))")?ArgType::BOOL:0;
    res |= ArgType::STRING; /* always ON */

    return res;
}

Args requestArgs()
{
    /* cin line to istringstream */
    std::string userInput;
    std::getline(std::cin, userInput);

    /* split the arguments and apply correct types */
    Args res = split(userInput);
    std::for_each(res.begin(), res.end(), [](auto& e){
        std::string& str = std::get<std::string>(e);
        ArgType type = (ArgType)msb((int)nextArgType(str));
        e = converter.at(type)(str);
    });

    return res;
}

// g++ --std=c++17 c.cpp
int main()
{
    auto userInput = requestArgs();
    for(const auto& arg : userInput)
    {
        std::visit(overload{
            [](double d){std::cout << "double: " << d;},
            [](long long i){std::cout << "long long: " << i;},
            [](char c){std::cout << "char: " << c;},
            [](bool b){std::cout << "bool: " << b;},
            [](const auto& str){std::cout << "str: " << str;}
        }, arg);
        std::cout << std::endl;
    }
}

