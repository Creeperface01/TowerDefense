#include "EntityBehavior.h"

#include "../Entity.h"

EntityBehavior::EntityBehavior(Entity *e) : entity_(e) {

}

bool EntityBehavior::canContinue() {
    return shouldExecute();
}

bool EntityBehavior::startExecuting() {
    return true;
}

void EntityBehavior::reset() {

}

bool EntityBehavior::isInterruptible() {
    return false;
}

uint64_t EntityBehavior::getCompatibility() const {
    return compatibility_;
}

void EntityBehavior::setCompatibility(uint64_t compatibility) {
    compatibility_ = compatibility;
}

void EntityBehavior::tick(uint32_t tick) {

}
