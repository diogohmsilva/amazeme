#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "amazefunc.h"


/*check if coordenate l,c is inside the map*/
int inside(game g, int l ,int c){
	
	if(l>=0 && l<g.L){
		if(c>=0 && c<g.C){
			return 1;
		}
	}
	return 0;	
} 


/*check if game properties all well defined*/
int isValid(game * g){
	
		
	if(g->goal == -2 || g->goal > 0){ /*objectives*/
		if(g->l>0 && g->l<=g->L){ /*initial position*/
			if(g->c>0 && g->c<=g->C){
				if(g->k < g->L * g->C && g->k >= 0){/*number of valid steps*/
					if(g->initial_E > 0){ /*inital energy*/
						return 1;
					}			
				}
			}
		}
	}
	
	return 0;	
} 

/*memory allocation*/
void createGrid(game * g){
	
	int i;
	
	int *path = (int*)malloc((g->k + 1 )* sizeof(int));
	int *path_b = (int*)malloc((g->k + 1 )* sizeof(int));
	int **game = (int**)malloc((g->L)*sizeof(int*));	
	int **visited = (int**)malloc((g->L)*sizeof(int*));
	

	for(i = 0; i<g->L ; i++){
		game[i] = (int*)malloc(g->C*sizeof(int));
		visited[i] = (int*)malloc(g->C*sizeof(int));
	}
	
	for(i = 0; i< g->k;i++){
		path[i] = 0;
		path_b[i] = 0;	
	}

	g->grid = game;
	g->visited = visited;
	g->path = path;
	g->path_best = path_b;
	
	return;
}
/*cumulative sum of integers received*/
int Sum(int new, int current){
	if(new > 0) current += new;
	return current;
}

/*returns the sum of points with a positive value in a radius steps of the coordinate l, c*/
int upperBound(game * g, int l, int c, int steps){
	
	int r=0;
	int i,j;
	int aux_k = steps;
	int var = 0;
	 
	if(steps == 0){
		var = Sum(g->grid[l][c], 0);
	}else{	
		for(j=c - aux_k; j<=c + aux_k ; j++){	
			r = aux_k - abs((c - j)); /*maximum vertical displacement to be considered keeping the distance to the starting point less than or equal to the radius steps*/
			for(i = l - r; i <= l +r ; i++){
					if(inside(*g, i, j)){
						var = Sum((*g).grid[i][j], var);
					}
			}
		}
	}
	
	
	return var;
}

/*provides the arguments to upperBound depending on the objective of the game and returns 1 if the points in a radius steps have enough energy to solve the problem*/
int checkupperBound(game *g, int l, int c, int steps){

	if(g->goal>0){
		if(upperBound(g,l,c, steps) >= (g->goal - g->curr_E)) return 1;
	}else{
		if(upperBound(g, l, c, steps) + g->curr_E >  g->best_E) return 1;
	}

	return 0;

}

