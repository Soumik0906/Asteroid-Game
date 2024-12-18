#ifndef UTILITIES_H
#define UTILITIES_H

#include <random>

namespace Constants {
    inline constexpr float maxShipSpeed = 450.f;
    inline constexpr float frictionFactor = 0.7f;
    inline constexpr float rotationSpeed = 250.f;    // Degrees per second
    inline constexpr float acceleration = 800.f;    // Pixels per second^2
    inline constexpr float bulletSpeed = 550.f;
    inline constexpr float maxAsteroidSpeed = 100.f;
    inline constexpr float spaceShipScale = 2.f;
    // Window sizes
    inline constexpr float windowWidth = 1000.f;
    inline constexpr float windowHeight = 1000.f;
}

namespace Utils {
    // Generate random number in given range using Mersenne Twister
    inline std::mt19937 generator(std::random_device{}());
    inline float getRandomInRange(const float min, const float max) {
        std::uniform_real_distribution distribution(min, max);
        return distribution(generator);
    }
}

#endif // UTILITIES_H