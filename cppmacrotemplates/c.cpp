#define LOG(msg) log_err(__FILE__, __LINE__, msg)
#define TRY(x) try_catch([=]{x});

#include <iostream>

void print(std::ostream& os, const char* format)
{
    os << format;
}

template<typename T, typename... Targs>
void print(std::ostream& os, const char* format, T value, Targs... Fargs)
{
    for (; *format != '\0'; ++format)
    {
        if (*format == '{' && *(format + 1) == '}')
        {
            os << value;
            print(os, format + 2, Fargs...);
            return;
        }
        os << *format;
    }
}

void log_err(const std::string& filename, int line, const std::string& msg) {
    print(std::cerr, "[{}:L{}] {}\n", filename, line, msg);
}

template <class Function>
void try_catch(Function f) {
    try {
        f();
    } catch (std::exception e) {
        LOG("uh oh");
    }
}

void hihi(int dummy) {
    print(std::cout, "hihi\n");
}

void hihi() {
    throw std::exception();
}

int main()
{
    int a = 91;
    TRY (
        hihi(a);
    )
    
    TRY (
        hihi();
    )
}
