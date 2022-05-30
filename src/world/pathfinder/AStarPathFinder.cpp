#include "AStarPathFinder.h"
#include <cmath>
#include <algorithm>
#include <array>
#include <numbers>

#include "../World.h"
#include "../../math/Direction.h"

AStarPathFinder::AStarPathFinder(const World &world) : world_(world) {}

float heuristic(uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1) {
    auto dx = (float) std::fabs(x0 - x1);
    auto dy = (float) std::fabs(y0 - y1);

//    return std::sqrt(dx * dx + dy * dy);
    return dx + dy;
}

float heuristic(const Vector2i &vec1, const Vector2i &vec2) {
    return heuristic(vec1.x(), vec1.y(), vec2.x(), vec2.y());
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "LocalValueEscapesScope"

std::optional<Path> AStarPathFinder::findPath(const Vector2i &start, const Vector2i &end) {
    nodes_.clear();

    std::vector<Node *> openList;

    std::make_heap(
            openList.begin(),
            openList.end()
    );

    auto *startNode = getNode(start);
    auto *endNode = getNode(end);

    startNode->opened_ = true;

    openList.push_back(startNode);
    std::push_heap(openList.begin(), openList.end());

    while (!openList.empty()) {
        std::pop_heap(openList.begin(), openList.end());

        auto node = openList.back();
        openList.pop_back();

        node->closed_ = true;

        if (node->vec_ == endNode->vec_) {
            std::vector<Vector2i> path{endNode->vec_};

            Node *n = endNode;
            while (n->parent_ != nullptr) {
                n = n->parent_;
                path.push_back(n->vec_);
            }

            std::reverse(path.begin(), path.end());

            return {{start, end, std::move(path)}};
        }

        auto neighbors = getNeighbors(node);

        for (auto neighbor: neighbors) {
            if (neighbor->closed_) {
                continue;
            }

            auto &v = neighbor->vec_;

            auto ng = node->g_ + (((v.x() - node->vec_.x()) == 0 || (v.y() - node->vec_.y()) == 0) ? 1
                                                                                                   : std::numbers::sqrt2_v<float>);

            if (!neighbor->opened_ || ng < neighbor->g_) {
                neighbor->g_ = ng;
                neighbor->h_ = neighbor->h_ != 0 ? neighbor->h_ : heuristic(v, endNode->vec_);
                neighbor->f_ = neighbor->g_ + neighbor->h_;
                neighbor->parent_ = node;

                if (!neighbor->opened_) {
                    openList.push_back(neighbor);
                    std::push_heap(openList.begin(), openList.end());

                    neighbor->opened_ = true;
                } else {
                    std::make_heap(
                            openList.begin(),
                            openList.end()
                    );
                }
            }
        }
    }

    return std::nullopt;
}

#pragma clang diagnostic pop

std::vector<AStarPathFinder::Node *> AStarPathFinder::getNeighbors(const AStarPathFinder::Node *node) {
    std::vector<Node *> neighbors;

//    std::array<bool, 4> s{};

    auto &vec = node->vec_;
    for (const auto &item: Direction::values()) {
        auto side = vec.offset(*item);
        if (isWalkableAt(side)) {
//            s[item->getIndex()] = true;
//            auto tile = world_.getTile(side);

            neighbors.push_back(getNode(side));
        }
    }

//    for (const auto &item: Direction::diagonal()) {
//        auto &d1 = item.first, &d2 = item.second;
//
//        if (s[d1->getIndex()] && s[d2->getIndex()]) {
//            auto side = vec.add(
//                    static_cast<VectorType>(d1->getXOffset() + d2->getXOffset()),
//                    static_cast<VectorType>(d1->getYOffset() + d2->getYOffset())
//            );
//
//            neighbors.push_back(&getNode(side));
//        }
//    }

    return neighbors;
}

bool AStarPathFinder::isWalkableAt(const Vector2i &vec) const {
    return world_.getTile(vec)->passable;
}

bool AStarPathFinder::isWalkableAt(VectorType x, VectorType y) const {
    return isWalkableAt({x, y});
}

AStarPathFinder::Node *AStarPathFinder::getNode(const Vector2i &vec) {
    if (!nodes_.contains(vec)) {
        nodes_.emplace(std::piecewise_construct, std::forward_as_tuple(vec), std::forward_as_tuple(vec));
    }

    return &nodes_.at(vec);
}

bool Path::hasNext() const {
    return current_ < (nodes_.size() - 1);
}

void Path::reset() {
    current_ = 0;
}

const Vector2i &Path::next() {
    if ((current_ + 1) >= nodes_.size()) {
        throw std::runtime_error("No next node in path");
    }

    return nodes_[++current_];
}

const Vector2i &Path::current() const {
    return nodes_[current_];
}

const Vector2i &Path::getStart() const {
    return start_;
}

const Vector2i &Path::getEnd() const {
    return end_;
}

const std::vector<Vector2i> &Path::getNodes() const {
    return nodes_;
}

Path::Path(const Vector2i &start, const Vector2i &anEnd, std::vector<Vector2i> nodes) : start_(start), end_(anEnd),
                                                                                        nodes_(std::move(nodes)) {}

std::partial_ordering AStarPathFinder::Node::operator<=>(const AStarPathFinder::Node &other) const {
    return this->f_ <=> other.f_;
}
