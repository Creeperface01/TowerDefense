#pragma once

#include "../EntityBehavior.h"
#include "../../../math/Vector.h"

class ExplodeCloseToTarget : public EntityBehavior {
private:
    Vector2f target_;

    float distance_;

public:
    ExplodeCloseToTarget(
            Entity *e,
            Vector2f target,
            float distance
    );

    bool shouldExecute() override;

    bool startExecuting() override;

    bool canContinue() override;
};
