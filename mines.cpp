#include "mines.h"


void setTextColor(int colorCode) {
    std::cout << "\033[38;5;" << colorCode << "m";
}

bool Cell::getIsMine() const {
    return m_is_mine;
}

bool Cell::getIsOpen() const {
    return m_is_open;
}

void Cell::setOpen(bool is_open) {
    m_is_open = is_open;
}

char Cell::getValue() const {
    return m_value;
}

void Cell::setMine(bool is_mine) {
    m_is_mine = is_mine;
}

void Cell::setValue(char value) {
    m_value = value;
}


bool Cell::getIsNow() const {
    return m_is_now;
}


void Cell::setNow(){
    m_is_now = !(m_is_now);  
}


Board::Board(short width,short height,short mines){
    m_height = height;
    m_width = width;
    m_mines = mines;
    m_grid = new Cell*[m_height];
    for(int i = 0;i < m_height ; ++i){
        m_grid[i] = new Cell[m_width];
    }
    m_is_lose = false;
}


bool Board::isValidPosition(int row,int col) {
    if( (row >= 0 && row < m_height && col >= 0 && col < m_width) ){
        return true;
    }
    return false;
}

void Board::calculateMine(short x, short y){
     int count = 0 ;
     for(int a = x - 1;  a <= x + 1 ; ++a){
         for(int b = y - 1; b <= y + 1 ; ++b){
             if(isValidPosition(a,b)){
                 if(m_grid[a][b].getIsMine()){
                     ++count;
                 }
             }
         }
     }
     m_grid[x][y].setValue(count + '0');
}


void Board::createBoard() {
    int row = 0;
    int col = 0;

    for (int i = 0 ; i < m_mines ; ++i) {
        row = rand() % m_height;
        col = rand() % m_width;
        if (m_grid[row][col].getIsMine()) {
            --i;
            continue;
        }
        m_grid[row][col].setMine(true);
        m_grid[row][col].setValue('*');
    }
     
    for(int i = 0 ; i < m_height ; ++i){
        for(int j =0 ; j < m_width ; ++j){
            if(m_grid[i][j].getIsMine()) {
                continue;
            }
           calculateMine(i,j) ; 
        }
    }
}


void Board::openAction(short x, short y) {
    if(!(isValidPosition(x,y)) || m_grid[x][y].getIsOpen()){
        return ;
    }
    m_grid[x][y].setOpen(true);
    if(m_grid[x][y].getIsMine()){
        m_is_lose = true;
        return;
    }
    if(m_grid[x][y].getValue() > '0' && m_grid[x][y].getValue() < '9'){
        return;
    }
    for(int i = x - 1; i <= x + 1 ; ++i){
        for(int j = y - 1; j <= y + 1 ; ++j){
            openAction(i,j);
        }
    }

}

bool Board::checkLose() {
    if (m_is_lose) {
        return true;
    }
    return false;
}

bool Board::checkWin() {
    for (int i = 0; i < m_height; ++i){
        for (int j = 0; j < m_width; ++j) {
            if (!(m_grid[i][j].getIsOpen()) && !(m_grid[i][j].getIsMine())) {
                return false;
            }
        }
    }
    return true;
}


void Board::display() {
    for (int i = 0; i < m_height; ++i) {
        for (int j = 0; j < m_width; ++j) {
            if (m_grid[i][j].getIsOpen()) {
                if(m_grid[i][j].getIsNow())
                {
                    //setTextColor(45);
                    std::cout << m_grid[i][j].getValue();
                    //setTextColor(0);
                    std::cout << " "; 
                }
                else
                {
                    std::cout << m_grid[i][j].getValue() << " ";
                } 
                 
            } else {
                if(m_grid[i][j].getIsNow())
                {
                    setTextColor(45);
                    std::cout << "\u25A1"; 
                    setTextColor(0);
                    std::cout<< " "; 
                }
                else
                {
                    std::cout << "\u25A1 ";
                } 
            }
        }
        std::cout << std::endl;
    }
    std::cout << "Enter 'w', 'a', 's', 'd' to move \n";
    std::cout << "Enter 'enter' to select";
}



bool Board::moveNow(short& x, short& y){
    
    char input =  getchar();
    m_grid[x][y].setNow();
    switch (input) {
         case 'w': {
            if(x == 0) {
                if(y == 0)
                {
                    y = m_width - 1;
                    x = m_height - 1;
                }
                else
                {
                    --y;
                    x = m_height - 1;
                }
            } else {
                --x;
            }
            m_grid[x][y].setNow();
            return false;
        }
        case 'a': {
           if(y == 0) {
                if(x == 0) {
                    y = m_width - 1;
                    x = m_height - 1;
                } else {
                    --x;
                    y = m_width - 1;
                }
            } else {
                --y;
            }
            m_grid[x][y].setNow();
            return false;
        }
        case 's': {
            if(x == m_height - 1) {
                if(y == m_width - 1) {
                    y = 0;
                    x = 0;
                } else {
                    ++y;
                    x = 0;
                }
            } else {
                ++x;
            }
            m_grid[x][y].setNow();
            return false;
        }
        case 'd': {
           if(y == m_width - 1) {
                if(x == m_height - 1) {
                    y = 0;
                    x = 0;
                } else {
                    ++x;
                    y = 0;
                }
            } else {
                ++y;
            }
            m_grid[x][y].setNow();
            return false;
        }
        case '\n': { // Enter
            return true;
        }
    }   
    return false;
}



//Game class functions

Game::Game(short width, short height, short countMine) : board(width, height, countMine), gameOver(false),is_lose(false) {
    board.createBoard();
}

void Game::play() {
    short row = 0;
    short col = 0;
    while (!gameOver) {   
        system("clear");
        board.display();
        bool flag = inputAction(row, col);
        if(flag)
        {
            board.openAction(row, col);
            gameOver = board.checkWin() || board.checkLose();
            is_lose = board.checkLose();
        }
    }
    display(!is_lose);
}

bool Game::inputAction(short& row, short& col) {
    return board.moveNow(row, col);
}

void Game::display(bool flag) {
    if (flag) {
        setTextColor(32);
        std::cout << "\n    YOU WIN" << std::endl;
    }
    else {
        setTextColor(31); // Set text color to red
        std::cout << "\n    YOU LOSE" << std::endl;
    }
}

void Game::setTextColor(int colorCode) {
    std::cout << "\033[20;5;" << colorCode << "m"; // 38;5;colorCode sets text color
}

// Global variable for storing old terminal settings
struct termios oldTermios;

//Function to restore old terminal settings
void resetInputMode() {
    tcsetattr(STDIN_FILENO, TCSANOW, &oldTermios);
}

// Signal handler (eg SIGINT for Ctrl+C)
void handleSignal(int signal) {
    resetInputMode();
    exit(0);
}

// Function to set a new input mode
void setInputMode() {
    struct termios t;
    // Save current settings
    tcgetattr(STDIN_FILENO, &oldTermios);
    t = oldTermios;

    // Disable canonical mode and echo
    t.c_lflag &= ~(ICANON | ECHO);

    // Setting up new settings
    tcsetattr(STDIN_FILENO, TCSANOW, &t);

    // Registering a signal handler
    signal(SIGINT, handleSignal); // SIGINT triggered when Ctrl+C
}

