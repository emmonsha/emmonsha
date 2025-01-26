#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ncurses.h>
#include <time.h>

// Перечисление для действий пользователя
typedef enum {
    Start,
    Pause,
    Terminate,
    Left,
    Right,
    Up,
    Down,
    Action
} UserAction_t;

// Перечисление для типов тетрамино
typedef enum {
    TC_EMPTY,
    TC_TYPE_I,
    TC_TYPE_J,
    TC_TYPE_L,
    TC_TYPE_O,
    TC_TYPE_S,
    TC_TYPE_T,
    TC_TYPE_Z
} TetType_t;

// Структура для хранения информации о текущем тетрамино
typedef struct {
    int **tetromino;
    int tet_x;
    int tet_y;
    TetType_t tet_type;
} Tetromino_t;

// Структура для хранения информации о игре
typedef struct {
    int **field;
    int **next;
    int score;
    int high_score;
    int level;
    int speed;
    int pause;
    Tetromino_t *current;
    TetType_t *next_tet_type;
} GameInfo_t;

// Прототипы функций
void userInput(UserAction_t action, GameInfo_t *gameInfo);
GameInfo_t updateCurrentState(void);
void renderField(GameInfo_t gameInfo);
void initializeGame(GameInfo_t *gameInfo);
void cleanupGame(GameInfo_t *gameInfo);
void gameLoop(GameInfo_t *gameInfo);
GameInfo_t bufferGameInfo(GameInfo_t *newGameInfo);
void tMove(UserAction_t action, GameInfo_t *gameInfo);
void mv_left(GameInfo_t *gameInfo);
void mv_right(GameInfo_t *gameInfo);
void rotate_tet(GameInfo_t *gameInfo);
void rotate_clockwise(GameInfo_t *gameInfo);
void rotate_counter_clockwise(GameInfo_t *gameInfo);
void mv_down(GameInfo_t *gameInfo);
void mv_drop(GameInfo_t *gameInfo);
void do_nothing(GameInfo_t *gameInfo);
bool check_collision(GameInfo_t *gameInfo);
int** create_matrix(int rows, int cols);
void free_matrix(int rows, int **matrix);
void copy_matrix(int **dest, int **src);
void initializeTetromino(Tetromino_t *tetromino);
void updateField(GameInfo_t *gameInfo);
void checkAndClearLines(GameInfo_t *gameInfo);
void updateScore(GameInfo_t *gameInfo, int linesCleared);
void createNewTetromino(GameInfo_t *gameInfo);
void set_tetramino(int** matrix, TetType_t tet_type);
TetType_t random_Tetromino();
void get_new_falling_tetramino(GameInfo_t *gameInfo);

// Константы
#define TETSIZE 4
#define FIELD_WIDTH 10
#define FIELD_HEIGHT 20
#define TETNUM 7

// Инициализация игры
void initializeGame(GameInfo_t *gameInfo) {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    curs_set(0);

    gameInfo->score = 0;
    gameInfo->high_score = 0;
    gameInfo->level = 1;
    gameInfo->speed = 100;
    gameInfo->pause = 0;

    gameInfo->field = (int **)malloc(FIELD_HEIGHT * sizeof(int *));
    for (int i = 0; i < FIELD_HEIGHT; i++) {
        gameInfo->field[i] = (int *)calloc(FIELD_WIDTH, sizeof(int));
    }

    gameInfo->current = (Tetromino_t *)malloc(sizeof(Tetromino_t));
    gameInfo->next_tet_type = (TetType_t *)malloc(sizeof(TetType_t));
    initializeTetromino(gameInfo->current);
    get_new_falling_tetramino(gameInfo);
}

// Инициализация тетрамино
void initializeTetromino(Tetromino_t *tetromino) {
    tetromino->tetromino = create_matrix(TETSIZE, TETSIZE);
    tetromino->tet_x = FIELD_WIDTH / 2 - TETSIZE / 2;
    tetromino->tet_y = 0;
    tetromino->tet_type = TC_EMPTY;
}

