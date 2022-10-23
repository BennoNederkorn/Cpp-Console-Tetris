#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <chrono>             // chrono::milliseconds()
#include <condition_variable> // std::condition_variable
#include <thread>             // std::jthread
#include <termios.h>          // termios, TCSANOW, ECHO, ICANON
#include <unistd.h>           // sleep(), STDIN_FILENO
#include <queue>              // std::queue
#include <memory>             // std::unique_ptr, std::make_unique

#include "modelPlayground.h"
#include "modelPart.h"
#include "view.h"

/**
 * @brief class that manages the terminal settings
 */
class TerminalManagement
{
private:
    /**
     * @brief oldT stores old terminal settings
     */
    struct termios oldT;

    /**
     * @brief newT stores new terminal settings
     */
    struct termios newT;

public:
    /**
     * @brief This changes the Terminal settings so that the terminal processes the input immediately
     * without waiting for an end-of-line symbol. It also disassociates the input from the output.
     * @link https://stackoverflow.com/questions/1798511/how-to-avoid-pressing-enter-with-getchar-for-reading-a-single-character-only @endlink
     */
    void setUpTerminal();

    /**
     * @brief restore the old terminal settings
     */
    void resetTerminal();
};

/**
 * @brief class that controls the users' input and the models for the game
 */
class Controler
{
private:
    /**
     * @brief synchronises the use of the shared variable cmds
     */
    std::condition_variable cv;

    /**
     * @brief protects the shared variable cmds
     */
    std::mutex cmdsMutex;

    /**
     * @brief read constantly chars from the terminal and stores them in a queue
     *
     * @param[out] cmds stores the chars from the users' input
     * @param[in] run controls the loop. As long as it is true the loop will run.
     */
    void inputThrFunc(std::queue<char> &cmds, bool &run);

    /**
     * @brief removes constantly chars from a queue and processes the commands
     *
     * @param cmds[in, out] stores the chars from the users' input
     * @param part[in, out] is the active part that the user controls
     * @param playground[in] stores all the information about the game field
     * @param view[in] will print the playground and the active part
     * @param run[in] controls the loop. As long as it is true the loop will run.
     */
    void controlThrFunc(std::queue<char> &cmds, std::shared_ptr<Part> &part, Playground &playground, View &view, bool &run);

    /**
     * @brief starts and controls the threads that are needed for the game and
     * starts the game loop that manages the active parts
     *
     * @param[in, out] playground stores all the information about the game field
     * @param[in] view will print the playground and the active part
     */
    void startGameLoop(Playground &playground, View &view);

public:
    /**
     * @brief setup the terminal settings, creates the playground and the view and starts the game loop
     */
    void startGame();
};

int main()
{
    Controler controler;
    controler.startGame();

    return 0;
}

#endif