#include "TileEntity.h"

#include <cmath>

TileEntitySnapshot *TileEntity::snapshot() const {
    return new TileEntitySnapshot(
            this->type_,
            this->position_,
            this->boundingBox_,
            this->invulnerable_,
            this->health_
    );
}

void TileEntity::setPosition(Vector2f position) {
    Entity::setPosition(position.floor());
}

Vector2i TileEntity::getTilePosition() const {
    return {
            static_cast<VectorType>(position_.x()),
            static_cast<VectorType>(position_.y())
    };
}
