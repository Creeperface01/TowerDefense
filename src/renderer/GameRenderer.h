#pragma once

#include <centurion.hpp>

#include "../world/World.h"
#include "../world/WorldSnapshot.h"
#include "../entity/EntitySnapshot.h"
#include "../entity/TileEntitySnapshot.h"
#include "../tile/Tile.h"
#include "../tile/Tiles.h"
#include "RenderSettings.h"
#include "game_basic_renderer.h"

class GameRenderer {
private:
    const RenderSettings settings_;

    const World &world_;

    cen::renderer_handle renderer_;
    game_basic_renderer game_renderer_;

public:
    explicit GameRenderer(
            cen::renderer_handle &renderer,
            game_basic_renderer &game_renderer,
            World &world
    );

    void render();

private:
    void render(const EntitySnapshot *entity);

//    void render(const TileEntitySnapshot *entity);

    void render(const Tile *tile, const Vector2i &pos);

    void render(const WorldSnapshot &world);
};