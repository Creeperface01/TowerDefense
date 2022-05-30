#include "World.h"

#include "../entity/TileEntityTypes.h"
#include "../entity/EntityTypes.h"

#include <mutex>

void World::tick() {
    executeActions();

    {
        std::lock_guard entity_m(this->state_mutex_);

        erase_if(entities_, [](const auto &pair) {
            return pair.second->isClosed();
        });

        for (auto &item: entities_) {
            item.second->tick(tick_);
        }
    }

    {
        std::lock_guard entity_m(this->state_mutex_);

        erase_if(tileEntities_, [](const auto &pair) {
            return pair.second->isClosed();
        });

        for (auto &item: tileEntities_) {
            item.second->tick(tick_);
        }
    }

    tick_++;
}

const Tile *World::getTile(const Vector2i &vec) const {
    if (!this->tiles_.contains(vec)) {
        return Tiles::BARRIER;
    }

    return this->tiles_.at(vec);
}

const AABB &World::getBoundingBox() const {
    return boundingBox_;
}

World::World(MapConfiguration configuration) :
        boundingBox_(
                0.0f, 0.0f,
                (float) configuration.width_, (float) configuration.height_
        ),
        configuration_(std::move(configuration)),
        path_finder_(*this) {

    auto terrain = configuration_.terrain_.get();

    for (VectorType x = 0; x < configuration_.width_; ++x) {
        for (VectorType y = 0; y < configuration_.height_; ++y) {
            this->tiles_[{x, y}] = terrain->tiles_[y * configuration_.width_ + x];
        }
    }

    for (const auto &item: this->configuration_.terrain_->spawn_positions_) {
        createEntity(TileEntityTypes::SPAWNER, item);
    }

    for (const auto &item: this->configuration_.terrain_->objective_positions_) {
        createEntity(TileEntityTypes::OBJECTIVE, item);
    }

//    createEntity(EntityTypes::BOMB, {2, 1});

//    auto path = path_finder_.findPath({2, 1}, {15, 18});
//
//    for (const auto &item: path.value().getNodes()) {
//        tiles_[item] = Tiles::PATH_TEST;
//    }
//
//    int a = 1;
}

const std::unordered_map<uint64_t, std::unique_ptr<Entity>> &World::getEntities() const {
    return entities_;
}

const std::unordered_map<Vector2i, std::unique_ptr<TileEntity>> &World::getTileEntities() const {
    return tileEntities_;
}

const std::unordered_map<Vector2i, const Tile *> &World::getTiles() const {
    return tiles_;
}

WorldSnapshot World::snapshot() const {
    std::lock_guard lck(this->state_mutex_);

    std::vector<std::unique_ptr<EntitySnapshot>> entities;
    entities.reserve(this->entities_.size());

    std::transform(
            this->entities_.begin(),
            this->entities_.end(),
            std::back_inserter(entities),
            [](const std::pair<const uint64_t, std::unique_ptr<Entity>> &entry) {
                return std::unique_ptr<EntitySnapshot>(entry.second->snapshot());
            }
    );

    std::vector<std::unique_ptr<TileEntitySnapshot>> tile_entities;
    tile_entities.reserve(this->tileEntities_.size());

    std::transform(
            this->tileEntities_.begin(),
            this->tileEntities_.end(),
            std::back_inserter(tile_entities),
            [](const std::pair<const Vector2i, std::unique_ptr<TileEntity>> &entry) {
                return std::unique_ptr<TileEntitySnapshot>(entry.second->snapshot());
            }
    );

    return {this, std::move(entities), std::move(tile_entities)};
}

uint32_t World::getTick() const {
    return tick_;
}

Entity *World::createEntity(const EntityType *type, const Vector2f &position) {
    auto entity = type->create(*this);
    entity->setPosition(position);

    entity->initEntity();

    if (auto tileEntity = dynamic_cast<TileEntity *>(entity)) {
        this->tileEntities_.insert(
                {
                        tileEntity->getTilePosition(),
                        std::unique_ptr<TileEntity>(tileEntity)
                }
        );
    } else {
        this->entities_.insert({entity->getId(), std::unique_ptr<Entity>(entity)});
    }

    return entity;
}


#include <map>

AStarPathFinder &World::getPathFinder() {
    return path_finder_;
}

const MapConfiguration &World::getConfiguration() const {
    return configuration_;
}

std::optional<Entity *>
World::findNearestEntity(
        const Vector2f &pos,
        const EntityType *targetType,
        const Entity *source,
        std::optional<float> limit
) const {
    return findNearest<Entity>(
            this->entities_,
            pos,
            targetType,
            source,
            limit
    );
}

std::optional<TileEntity *>
World::findNearestTileEntity(
        const Vector2f &pos,
        const EntityType *targetType,
        const TileEntity *source,
        std::optional<float> limit
) const {
    return findNearest<TileEntity>(
            this->tileEntities_,
            pos,
            targetType,
            source,
            limit
    );
}

std::optional<Vector2i> World::findClosestWalkableTile(const Vector2i &pos, VectorType radius) const {
    Vector2i p;
    for (VectorType i = 0; i < radius; ++i) {

        for (auto x = static_cast<VectorType>(-i); x <= i; ++x) {
            p = pos.add(x, static_cast<VectorType >(-i));

            if (getTile(p)->passable) {
                return {p};
            }

            p = pos.add(x, static_cast<VectorType >(i));

            if (getTile(p)->passable) {
                return {p};
            }
        }

        for (auto y = static_cast<VectorType>(-i); y <= i; ++y) {
            p = pos.add(static_cast<VectorType >(-i), y);

            if (getTile(p)->passable) {
                return {p};
            }

            p = pos.add(static_cast<VectorType >(i), y);

            if (getTile(p)->passable) {
                return {p};
            }
        }
    }

    return std::nullopt;
}

void World::removeEntity(const Entity *entity) {
    this->entities_.erase(entity->getId());
}

void World::addAction(const std::function<void(World &)> &action) {
    std::lock_guard lck(action_mutex_);
    actions_.push(action);
}

void World::executeActions() {
    std::lock_guard lck(action_mutex_);

    while (!actions_.empty()) {
        auto action = actions_.front();

        action(*this);

        actions_.pop();
    }
}

std::optional<const TileEntity *> World::getTileEntity(const Vector2i &pos) const {
    auto entry = tileEntities_.find(pos);

    if (entry == tileEntities_.end()) {
        return std::nullopt;
    }

    return {entry->second.get()};
}

std::optional<TileEntity *> World::getTileEntity(const Vector2i &pos) {
    auto entry = tileEntities_.find(pos);

    if (entry == tileEntities_.end()) {
        return std::nullopt;
    }

    return {entry->second.get()};
}

std::vector<Entity *> World::findCollidingEntities(const Vector2f &pos, Entity *source) const {
    std::vector<Entity *> entities;

    for (const auto &item: entities_) {
        auto entity = item.second.get();

        if (entity == source) {
            continue;
        }

        if (entity->collidesWith(*source)) {
            entities.push_back(entity);
        }
    }

    return entities;
}