/*finds the best path from point l, c*/
/*returns 1 if solution for objective 1 has been found*/
/*returns 0 if it can't find a solution for objectives 1 and 2 or returns 2 if it finds a solution for objective 2*/
int findPath(game *G, int l, int c, int steps){
	
	int i,j;
	
	/*marca-se o ponto l,c como visitado*/
	G->visited[l][c]=1;
	
	
	if(steps > 0){	/*if there are still steps to take*/	
		for(i=1; i<6; i++){/*checks all directions*/
			if(i==1){/*cima*/
				if(inside(*G, l-1, c) && G->visited[l-1][c]==0){ /*if the top point is within the map and has not yet been visited*/
					if(G->curr_E + G->grid[l-1][c] > 0){ /*if it doesn't die when entering the cell above*/
						if(checkupperBound(G, l-1, c, steps-1)){/*check if it is worth entering the cell*/
							G->path[G->k - steps] = i; /*record the direction taken on the way*/						
							G->curr_E += G->grid[l-1][c];/*current energy is updated*/	

							if(findPath(G, l-1, c, steps-1)){
								return 1;		/*solution found; exit function*/				
							}						
						}
					}
				}
			}else if(i==2){/*down*/
				if(inside(*G, l+1, c) && G->visited[l+1][c]==0){
					if(G->curr_E + G->grid[l+1][c] > 0){
						if(checkupperBound(G, l+1, c, steps-1)){
							G->path[G->k - steps] = i;						
							G->curr_E += G->grid[l+1][c];	
							if(findPath(G, l+1, c, steps-1)){
								return 1;						
							}
						}
					}
				}
			}else if(i==3){/*left*/
				if(inside(*G, l, c-1) && G->visited[l][c-1]==0){
					if(G->curr_E + G->grid[l][c-1] > 0){
						if(checkupperBound(G, l, c-1, steps-1)){
							G->path[G->k - steps] = i;						
							G->curr_E += G->grid[l][c-1];	
							if(findPath(G, l, c-1, steps-1)){
								return 1;						
							}
						}
					}
				}
	
			}else if(i==4){/*right*/
				if(inside(*G, l, c+1) && G->visited[l][c+1]==0){
					if(G->curr_E + G->grid[l][c+1] > 0){
						if(checkupperBound(G, l, c+1, steps-1)){
							G->path[G->k - steps] = i;						
							G->curr_E += G->grid[l][c+1];	
							if(findPath(G, l, c+1, steps-1)){
								return 1;						
							}
						}
					}
				}

			}else{ /*no solution. return to previous point*/
				G->visited[l][c] = 0;
				G->curr_E -= G->grid[l][c];				
				G->path[G->k - steps] = 0;
				return 0;			
			}	
		}
	}else{ /*if there are no more steps to take*/
		if(G->goal > 0){	/*for objective 1*/
			if(G->curr_E >= G->goal){	/*check if a solution as been found*/
				G->best_E = G->curr_E;	
				return 1;	/*solution found. exit function*/					
			}else{			/*no solution; return to previous point*/
				G->visited[l][c] = 0;
				G->curr_E -= G->grid[l][c];			
				G->path[G->k - steps] = 0;
				return 0;		
			}
		}else{/*objectivo 2*/
			if(G->curr_E > G->best_E){ /*if a better solution has been found*/
				G->best_E = G->curr_E; /*update best solution*/
				for(j =0;j<G->k;j++){  
					G->path_best[j] = G->path[j];
				}
				/*return to previous point and look for an even better solution*/
				G->visited[l][c] = 0;
				G->curr_E -= G->grid[l][c];			
				G->path[G->k - steps] = 0;
				return 0;		
			}else{					/*no oslution; return to previous point*/
				G->visited[l][c] = 0;
				G->curr_E -= G->grid[l][c];			
				G->path[G->k - steps] = 0;
				return 0;		
			}			
		}
	}

	return 0;

}


/*receives solution and prints it to file*/
void printSol(char * file, game * g, int * path){
	
	FILE * fo;
	int i;
	int l = g->l;
	int c = g->c;
	
	fo = fopen(file, "a");
	/*header writing*/
	fprintf(fo, "%d %d %d %d %d %d %d %d\n", g->L, g->C, g->goal,  g->l, g->c, g->k, g->initial_E, g->best_E);

	/*writing of the path taken and the value of each cell*/
	for(i=0; i<g->k; i++){
		if(path[i]==1){
			l--;
		}else if(path[i]==2){
			l++;
		}else if(path[i]==3){
			c--;
		}else if(path[i]==4){
			c++;
		}
		
		fprintf(fo, "%d %d %d\n", l, c, g->grid[l-1][c-1]);
	}
	
	fprintf(fo, "\n");
	fclose(fo);
	
	return;
	
}

/*calls function findPath and printSol for both objectives*/
void play(game * g, char * file){

	FILE * fo;

	
	if(findPath(g, g->l-1, g->c-1, g->k)){
	/*solution found for 1st objective*/
		printSol(file,g, g->path);
	}else if(g->goal > 0){
		/*no solution found for objective 1*/
		fo = fopen(file, "a");	
		fprintf(fo, "%d %d %d %d %d %d %d -1\n\n", g->L, g->C, g->goal,  g->l, g->c, g->k, g->initial_E);
		fclose(fo);		
	}else{
	/*2nd objective*/
		if(g->best_E == 0){
			/*no solution*/
			fo = fopen(file, "a");	
			fprintf(fo, "%d %d %d %d %d %d %d -1\n\n", g->L, g->C, g->goal,  g->l, g->c, g->k, g->initial_E);
			fclose(fo);
		}else{
			/*solution found*/
			printSol(file,g, g->path_best);	
		}	
	}
	
	
	return;
}

/*free allocated memory*/
void freeAll(game * g){

	int i;

	for(i = 0; i < g->L ; i++){
		free(g->grid[i]);
		free(g->visited[i]);
	}
	
	free(g->path_best);
	
	free(g->path);
	
	free(g->grid);
	free(g->visited);

	return;
}

/*ignores the map for poorly formulated problems*/
void skipGrid(game *g, FILE * f){

	int aux, i, j;

	for(i = 0; i<g->L ; i++){
		for(j = 0; j<g->C ; j++){		
			if(fscanf(f, "%d", &aux)!=1){
				exit(-1);
			}		
		}
	}

	return;

}

















