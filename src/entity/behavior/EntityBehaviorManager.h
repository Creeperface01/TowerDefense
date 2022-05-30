#pragma once

#include <cstdint>
#include <memory>
#include <vector>

#include "EntityBehavior.h"

class EntityBehaviorManager {
private:

    static uint32_t const TICK_RATE = 3;

    struct Entry {
        std::unique_ptr<EntityBehavior> behavior;

        int32_t priority;

        bool active = false;

        Entry(std::unique_ptr<EntityBehavior> behavior, int32_t priority);

        bool operator==(const Entry &) const = default;
    };

    std::vector<Entry> behaviors;

    std::vector<Entry *> activeBehaviors;

    bool canActivate(Entry &entry);

public:

    void addBehavior(int32_t priority, std::unique_ptr<EntityBehavior> behavior);

    void tick(uint32_t tick, bool force = false);

    bool areBehaviorsCompatible(const EntityBehavior *b1, const EntityBehavior *b2) const;
};
