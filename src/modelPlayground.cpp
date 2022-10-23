#include "../include/modelPlayground.h"

Playground::Playground()
{
    setUpField();
}

void Playground::setUpField()
{
    for (std::size_t x{0}; x < FIELD_WIDTH; ++x)
    {
        for (std::size_t y{0}; y < FIELD_HEIGHT; ++y)
        {
            field[x][y] = ' ';
        }
    }
    for (std::size_t x{0}; x < FIELD_WIDTH; ++x)
    {
        field[x][0] = '#';
        field[x][FIELD_HEIGHT - 1] = '#';
    }
    for (std::size_t y{0}; y < FIELD_HEIGHT; ++y)
    {
        field[0][y] = '#';
        field[FIELD_WIDTH - 1][y] = '#';
        field[MAX_PLAYGROUND_WIDTH + 1][y] = '#';
    }
    for (std::size_t x{MAX_PLAYGROUND_WIDTH + 2}; x < FIELD_WIDTH - 1; ++x)
    {
        field[x][8] = '#';
        field[x][13] = '#';
    }
    field[13][19] = 'n';
    field[14][19] = 'e';
    field[15][19] = 'x';
    field[16][19] = 't';
    field[13][18] = 'p';
    field[14][18] = 'a';
    field[15][18] = 'r';
    field[16][18] = 't';
    field[13][11] = 's';
    field[14][11] = 'c';
    field[15][11] = 'o';
    field[16][11] = 'r';
    field[17][11] = 'e';
    field[13][6] = 'l';
    field[14][6] = 'e';
    field[15][6] = 'v';
    field[16][6] = 'e';
    field[17][6] = 'l';
    setLevel();
    setScore();
}

bool Playground::checkRow(int y)
{
    for (std::size_t x{MIN_PLAYGROUND_WIDTH}; x <= MAX_PLAYGROUND_WIDTH; x++)
    {
        if (field[x][y] == ' ')
        {
            return false;
        }
    }
    return true;
}

bool Playground::contains(std::array<int, 4> arr, int element)
{
    for (int i : arr)
    {
        if (i == element)
            return true;
    }
    return false;
}

void Playground::deleteRow(int y)
{
    for (std::size_t x{MIN_PLAYGROUND_WIDTH}; x <= MAX_PLAYGROUND_WIDTH; x++)
    {
        field[x][y] = ' ';
    }
}

void Playground::gravity(size_t row)
{
    for (std::size_t y{row}; y <= MAX_PLAYGROUND_HEIGHT - 1; y++)
    {
        for (std::size_t x{MIN_PLAYGROUND_WIDTH}; x <= MAX_PLAYGROUND_WIDTH; x++)
        {
            field[x][y] = field[x][y + 1];
        }
    }
    for (std::size_t x{MIN_PLAYGROUND_WIDTH}; x <= MAX_PLAYGROUND_WIDTH; x++)
    {
        field[x][MAX_PLAYGROUND_HEIGHT] = ' ';
    }
}

void Playground::setLevel()
{
    level = lines / 2;
    std::string levelStr = std::to_string(level);
    std::string baseStr = "0";
    baseStr.append(levelStr);
    field[14][5] = baseStr[baseStr.size() - 2];
    field[15][5] = baseStr[baseStr.size() - 1];
}

void Playground::setScore()
{
    std::string scoreStr = std::to_string(score);
    std::string baseStr = "0000";
    baseStr.append(scoreStr);
    for (int i{1}; i <= 5; i++)
        field[18 - i][10] = baseStr[baseStr.size() - i];
}

void Playground::increaseScore(int rows)
{
    switch (rows)
    {
    case 1:
        score += 40 * (level + 1);
        break;
    case 2:
        score += 100 * (level + 1);
        break;
    case 3:
        score += 300 * (level + 1);
        break;
    case 4:
        score += 1200 * (level + 1);
        break;
    default:
        break;
    }
}

bool Playground::isFree(std::array<std::pair<size_t, size_t>, 4> partPosition)
{
    for (auto [x, y] : partPosition)
    {
        if ((x >= FIELD_WIDTH && y >= FIELD_HEIGHT) || ' ' != field[x][y])
            return false;
    }
    return true;
}

void Playground::setDownPart(std::array<std::pair<size_t, size_t>, 4> partPosition, char symbol)
{
    for (auto [x, y] : partPosition)
    {
        field[x][y] = symbol;
    }

    std::array<int, 4> rows = {-1, -1, -1, -1};
    int i{0};
    for (auto [x, y] : partPosition)
    {
        if (!contains(rows, y))
        {
            rows[i] = y;
            ++i;
        }
    }

    std::sort(rows.begin(), rows.end());
    int numberOfRows{0};
    for (int i{3}; i >= 0; i--)
    {
        if (rows[i] == -1)
        {
            break;
        }
        if (checkRow(rows[i]))
        {
            ++numberOfRows;
            deleteRow(rows[i]);
            gravity(rows[i]);
        }
    }

    lines += numberOfRows;
    setLevel();

    increaseScore(numberOfRows);
    setScore();
}

void Playground::setNextPart(std::array<std::pair<size_t, size_t>, 4> partPosition, char symbol)
{
    for (int x{13}; x <= 16; ++x)
    {
        field[x][15] = ' ';
        field[x][16] = ' ';
    }
    for (auto [x, y] : partPosition)
    {
        field[x + 10][y - 4] = symbol;
    }
}