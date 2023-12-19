#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/Text.hpp>
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <fstream>
#include <sstream>

using namespace sf;
using namespace std;

constexpr int blockShapes[7][4][4][4] = {
        // Type: O
        {
                {
                        { 0, 0, 0, 0 },
                        { 0, 1, 2, 0 },
                        { 0, 1, 1, 0 },
                        { 0, 0, 0, 0 }
                },
                {
                        { 0, 0, 0, 0 },
                        { 0, 1, 2, 0 },
                        { 0, 1, 1, 0 },
                        { 0, 0, 0, 0 }
                },
                {
                        { 0, 0, 0, 0 },
                        { 0, 1, 2, 0 },
                        { 0, 1, 1, 0 },
                        { 0, 0, 0, 0 }
                },
                {
                        { 0, 0, 0, 0 },
                        { 0, 1, 2, 0 },
                        { 0, 1, 1, 0 },
                        { 0, 0, 0, 0 }
                }
        },

        // Type: I
        {
                {
                        { 0, 0, 0, 0 },
                        { 1, 1, 2, 1 },
                        { 0, 0, 0, 0 },
                        { 0, 0, 0, 0 }
                },
                {
                        { 0, 0, 1, 0 },
                        { 0, 0, 2, 0 },
                        { 0, 0, 1, 0 },
                        { 0, 0, 1, 0 }
                },
                {
                        { 0, 0, 0, 0 },
                        { 1, 1, 2, 1 },
                        { 0, 0, 0, 0 },
                        { 0, 0, 0, 0 }
                },
                {
                        { 0, 0, 1, 0 },
                        { 0, 0, 2, 0 },
                        { 0, 0, 1, 0 },
                        { 0, 0, 1, 0 }
                }
        },

        // Type: S
        {
                {
                        { 0, 0, 0, 0 },
                        { 0, 0, 2, 1 },
                        { 0, 1, 1, 0 },
                        { 0, 0, 0, 0 }
                },
                {
                        { 0, 0, 1, 0 },
                        { 0, 0, 2, 1 },
                        { 0, 0, 0, 1 },
                        { 0, 0, 0, 0 }
                },
                {
                        { 0, 0, 0, 0 },
                        { 0, 0, 2, 1 },
                        { 0, 1, 1, 0 },
                        { 0, 0, 0, 0 }
                },
                {
                        { 0, 0, 1, 0 },
                        { 0, 0, 2, 1 },
                        { 0, 0, 0, 1 },
                        { 0, 0, 0, 0 }
                }
        },

        // Type: Z
        {
                {
                        { 0, 0, 0, 0 },
                        { 0, 1, 2, 0 },
                        { 0, 0, 1, 1 },
                        { 0, 0, 0, 0 }
                },
                {
                        { 0, 0, 0, 1 },
                        { 0, 0, 2, 1 },
                        { 0, 0, 1, 0 },
                        { 0, 0, 0, 0 }
                },
                {
                        { 0, 0, 0, 0 },
                        { 0, 1, 2, 0 },
                        { 0, 0, 1, 1 },
                        { 0, 0, 0, 0 }
                },
                {
                        { 0, 0, 0, 1 },
                        { 0, 0, 2, 1 },
                        { 0, 0, 1, 0 },
                        { 0, 0, 0, 0 }
                }
        },

        // Type: L
        {
                {
                        { 0, 0, 0, 0 },
                        { 0, 1, 2, 1 },
                        { 0, 1, 0, 0 },
                        { 0, 0, 0, 0 }
                },
                {
                        { 0, 0, 1, 0 },
                        { 0, 0, 2, 0 },
                        { 0, 0, 1, 1 },
                        { 0, 0, 0, 0 }
                },
                {
                        { 0, 0, 0, 1 },
                        { 0, 1, 2, 1 },
                        { 0, 0, 0, 0 },
                        { 0, 0, 0, 0 }
                },
                {
                        { 0, 1, 1, 0 },
                        { 0, 0, 2, 0 },
                        { 0, 0, 1, 0 },
                        { 0, 0, 0, 0 }
                }
        },

        // Type: J
        {
                {
                        { 0, 0, 0, 0 },
                        { 0, 1, 2, 1 },
                        { 0, 0, 0, 1 },
                        { 0, 0, 0, 0 }
                },
                {
                        { 0, 0, 1, 1 },
                        { 0, 0, 2, 0 },
                        { 0, 0, 1, 0 },
                        { 0, 0, 0, 0 }
                },
                {
                        { 0, 1, 0, 0 },
                        { 0, 1, 2, 1 },
                        { 0, 0, 0, 0 },
                        { 0, 0, 0, 0 }
                },
                {
                        { 0, 0, 1, 0 },
                        { 0, 0, 2, 0 },
                        { 0, 1, 1, 0 },
                        { 0, 0, 0, 0 }
                }
        },

        // Type: T
        {
                {
                        { 0, 0, 0, 0 },
                        { 0, 1, 2, 1 },
                        { 0, 0, 1, 0 },
                        { 0, 0, 0, 0 }
                },
                {
                        { 0, 0, 1, 0 },
                        { 0, 0, 2, 1 },
                        { 0, 0, 1, 0 },
                        { 0, 0, 0, 0 }
                },
                {
                        { 0, 0, 1, 0 },
                        { 0, 1, 2, 1 },
                        { 0, 0, 0, 0 },
                        { 0, 0, 0, 0 }
                },
                {
                        { 0, 0, 1, 0 },
                        { 0, 1, 2, 0 },
                        { 0, 0, 1, 0 },
                        { 0, 0, 0, 0 }
                }
        }
};

