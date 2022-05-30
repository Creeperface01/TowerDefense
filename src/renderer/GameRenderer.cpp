#include "GameRenderer.h"

#include "../entity/EntityTypes.h"
#include "../entity/TileEntityTypes.h"
#include "../tile/Tiles.h"

#include <unordered_map>
#include <cmath>

GameRenderer::GameRenderer(
        cen::renderer_handle &renderer,
        game_basic_renderer &game_renderer,
        World &world
) :
        world_(world),
        renderer_(renderer),
        game_renderer_(game_renderer) {
//    renderer_.set_translation_viewport(cen::frect({settings.offsetX, settings.offsetY}));
}

void GameRenderer::render(const EntitySnapshot *entity) {
    static const std::unordered_map<const EntityType *, cen::color> colors(
            {
                    {EntityTypes::BOMB,          cen::colors::red},
                    {EntityTypes::LASER_BEAM,    cen::colors::light_green},
                    {TileEntityTypes::OBJECTIVE, cen::colors::white},
                    {TileEntityTypes::SPAWNER,   cen::colors::red},
                    {TileEntityTypes::CANON,     cen::colors::blue},
            }
    );

    auto &bb = entity->boundingBox_;
    auto &pos = entity->position_;

    auto center = bb.getCenter();

    renderer_.set_color(colors.find(entity->type_)->second);

    if (entity->type_->getType() == EntityType::Type::ENTITY) {
        game_renderer_.fill_circle_m<float>({center.x(), center.y()}, bb.getWidth() / 2);
    } else {
        game_renderer_.fill_rect_m<float>(
                {
                        std::floor(pos.x()),
                        std::floor(pos.y()),
                        bb.getWidth(),
                        bb.getHeight()
                }
        );
    }

    if (!entity->invulnerable_) {
        renderer_.set_color(cen::colors::white);

        cen::frect health_bar = {
                bb.getMinX(),
                static_cast<float>(bb.getMinY() + (bb.getHeight() * 0.75)),
                bb.getWidth(),
                0.3f
        };

        game_renderer_.fill_rect_m<float>(health_bar);

        renderer_.set_color(cen::colors::light_green);

        health_bar.set_width(health_bar.width() * entity->health_);
        game_renderer_.fill_rect_m<float>(health_bar);
    }
}

//void GameRenderer::render(const TileEntitySnapshot *entity) {
//    static const std::unordered_map<const EntityType *, cen::color> colors(
//            {
//                    {TileEntityTypes::OBJECTIVE, cen::colors::white},
//                    {TileEntityTypes::SPAWNER,   cen::colors::red},
//                    {TileEntityTypes::CANON,   cen::colors::blue},
//            }
//    );
//
//    auto &bb = entity->boundingBox_;
//    auto &pos = entity->position_;
//
//    renderer_.set_color(colors.find(entity->type_)->second);
//    game_renderer_.fill_rect_m<float>(
//            {
//                    std::floor(pos.x()),
//                    std::floor(pos.y()),
//                    1,
//                    1
//            });
//}

void GameRenderer::render(const Tile *tile, const Vector2i &pos) {
    static const std::unordered_map<const Tile *, cen::color> colors(
            {
                    {Tiles::GROUND,    cen::colors::dark_olive_green},
                    {Tiles::PATH,      cen::colors::sandy_brown},
                    {Tiles::PATH_TEST, cen::colors::pink}
            }
    );

    renderer_.set_color(colors.find(tile)->second);

    game_renderer_.fill_rect_m<float>(
            {
                    static_cast<float>(pos.x()),
                    static_cast<float>(pos.y()),
                    1,
                    1
            }
    );
}

void GameRenderer::render(const WorldSnapshot &world) {
    auto bb = world.obj_->getBoundingBox();

    renderer_.set_color(cen::colors::black);
    renderer_.fill();

    renderer_.set_color(cen::colors::white);
    game_renderer_.fill_rect_m<float>(
            {
                    bb.getMinX(),
                    bb.getMinY(),
                    bb.getWidth(),
                    bb.getHeight()
            }
    );

    for (const auto &pair: world.obj_->tiles_) {
        render(pair.second, pair.first);
    }

    for (const auto &item: world.tileEntities_) {
        render(item.get());
    }

    for (const auto &item: world.entities_) {
        render(item.get());
    }
}

void GameRenderer::render() {
    this->render(this->world_.snapshot());
}
