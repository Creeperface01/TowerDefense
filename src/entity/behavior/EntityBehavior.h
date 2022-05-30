#pragma once

#include <cstdint>

class Entity;

class EntityBehavior {
private:
    uint64_t compatibility_ = 0;

protected:
    Entity *entity_;

    bool justStarted_ = false;

public:
    explicit EntityBehavior(Entity *e);

    virtual ~EntityBehavior() = default;

    virtual void tick(uint32_t tick);

    virtual bool shouldExecute() = 0;

    virtual bool canContinue();

    virtual bool startExecuting();

    virtual void reset();

    virtual bool isInterruptible();

    [[nodiscard]] uint64_t getCompatibility() const;

    void setCompatibility(uint64_t compatibility);
};


