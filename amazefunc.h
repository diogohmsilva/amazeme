typedef struct Game {
	int L, C, goal,l, c, k, initial_E, curr_E, best_E;
	int * path;
	int * path_best;
	int** grid; 
	int** visited;
}game;

int inside(game g, int l ,int c);
int isValid(game * g);
void createGrid(game * g);
int Sum(int new, int current);
int upperBound(game * g, int l, int c, int steps);
int checkupperBound(game *g, int l, int c, int steps);
int findPath(game *G, int l, int c, int steps);
void printSol(char * file, game * g, int * path);
void play(game * g, char * file);
void freeAll(game * g);
void skipGrid(game *g, FILE * f);
void fileToGame(char *file, game *g);

