#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define GRID_SIZE 33

#define ANSI_RESET   "\033[0m"
#define ANSI_GRAY    "\033[90m"
#define ANSI_BLUE    "\033[34m"
#define ANSI_GREEN   "\033[32m"
#define ANSI_YELLOW  "\033[33m"
#define ANSI_MAGENTA "\033[35m"
#define ANSI_RED     "\033[31m"

FILE *csv_file = NULL;
long iteration = 0;

int avalanche_size = 0;
int avalanche_duration = 0;
int active_row = -1;
int active_col = -1;
int grid[GRID_SIZE][GRID_SIZE];

void sleep_ms(long ms)
{
  struct timespec ts;
  ts.tv_sec=ms/1000;
  ts.tv_nsec=(ms%1000)*1000000L;

  nanosleep(&ts, NULL);
}

void init_grid(void)
{
  int i, j;

  for(i=0; i<GRID_SIZE; i++){
    for (j=0; j<GRID_SIZE; j++){
      grid[i][j] = 0;
    }
  }
}

void print_grid(void)
{
  int i, j;
  const char *color;

  for(i=0; i<GRID_SIZE; i++){
    for (j=0; j<GRID_SIZE; j++){
      if (i == active_row && j == active_col){
        color = ANSI_RED;
      } else {
        switch (grid[i][j]) {
          case 0: color = ANSI_GRAY; break;
          case 1: color = ANSI_BLUE; break;
          case 2: color = ANSI_GREEN; break;
          case 3: color = ANSI_YELLOW; break;
          default: color = ANSI_MAGENTA; break;
        }
      }

      printf("%s%2d%s ", color, grid[i][j], ANSI_RESET);
    }
    printf("\n");
  }
}

void add_grain(int row, int col)
{
  if (row < 0 || row >= GRID_SIZE){
    return;
  }
  if (col < 0 || col >= GRID_SIZE){
    return;
  }
  grid[row][col]++;
}

int has_unstable(void)
{
  int i, j;

  for(i=0; i<GRID_SIZE; i++){
    for(j=0; j<GRID_SIZE; j++){
      if (grid[i][j]>=4){
        return 1;
      }
    }
  }
  return 0;
}

void topple_cell(int row, int col)
{
  if (grid[row][col]<4) {
    return;
  }

  avalanche_size++;

  grid[row][col] -= 4;
  if (row > 0){
    grid[row-1][col]++;
  }
  if (row < GRID_SIZE-1){
    grid[row+1][col]++;
  }
  if (col > 0){
    grid[row][col-1]++;
  }
  if (col < GRID_SIZE-1){
    grid[row][col+1]++;
  }
}

void relax(void)
{
  int i, j;
  while(has_unstable()){
    for (i=0; i<GRID_SIZE; i++){
      for (j=0; j<GRID_SIZE; j++){
        if (grid[i][j] >= 4){
          topple_cell(i,j);
        }
      }
    }
  }
}

int relax_step(void)
{
    int i, j;

    for (i = 0; i < GRID_SIZE; i++) {
        for (j = 0; j < GRID_SIZE; j++) {
            if (grid[i][j] >= 4) {
                active_row = i;
                active_col = j;
                topple_cell(i, j);
                return 1;
            }
        }
    }

    return 0;
}

void add_random_grain(void)
{
  int row;
  int col;
  row = rand() % GRID_SIZE;
  col = rand() % GRID_SIZE;

  add_grain(row,col);
}

void simulate_step(void)
{
    add_random_grain();
    relax();
}

void render_stats(void)
{
  printf("\033[%d;1H", GRID_SIZE + 2);
  printf("Avalanche size: %d | Duration: %d     ",
         avalanche_size, avalanche_duration);
}

int main(void)
{
  srand(time(NULL));

  csv_file = fopen("avalanches.csv", "w");
  if (!csv_file) {
    perror("fopen");
    return 1;
  }
  fprintf(csv_file, "iteration,size,duration\n");

  init_grid();
  
  printf("\033[2J"); // clean
  printf("\033[H"); // move cursor 
  
  while (1){
    avalanche_size = 0;
    avalanche_duration = 0;

    add_random_grain();

    while(relax_step()){
      avalanche_duration++;
      printf("\033[H"); // move cursor 
      print_grid();
      render_stats();
      sleep_ms(10);
    }
    
    iteration++;

    fprintf(csv_file, "%ld,%d,%d\n",
            iteration,
            avalanche_size,
            avalanche_duration);
    fflush(csv_file);

    active_row = -1;
    active_col = -1;

    printf("\033[H");
    print_grid();
    render_stats();
    sleep_ms(10);
    }

  fclose(csv_file);
  return 0;
}

