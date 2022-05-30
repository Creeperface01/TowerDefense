#pragma once

#include "../math/Vector.h"
#include "../math/BoundingBox.h"
#include "../world/Collidable.h"
#include "EntityType.h"
#include "EntitySnapshot.h"
#include "behavior/EntityBehaviorManager.h"
#include "behavior/EntityBehavior.h"
#include "attribute/EntityAttribute.h"
#include "../util/Util.h"

#include <memory>
#include <unordered_map>

class World;

class Entity : public Collidable {
protected:
    static uint64_t idCounter_;

    const uint64_t id_;

    const EntityType *type_;

    uint64_t ticks_lived_ = 0;

    bool invulnerable_ = false;

    float health_ = 0;

    bool closed_;

    Vector2f position_;

    Vector2f motion_;

    AABB boundingBox_;

    EntityBehaviorManager behaviorManager_;

    std::unordered_map<const attribute_base *, unique_void_ptr> attributes_;

public:
    World &world_;

public:
    explicit Entity(const EntityType *type, World &world);

    void initEntity();

    virtual void init();

    void close();

    [[nodiscard]] uint64_t getId() const;

    [[nodiscard]] bool isClosed() const;

    [[nodiscard]] World &getWorld() const;

    [[nodiscard]] const EntityType *getType() const;

    virtual void tick(uint32_t tick);

    [[nodiscard]] virtual const Vector2f &getPosition() const;

    virtual void setPosition(Vector2f position);

    [[nodiscard]] virtual const Vector2f &getMotion() const;

    virtual void setMotion(Vector2f motion);

    [[nodiscard]] const AABB &getBoundingBox() const override;

    [[nodiscard]] virtual AABB &getBoundingBox();

    [[nodiscard]] bool canPassThrough() const override;

    [[nodiscard]] virtual EntitySnapshot *snapshot() const;

    [[nodiscard]] bool isInvulnerable() const;

    void setInvulnerable(bool invulnerable);

    [[nodiscard]] float getHealth() const;

    void setHealth(float health);

    [[nodiscard]] uint64_t getTicksLived() const;

    void attack(float damage);

    void recalculateBoundingBox();

    void addBehavior(int32_t priority, EntityBehavior *behavior);

    template<typename T>
    T getAttribute(const EntityAttribute<T> *attribute) const {
        auto it = attributes_.find(attribute);

        if (it == attributes_.end()) {
            return attribute->getDefaultValue();
        }

        return *static_cast<const T *>((*it).second.get());
    }

    template<typename T>
    void setAttribute(const EntityAttribute<T> *attribute, T value) {
        attributes_.insert(
                {
                        attribute,
                        unique_void(
                                static_cast<void *>(new T(value))
                        )
                }
        );
//        attributes_.at(attribute) = unique_void(
//                static_cast<void *>(new T(value))
//        );
    }
};


