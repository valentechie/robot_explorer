// Simulation of a Robot Explorer on a Board with Obstacles

// Author: Valentina (valentechie)
// Date: 31/01

#include <iostream>
#include <string>
#include <fstream>
#include <cassert>

struct Board {
    char** board;
    int rows;
    int columns;
};

struct Robot {
    int Rx;
    int Ry;
};

struct Obstacle {
    int row;
    int column;
};

void readFile(const std::string&, int&, int&, int&, int&, Obstacle*&, int&);
void createBoard(Board&);
void displayBoard(Board&);
bool validPosition(Board&, int, int);
bool possibleMovement(Board&, Robot&);
void moveRobot(Board&, Robot&);
int currentState(Board&, char);
void releaseMemory(Board&, Obstacle*);

int main() {
    Obstacle* obstacles = nullptr; 
    int num_obstacles = 0;
    Board mymap;
    int n_rows = 0, m_columns = 0, robot_rows = 0, robot_columns = 0;
    
    std::string archive = "input.txt";
    readFile(archive, n_rows, m_columns, robot_rows, robot_columns, obstacles, num_obstacles);
    
    mymap.rows = n_rows;
    mymap.columns = m_columns;

    createBoard(mymap);
    
    mymap.board[robot_rows][robot_columns] = 'R';
    Robot robot = {robot_rows, robot_columns};
    
    for (int i = 0; i < num_obstacles; i++) {
        if (obstacles[i].row != robot.Rx || obstacles[i].column != robot.Ry) {
            mymap.board[obstacles[i].row][obstacles[i].column] = '#';
        } else {
            std::cerr << "Error: An obstacle cannot be in the same position as the robot.\n";
            releaseMemory(mymap, obstacles);
            return 0;
        }
    }

    while (possibleMovement(mymap, robot)) {
        displayBoard(mymap);
        std::cout << "Occupied cells: " << currentState(mymap, '*') << std::endl;
        std::cout << "Free cells: " << currentState(mymap, '.') << std::endl;

        std::cout << "Press Enter to continue . . .";
        std::cin.get();
        system("clear"); // or "cls" for windows

        moveRobot(mymap, robot);
    }

    displayBoard(mymap);
    std::cout << "Occupied cells " << currentState(mymap, '*') << std::endl;
    std::cout << "Free cells: " << currentState(mymap, '.') << std::endl;

    std::ofstream write_output ("output.txt");
    assert(write_output.is_open());
    for (int i = 0; i < mymap.rows; i++) {
        for (int j = 0; j < mymap.columns; j++) {
            write_output << mymap.board[i][j] << " ";
        }
        write_output << std::endl;
    }

    write_output << "Occupied cells: " << currentState(mymap, '*') << std::endl;
    write_output << "Free cells: " << currentState(mymap, '.') << std::endl;
    write_output.close();
    
    releaseMemory(mymap, obstacles);
    return 0;
}

void readFile(const std::string& archive, int& n_rows, int& m_columns, int& robot_rows, int& robot_columns, Obstacle*& obstacles, int& num_obstacles) {
    std::string lines;
    std::ifstream read_file(archive);
    assert(read_file.is_open());

    int counter = 0;
    while (std::getline(read_file, lines)) {
        counter++;
   
        if(counter == 1) {
            std::string find = ",";
            std::size_t position = lines.find(find);

            std::string line1_right = lines.substr(0, position);
            std::string line1_left = lines.substr(position + 1);

            if (stoi(line1_right) < 0 || stoi(line1_left) < 0) {
                std::cerr << "Error: The board dimensions must be greater than zero." << std::endl;
                return;
            }

            n_rows = stoi(line1_right);
            m_columns = stoi(line1_left);
        }

        if(counter == 2) {
            std::string find = ",";
            std::size_t position = lines.find(find);

            std::string line2_right = lines.substr(0, position);
            std::string line2_left = lines.substr(position + 1);

            robot_rows = stoi(line2_right);
            robot_columns = stoi(line2_left);
           
            if (robot_rows < 0 || robot_rows >= n_rows || robot_columns < 0 || robot_columns >= m_columns) {
                std::cerr << "Error: The coordinates of the robot are outside the board limits." << std::endl;
                return;
            }
        }
   
        if(counter >= 3) {
            std::string find = ",";
            std::size_t position = lines.find(find);

            std::string line3_right = lines.substr(0, position);
            std::string line3_left = lines.substr(position + 1);

            int obstacle_row = stoi(line3_right);
            int obstacle_column = stoi(line3_left);

            Obstacle* temp = new Obstacle[num_obstacles + 1];
            for (int i = 0; i < num_obstacles; ++i) {
                temp[i] = obstacles[i];
            }

            temp[num_obstacles].row = obstacle_row;
            temp[num_obstacles].column = obstacle_column;

            delete[] obstacles;
            obstacles = temp;
            num_obstacles++;
        }
    }
    read_file.close();
}

void createBoard(Board& map) {
    map.board = new char*[map.rows];
    for(int i = 0; i < map.rows; i++) {
        map.board[i] = new char[map.columns];
    }

    for(int i = 0; i < map.rows; i++) {
        for(int j = 0; j < map.columns; j++) {
            map.board[i][j] = '.';
        }
    }
}

void displayBoard(Board& map) {
    for(int i = 0; i < map.rows; i++) {
        for(int j = 0; j < map.columns; j++) {
            std::cout << map.board[i][j] << " ";
        }
        std::cout << "\n";
    }
}

bool validPosition(Board& map, int row, int column) {
    if (row < 0 || row >= map.rows || column < 0 || column >= map.columns) {
        return false;
    }

    if (map.board[row][column] == '*' || map.board[row][column] == '#' || map.board[row][column] == 'R') {
        return false;
    }
    return true;
}

bool possibleMovement(Board& map, Robot& robot) {
    return (validPosition(map, robot.Rx - 1, robot.Ry) || validPosition(map, robot.Rx + 1, robot.Ry) ||  
            validPosition(map, robot.Rx, robot.Ry - 1) || validPosition(map, robot.Rx, robot.Ry + 1) ||  
            validPosition(map, robot.Rx - 1, robot.Ry - 1) || validPosition(map, robot.Rx - 1, robot.Ry + 1) ||
            validPosition(map, robot.Rx + 1, robot.Ry - 1) || validPosition(map, robot.Rx + 1, robot.Ry + 1));
}

void moveRobot(Board& map, Robot& robot) {
    int new_row = robot.Rx;
    int new_column = robot.Ry;
   
    int movements[8][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};
   
    for (int i = 0; i < 8; i++) {
        new_row = robot.Rx + movements[i][0];
        new_column = robot.Ry + movements[i][1];
       
        if (validPosition(map, new_row, new_column)) {
            map.board[robot.Rx][robot.Ry] = '*';
           
            robot.Rx = new_row;
            robot.Ry = new_column;
            map.board[robot.Rx][robot.Ry] = 'R';
            return;
        }
    }
}

int currentState(Board& map, char sign) {
    int counter = 0;
    for(int i = 0; i < map.rows; i++) {
        for(int j = 0; j < map.columns; j++) {
            if (map.board[i][j] == sign) {
                counter++;
            }
        }
    }
    return counter;
}

void releaseMemory(Board& map, Obstacle* obstacles) {
    if (map.board != nullptr) {
        for (int i = 0; i < map.rows; i++) {
            if (map.board[i] != nullptr) {
                delete[] map.board[i];
            }
        }
        delete[] map.board;
        map.board = nullptr;
    }
    
    delete[] obstacles;
}
