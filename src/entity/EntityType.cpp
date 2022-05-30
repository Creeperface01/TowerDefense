#include "EntityType.h"

#include <utility>

#include "Entity.h"

bool EntityType::operator==(const EntityType &other) const {
    return this == &other;
}

bool EntityType::operator!=(const EntityType &other) const {
    return this != &other;
}

const std::string &EntityType::getName() const {
    return name_;
}

EntityType::EntityType(
        std::string name,
        Type type,
        float width,
        float height,
        std::function<std::unordered_map<const attribute_base *, void *>()> attributes,
        std::function<Entity *(const EntityType *, World &)> factory
) :
        name_(std::move(name)),
        type_(type),
        width_(width),
        height_(height),
        attributes_(std::move(attributes)),
        factory_(std::move(factory)) {
}

Entity *EntityType::create(World &world) const {
    return factory_(this, world);
}

EntityType::Type EntityType::getType() const {
    return type_;
}

float EntityType::getWidth() const {
    return width_;
}

float EntityType::getHeight() const {
    return height_;
}

std::unordered_map<const attribute_base *, void *> EntityType::getAttributes() const {
    return this->attributes_();
}
