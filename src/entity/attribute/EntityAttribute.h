#pragma once

#include <string>
#include <utility>
#include <functional>

struct attribute_base {
public:
    using pair_type = std::pair<const attribute_base *, void *>;
};

template<typename T>
class EntityAttribute : public attribute_base {
public:
    using this_type = EntityAttribute<T>;
    using value_type = T;

private:

    std::string name_;

    T min_value_;
    T max_value_;

    T default_value_;

    friend class AttributeAdapter;

public:

    EntityAttribute(
            std::string name,
            T minValue,
            T maxValue,
            T defaultValue
    ) :
            name_(std::move(name)),
            min_value_(minValue),
            max_value_(maxValue),
            default_value_(defaultValue) {}

    EntityAttribute(const this_type &) = delete;

    this_type &operator=(const this_type &) = delete;

    [[nodiscard]] const std::string &getName() const {
        return name_;
    }

    T getMinValue() const {
        return min_value_;
    }

    T getMaxValue() const {
        return max_value_;
    }

    T getDefaultValue() const {
        return default_value_;
    }

    static void *value(T value) {
        return static_cast<void *>(new T(value));
    }

    pair_type valuePair(T value) const {
        return {
                this,
                static_cast<void *>(new T(value))
        };
    }

};