constexpr int DEFAULT_ROWS_COUNT = 23;
constexpr int DEFAULT_COLUMNS_COUNT = 12;
constexpr int DEFAULT_CELL_SIZE = 35;

class Map {
private:
    int width;
    int height;
    RectangleShape field;
    vector<vector<int>> grid;

public:
    int removedLines;

    Map(int w, int h) : width(w), height(h), removedLines(0) {
        field.setSize(Vector2f(width, height));
        field.setFillColor(Color::Black);
        field.setPosition((1000 - width) / 2.0f,0);
        grid.resize(DEFAULT_ROWS_COUNT, vector<int>(DEFAULT_COLUMNS_COUNT, -1));
    }

    Color getColorForType(int blockType) {
        switch (blockType) {
            case 0: return Color(102, 0, 51); // Type O
            case 1: return Color(153, 0, 76); // Type I
            case 2: return Color(204, 0, 102); // Type S
            case 3: return Color(255, 0, 127); // Type Z
            case 4: return Color(255, 51, 153); // Type L
            case 5: return Color(255, 153, 204);// Type J
            case 6: return Color(255, 204, 229); // Type T
        }
    }

    void draw(RenderWindow& window) {
        window.draw(field);

        // draw the grid
        for (int row = 0; row < DEFAULT_ROWS_COUNT; ++row) {
            for (int col = 0; col < DEFAULT_COLUMNS_COUNT; ++col) {
                RectangleShape cell(Vector2f(DEFAULT_CELL_SIZE, DEFAULT_CELL_SIZE));
                cell.setPosition(field.getPosition().x + col * DEFAULT_CELL_SIZE,
                                 field.getPosition().y + row * DEFAULT_CELL_SIZE);
                cell.setFillColor(grid[row][col] == -1 ? Color::Transparent : getColorForType(grid[row][col]));
                cell.setOutlineColor(Color(55, 55, 55));
                cell.setOutlineThickness(1);
                window.draw(cell);
            }
        }
    }

    bool canPlaceBlock(int x, int y, int shape[4][4]) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (shape[i][j] != 0) {
                    int gridX = x + j;
                    int gridY = y + i;
                    if (gridX < 0 || gridX >= DEFAULT_COLUMNS_COUNT || gridY < 0 ||
                    gridY >= DEFAULT_ROWS_COUNT || grid[gridY][gridX] != -1) {
                        return false;
                    }
                }
            }
        }
        return true;
    }

    void dropBlock(int x, int y, int blockType, int shape[4][4]) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (shape[i][j] != 0) {
                    grid[y + i][x + j] = blockType;
                }
            }
        }
    }

    void removeLine(){
        for (int y = DEFAULT_ROWS_COUNT - 1; y >= 0; --y) {
            bool rowFull = true;

            for (int x = 0; x < DEFAULT_COLUMNS_COUNT; ++x) {
                if (grid[y][x] == -1) {
                    rowFull = false;
                    break;
                }
            }

            if (rowFull) {
                for (int i = y; i > 0; --i) {
                    for (int j = 0; j < DEFAULT_COLUMNS_COUNT; ++j) {
                        grid[i][j] = grid[i - 1][j];
                    }
                }

                // check the row again, after moving everything down
                y++;
                removedLines++;
            }
        }
    };

    int getFieldX(){
        return this->field.getPosition().x;
    }

    void changeSize();
};

