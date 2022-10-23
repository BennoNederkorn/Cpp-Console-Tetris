Console Tetris Game
- created by Benno Nederkorn in October 2022
- tested only on Ubuntu 20.04

Build:
- clone the repository and go to the project folder
- create build folder: mkdir build
- build the game with cmake: cmake -S . -B ./build
- create the executable: make -C ./build
- run the game with: ./build/tetris

Controls:
- move Part down:           's' or 'k'
- move Part to the left:    'a' or 'j'
- move Part to the right:   'd' or 'l'
- rotate Part to the left:  'q' or 'u'
- rotate Part to the right: 'e' or 'o'
