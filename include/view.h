#ifndef VIEW_H
#define VIEW_H

#include <utility> // std::pair, std::make_pair
#include <string>  // std::string, printf
#include <array>   // std::array
#include "modelPlayground.h"
#include "modelPart.h"

class View
{
private:
    /**
     * @brief ensures that several playgrounds are not printed at the same time
     */
    std::mutex displayMutex;

    /**
     * @brief creates a string about the current game situation.
     *
     * @param[in] playground stores all the information about the game field
     * @param[in] part is the active part that the user controls.
     */
    std::string toString(Playground &playground, Part &part);

public:
    /**
     * @brief prints the playground and the active part into the terminal.
     *
     * @param[in] playground stores all the information about the game field
     * @param[in] part is the active part that the user controls.
     */
    void display(Playground &playground, Part &part);
};

#endif