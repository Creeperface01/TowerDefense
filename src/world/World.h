#pragma once

#include <vector>
#include <unordered_map>
#include <mutex>
#include <ranges>
#include <queue>
#include <functional>

#include "../entity/Entity.h"
#include "../entity/TileEntity.h"
#include "../util/Types.h"
#include "../tile/Tile.h"
#include "../tile/Tiles.h"
#include "../math/BoundingBox.h"
#include "../map/MapConfiguration.h"
#include "WorldSnapshot.h"
#include "../registry/EntityRegistry.h"
#include "pathfinder/AStarPathFinder.h"
#include "../entity/EntityTypes.h"
#include "../entity/TileEntityTypes.h"

class World {
private:
    const MapConfiguration configuration_;

    const AABB boundingBox_;

    std::unordered_map<uint64_t, std::unique_ptr<Entity>> entities_;
    std::unordered_map<Vector2i, std::unique_ptr<TileEntity>> tileEntities_;

    std::unordered_map<Vector2i, const Tile *> tiles_;

    uint32_t tick_ = 0;

    mutable std::mutex state_mutex_;

    AStarPathFinder path_finder_;

    std::mutex action_mutex_;
    std::queue<std::function<void(World &)>> actions_;

    friend class GameRenderer;

    template<class T, typename D>
    std::optional<T *> findNearest(
            const D &data,
            const Vector2f &pos,
            const EntityType *targetType = nullptr,
            const T *source = nullptr,
            std::optional<float> limit = std::nullopt
    ) const {
        float distance = std::numeric_limits<float>::max();
        std::optional<T *> nearest;

        for (auto &entry: data) {
            auto item = entry.second.get();

            if (item == source) {
                continue;
            }

            if (targetType != nullptr && item->getType() != targetType) {
                continue;
            }

            auto ref = item->getPosition().distanceSquared(pos);
            if ((!limit.has_value() || ref <= limit.value()) && ref < distance) {
                distance = ref;
                nearest = item;
            }
        }

        return nearest;
    }

    void executeActions();

public:
    explicit World(MapConfiguration configuration);

    const MapConfiguration &getConfiguration() const;

    void tick();

    uint32_t getTick() const;

    [[nodiscard]] const Tile *getTile(const Vector2i &vec) const;

    [[nodiscard]] const std::unordered_map<uint64_t, std::unique_ptr<Entity>> &getEntities() const;

    [[nodiscard]] const std::unordered_map<Vector2i, std::unique_ptr<TileEntity>> &getTileEntities() const;

    std::optional<const TileEntity *> getTileEntity(const Vector2i &pos) const;

    std::optional<TileEntity *> getTileEntity(const Vector2i &pos);

    [[nodiscard]] const std::unordered_map<Vector2i, const Tile *> &getTiles() const;

    [[nodiscard]] const AABB &getBoundingBox() const;

    AStarPathFinder &getPathFinder();

    [[nodiscard]] WorldSnapshot snapshot() const;

    Entity *createEntity(const EntityType *type, const Vector2f &position);

    void removeEntity(const Entity *entity);

    std::optional<Entity *> findNearestEntity(
            const Vector2f &pos,
            const EntityType *targetType = nullptr,
            const Entity *source = nullptr,
            std::optional<float> limit = std::nullopt
    ) const;

    std::optional<TileEntity *> findNearestTileEntity(
            const Vector2f &pos,
            const EntityType *targetType = nullptr,
            const TileEntity *source = nullptr,
            std::optional<float> limit = std::nullopt
    ) const;

    std::optional<Vector2i> findClosestWalkableTile(const Vector2i &pos, VectorType radius = 5) const;

    void addAction(const std::function<void(World &)> &action);

    std::vector<Entity *> findCollidingEntities(const Vector2f &pos, Entity *source) const;
};