class Block {
public:
    enum class Type { O, I, S, Z, L, J, T };

private:
    int rotationState;
    friend class GameMenu;

protected:
    Type type;
    int shape[4][4];

public:

    Block(Type& type) : type(type), rotationState(0) {
        // copying a block of memory from one location to another
        // destination (where to copy), source (where to copy from) and size of the memory block to be copied
        memcpy(shape, blockShapes[static_cast<int>(type)][rotationState], sizeof(shape));
    }

    void rotate() {
        rotationState = (rotationState + 1) % 4;
        memcpy(shape, blockShapes[static_cast<int>(type)][rotationState], sizeof(shape));
    }

    void draw(RenderWindow &window,Map& map, int x, int y) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (shape[i][j] != 0) {
                    RectangleShape cell(Vector2f(DEFAULT_CELL_SIZE, DEFAULT_CELL_SIZE));
                    cell.setPosition(map.getFieldX() + (x + j) * DEFAULT_CELL_SIZE,
                                     0 + (y + i) * DEFAULT_CELL_SIZE);
                    cell.setFillColor(map.getColorForType(static_cast<int>(type)));
                    window.draw(cell);
                }
            }
        }
    }

    void move(Map& map, Vector2i& blockPosition){
        // move block left
        if (Keyboard::isKeyPressed(Keyboard::Left)) {
            if (map.canPlaceBlock(blockPosition.x - 1, blockPosition.y, this->shape)) {
                blockPosition.x -= 1;
            }
        }

        // move block right
        if (Keyboard::isKeyPressed(Keyboard::Right)) {
            if (map.canPlaceBlock(blockPosition.x + 1, blockPosition.y, this->shape)) {
                blockPosition.x += 1;
            }
        }

        // speed up the block
        if (Keyboard::isKeyPressed(Keyboard::Down)) {
            if (map.canPlaceBlock(blockPosition.x + 1, blockPosition.y, this->shape)) {
                blockPosition.y += 1;
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Up)) {
            int previousRotationState = this->rotationState;
            this->rotate();

            // check if the new rotation is possible, if not revert
            if (!map.canPlaceBlock(blockPosition.x, blockPosition.y, this->shape)) {
                this->rotationState = previousRotationState;
                memcpy(this->shape, blockShapes[static_cast<int>(this->type)][this->rotationState], sizeof(this->shape));
            }
        }
    }
};

class Player {
private:
    string name;
    int currentScore;
    int bestScore;

public:
    Player(string name) : name(name), currentScore(0), bestScore(0) {}
};

class GameDataStorage {
private:
    vector<Player*> players;

public:
    void savePlayerData(Player& player);
    vector<Player*> loadPlayersData();
};

class GameStateManager {
private:
    string currentState;

public:
    void changeState(string newState);
    string getState();
    void pauseGame();
    void resumeGame();
};

class Button {
private:
    Sprite sprite;

    bool isHovered(RenderWindow& window) {
        auto mousePos = Mouse::getPosition(window);
        return sprite.getGlobalBounds().contains(static_cast<Vector2f>(mousePos));
    }

public:
    Button(Texture& texture, float x, float y) {
        sprite.setTexture(texture);
        sprite.setPosition(x, y);
    }
    void draw(RenderWindow& window) {
        window.draw(sprite);
    }
    bool isClicked(RenderWindow& window) {
        return isHovered(window) && Mouse::isButtonPressed(Mouse::Left);
    }
};

class GameMenu {
private:
    bool gameOver, keyHandled, isMenu;
    Block::Type types[7] = {Block::Type::O, Block::Type::I, Block::Type::S, Block::Type::Z,
                            Block::Type::L, Block::Type::J, Block::Type::T};
    Font font;
    Text scoreText;
    Texture backgroundImage, playImage, exitImage, backgroundImageForGame;
    Sprite backgroundSprite, backgroundImageForGameSprite;
    Text nameText;
    string playerInput;

public:
    GameMenu(): gameOver(false), isMenu(true), keyHandled(false){
        font.loadFromFile("/Users/Yarrochka/Downloads/VCR_OSD_MONO.ttf");
        scoreText.setFont(font);
        scoreText.setCharacterSize(25);
        scoreText.setFillColor(Color::Black);
        scoreText.setStyle(Text::Bold);
        scoreText.setPosition(60, 60);
        scoreText.setString("Score: ");

        nameText.setFont(font);
        nameText.setCharacterSize(24);
        nameText.setFillColor(Color::White);
        nameText.setString("Name: ");
        nameText.setPosition(120, 60);
    };

