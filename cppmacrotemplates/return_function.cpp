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

void log_err(const std::string& filename, int line, const std::string& msg) {
    print(std::cerr, "[{}:L{}] {}\n", filename, line, msg);
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

void haha(int dummy) {
    print(std::cout, "haha\n");
}

void hihi() {
    throw std::exception();
}

int main()
{
    int a = 91;
    auto haha_with_logging = wrap_try_catch(haha);
    haha_with_logging(a);

    auto hihi_with_logging = wrap_try_catch(hihi);
    hihi_with_logging();
}
    