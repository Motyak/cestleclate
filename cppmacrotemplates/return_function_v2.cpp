#define LOG(msg) log_err(__FILE__, __LINE__, msg)

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

void log_err(const std::string& file, int line, const std::string& msg) {
    print(std::cerr, "[{}:L{}] {}\n", file, line, msg);
}

template <class Function>
auto wrap_try_catch(Function f) {
    auto wrapped = [f](auto... args) {
        try {
            f(args...);
        } catch (const std::exception& e) {
            LOG("uh oh");
        }
    };
    return wrapped;
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
    auto hihi_int_with_logging = wrap_try_catch(static_cast<void(*)(int)>(hihi));
    hihi_int_with_logging(a);

    auto hihi_with_logging = wrap_try_catch(static_cast<void(*)()>(hihi));
    hihi_with_logging();
}
    