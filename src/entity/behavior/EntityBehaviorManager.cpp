#include "EntityBehaviorManager.h"

#include <algorithm>

EntityBehaviorManager::Entry::Entry(
        std::unique_ptr<EntityBehavior> behavior,
        int32_t priority
) : behavior(std::move(behavior)), priority(priority) {}

void EntityBehaviorManager::addBehavior(int32_t priority, std::unique_ptr<EntityBehavior> behavior) {
    behaviors.emplace_back(std::move(behavior), priority);
}

void EntityBehaviorManager::tick(uint32_t tick, bool force) {
    if (tick % TICK_RATE == 0 || force) {
        for (auto &entry: behaviors) {
            if (entry.active) {
                if (!canActivate(entry) || !entry.behavior->canContinue()) {
                    entry.active = false;
                    entry.behavior->reset();
                    activeBehaviors.erase(
                            std::remove(
                                    activeBehaviors.begin(),
                                    activeBehaviors.end(),
                                    &entry
                            ),
                            activeBehaviors.end()
                    );
                }
            } else if (canActivate(entry) && entry.behavior->shouldExecute()) {
                if (entry.behavior->startExecuting()) {
                    entry.active = true;
                    activeBehaviors.push_back(&entry);
                }
            }
        }
    } else {
        erase_if(
                activeBehaviors,
                [](Entry *entry) {
                    if (!entry->behavior->canContinue()) {
                        entry->active = false;
                        entry->behavior->reset();
                        return true;
                    }

                    return false;
                }
        );
    }

    for (auto &item: activeBehaviors) {
        item->behavior->tick(tick);
    }
}

bool EntityBehaviorManager::canActivate(Entry &entry) {
    if (activeBehaviors.empty()) {
        return true;
    }

    for (auto &active: activeBehaviors) {
        if (*active == entry) {
            continue;
        }

        if (!areBehaviorsCompatible(entry.behavior.get(), active->behavior.get())) {
            if (entry.priority > active->priority && !active->behavior->isInterruptible()) {
                return false;
            }
        }

//        if (entry.priority >= active->priority) {
//            if (!areBehaviorsCompatible(entry.behavior.get(), active->behavior.get())) {
//                return false;
//            }
//        } else if (!active->behavior->isInterruptible()) {
//            return false;
//        }
    }

    return true;
}

bool EntityBehaviorManager::areBehaviorsCompatible(const EntityBehavior *b1, const EntityBehavior *b2) const {
    return (b1->getCompatibility() & b2->getCompatibility()) == 0;
}
