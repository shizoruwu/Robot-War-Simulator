/*********** | *********** | *********** |
Program: RobotWarSimulator.cpp
Course: CCP6124 Object Oriented Programming and Data Structures
Trimester: 2510
Name: LEE YUNG YAU | 
Id: 242UC244NX | 
Lecture Section: TC3L
Tutorial Section: T11L
Email: lee.yung.yau@student.mmu.edu.my | 
Phone: +60102998918 | 
*********** | *********** | ***********/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <sstream>
#include <memory>

using namespace std;

// Foward Declaration
class Battlefield;

// Base Abstract Class
class Robot {
  protected:
    string name;
    int x;
    int y;
    int health;

  public:
    // Virtual destructor
    virtual ~Robot() {}

    virtual void setShells(int shell) = 0;

    virtual int getShells() = 0;

    virtual void perform(class Battlefield* field, ofstream& logfile) = 0;

    // When damage took
    void damage(int width, int row);

    // Getters   
    virtual string getType() = 0;

    // Check if robot is alive
    bool isAlive() const { 
      return health > 0;
    }

    string getName() const { 
      return name; 
    }

    int getX() const { 
      return x; 
    }

    int getY() const { 
      return y; 
    }

    int getHealth() const{ 
      return health; 
    }
};

// Basic Abstract subclasses ( Interface )
class MovingRobot : virtual public Robot{
  public:
    virtual void move(int dx, int dy, ofstream& logfile, Battlefield* field) = 0;
  };
  
class SeeingRobot : virtual public Robot{
  public:
    virtual void look(ofstream& logfile, Battlefield* field) = 0;
};
  
class ShootingRobot : virtual public Robot{
  public:
    virtual void fire(int dx, int dy, ofstream& logfile, Battlefield* field) = 0;
};
  
class ThinkingRobot : virtual public Robot{
  public:
    virtual void think(ofstream& logfile) = 0;
};

// Generic Robot Class
class GenericRobot : public MovingRobot, public SeeingRobot, public ShootingRobot, public ThinkingRobot{
  protected:  
    int shells;
  
  public:
    // Constructor
    GenericRobot(){};

    GenericRobot(string name, int x, int y, int health) {
      this->name = name;
      this->x = x;
      this->y = y;
      this->health = health;

      shells = 10;
    }
    
    // Virtual Function Override
    void think(ofstream& logfile) override;

    void look(ofstream& logfile, Battlefield* field) override;

    void fire(int dx, int dy, ofstream& logfile, Battlefield* field) override;

    void move(int dx, int dy, ofstream& logfile, Battlefield* field) override;

    // Perform action function
    void perform(Battlefield* field, ofstream& logfile) override;

    // Setter Function
    void setShells(int shell) override {
      shells = shell;
    }

    // Getter Function
    string getType() override {
      return "GenericRobot";
    }

    int getShells() override {
      return shells;
    }
};

// Battlefield Class
class Battlefield{
  private:
    int width;
    int height;
    int totalSteps;
    int robotNum;
    list<Robot*> robots;

  public:
    // Battlefield Constructor
    Battlefield(){
      width = height = totalSteps = 0;
      srand(time(0));
      loadConfig();
    }
    
    // Grid Display Function
    void displayGrid(ofstream& logfile,Robot* robot);

    // Read Robot Line to Abstract Data
    void readRobotLine(const string& line);
    
    // Load Config File Settings
    void loadConfig(const string& filename = "config.txt"); 
    
    // Return robot ptr IF at x,t location
    Robot* getRobotAt(int x, int y);
    
    // Simulation
    void simulate();
    
    // Getter methods
    int getWidth() const { 
      return width; }

    int getHeight() const {
      return height; }

    int getTotalSteps() const {
      return totalSteps; }

    // friend class GenericRobot
    friend GenericRobot;
};  

// Upgrade Class
// Hide Bot -> MOVING
class HideBot : public GenericRobot{
  private:
    int hideChance;
  public:
    // Constructor
    HideBot(Robot* robot){
      x = robot->getX();
      y = robot->getY();
      health = robot->getHealth();
      shells = robot->getShells();

      hideChance = 3;
    }
    // Hide Function

    // Override Move Function with Hide Chance
};

// Jump Bot -> MOVING
class JumpBot : public GenericRobot{
  private:
    int JumpChance;
  public:
    // Constructor
    JumpBot(Robot* robot){
      x = robot->getX();
      y = robot->getY();
      health = robot->getHealth();
      shells = robot->getShells();

      JumpChance = 3;
    }

    // Jump Function

    // Override Move Function with Chance to Jump
};

// Long Shot Bot -> SHOOTING
class LongShotBot : public GenericRobot{
  public:
    // Constructor
    LongShotBot(Robot* robot){
      x = robot->getX();
      y = robot->getY();
      health = robot->getHealth();
      shells = robot->getShells();
    }

    // Override Fire Function to Fire with 3 Unit Distance
};

