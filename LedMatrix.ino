//5x7_LED Matrix Snake Game

//Input Pins
const int up = 2;
const int down = 3;
const int left = 4;
const int right = 5;

//LED Matrix Size
const int rowSize = 5;
const int columnSize = 7;

//Matrix Pins
const int row[rowSize] = {9, 8, 7, 6, 10};
const int column[columnSize] = {11, 12, A0, A1, A2, A3, A4};

boolean frame[rowSize][columnSize];

const int gameIntervall = 200; //Snake moves every 200ms
const int snakeStartX = 2;
const int snakeStartY = 3;
const int snakeStartLength = 1;
unsigned long lastGameInterrupt = 0;
int snakeLength;
int snakeX[rowSize*columnSize];
int snakeY[rowSize*columnSize];
int xDir;
int yDir;
int foodX;
int foodY;

void setup() { 
 pinMode(up, INPUT_PULLUP);
 pinMode(down, INPUT_PULLUP);
 pinMode(left, INPUT_PULLUP);
 pinMode(right, INPUT_PULLUP);
 
 for(int i = 0; i < rowSize; i++) {
  pinMode(row[i], OUTPUT);
  digitalWrite(row[i], HIGH); //Row off
 }
 for(int i = 0; i < columnSize; i++) {
  pinMode(column[i], OUTPUT);
  digitalWrite(column[i], LOW); //Column off
 }
 startSnake();
}

void loop() {
  snake();
}

void snake() {
 readInput(); 
 moveSnake();
 checkFoodCollision();
 checkWallCollision();
 checkSelfCollision();
 drawSnake();
 display();
}

void readInput() {
  if (!digitalRead(up)) {
    xDir = -1; yDir = 0;
  }
  if (!digitalRead(down)) {
    xDir = 1; yDir = 0;
  }
  if (!digitalRead(left)) {
    yDir = -1; xDir = 0;
  }
  if (!digitalRead(right)) {
    yDir = 1; xDir = 0;
  }
}

void moveSnake() {
  if (millis() - lastGameInterrupt > gameIntervall) {
    for (int i = snakeLength; i > 0; i--) {
      snakeX[i] = snakeX[i-1];
      snakeY[i] = snakeY[i-1];
    }
    snakeX[0] += xDir;
    snakeY[0] += yDir;
    lastGameInterrupt = millis();
  }
}

void drawSnake() {
  clearPixel(snakeX[snakeLength],snakeY[snakeLength]);
  drawPixel(snakeX[0],snakeY[0]);
}

void checkWallCollision() {
  if (snakeX[0] < 0 || snakeX[0] > rowSize-1) {
    startSnake();
  }
  if (snakeY[0] < 0 || snakeY[0] > columnSize-1) {
    startSnake();
  }
}

void checkSelfCollision() {
  if (snakeLength > snakeStartLength) {
    for (int i = 1; i <= snakeLength; i++) {
      if (snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i]) {
        startSnake();
      }
    } 
  }
}

void checkFoodCollision() {
  if (snakeX[0] == foodX && snakeY[0] == foodY) {
    snakeLength ++;
    dropFood();
  }
}

void startSnake() {
 clearFrame();
 xDir = 0;
 yDir = 0;
 snakeLength = snakeStartLength;
 snakeX[0] = snakeStartX;
 snakeY[0] = snakeStartY;
 dropFood();
}

void dropFood() {
 do {
 foodX = random(0,rowSize-1);
 foodY = random(0,columnSize-1);
 } while (frame[foodX][foodY] == 1);
 drawPixel(foodX,foodY);
}

void display() {
  // display frame buffer
  for(int x = 0; x < rowSize; x++) {
      for(int y = 0; y < columnSize; y++) {
        digitalWrite(column[y], frame[x][y]);
      }
    digitalWrite(row[x], LOW);
    delay(2);
    digitalWrite(row[x], HIGH);
  }
}

void drawPixel(int x, int y) {
  frame[x][y] = 1;
}

void clearPixel(int x, int y) {
  frame[x][y] = 0;
}

void clearFrame() {
  for(int x = 0; x < rowSize; x++) {
    for(int y = 0; y < columnSize; y++) {
      clearPixel(x,y);
    }
  }
}
