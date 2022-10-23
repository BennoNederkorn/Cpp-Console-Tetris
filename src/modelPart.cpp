#include "../include/modelPart.h"

Part::Part(size_t x, size_t y)
{
    std::random_device rd;                          // obtain a random number from hardware
    std::mt19937 gen{rd()};                         // seed the generator
    std::uniform_int_distribution<int> distr(0, 6); // define the range
    switch (distr(gen))
    {
    case 0: // Part I
        symbol = '@';
        partPosition[0] = std::make_pair(x - 1, y);
        partPosition[1] = std::make_pair(x, y);
        partPosition[2] = std::make_pair(x + 1, y);
        partPosition[3] = std::make_pair(x + 2, y);
        break;
    case 1: // Part T
        symbol = '%';
        partPosition[0] = std::make_pair(x, y);
        partPosition[1] = std::make_pair(x + 1, y);
        partPosition[2] = std::make_pair(x - 1, y);
        partPosition[3] = std::make_pair(x, y - 1);
        break;
    case 2: // Part O
        symbol = 'W';
        partPosition[0] = std::make_pair(x, y);
        partPosition[1] = std::make_pair(x + 1, y);
        partPosition[2] = std::make_pair(x, y - 1);
        partPosition[3] = std::make_pair(x + 1, y - 1);
        break;
    case 3: // Part L
        symbol = '&';
        partPosition[0] = std::make_pair(x, y);
        partPosition[1] = std::make_pair(x + 1, y);
        partPosition[2] = std::make_pair(x - 1, y);
        partPosition[3] = std::make_pair(x - 1, y - 1);
        break;
    case 4: // Part J
        symbol = '&';
        partPosition[0] = std::make_pair(x, y);
        partPosition[1] = std::make_pair(x + 1, y);
        partPosition[2] = std::make_pair(x - 1, y);
        partPosition[3] = std::make_pair(x + 1, y - 1);
        break;
    case 5: // Part S
        symbol = 'Q';
        partPosition[0] = std::make_pair(x, y);
        partPosition[1] = std::make_pair(x + 1, y);
        partPosition[2] = std::make_pair(x, y - 1);
        partPosition[3] = std::make_pair(x - 1, y - 1);
        break;
    case 6: // Part Z
        symbol = 'Q';
        partPosition[0] = std::make_pair(x, y);
        partPosition[1] = std::make_pair(x - 1, y);
        partPosition[2] = std::make_pair(x, y - 1);
        partPosition[3] = std::make_pair(x + 1, y - 1);
    default:
        break;
    }
}

std::pair<size_t, size_t> Part::turnOnePointLeft(std::pair<size_t, size_t> centre, std::pair<size_t, size_t> oldPoint)
{
    return std::make_pair(centre.first - (oldPoint.second - centre.second), centre.second + (oldPoint.first - centre.first));
}

std::pair<size_t, size_t> Part::turnOnePointRight(std::pair<size_t, size_t> centre, std::pair<size_t, size_t> oldPoint)
{
    return std::make_pair(centre.first + (oldPoint.second - centre.second), centre.second - (oldPoint.first - centre.first));
}

bool Part::moveDown(Playground &playground)
{
    const std::lock_guard<std::mutex> lock(partMutex);
    std::array<std::pair<size_t, size_t>, NUMBER_OF_COMPONENTS> newPartPosition;
    newPartPosition[0] = std::make_pair(partPosition[0].first, partPosition[0].second - 1);
    newPartPosition[1] = std::make_pair(partPosition[1].first, partPosition[1].second - 1);
    newPartPosition[2] = std::make_pair(partPosition[2].first, partPosition[2].second - 1);
    newPartPosition[3] = std::make_pair(partPosition[3].first, partPosition[3].second - 1);
    if (playground.isFree(newPartPosition))
    {
        partPosition = std::move(newPartPosition);
        return true;
    }
    return false;
}

void Part::turnLeft(Playground &playground)
{
    const std::lock_guard<std::mutex> lock(partMutex);
    std::array<std::pair<size_t, size_t>, NUMBER_OF_COMPONENTS> newPartPosition;
    newPartPosition[0] = partPosition[0];
    newPartPosition[1] = turnOnePointLeft(partPosition[0], partPosition[1]);
    newPartPosition[2] = turnOnePointLeft(partPosition[0], partPosition[2]);
    newPartPosition[3] = turnOnePointLeft(partPosition[0], partPosition[3]);
    if (playground.isFree(newPartPosition))
    {
        partPosition = std::move(newPartPosition);
    }
}

void Part::turnRight(Playground &playground)
{
    const std::lock_guard<std::mutex> lock(partMutex);
    std::array<std::pair<size_t, size_t>, NUMBER_OF_COMPONENTS> newPartPosition;
    newPartPosition[0] = partPosition[0];
    newPartPosition[1] = turnOnePointRight(partPosition[0], partPosition[1]);
    newPartPosition[2] = turnOnePointRight(partPosition[0], partPosition[2]);
    newPartPosition[3] = turnOnePointRight(partPosition[0], partPosition[3]);
    if (playground.isFree(newPartPosition))
    {
        partPosition = std::move(newPartPosition);
    }
}

void Part::moveLeft(Playground &playground)
{
    const std::lock_guard<std::mutex> lock(partMutex);
    std::array<std::pair<size_t, size_t>, NUMBER_OF_COMPONENTS> newPartPosition;
    newPartPosition[0] = std::make_pair(partPosition[0].first - 1, partPosition[0].second);
    newPartPosition[1] = std::make_pair(partPosition[1].first - 1, partPosition[1].second);
    newPartPosition[2] = std::make_pair(partPosition[2].first - 1, partPosition[2].second);
    newPartPosition[3] = std::make_pair(partPosition[3].first - 1, partPosition[3].second);
    if (playground.isFree(newPartPosition))
    {
        partPosition = std::move(newPartPosition);
    }
}

void Part::moveRight(Playground &playground)
{
    const std::lock_guard<std::mutex> lock(partMutex);
    std::array<std::pair<size_t, size_t>, NUMBER_OF_COMPONENTS> newPartPosition;
    newPartPosition[0] = std::make_pair(partPosition[0].first + 1, partPosition[0].second);
    newPartPosition[1] = std::make_pair(partPosition[1].first + 1, partPosition[1].second);
    newPartPosition[2] = std::make_pair(partPosition[2].first + 1, partPosition[2].second);
    newPartPosition[3] = std::make_pair(partPosition[3].first + 1, partPosition[3].second);
    if (playground.isFree(newPartPosition))
    {
        partPosition = std::move(newPartPosition);
    }
}