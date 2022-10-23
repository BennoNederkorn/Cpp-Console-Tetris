#ifndef MODEL_PART_H
#define MODEL_PART_H

#include <array>   // std::array
#include <mutex>   // std::mutex
#include <utility> // std::pair, std::make_pair
#include <random>  // std::random_device
#include "modelPlayground.h"

class Part
{
private:
    /**
     * @brief stores the number of characters that make up each part
     */
    static const std::size_t NUMBER_OF_COMPONENTS{4};

    /**
     * @brief stores the position of the part. The first pair is the spawn and turning position
     */
    std::array<std::pair<size_t, size_t>, NUMBER_OF_COMPONENTS> partPosition;

    /**
     * @brief symbol of the part
     */
    char symbol = ' ';

    /**
     * @brief protects the position of the part
     */
    std::mutex partMutex;

    /**
     * @brief evaluates the new position of one point after a rotation to the left
     *
     * @param[in] centre is the point around which to rotate
     * @param[in] oldPoint is the point which is turned around the centre
     *
     * @return the new position of the point
     */
    std::pair<size_t, size_t> turnOnePointLeft(std::pair<size_t, size_t> centre, std::pair<size_t, size_t> oldPoint);

    /**
     * @brief evaluates the new position of one point after a rotation to the right
     *
     * @param[in] centre is the point around which to rotate
     * @param[in] oldPoint is the point which is turned around the centre
     *
     * @return the new position of the point
     */
    std::pair<size_t, size_t> turnOnePointRight(std::pair<size_t, size_t> centre, std::pair<size_t, size_t> oldPoint);

public:
    Part() = delete;

    /**
     * @brief creates a random part in the play area
     *
     * @param[in] x is the position of the part spawn on the x-axis
     * @param[in] y is the position of the part spawn on the y-axis
     */
    Part(size_t x, size_t y);

    /**
     * @brief move the part down
     *
     * @param[in] playground is needed to check if the position free
     * @return false if the part cannot move down, true if the part can move down
     */
    bool moveDown(Playground &playground);

    /**
     * @brief[in] turns the part left
     *
     * @param playground is needed to check if the position free
     */
    void turnLeft(Playground &playground);

    /**
     * @brief[in] turns the part right
     *
     * @param playground is needed to check if the position free
     */
    void turnRight(Playground &playground);

    /**
     * @brief[in] move the part left
     *
     * @param playground is needed to check if the position free
     */
    void moveLeft(Playground &playground);

    /**
     * @brief[in] move the part right
     *
     * @param playground is needed to check if the position free
     */
    void moveRight(Playground &playground);

    static constexpr std::size_t getNumberOfComponents() { return NUMBER_OF_COMPONENTS; }
    std::array<std::pair<size_t, size_t>, NUMBER_OF_COMPONENTS> getPartPosition() { return partPosition; }
    char getSymbol() { return symbol; }
};

#endif