#include "../include/view.h"

std::string View::toString(Playground &playground, Part &part)
{
    std::array<std::pair<size_t, size_t>, part.getNumberOfComponents()> partPosition = part.getPartPosition();
    std::string str;
    for (size_t y{playground.getHeight() - 1}; true; --y)
    {
        for (size_t x{0}; x < playground.getWidth(); ++x)
        {
            str.push_back(playground.getField()[x][y]);

            for (auto [xCoordinate, yCoordinate] : partPosition)
            {
                if (xCoordinate == x && yCoordinate == y)
                {
                    str.pop_back();
                    str.push_back(part.getSymbol());
                }
            }
        }
        str.push_back('\n');
        if (y <= 0)
            return str;
    }
}

void View::display(Playground &playground, Part &part)
{
    const std::lock_guard<std::mutex> lock(displayMutex);
    printf("\x1b[H"); // returning the cursor to the home position
    printf("%s", toString(playground, part).c_str());
}