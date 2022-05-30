#pragma once

#include "../EntityBehavior.h"
#include "../../../math/Vector.h"
#include "../../../world/World.h"
#include "../../../world/pathfinder/AStarPathFinder.h"

#include <optional>

class MoveToStaticTargetBehavior : public EntityBehavior {
private:
    Vector2f position_;
    float distance_;

    std::optional<Path> path_;

public:
    MoveToStaticTargetBehavior(Entity *e, Vector2f position, float distance = 0.1f);

    bool canContinue() override;

    bool startExecuting() override;

    bool shouldExecute() override;

    void tick(uint32_t tick) override;

    void reset() override;
};