// Установка тетрамино
void set_tetramino(int** matrix, TetType_t tet_type) {
    int index = tet_type - 1;
    int tetrominoes[TETNUM][TETSIZE][TETSIZE] = {
        // I-фигура
        {{0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}},
        // J-фигура
        {{1, 0, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
        // L-фигура
        {{0, 0, 1, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
        // O-фигура
        {{0, 0, 0, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}},
        // S-фигура
        {{0, 1, 1, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
        // T-фигура
        {{0, 1, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
        // Z-фигура
        {{1, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}};

    // запись текущего тетрамино из стека тетрамино
    for (int i = 0; i < TETSIZE; i++) {
        for (int j = 0; j < TETSIZE; j++) {
            if (tetrominoes[index][i][j] != 0) {
                matrix[i][j] = tet_type;
            }
        }
    }
}

// Получение нового падающего тетрамино
void get_new_falling_tetramino(GameInfo_t *gameInfo) {
    if (gameInfo->current->tetromino != NULL) {
        free_matrix(TETSIZE, gameInfo->current->tetromino);
    }
    gameInfo->current->tetromino = create_matrix(TETSIZE, TETSIZE);

    static int counter = 0;

    if (counter == 0) {
        *gameInfo->next_tet_type = random_Tetromino();
        gameInfo->current->tet_type = random_Tetromino();
    } else {
        gameInfo->current->tet_type = *gameInfo->next_tet_type;
    }
    *gameInfo->next_tet_type = random_Tetromino();
    set_tetramino(gameInfo->current->tetromino, gameInfo->current->tet_type);
    if (gameInfo->next != NULL) {
        free_matrix(TETSIZE, gameInfo->next);
    }
    gameInfo->next = create_matrix(TETSIZE, TETSIZE);
    set_tetramino(gameInfo->next, *gameInfo->next_tet_type);
    gameInfo->current->tet_y = 0;
    gameInfo->current->tet_x = FIELD_WIDTH / 2 - 2;

    counter++;
}

// Генерация случайного тетрамино
TetType_t random_Tetromino() {
    return (TetType_t)(rand() % TETNUM + 1);
}

// Отрисовка игрового поля
void renderField(GameInfo_t gameInfo) {
    clear();
    for (int y = 0; y < FIELD_HEIGHT; y++) {
        for (int x = 0; x < FIELD_WIDTH; x++) {
            if (gameInfo.field[y][x] == 1) {
                mvprintw(y, x, "#");
            } else {
                mvprintw(y, x, " ");
            }
        }
    }
    mvprintw(22, 0, "Score: %d", gameInfo.score);
    mvprintw(23, 0, "High Score: %d", gameInfo.high_score);
    refresh();
}

// Функция-буфер для проверки рекурсии и переноса данных
GameInfo_t bufferGameInfo(GameInfo_t *newGameInfo) {
    static GameInfo_t *currentGameInfo = NULL;
    if (currentGameInfo == NULL) {
        currentGameInfo = newGameInfo;
    } else {
        // Перенос данных из старого состояния в новое
        for (int i = 0; i < FIELD_HEIGHT; i++) {
            for (int j = 0; j < FIELD_WIDTH; j++) {
                newGameInfo->field[i][j] = currentGameInfo->field[i][j];
            }
        }
        newGameInfo->score = currentGameInfo->score;
        newGameInfo->high_score = currentGameInfo->high_score;
        newGameInfo->level = currentGameInfo->level;
        newGameInfo->speed = currentGameInfo->speed;
        newGameInfo->pause = currentGameInfo->pause;
        newGameInfo->current->tet_x = currentGameInfo->current->tet_x;
        newGameInfo->current->tet_y = currentGameInfo->current->tet_y;
        copy_matrix(newGameInfo->current->tetromino, currentGameInfo->current->tetromino);
        newGameInfo->current->tet_type = currentGameInfo->current->tet_type;
        *newGameInfo->next_tet_type = *currentGameInfo->next_tet_type;

        // Освобождение памяти старого состояния
        for (int i = 0; i < FIELD_HEIGHT; i++) {
            free(currentGameInfo->field[i]);
        }
        free(currentGameInfo->field);
        if (currentGameInfo->current->tetromino != NULL) {
            free_matrix(TETSIZE, currentGameInfo->current->tetromino);
        }
        free(currentGameInfo->current);
        free(currentGameInfo->next_tet_type);
        currentGameInfo = newGameInfo;
    }
    return *newGameInfo;
}

// Обработка пользовательского ввода
void userInput(UserAction_t action, GameInfo_t *gameInfo) {
    int ch = getch();
    switch (ch) {
        case KEY_LEFT:
            action = Left;
            break;
        case KEY_RIGHT:
            action = Right;
            break;
        case KEY_UP:
            action = Up;
            break;
        case KEY_DOWN:
            action = Down;
            break;
        case ' ':
            action = Action;
            break;
        case 'p':
        case 'P':
            action = Pause;
            break;
        case 'q':
        case 'Q':
            action = Terminate;
            break;
        case '\n':
            action = Start;
            break;
        default:
            action = Up;
            break;
    }

    // Изменение состояния игры в зависимости от действия пользователя
    tMove(action, gameInfo);
}

// Обновление состояния игры
GameInfo_t updateCurrentState(void) {
    static GameInfo_t *gameInfo = NULL;
    if (gameInfo == NULL) {
        gameInfo = (GameInfo_t *)malloc(sizeof(GameInfo_t));
        initializeGame(gameInfo);
    }
    return *gameInfo;
}

// Основной игровой цикл
void gameLoop(GameInfo_t *gameInfo) {
    if (gameInfo == NULL) {
        gameInfo = (GameInfo_t *)malloc(sizeof(GameInfo_t));
        initializeGame(gameInfo);
    }

    UserAction_t action;
    action = Up;

    while (true) {
        // Обработка пользовательского ввода
        userInput(action, gameInfo);

        // Отрисовка игрового поля
        renderField(*gameInfo);

        // Проверка условий завершения игры
        if (action == Terminate || gameInfo->pause == 1 || gameInfo->current->tet_y == 0) {
            break;
        }

        // Задержка для контроля скорости игры
        napms(gameInfo->speed);
    }

    // Очистка ресурсов игры
    cleanupGame(gameInfo);
}

// Очистка ресурсов игры
void cleanupGame(GameInfo_t *gameInfo) {
    for (int i = 0; i < FIELD_HEIGHT; i++) {
        free(gameInfo->field[i]);
    }
    free(gameInfo->field);
    if (gameInfo->current->tetromino != NULL) {
        free_matrix(TETSIZE, gameInfo->current->tetromino);
    }
    free(gameInfo->current);
    free(gameInfo->next_tet_type);
    endwin();
}

// Функции движения тетрамино
void tMove(UserAction_t action, GameInfo_t *gameInfo) {
    if (action != Pause) {
        switch (action) {
            case Left:
                mv_left(gameInfo);
                break;
            case Right:
                mv_right(gameInfo);
                break;
            case Up:
                rotate_tet(gameInfo);
                break;
            case Down:
                mv_down(gameInfo);
                break;
            case Action:
                mv_drop(gameInfo);
                break;
            default:
                do_nothing(gameInfo);
                break;
        }
        mv_down(gameInfo);
    }
}

void mv_left(GameInfo_t *gameInfo) {
    gameInfo->current->tet_x--;
    if (check_collision(gameInfo)) {
        gameInfo->current->tet_x++;
    }
}

void mv_right(GameInfo_t *gameInfo) {
    gameInfo->current->tet_x++;
    if (check_collision(gameInfo)) {
        gameInfo->current->tet_x--;
    }
}

void rotate_tet(GameInfo_t *gameInfo) {
    rotate_clockwise(gameInfo);
    if (check_collision(gameInfo)) {
        rotate_counter_clockwise(gameInfo);
    }
}

void rotate_clockwise(GameInfo_t *gameInfo) {
    int **new_matrix = create_matrix(TETSIZE, TETSIZE);
    int **tmp_matrix = create_matrix(TETSIZE, TETSIZE);
    copy_matrix(tmp_matrix, gameInfo->current->tetromino);

    int size = 3;
    if (gameInfo->current->tet_type == TC_TYPE_I || gameInfo->current->tet_type == TC_TYPE_O) {
        size = 4;
    }

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            new_matrix[j][size - 1 - i] = gameInfo->current->tetromino[i][j];
        }
    }

    free_matrix(TETSIZE, gameInfo->current->tetromino);
    gameInfo->current->tetromino = new_matrix;

    if (check_collision(gameInfo)) {
        rotate_counter_clockwise(gameInfo);
        free_matrix(TETSIZE, new_matrix);
    } else {
        free_matrix(TETSIZE, tmp_matrix);
    }
}

void rotate_counter_clockwise(GameInfo_t *gameInfo) {
    int **new_matrix = create_matrix(TETSIZE, TETSIZE);
    int size = 3;
    if (gameInfo->current->tet_type == TC_TYPE_I || gameInfo->current->tet_type == TC_TYPE_O) {
        size = 4;
    }

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            new_matrix[size - 1 - j][i] = gameInfo->current->tetromino[i][j];
        }
    }

    free_matrix(TETSIZE, gameInfo->current->tetromino);
    gameInfo->current->tetromino = new_matrix;
}

void mv_down(GameInfo_t *gameInfo) {
    gameInfo->current->tet_y++;
    if (check_collision(gameInfo)) {
        gameInfo->current->tet_y--;
        if (gameInfo->current->tet_y == 0) {
            gameInfo->pause = 1; // Game over
        } else {
            updateField(gameInfo);
            checkAndClearLines(gameInfo);
            get_new_falling_tetramino(gameInfo);
        }
    }
}

void mv_drop(GameInfo_t *gameInfo) {
    while (gameInfo->pause == 0 && gameInfo->current->tet_y != 0) {
        mv_down(gameInfo);
    }
}

void do_nothing(GameInfo_t *gameInfo) {
    // Пустое действие
    if (gameInfo->level == 10) {
        printf("you win\n");
    }
}

bool check_collision(GameInfo_t *gameInfo) {
    for (int i = 0; i < TETSIZE; i++) {
        for (int j = 0; j < TETSIZE; j++) {
            if (gameInfo->current->tetromino[i][j] != 0) {
                int fy = gameInfo->current->tet_y + i;
                int fx = gameInfo->current->tet_x + j;
                // проверка на выход за границы
                if (fx < 0 || fx >= FIELD_WIDTH || fy < 0 || fy >= FIELD_HEIGHT) {
                    return true;
                }
                // проверка на заполненность поля
                if (gameInfo->field[fy][fx] != 0) {
                    return true;
                }
            }
        }
    }
    return false;
}

void updateField(GameInfo_t *gameInfo) {
    for (int i = 0; i < TETSIZE; i++) {
        for (int j = 0; j < TETSIZE; j++) {
            if (gameInfo->current->tetromino[i][j] != 0) {
                int fy = gameInfo->current->tet_y + i;
                int fx = gameInfo->current->tet_x + j;
                gameInfo->field[fy][fx] = gameInfo->current->tetromino[i][j];
            }
        }
    }
}

void checkAndClearLines(GameInfo_t *gameInfo) {
    int linesCleared = 0;
    for (int y = FIELD_HEIGHT - 1; y >= 0; y--) {
        bool lineFull = true;
        for (int x = 0; x < FIELD_WIDTH; x++) {
            if (gameInfo->field[y][x] == 0) {
                lineFull = false;
                break;
            }
        }
        if (lineFull) {
            linesCleared++;
            for (int k = y; k > 0; k--) {
                for (int x = 0; x < FIELD_WIDTH; x++) {
                    gameInfo->field[k][x] = gameInfo->field[k - 1][x];
                }
            }
            for (int x = 0; x < FIELD_WIDTH; x++) {
                gameInfo->field[0][x] = 0;
            }
            y++; // Recheck the same line after shifting
        }
    }
    updateScore(gameInfo, linesCleared);
}

void updateScore(GameInfo_t *gameInfo, int linesCleared) {
    gameInfo->score += linesCleared * 100; // Пример обновления счета
    if (gameInfo->score > gameInfo->high_score) {
        gameInfo->high_score = gameInfo->score;
    }
}

int** create_matrix(int rows, int cols) {
    int **matrix = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int *)calloc(cols, sizeof(int));
    }
    return matrix;
}

void free_matrix(int rows, int **matrix) {
    if (matrix != NULL) {
        for (int i = 0; i < rows; i++) {
            free(matrix[i]);
        }
        free(matrix);
    }
}

void copy_matrix(int **dest, int **src) {
    for (int i = 0; i < TETSIZE; i++) {
        for (int j = 0; j < TETSIZE; j++) {
            dest[i][j] = src[i][j];
        }
    }
}

int main() {
    printf("before loop\n");
    srand(time(NULL)); // Инициализация генератора случайных чисел
    printf("before loop\n");
    GameInfo_t gameInfo;
    initializeGame(&gameInfo);
    printf("before loop\n");
    gameLoop(&gameInfo);
    cleanupGame(&gameInfo); // Очистка памяти после завершения игры
    return 0;
}
