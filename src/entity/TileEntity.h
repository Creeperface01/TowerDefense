#pragma once

#include "Entity.h"
#include "TileEntitySnapshot.h"

#include <memory>
#include <unordered_map>

class TileEntity : public Entity {

public:
    using Entity::Entity;

    [[nodiscard]] Vector2i getTilePosition() const;

    void setPosition(Vector2f position) override;

    [[nodiscard]] TileEntitySnapshot *snapshot() const override;
};

template<class T>
EntityType *EntityType::of(
        std::string name,
        float width,
        float height,
        const std::function<std::unordered_map<const attribute_base *, void *>()> &attributes
) {
    return new EntityType(
            std::move(name),
            std::is_base_of_v<TileEntity, T> ? Type::TILE_ENTITY : Type::ENTITY,
            width,
            height,
            attributes,
            [](const EntityType *type, World &world) {
                return new T(type, world);
            }
    );
}