// Semi Auto Bot -> SHOOTING
class SemiAutoBot : public GenericRobot{
  public:
    // Constructor
    SemiAutoBot(Robot* robot){
      x = robot->getX();
      y = robot->getY();
      health = robot->getHealth();
      shells = robot->getShells();
    }

    // Override Fire Function to Fire 3 Times 
};

// Thirty Shot Bot -> SHOOTING
class ThirtyShotBot : public GenericRobot{
  public:
    // Constructor
    ThirtyShotBot(Robot* robot){
      x = robot->getX();
      y = robot->getY();
      health = robot->getHealth();

      shells = 30;
    }
};

// Scout Bot -> SEEING
class ScoutBot : public GenericRobot{
  public:
    // Constructor
    ScoutBot(Robot* robot){
      x = robot->getX();
      y = robot->getY();
      health = robot->getHealth();
      shells = robot->getShells();
    }

    // Override Look Function to Show Whole Battlefield
};

// Track Bot -> SEEING
class TrackBot : public GenericRobot{
  public:
  // Constructor
  TrackBot(Robot* robot){
    x = robot->getX();
    y = robot->getY();
    health = robot->getHealth();
    shells = robot->getShells();
  }

  // Add a Track Function to Track Robot
};


// Declaration for Robot Base Abstract Class
void Robot::damage(int width, int row){
  // Robot Damages, Health -1
  health--;

  int tempx = (rand() % width) + 1; 
  int tempy = (rand() % row) + 1;

  x = tempx;
  y = tempy;
}

// Declaration for GenericRobot Perform function
void GenericRobot::think(ofstream& logfile) {
  cout << name << " is thinking...\n";
  logfile << name << " is thinking...\n";
}

void GenericRobot::move(int dx, int dy, ofstream& logfile, Battlefield* field) {
  if (!field->getRobotAt(x+dx, y+dy)) {
    x += dx;
    y += dy;

    cout << name << " moves to [" << x << "," << y << "]\n";
    logfile << name << " moves to [" << x << "," << y << "]\n";    
  } 
  else {
    cout << name << " moves to [" << x << "," << y << "]\n";
    logfile << name << " moves to [" << x << "," << y << "]\n";

    // Coordinates is occupied
    cout << "That coordinate is occupied, failed to move.\n"; 
    logfile << "That coordinate is occupied, failed to move.\n"; 
  }
}

void GenericRobot::look(ofstream&logfile, Battlefield* field) {
  cout << name << " looks at [" << x << "," << y << "]\n";
  logfile << name << " looks at [" << x << "," << y << "]\n";

  for (int i=-1; i<=1; ++i){
    int dy = y + i;

    for (int j=-1; j<=1; ++j){
      int dx = x + j;

      if (dx <= 0 || dy <= 0 || dx > field->getWidth() || dy > field->getHeight()) {
        cout << " # ";
        logfile << " # ";
        continue;
      }

      // Get Robot if at (x,y)
      Robot* other = field->getRobotAt(dx, dy);

      if (other && other != this) {
        cout << " " << other->getName()[0] << " ";
        logfile << " " << other->getName()[0] << " ";
      } 
      else if (dx == x && dy == y) {
        cout << " " << name[0] << " ";
        logfile << " " << name[0] << " ";
      } 
      else {
        cout << " . ";
        logfile << " . ";
      }
    }
    
    cout << "\n";
    logfile << "\n";
  }
}

void GenericRobot::fire(int dx, int dy, ofstream& logfile, Battlefield* field) {
  cout << name << " fires at [" << x+dx << "," << y+dy << "] ";
  logfile << name << " fires at [" << x+dx << "," << y+dy << "] ";
  shells--;  
     
  Robot* target = field->getRobotAt(x + dx, y + dy);
  if ((rand() % 100) < 70) {
    cout << "- Hit! " << "\n";
    logfile << "- Hit! " << "\n";

    if (target && target != this && shells > 0) {
      cout << "Target Hit! " << endl;
      logfile << "Target Hit! " << endl;
          
      target->damage(field->getWidth(),field->getHeight());
      target->setShells(10);

      cout << target->getName() << " was hit! Remaining HP: " << target->getHealth() << "\n Target is: " << (target->isAlive() ? "alive" : "dead") << "\n";
      logfile << target->getName() << " was hit! Remaining HP: " << target->getHealth() << "\n Target is: " << (target->isAlive() ? "alive" : "dead") << "\n";

      if (target->getHealth() == 0){
        field->robots.remove(target);
      }
    }
  }
  else {
    cout << "- Missed! " << endl;
    logfile << "- Missed! " << endl;
  }
}

