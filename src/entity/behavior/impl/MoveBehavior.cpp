#include "MoveBehavior.h"

#include "../../Entity.h"

#include <iostream>

void MoveBehavior::tick(uint32_t tick) {
    auto motion = entity_->getMotion();

    entity_->setPosition(entity_->getPosition().add(motion));
}

bool MoveBehavior::shouldExecute() {
    return !entity_->getMotion().is_zero();
}
