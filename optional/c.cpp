#include <iostream>
#include <optional>

template <typename T>
struct Optional {
  private:
    std::optional<T> opt;

    Optional() = default;

    Optional(T value) {
        opt = value;
    }

  public:
    static Optional<T> of(T value) {
        return Optional{value};
    }

    static Optional<T> of(T* value) {
        return (value == nullptr)? Optional::empty() : Optional{*value};
    }

    static Optional<T> empty() {
        return Optional{};
    }

    T get() {
        return opt.value();
    }

    bool isPresent() {
        return (bool) opt;
    }

    bool isEmpty() {
        return !isPresent();
    }

    T orElse(T other) {
        return isPresent()? opt.value() : other;
    }

    T orElseThrow() {

        if (isEmpty()) {
            throw new BadAccessError();
        }
        return opt.value();
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
