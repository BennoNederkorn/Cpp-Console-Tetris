#include "../include/controler.h"

void TerminalManagement::setUpTerminal()
{

    /*
     * tcgetattr gets the parameters of the current terminal
     * STDIN_FILENO will tell tcgetattr that it should write the settings
     * of stdin to oldT
     */
    tcgetattr(STDIN_FILENO, &oldT);

    /*
     * now the settings will be copied
     */
    newT = oldT;

    /*
     * ICANON normally takes care that one line at a time will be processed;
     * that means it will return if it sees a "\n" or an EOF or an EOL.
     * The ECHO flag disassociate the input from the output.
     */
    newT.c_lflag &= ~(ICANON | ECHO);

    /*
     * Those new settings will be set to STDIN
     * TCSANOW tells tcsetattr to change attributes immediately.
     */
    tcsetattr(STDIN_FILENO, TCSANOW, &newT);

    /*
     * clear screen
     */
    printf("\x1b[2J");
}

void TerminalManagement::resetTerminal()
{
    tcsetattr(STDIN_FILENO, TCSANOW, &oldT);
}

void Controler::inputThrFunc(std::queue<char> &cmds, bool &run)
{
    while (run)
    {
        char c = getchar();

        if (c == 'a' || c == 'A' || c == 's' || c == 'S' || c == 'd' || c == 'D' || c == 'q' || c == 'Q' || c == 'e' || c == 'E' ||
            c == 'j' || c == 'J' || c == 'k' || c == 'K' || c == 'l' || c == 'L' || c == 'u' || c == 'U' || c == 'o' || c == 'O')
        {
            const std::lock_guard<std::mutex> lock(cmdsMutex);
            cmds.push(c);
            cv.notify_one();
        }
    }
}

void Controler::controlThrFunc(std::queue<char> &cmds, std::shared_ptr<Part> &part, Playground &playground, View &view, bool &run)
{
    while (run)
    {
        std::unique_lock lock(cmdsMutex);
        cv.wait(lock, [&cmds]
                { return cmds.size() > 0; });
        char cmd;
        cmd = cmds.front();
        cmds.pop();
        if (cmd == 's' || cmd == 'S' || cmd == 'k' || cmd == 'K')
        {
            part->moveDown(playground);
            view.display(playground, *part);
        }
        else if (cmd == 'a' || cmd == 'A' || cmd == 'j' || cmd == 'J')
        {
            part->moveLeft(playground);
            view.display(playground, *part);
        }
        else if (cmd == 'd' || cmd == 'D' || cmd == 'l' || cmd == 'L')
        {
            part->moveRight(playground);
            view.display(playground, *part);
        }
        else if (cmd == 'q' || cmd == 'Q' || cmd == 'u' || cmd == 'U')
        {
            part->turnLeft(playground);
            view.display(playground, *part);
        }
        else if (cmd == 'e' || cmd == 'E' || cmd == 'o' || cmd == 'O')
        {
            part->turnRight(playground);
            view.display(playground, *part);
        }
    }
}

void Controler::startGameLoop(Playground &playground, View &view)
{
    // create current/first and next/second Parts of the game.
    int xSpawn = (playground.getMaxPlaygroundWidth() - playground.getMinPlaygroundWidth()) / 2;
    int ySpawn = playground.getMaxPlaygroundHeight();
    std::shared_ptr<Part> nextPart = std::make_shared<Part>(xSpawn, ySpawn);
    std::shared_ptr<Part> currentPart;

    // start a Thread that processes the players' inputs and
    // terminate if run is false
    std::queue<char> cmds;
    bool run = true;
    std::jthread controlThr(&Controler::controlThrFunc, this, std::ref(cmds), std::ref(currentPart), std::ref(playground), std::ref(view), std::ref(run));

    // start a Thread that collects all the players' inputs
    std::jthread inputThr(&Controler::inputThrFunc, this, std::ref(cmds), std::ref(run));

    // start outer game loop that creates nextParts
    while (true)
    {
        // move the nextPart to the currentPart and create a new nextPart.
        if (playground.isFree(nextPart->getPartPosition()))
        {
            currentPart = std::move(nextPart);
            nextPart = std::make_shared<Part>(xSpawn, ySpawn);
        }
        else
        {
            break;
        }

        // display the first Playground
        playground.setNextPart(nextPart->getPartPosition(), nextPart->getSymbol());
        view.display(playground, *currentPart);

        // calculate game speed;
        int sleepTime = 500 - playground.getLevel() * 50;
        if (sleepTime <= 0)
            sleepTime = 50;

        // start inner game loop that moveDown the currentPart and
        // exit if the currentPart reaches the bottom
        bool activePart = true;
        while (activePart)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
            activePart = currentPart->moveDown(playground);
            view.display(playground, *currentPart);
        }

        // update playground, check rows and update level and score
        playground.setDownPart(currentPart->getPartPosition(), currentPart->getSymbol());
    }

    run = false;
}

void Controler::startGame()
{
    TerminalManagement tm;
    tm.setUpTerminal();

    View view;
    Playground playground;
    startGameLoop(playground, view);

    tm.resetTerminal();
}