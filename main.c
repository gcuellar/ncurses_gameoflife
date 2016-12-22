#include <ncurses.h>
#include <string.h>

#define WIDTH 80
#define HEIGHT 25

void setupScreen();
void shutdownScreen();
void initGame(bool[WIDTH][HEIGHT]);
void printBoard(bool[WIDTH][HEIGHT]);
void updateBoard(bool[WIDTH][HEIGHT]);
int aliveNeighbours(int, int, bool[WIDTH][HEIGHT]);

int main(){

  bool board[WIDTH][HEIGHT];

  setupScreen();
  initGame(board);

  while(getch() != 'q'){
      printBoard(board);
      updateBoard(board);
      napms(500);
  }

  shutdownScreen();

	return 0;
}

void setupScreen(){

  /*
  * Default screen of 80x25
  */

  initscr();			/* Start curses mode*/
  noecho();
  nodelay(stdscr, TRUE);// Causes getch to be a non-blocking call
  mvprintw(10,80,"G");
  mvprintw(11,80,"A");
  mvprintw(12,80,"M");
  mvprintw(13,80,"E");
  mvprintw(15,80,"O");
  mvprintw(16,80,"F");
  mvprintw(18,80,"L");
  mvprintw(19,80,"I");
  mvprintw(20,80,"F");
  mvprintw(21,80,"E");

	refresh();			/* Print it on to the real screen */
}

void shutdownScreen(){
  endwin();
}

void initGame(bool board[WIDTH][HEIGHT]){
  int i,j;

  for (i=0;i<WIDTH;i++){
    for(j=0;j<HEIGHT;j++){
      board[i][j] = false;
    }
  }

  board[3][3] = true;
  board[4][3] = true;
  board[7][3] = true;
  board[8][3] = true;
  board[9][3] = true;
  board[6][4] = true;
  board[4][5] = true;

  board[8][8] = true;
  board[9][8] = true;
  board[8][9] = true;
  board[9][9] = true;

  board[12][12] = true;
  board[13][12] = true;
  board[12][13] = true;
  board[13][13] = true;

  board[23][3] = true;
  board[24][3] = true;
  board[27][3] = true;
  board[28][3] = true;
  board[29][3] = true;
  board[26][4] = true;
  board[24][5] = true;

  board[42][12] = true;
  board[43][12] = true;
  board[42][13] = true;
  board[43][13] = true;

  board[60][19] = true;
  board[60][20] = true;
  board[60][21] = true;
  board[59][21] = true;
  board[61][20] = true;
}

void printBoard(bool board[WIDTH][HEIGHT]){
  int i,j;

  for (i=0;i<WIDTH;i++){
    for(j=0;j<HEIGHT;j++){
      if(board[i][j]){
        mvprintw(j,i,"@");
      }else{
        mvprintw(j,i,"-");
      }
    }
  }
  refresh();
}

void updateBoard(bool board[WIDTH][HEIGHT]){
  bool result[WIDTH][HEIGHT];
  int i,j;

  for (i=0;i<WIDTH;i++){
    for(j=0;j<HEIGHT;j++){

      int nAlive = aliveNeighbours(i,j,board);

      if(board[i][j]){ // Is alive
        if( nAlive == 2 || nAlive == 3 ){
          // Live
          result[i][j] = true;
        }else{
          // Dead
          result[i][j] = false;
        }
      }else{ // Is dead
        if(nAlive == 3){
          // Live
          result[i][j] = true;
        }else{
          // Dead
          result[i][j] = false;
        }
      }
    }
  }

  memcpy(board,result, WIDTH*HEIGHT*sizeof(bool));
}

int aliveNeighbours(int x, int y, bool board[WIDTH][HEIGHT]){
  int counter = 0;

  if(x-1 >= 0 && board[x-1][y]){
    counter++;
  }

  if(x-1 >= 0 && y-1 >= 0 && board[x-1][y-1]){
    counter++;
  }

  if(x-1 >= 0 && y+1 < HEIGHT && board[x-1][y+1]){
    counter++;
  }

  if(x+1 < WIDTH && board[x+1][y]){
    counter++;
  }

  if(x+1 < WIDTH && y-1 >= 0 && board[x+1][y-1]){
    counter++;
  }

  if(x+1 < WIDTH && y+1 < HEIGHT && board[x+1][y+1]){
    counter++;
  }

  if(y-1 >= 0 && board[x][y-1]){
    counter++;
  }

  if(y+1 < HEIGHT && board[x][y+1]){
    counter++;
  }

  return counter;
}
