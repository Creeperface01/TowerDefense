#pragma once

#include "../TileEntity.h"

class TileEntityCanon : public TileEntity {

public:
    using TileEntity::TileEntity;

    void init() override;
};
