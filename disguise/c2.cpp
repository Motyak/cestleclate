#include <iostream>
#include <functional>
#include <variant>

/* overload pattern */
template<class... Ts> struct overload : Ts... { using Ts::operator()...; };
template<class... Ts> overload(Ts...) -> overload<Ts...>;

template <class Supertype>
void call(std::function<void(Supertype)> fn, auto sub) {
    return fn(Supertype{sub});
}

struct Json { std::string _; };
struct Csv { std::string _; };
using Parsable = std::variant<Json,Csv>;


void parse(Parsable p) {
    std::visit(overload {
        [](Json){ std::cout << "json" << std::endl; },
        [](Csv){ std::cout << "csv" << std::endl; }
    }, p);
}

int main()
{
    std::string text = "fds";
    call<Json>(parse, text);
    call<Csv>(parse, text);
}
