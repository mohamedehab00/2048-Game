#include <bits/stdc++.h>
using namespace std;

const int N = 4;
const int GOAL = 1 << (3*N-1);
int grid[N][N];

//This function prints the grid of 2048 Game as the game progresses
void print_grid() {
	for (int i = 0; i < ((N + 4) * N + N + 1); cout << "-", i++);
	cout << "\n";
	for (int i = 0; i < N; i++) {
        cout << "|";
		for (int j = 0; j < N; j++) {
			string e = "";
            if (grid[i][j] == 0) {
				for (int t = 0; t < N+4; e += " ", t++);
			}
            else {
                int str_len = to_string(grid[i][j]).size();
                int r1 = ((N+4) - str_len + 1) / 2;
                int r2 = ((N+4) - str_len) - r1;
				for (int t = 0; t < r1; e += " ", t++);
				e += to_string(grid[i][j]);
				for (int t = 0; t < r2; e += " ", t++);
			}
			cout << e << "|";
		}
		cout << "\n";
		for (int t = 0; t < ((N + 4) * N + N + 1); cout << "-", t++);
		cout << "\n";
	}
}
//This function generates a cell with value 2 
void generate_cell() {
    int a = rand() % N;
	int b = rand() % N;
    while (grid[a][b] != 0) {
        a = rand() % N;
        b = rand() % N;
	}
    grid[a][b] = 2;
}
//This function rotates the grid by 90 degree anti-clockwise
void rotate_90() {
	for (int i = 0; i < N/2; i++) {
		for (int j = i; j < N-i-1; j++) {
            int k              = grid[i][j];
            grid[i][j]         = grid[N-j-1][i];
            grid[N-j-1][i]     = grid[N-i-1][N-j-1];
            grid[N-i-1][N-j-1] = grid[j][N-i-1];
            grid[j][N-i-1]     = k;
		}
	}
}
//This function checks if the game state reachs 2048 or not 
bool check_win() {
    for (int i = 0 ; i<N ; i++){
        for (int j = 0 ; j<N ; j++){
            if(grid[i][j]==GOAL){
                return true;
            }
        }    
    }
    return false;
}
bool check_available_move_per_row(int row) {
    for(int col = N-1 ; col>0 ; col--){
        if((grid[row][col] == grid[row][col-1] && grid[row][col]!=0)||(grid[row][col]< grid[row][col-1] && grid[row][col] == 0)){
            return true;
        }
    }
    return false;
}
//This function checks if the current right direction has a movement state or not
bool check_available_direction() {
    for(int row=0; row<N ; row++){
        if( check_available_move_per_row(row) ){
            return true;
        }
    }
    return false;
}
//This function checks if the given direction has a movement state or not
bool check_available_move(int d) {
    bool res = false;
    //check direction right
    if (d == 3) res = check_available_direction();
    rotate_90();
    //check direction up
    if (d == 5) res = check_available_direction();
    rotate_90();
    //check direction left
    if (d == 1) res = check_available_direction();
    rotate_90();
    //check direction down
    if (d == 2) res = check_available_direction();
    rotate_90();
    return res;
}
//This function checks if the game has a full state or not
bool check_full() {
    for(int row = 0;row<N;row++){
        for(int col = 0;col<N-1;col++){
            if(grid[row][col] == grid[row][col+1] || grid[row][col] == 0 || grid[row][col+1] == 0){
                return false;
            }
        }    
    }
    for(int col = 0;col<N;col++){
        for(int row = 0;row<N-1;row++){
            if(grid[row][col] == grid[row+1][col]){
                return false;
            }
        }    
    }
    return false;
}

//This function merges the grid with the right direction 
void merge() {
    for(int row = 0 ; row<N ; row++){
      for(int col = N-1 ; col>0 ; col--){
         if(grid[row][col] == grid[row][col-1] ){
           grid[row][col]*=2;
           grid[row][col-1] = 0;
           col-=1;
         }
      }
    }
}
//This function merges the grid with the given direction 
void merge_direction(int d) {
    //merge direction right
    if (d == 3) merge();
    rotate_90();
    //merge direction up
    if (d == 5) merge();
    rotate_90();
    //merge direction left
    if (d == 1) merge();
    rotate_90();
    //merge direction down
    if (d == 2) merge();
    rotate_90();
}
//This function moves the grid with the right direction 
void move() {
    for(int i = 0 ; i<N ; i++){
        for(int t = 0 ; t<N ; t++){
            for(int j = 0 ; j<N-1 ; j++){
                if(grid[i][j]!=0 && grid[i][j+1] == 0){
                    int temp = grid[i][j];
                    grid[i][j] = 0;
                    grid[i][j+1] = temp; 
                }
            }
        }    
    }
}
//This function moves the grid with the given direction 
void move_direction(int d) {
    //move direction right
    if (d == 3) move();
    rotate_90();
    //move direction up
    if (d == 5) move();
    rotate_90();
    //move direction left
    if (d == 1) move();
    rotate_90();
    //move direction down
    if (d == 2) move();
    rotate_90();
}
//This function checks if the given direction is valid or not 
bool check_valid_direction(int i) {
    if(( 0<i && i<4 )|| i == 5){
    	return true;
	}
	else{
		return false;
	}
}
//This function clears the game structures
void grid_clear() {
	for(int i = 0 ; i<N ; i++){
		for(int j = 0 ; j<N ; j++){
			grid[i][j] = 0;
		}	
	}
}
//This function reads a valid direction
void read_input(int &i) {
    cout << "Enter the direction: ";
	cin >> i;
    while (!check_valid_direction(i) || !check_available_move(i)) {
        cout << "Enter a valid direction: ";
		cin >> i;
	}
}
//MAIN FUNCTION
void play_game() {
    cout << "2048 Game!\n";
    cout << "Welcome...\n";
    cout << "============================\n";
    while (true) {
        //Generate a cell in the grid
        generate_cell();
        //Prints the grid
        print_grid();
        //Check if the state of the grid has a tie state
        if (check_full()) {
            cout << "Game Over\n";
            break;
		}
        //Read an input from the player
		int i;
		read_input(i);
        //Move with the input direction
        move_direction(i);
        //Merge with the input direction
        merge_direction(i);
        //Move with the input direction
        move_direction(i);
        //Check if the grid has a win state
        if (check_win()) {
            //Prints the grid
            print_grid();
            //Announcement of the final statement
            cout << "Congrats, You won!\n";
            //Ask for continuing the game
			char c;
			cout << "Continue [Y/N] ";
			cin >> c;
			if (c != 'y' && c != 'Y')
				break;
		}
	}
}
int main() {
	while (true) {
		grid_clear();
		play_game();
    	char c;
    	cout << "Play Again [Y/N] ";
    	cin >> c;
    	if (c != 'y' && c != 'Y')
    		break;
	}
}
