#include "TileEntityCanon.h"

#include "../behavior/impl/ShootOnMovingTargetBehavior.h"
#include "../finder/EntityFurthestApproachingTargetFinder.h"
#include "../finder/EntityClosestTargetFinder.h"
#include "../finder/selector/EntityTypeSelector.h"
#include "../EntityTypes.h"

void TileEntityCanon::init() {
    Entity::init();

    this->invulnerable_ = true;

    auto finder = new EntityFurthestApproachingTargetFinder(
            &this->world_,
            {10},
            {new EntityTypeSelector(EntityTypes::BOMB)}
    );

    this->addBehavior(
            0,
            new ShootOnMovingTargetBehavior(
                    this,
                    finder,
                    20,
                    EntityTypes::LASER_BEAM,
                    0.5f
            ));
}
