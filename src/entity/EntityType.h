#pragma once

#include "attribute/EntityAttribute.h"

#include <concepts>
#include <type_traits>
#include <string>
#include <utility>
#include <vector>
#include <functional>
#include <initializer_list>
#include <unordered_map>

class Entity;

class World;

class EntityType {
public:

    enum class Type {
        ENTITY,
        TILE_ENTITY
    };

private:
    std::string name_;

    Type type_;

    float width_;

    float height_;

    std::function<std::unordered_map<const attribute_base *, void *>()> attributes_;

    std::function<Entity *(const EntityType *, World &)> factory_;

    EntityType(
            std::string name,
            Type type,
            float width,
            float height,
            std::function<std::unordered_map<const attribute_base *, void *>()> attributes,
            std::function<Entity *(const EntityType *, World &)> factory
    );

    [[nodiscard]] Entity *create(World &world) const;

private:

    friend class World;

public:

    EntityType(const EntityType &) = delete;

    EntityType &operator=(const EntityType &) = delete;

    bool operator==(const EntityType &other) const;

    bool operator!=(const EntityType &other) const;

    [[nodiscard]] const std::string &getName() const;

    [[nodiscard]] Type getType() const;

    [[nodiscard]] float getWidth() const;

    [[nodiscard]] float getHeight() const;

    [[nodiscard]] std::unordered_map<const attribute_base *, void *> getAttributes() const;

    template<class T>
    static EntityType *of(
            std::string name,
            float width,
            float height,
            const std::function<std::unordered_map<const attribute_base *, void *>()> &attributes = []() -> std::unordered_map<const attribute_base *, void *> {
                return {};
            }
    );
};