void GenericRobot::perform(Battlefield* field, ofstream& logfile) {
  // Perform THINK
  think(logfile);

  // Perform LOOK on own coordinates
  look(logfile, field);

  // rand x,y to FIRE
  int dx = rand() % 3 - 1;
  int dy = rand() % 3 - 1;
  if (x + dx <= 0 || x + dx >= field->getWidth()) {
    dx = 0;
  }
  if (y + dy <= 0 || y + dy >= field->getHeight()) {
    dy = 0;
  }
  
  // FIRE if not on self location
  if (dx != 0 && dy != 0){
    fire(dx, dy, logfile, field);
  }

  // rand x,y to MOVE
  dx = rand() % 3 - 1;
  dy = rand() % 3 - 1;
  if (x + dx <= 0 || x + dx >= field->getWidth()) {
    dx = 0;
  }
  if (y + dy <= 0 || y + dy >= field->getHeight()) {
    dy = 0;
  }

  // MOVE if not on self location
  if (dx != 0 && dy != 0){
    move(dx, dy, logfile, field);
  }

  // Check if shells = 0
  if (shells == 0 && isAlive()) {
    cout << name << " has exhausted all shells and self-destructs!\n";
    logfile << name << " has exhausted all shells and self-destructs!\n";
    damage(field->getWidth(),field->getHeight());

    cout << "Remaining HP: " << getHealth() << "\n";
    logfile << "Remaining HP: " << getHealth() << "\n";

    shells = 10;
  }
}

// Declaration for Battlefield Class
void Battlefield::displayGrid(ofstream& logfile, Robot* robot) { 
  vector<vector<char>>grid(height, vector<char>(width, '.'));

  int rx = robot->getX();
  int ry = robot->getY();
          
  if (rx >= 1 && rx <= width && ry >= 1 && ry <= height){
    grid[ry-1][rx-1] = robot->getName()[0];
      
    // Top Border
    cout << "   ";
    logfile << "   ";
    for (int col = 1; col < width+1; ++col) {
      if (col<10){
        cout << col << "  ";
        logfile << col << "  ";
      }
      else{
        cout << col << " ";
        logfile << col << " ";
      }
    }
    cout << "\n";
    logfile << "\n";

    // Display Battlefield
    for (int row = 0; row < height; ++row) {
      if (row+1 >= 10){
        cout << (row+1) << " ";
        logfile << (row+1) << " ";
      }
      else{
        cout << (row+1) << "  ";
        logfile << (row+1) << "  ";
      }

      for (int col = 0; col < width; ++col) {
        cout << grid[row][col] << "  " ;
        logfile << grid[row][col] << "  " ;
      }
      cout << "\n";
      logfile << "\n";
    }
  }
}

void Battlefield::readRobotLine(const string &line) {
  stringstream ss(line);
  string type, name, xStr, yStr;
  ss >> type >> name >> xStr >> yStr;
        
  bool random = (xStr == "random" || yStr == "random");
  int x = random ? rand() % width : stoi(xStr);
  int y = random ? rand() % height : stoi(yStr);

  if (type == "GenericRobot"){
    robots.push_back(new GenericRobot(name, x, y , 3));
  }
}

void Battlefield::loadConfig(const string &filename) {
  ifstream file(filename);
  if (!file.is_open()) {
    cerr << "Error: Could not find config.txt file " << filename << endl;
    exit(1);
  }
    
  string line;
  while (getline(file, line)) {
    if (line.empty()) 
      continue;
    
    if (line.find("M by N :") != string::npos) {
      stringstream ss(line.substr(8));
      ss >> width >> height;
      vector<vector<char>>grid(height, vector<char>(width, '.'));
    }
    else if (line.find("steps:") != string::npos) {
      stringstream ss(line.substr(6));
      ss >> totalSteps;
    }
    else if (!line.find("robots:")) {
      stringstream ss(line.substr(7));
      ss >> robotNum;
    }
    else {
      readRobotLine(line);
    }
  }

  file.close();
} 

Robot* Battlefield::getRobotAt(int x, int y) {
  for (auto r : robots) {
    // IF Robot avalible
    if (r->isAlive() && r->getX() == x && r->getY() == y)
      return r;
  }

  // ELSE return nullptr
  return nullptr;
}

void Battlefield::simulate() {
  ofstream logfile("simulation_log.txt");
  
  Robot* currRobot = nullptr;
  for (int step = 0; step < totalSteps && robots.size() > 1;) {
    cout << "\n --- Turn: " << step + 1 << " --- \n";
    logfile << "\n --- Turn: " << step + 1 << " --- \n";

    currRobot = robots.front(); 
    displayGrid(logfile,currRobot);
    robots.pop_front();

    if (currRobot->isAlive()) {

      // Perform robot action
      currRobot->perform(this, logfile);

      if (currRobot->getHealth() > 0){
        robots.push_back(currRobot);
      }
    } 
    
    ++step;
  }

  if (robots.size() == 1){
    cout << "\n" << robots.front()->getName() << " is the Winner! \n\n" ;
    logfile << "\n" << robots.front()->getName() << " is the Winner! \n\n" ;
  } 
  else {
    cout << "\nThere is no winner, maximum turn has reached. \n\n" ;
    logfile << "\nThere is no winner, maximum turn has reached. \n\n" ;
  }

  logfile.close();
}


// MAIN
int main() {
  // Create Object
  Battlefield simulation;

  // Run Simulation
  simulation.simulate();

  cout << "Simulation complete. All memory should clean up now." << endl;
  return 0;
}