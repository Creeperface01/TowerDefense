#include "TileEntitySpawner.h"

#include "../behavior/impl/SpawnBehavior.h"
#include "../../world/World.h"
#include "../EntityTypes.h"

#include <iostream>

void TileEntitySpawner::tick(uint32_t tick) {
    TileEntity::tick(tick);
}

void TileEntitySpawner::init() {
    Entity::init();

    this->invulnerable_ = true;

    this->addBehavior(0, new SpawnBehavior(
            this,
            this->getWorld().getConfiguration().spawning_rate_,
            EntityTypes::BOMB
    ));
}
