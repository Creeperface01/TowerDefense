#pragma once

#include "../TileEntity.h"

class TileEntitySpawner : public TileEntity {

public:
    using TileEntity::TileEntity;

    void init() override;

    void tick(uint32_t tick) override;
};
