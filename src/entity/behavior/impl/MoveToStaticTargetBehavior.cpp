#include "MoveToStaticTargetBehavior.h"

#include "../../Entity.h"
#include "../../common/EntityLaserBeam.h"

#include <iostream>

MoveToStaticTargetBehavior::MoveToStaticTargetBehavior(
        Entity *e,
        Vector2f position,
        float distance
) :
        EntityBehavior(e),
        position_(position),
        distance_(distance) {
}

void MoveToStaticTargetBehavior::tick(uint32_t tick) {
    float distance = entity_->getPosition().distanceSquared(path_->current());

    if (distance <= 0.2) {
        if (!path_->hasNext()) {
            return;
        }

        path_->next();
    }

    Vector2f motion = path_->current() - entity_->getPosition();

    if (!motion.is_zero()) {
        motion = static_cast<const vector2<float>>(motion.normalize());
        motion *= 0.3f;
    }

    entity_->setMotion(motion);
}

bool MoveToStaticTargetBehavior::shouldExecute() {
    return (entity_->getPosition().distanceSquared(this->position_) - (this->distance_ * this->distance_)) > 0.1f;
}

bool MoveToStaticTargetBehavior::canContinue() {
    return shouldExecute();
}

bool MoveToStaticTargetBehavior::startExecuting() {
    this->path_ = entity_->getWorld().getPathFinder().findPath(
            this->entity_->getPosition().toInt(),
            this->position_
    );

    return this->path_.has_value();
}

void MoveToStaticTargetBehavior::reset() {
    EntityBehavior::reset();

    this->entity_->setMotion({0, 0});
}
