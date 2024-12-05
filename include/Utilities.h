#pragma once
#include <random>

namespace Constants {
    inline constexpr float maxShipSpeed = 450.f;
    inline constexpr float frictionFactor = 0.02f;
    inline constexpr float rotationSpeed = 5.f;    // Degrees per second
    inline constexpr float acceleration = 120.f;    // Pixels per second^2
    inline constexpr float bulletSpeed = 550.f;
    inline constexpr float maxAsteroidSpeed = 100.f;
    inline constexpr float spaceShipScale = 2.f;
    // Window sizes
    inline constexpr float SIZE_X = 1000.f;
    inline constexpr float SIZE_Y = 1000.f;
}

namespace Utils {
    // Generate random number in given range using Mersenne Twister
    inline std::mt19937 generator(std::random_device{}());
    inline float getRandomInRange(const float min, const float max) {
        std::uniform_real_distribution distribution(min, max);
        return distribution(generator);
    }
}
