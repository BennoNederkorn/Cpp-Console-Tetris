#ifndef MODEL_PLAYGROUND_H
#define MODEL_PLAYGROUND_H

#include <array>  // std::array
#include <vector> // std::vector
#include <string> // std::string, std::to_string()

class Playground
{
private:
    /**
     * @brief height of the whole playground
     */
    const static std::size_t FIELD_HEIGHT{22};

    /**
     * @brief width of the whole playground
     */
    const static std::size_t FIELD_WIDTH{20};

    /**
     * @brief maximal height of the playarea, inclusive
     */
    const static std::size_t MAX_PLAYGROUND_HEIGHT{20};

    /**
     * @brief maximal width of the playarea, inclusive
     */
    const static std::size_t MAX_PLAYGROUND_WIDTH{10};

    /**
     * @brief minimal hight of the playarea, inclusive
     */
    const static std::size_t MIN_PLAYGROUND_HEIGHT{1};

    /**
     * @brief minimal width of the playarea, inclusive
     */
    const static std::size_t MIN_PLAYGROUND_WIDTH{1};

    /**
     * @brief stores all the chars of the playground in a two-dimensional array.
     * the coordinate origin (0,0) is in the bottom left.
     */
    std::array<std::array<char, FIELD_HEIGHT>, FIELD_WIDTH> field;

    /**
     * @brief the level is an abstraction of the game loop speed.
     * It is depended on the lines that are cleared
     */
    int level{0};

    /**
     * @brief stores the lines that are cleared
     */
    int lines{0};

    /**
     * @brief stores the score of the player
     */
    int score{0};

    /**
     * @brief set the whole playground up by filling the field with chars
     */
    void setUpField();

    /**
     * @brief checks if a row of the playfield is full
     *
     * @param[in] y is the row that is evaluated
     * @return true if the row is full, false if the row is not full
     */
    bool checkRow(int y);

    /**
     * @brief checks if an int array contains a given number
     *
     * @param[in] arr is the array of length 4 which is evaluated
     * @param[in] element is the number that is checked
     * @return true if the array contains the element, false if not
     */
    bool contains(std::array<int, 4> arr, int element);

    /**
     * @brief[in] clears a row of the play area
     *
     * @param y is the row that is cleared
     */
    void deleteRow(int y);

    /**
     * @brief moves all parts over a given row one step down
     *
     * @param[in] row is the row that is overwritten, this row should be empty
     */
    void gravity(size_t row);

    /**
     * @brief set the level as chars in the field
     */
    void setLevel();

    /**
     * @brief set the score as chars in the field
     */
    void setScore();

    /**
     * @brief increases the score
     *
     * @param[in] rows is the number of rows that are cleared.
     * The more rows are cleared the higher the new score
     */
    void increaseScore(int rows);

public:
    Playground();

    /**
     * @brief checks if the new position of a part is free
     *
     * @param[in] partPosition is the position that is evaluated
     * @return true if the given position is free, false if not
     */
    bool isFree(std::array<std::pair<size_t, size_t>, 4> partPosition);

    /**
     * @brief takes the position of an active part and transfers its symbol to the field
     *
     * @param[in] partPosition is the position of the active part
     * @param[in] symbol is the char that is written to the field
     */
    void setDownPart(std::array<std::pair<size_t, size_t>, 4> partPosition, char symbol);

    /**
     * @brief takes the position of a part and displays its symbol as the next part
     *
     * @param[in] partPosition is the position of the part
     * @param[in] symbol is the char that is written to the field
     */
    void setNextPart(std::array<std::pair<size_t, size_t>, 4> partPosition, char symbol);

    static constexpr std::size_t getHeight() { return FIELD_HEIGHT; }
    static constexpr std::size_t getWidth() { return FIELD_WIDTH; }
    static constexpr std::size_t getMaxPlaygroundHeight() { return MAX_PLAYGROUND_HEIGHT; }
    static constexpr std::size_t getMaxPlaygroundWidth() { return MAX_PLAYGROUND_WIDTH; }
    static constexpr std::size_t getMinPlaygroundHeight() { return MIN_PLAYGROUND_HEIGHT; }
    static constexpr std::size_t getMinPlaygroundWidth() { return MIN_PLAYGROUND_WIDTH; }
    std::array<std::array<char, FIELD_HEIGHT>, FIELD_WIDTH> getField() { return field; };
    int getLevel() { return level; }
    int getScore() { return score; }
};

#endif