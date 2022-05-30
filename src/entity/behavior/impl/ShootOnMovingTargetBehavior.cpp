#include "ShootOnMovingTargetBehavior.h"

#include "../../../world/World.h"
#include "../../../math/Util.h"

#include <cmath>
#include <iostream>

ShootOnMovingTargetBehavior::ShootOnMovingTargetBehavior(
        Entity *e,
        EntityTargetFinder *finder,
        uint32_t shooting_frequency,
        const EntityType *projectile_type,
        float projectile_speed
) :
        EntityBehavior(e),
        finder_(finder),
        shooting_frequency_(shooting_frequency),
        projectile_type_(projectile_type),
        projectile_speed_(projectile_speed) {}

bool ShootOnMovingTargetBehavior::shouldExecute() {
    return (entity_->getWorld().getTick() - last_shoot_tick_) >= shooting_frequency_;
}

bool ShootOnMovingTargetBehavior::startExecuting() {
    last_shoot_tick_ = entity_->getWorld().getTick();

    auto target_ = this->finder_->find(this->entity_);

    if (!target_.has_value()) {
        return false;
    }

    auto target = target_.value();

    float speed = projectile_speed_;

    Vector2f projectile_offset = Vector2f{
            projectile_type_->getWidth() / 2,
            projectile_type_->getHeight() / 2
    };

    Vector2f source_pos = entity_->getBoundingBox().getCenter() - projectile_offset;
    Vector2f target_pos = target->getBoundingBox().getCenter() - projectile_offset;
    Vector2f target_motion = target->getMotion();

    auto intercept_pos = MathUtil::intercept(
            source_pos,
            target_pos,
            target_motion,
            speed
    );

    if (!intercept_pos.has_value()) {
        return false;
    }

    Vector2f projectile_motion = intercept_pos.value() - source_pos;

    if (projectile_motion.is_zero()) {
        return false;
    }

    projectile_motion.normalize();
    projectile_motion *= speed;

    auto projectile = entity_->getWorld().createEntity(
            projectile_type_,
            entity_->getPosition()
    );
    projectile->setMotion(projectile_motion);

    return false;
}

ShootOnMovingTargetBehavior::~ShootOnMovingTargetBehavior() {
    EntityBehavior::~EntityBehavior();
}
