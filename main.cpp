#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

class Cell {
public:
    bool alive;

    Cell(bool state = false) : alive(state) {}

    void setAlive(bool state) {
        alive = state;
    }
};

class Field {
private:
    int width;
    int height;
    std::vector<std::vector<Cell>> grid;

    int countAliveNeighbors(int x, int y) {
        int count = 0;
        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                if ((dx != 0 || dy != 0) &&
                    x + dx >= 0 && x + dx < width &&
                    y + dy >= 0 && y + dy < height) {
                    count += grid[x + dx][y + dy].alive ? 1 : 0;
                }
            }
        }
        return count;
    }

public:
    Field(int w, int h) : width(w), height(h), grid(w, std::vector<Cell>(h)) {}

    void setCellAlive(int x, int y, bool state) {
        grid[x][y].setAlive(state);
    }

    void display() {
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                std::cout << (grid[x][y].alive ? 'O' : '.') << ' ';
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    void update() {
        std::vector<std::vector<Cell>> newGrid = grid;

        for (int x = 0; x < width; ++x) {
            for (int y = 0; y < height; ++y) {
                int aliveNeighbors = countAliveNeighbors(x, y);

                if (grid[x][y].alive) {
                    newGrid[x][y].setAlive(aliveNeighbors == 2 || aliveNeighbors == 3);
                }
                else {
                    newGrid[x][y].setAlive(aliveNeighbors == 3);
                }
            }
        }
        grid = newGrid;
    }
};

class Game {
private:
    Field field;
    int iterations;

public:
    Game(int width, int height, int iters) : field(width, height), iterations(iters) {}

    void initialize() {
        field.setCellAlive(1, 0, true);
        field.setCellAlive(2, 1, true);
        field.setCellAlive(0, 1, true);
        field.setCellAlive(1, 1, true);
        field.setCellAlive(2, 2, true);
        field.setCellAlive(1, 2, true);
        field.setCellAlive(2, 3, true);
        field.setCellAlive(3, 3, true);
        field.setCellAlive(4, 3, true);
    }

    void run() {
        for (int i = 0; i < iterations; ++i) {
            field.display();
            field.update();
            std::this_thread::sleep_for(std::chrono::milliseconds(400)); // задержка для наглядности
        }
    }
};

int main() {
    Game game(28, 28, 100); 
    game.initialize();
    game.run();

    return 0;
}
