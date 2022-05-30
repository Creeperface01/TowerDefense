#include "EntityLaserBeam.h"

#include "../behavior/impl/MoveBehavior.h"
#include "../../world/World.h"

#include <iostream>

void EntityLaserBeam::init() {
    Entity::init();

    this->invulnerable_ = true;

    this->addBehavior(0, new MoveBehavior(this));
}

void EntityLaserBeam::tick(uint32_t tick) {
    Entity::tick(tick);

    if (ticks_lived_ > 80) {
        close();
        return;
    }

    auto colliding = world_.findCollidingEntities(this->getPosition(), this);

    for (const auto &item: colliding) {
        if (item->getType() == EntityTypes::BOMB) {
            item->attack(5);
            this->close();
            break;
        }
    }
}
