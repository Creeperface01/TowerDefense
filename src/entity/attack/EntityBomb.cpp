#include "EntityBomb.h"

#include "../behavior/impl/AttackBehavior.h"
#include "../behavior/impl/MoveBehavior.h"
#include "../behavior/impl/MoveToStaticTargetBehavior.h"
#include "../behavior/impl/ExplodeCloseToTarget.h"

#include "../TileEntityTypes.h"

void EntityBomb::init() {
    Entity::init();

    auto nearest = this->world_.findNearestTileEntity(
            this->position_,
            TileEntityTypes::OBJECTIVE
    );

    if (nearest.has_value()) {
        this->addBehavior(
                -1,
                new ExplodeCloseToTarget(this, nearest.value()->getPosition(), 2)
        );

        auto walkablePos = this->world_.findClosestWalkableTile(nearest.value()->getTilePosition());

        if (walkablePos.has_value()) {
            this->addBehavior(
                    0,
                    new MoveToStaticTargetBehavior(
                            this,
                            walkablePos.value()
                    )
            );
        }
    }

    this->addBehavior(1, new MoveBehavior(this));
    this->addBehavior(2, new AttackBehavior(this));
}
