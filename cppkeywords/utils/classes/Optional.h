#ifndef UTILS_CLASSES_OPTIONAL_H
#define UTILS_CLASSES_OPTIONAL_H

#include <utils/keywords.h> // unless

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

        unless (isPresent()) {
            throw new BadAccessError();
        }
        return opt.value();
    }

    class BadAccessError : public std::runtime_error {
      public:
        BadAccessError() : std::runtime_error("Bad access error"){};
    };
};

#endif
