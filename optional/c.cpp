#define ASSERT(condition, message) \
    if (! (condition)) { \
        std::cerr << "Assertion `" #condition "` failed in " << __FILE__ \
                << " line " << __LINE__ << ": " << message << std::endl; \
        std::terminate(); \
    }

#include <iostream>
#include <optional>
#include <type_traits>

template <class T>
class Optional {
  private:
    std::optional<T> opt;

    Optional() = default;

    Optional(T value) {
        opt = value;
    }

  public:
    static Optional<T> of(T value) {
        return Optional(value);
    }

    static Optional<T> of(T* value) {
        ASSERT(value != nullptr, "passing null to Optional::of")
        return Optional(*value);
    }

    static Optional<T> ofNullable(T* value) {
        if (value == nullptr) {
            return Optional(*value);
        } else {
            return Optional::empty();
        }
    }

    static Optional<T> empty() {
        return Optional();
    }

    T get() {
        return opt.value();
    }

    bool isPresent() {
        return (bool)opt;
    }

    bool isEmpty() {
        return !isPresent();
    }

    T orElse(T other) {
        return isPresent()? opt.value() : other;
    }

    T orElseThrow() {
        if (isPresent()) {
            return opt.value();
        }
        throw new BadAccessError();
    }

    class BadAccessError : public std::runtime_error {
      public:
        BadAccessError() : std::runtime_error("Bad access error"){};
    };
};

#include <random>

using Entry = std::string;

Optional<Entry> getEntry() {
    if (std::random_device()() % 2) {
        return Optional<Entry>::empty();
    } else {
        return Optional<Entry>::of("lucky");
    }
}

int main()
{
    Optional<Entry> potentialEntry = getEntry();
    Entry entry = potentialEntry.orElse("unlucky");
    std::cout << entry << std::endl;
}

