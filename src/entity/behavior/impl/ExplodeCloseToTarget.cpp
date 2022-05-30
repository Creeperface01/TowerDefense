#include "ExplodeCloseToTarget.h"

#include "../../Entity.h"
#include "../../../world/World.h"

ExplodeCloseToTarget::ExplodeCloseToTarget(
        Entity *e,
        Vector2f target,
        float distance
) :
        EntityBehavior(e),
        target_(target),
        distance_(distance) {}

bool ExplodeCloseToTarget::shouldExecute() {
    return this->entity_->getPosition().distanceSquared(this->target_) <= (distance_ * distance_);
}

bool ExplodeCloseToTarget::startExecuting() {
    this->entity_->close();
    return true;
}

bool ExplodeCloseToTarget::canContinue() {
    return false;
}