    Block generateRandomBlock() {
        int randIndex = rand() % 7;
        return Block(types[randIndex]);
    }

    void updateScoreDisplay(int score) {
        scoreText.setString("Score: " + to_string(score));
    }

    void updateNameDisplay(string& name) {
        nameText.setString("Name: " + name);
    }

    void tetrisRun(Event& event, RenderWindow& window){
        Map gameMap(420, 805);

        while (!gameOver && window.isOpen()) {
            Block currentBlock = generateRandomBlock();
            Vector2i blockPosition(4, 0);

            bool blockPlaced = false;
            while (!blockPlaced && window.isOpen()) {
                while (window.pollEvent(event)) {
                    if (event.type == Event::Closed)
                        window.close();
                }

                currentBlock.move(gameMap, blockPosition);

                if (gameMap.canPlaceBlock(blockPosition.x, blockPosition.y + 1, currentBlock.shape)) {
                    blockPosition.y++;
                } else {
                    gameMap.dropBlock(blockPosition.x, blockPosition.y, static_cast<int>(currentBlock.type), currentBlock.shape);
                    blockPlaced = true;
                }

                // draw the block at its current position
                window.draw(backgroundImageForGameSprite);
                gameMap.draw(window);
                currentBlock.draw(window, gameMap, blockPosition.x, blockPosition.y);
                window.draw(scoreText);
                window.display();

                this_thread::sleep_for(chrono::milliseconds(450));

                if (!gameMap.canPlaceBlock(7, 0, currentBlock.shape)) {
                    gameOver = true;
                }
            }

            gameMap.removeLine();
            updateScoreDisplay(gameMap.removedLines * 100);
        }
    }

    void downloadTextures(RenderWindow& window){
        backgroundImage.loadFromFile("../Images/background1.png");
        backgroundSprite.setTexture(backgroundImage);
        backgroundSprite.setScale(
                float(window.getSize().x) / backgroundImage.getSize().x,
                float(window.getSize().y) / backgroundImage.getSize().y
        );

        playImage.loadFromFile("../Images/Buttons/play.png");
        exitImage.loadFromFile("../Images/Buttons/exit.png");

        backgroundImageForGame.loadFromFile("../Images/background2.png");
        backgroundImageForGameSprite.setTexture(backgroundImageForGame);
        backgroundImageForGameSprite.setScale(
                float(window.getSize().x) / backgroundImageForGame.getSize().x,
                float(window.getSize().y) / backgroundImageForGame.getSize().y
        );
    }

    void userInput(Event& event){
        if (event.type == Event::TextEntered && !keyHandled) {
            if (!keyHandled && event.text.unicode < 128) {
                keyHandled = true;
                if (event.text.unicode == '\b') {
                    if (!playerInput.empty()) {
                        playerInput.pop_back();
                    }
                } else if (event.text.unicode == '\n') {
                    isMenu = false;
                } else {
                    playerInput += static_cast<char>(event.text.unicode);
                }
                updateNameDisplay(playerInput);
            }
        } else if (event.type == Event::KeyReleased) {
            keyHandled = false;
        }
    }

    void startGame(){
        RenderWindow window(VideoMode(1000, 805), "Tetris game from Yarrochka");
        downloadTextures(window);
        while (window.isOpen()) {
            Event event;
            while (window.pollEvent(event)) {
                if (event.type == Event::Closed) {
                    window.close();
                }
            }

            window.clear();

            if (isMenu) {
                userInput(event);
                Player player(playerInput);
                Button playButton(playImage, 100, 100);
                Button exitButton(exitImage, 122, 250);
                window.draw(backgroundSprite);
                playButton.draw(window);
                exitButton.draw(window);
                window.draw(nameText);

                if (playButton.isClicked(window)) {
                    isMenu = false;
                }
                if (exitButton.isClicked(window)) {
                    window.close();
                }
            } else {
                tetrisRun(event, window);
            }

            window.display();
        }
    };
};

int main() {
    GameMenu gameMenu;
    gameMenu.startGame();

    return 0;
}
