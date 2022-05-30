#pragma once

#include <utility>
#include <vector>
#include <exception>
#include <unordered_map>
#include <memory>
#include <optional>

#include "../../math/Vector.h"
#include "../../util/Types.h"

class World;

class Path {
private:
    uint32_t current_ = 0;

    Vector2i start_;
    Vector2i end_;

    std::vector<Vector2i> nodes_;

public:

    Path(const Vector2i &start, const Vector2i &anEnd, std::vector<Vector2i> nodes);

    void reset();

    [[nodiscard]] bool hasNext() const;

    const Vector2i &next();

    [[nodiscard]] const Vector2i &current() const;

    [[nodiscard]] const Vector2i &getStart() const;

    [[nodiscard]] const Vector2i &getEnd() const;

    [[nodiscard]] const std::vector<Vector2i> &getNodes() const;
};

class AStarPathFinder {
private:
    const World &world_;

    struct Node {
        Vector2i vec_;
        float f_ = 0, g_ = 0, h_ = 0;
        bool opened_ = false, closed_ = false;

        Node *parent_ = nullptr;

        std::partial_ordering operator<=>(const Node &other) const;

        explicit Node(const Vector2i &vec) : vec_(vec) {}

        Node(const Node &) = delete;

        Node &operator=(const Node &) = delete;
    };

    std::unordered_map<Vector2i, Node> nodes_;

    [[nodiscard]] std::vector<Node *> getNeighbors(const Node *node);

    Node *getNode(const Vector2i &vec);

    [[nodiscard]] bool isWalkableAt(const Vector2i &vec) const;

    [[nodiscard]] bool isWalkableAt(VectorType x, VectorType y) const;

public:
    explicit AStarPathFinder(const World &world);

    std::optional<Path> findPath(const Vector2i &start, const Vector2i &end);
};
