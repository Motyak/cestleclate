#ifndef UTILS_CLASSES_OPTIONAL_H
#define UTILS_CLASSES_OPTIONAL_H

#include <utils/keywords.h> // unless

#include <optional> // std::optional
#include <type_traits> // std::is_pointer

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
        if constexpr (std::is_pointer<T>::value) {
            return of((T*) value);
        }
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

    T orElse(T other) {
        return isPresent()? opt.value() : other;
    }

    T orElseThrow(std::exception e = BadOptionalAccess()) {
        unless (isPresent()) {
            throw e;
        }
        return opt.value();
    }

    class BadOptionalAccess : public std::exception {
      public:
        char* what() {
            return "Cannot access empty Optional";
        }
    };
};

#endif
