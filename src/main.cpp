#include <iostream>
#include <numbers>

#include "TowerDefense.h"
#include "math/BoundingBox.h"
#include "math/Vector.h"
#include "tile/Tiles.h"

#define CENTURION_NO_VULKAN


int main() {
    std::unique_ptr<TowerDefense> main(new TowerDefense());

//    Vector2f source{0, 0}, p{0, 1};
//
//    Vector2f motion{1, -1};
//
//    Vector2f vec = source - p;
//
//    float angle = vec.angleBetween(motion);
//    float angle2 = p.angleBetween({1, 1});
//
//    std::cout << "pi: " << std::numbers::pi_v<float> << std::endl;
//    std::cout << "angle: " << angle << std::endl;
//    std::cout << "angle2: " << angle2 << std::endl;
//    std::cout << "angle < PI/2: " << (angle <= (std::numbers::pi_v<float> / 2.0f)) << std::endl;

    return 0;
}
