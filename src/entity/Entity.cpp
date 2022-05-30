#include "Entity.h"

#include "../world/World.h"
#include "attribute/EntityAttributes.h"

#include <algorithm>

uint64_t Entity::idCounter_ = 0;

Entity::Entity(const EntityType *type, World &world) :
        world_(world),
        id_(idCounter_++),
        type_(type),
        closed_(false) {
}

bool Entity::isClosed() const {
    return closed_;
}

World &Entity::getWorld() const {
    return world_;
}

void Entity::tick(uint32_t tick) {
    if (closed_) {
        return;
    }

    if (ticks_lived_ == 0) {
        this->behaviorManager_.tick(world_.getTick(), true);
    }

    if (!this->world_.getBoundingBox().isVectorInside(this->getPosition())) {
        this->close();
        return;
    }

    this->behaviorManager_.tick(tick);

    ticks_lived_++;
}

const Vector2f &Entity::getPosition() const {
    return position_;
}

void Entity::setPosition(Vector2f position) {
    position_ = position;

    recalculateBoundingBox();
}

const Vector2f &Entity::getMotion() const {
    return motion_;
}

void Entity::setMotion(Vector2f motion) {
    motion_ = motion;
}

uint64_t Entity::getId() const {
    return id_;
}

const AABB &Entity::getBoundingBox() const {
    return boundingBox_;
}

AABB &Entity::getBoundingBox() {
    return boundingBox_;
}

bool Entity::canPassThrough() const {
    return true;
}

const EntityType *Entity::getType() const {
    return type_;
}

EntitySnapshot *Entity::snapshot() const {
    return new EntitySnapshot(
            this->type_,
            this->position_,
            this->boundingBox_,
            this->invulnerable_,
            this->health_ / static_cast<float>(this->getAttribute(EntityAttributes::MAX_HEALTH))
    );
}

void Entity::addBehavior(int32_t priority, EntityBehavior *behavior) {
    this->behaviorManager_.addBehavior(priority, std::unique_ptr<EntityBehavior>{behavior});
}

void Entity::init() {

}

void Entity::close() {
    if (closed_) {
        return;
    }

    closed_ = true;
}

void Entity::initEntity() {
    recalculateBoundingBox();

    for (auto &item: type_->getAttributes()) {
        this->attributes_.insert({item.first, unique_void(item.second)});
    }

    float health = getAttribute(EntityAttributes::MAX_HEALTH);
    this->setHealth(getAttribute(EntityAttributes::MAX_HEALTH));

    this->init();
}

void Entity::recalculateBoundingBox() {
    this->boundingBox_ = {
            0.0f,
            0.0f,
            this->type_->getWidth(),
            this->type_->getHeight()
    };

    this->boundingBox_.offset(this->getPosition());
}

bool Entity::isInvulnerable() const {
    return invulnerable_;
}

void Entity::setInvulnerable(bool invulnerable) {
    invulnerable_ = invulnerable;
}

float Entity::getHealth() const {
    return health_;
}

void Entity::setHealth(float health) {
    health_ = health;
}

uint64_t Entity::getTicksLived() const {
    return ticks_lived_;
}

void Entity::attack(float damage) {
    this->health_ = std::max(0.0f, this->health_ - damage);

    if (this->health_ <= 0) {
        close();
    }
}
