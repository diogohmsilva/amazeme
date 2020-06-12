#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "amazefunc.h"


/*lê o mapa do ficheiro*/
void fileToGame(char *file, game *g){
	
	int i, j;
	FILE *f, *fo;
	char * output = '\0';
	char * aux;
	f = fopen(file, "r");	
	
	aux = strrchr(file, '.');
	if(aux != NULL){
		*aux = '\0';
		strcat(file, ".paths");
		output = file;
	}
	
	/*enquanto houver mapas a ler*/
	while(fscanf(f, "%d %d %d %d %d %d %d", &g->L, &g->C, &g->goal ,&g->l, &g->c, &g->k, &g->initial_E) == 7){	

		if(isValid(g)){	
			createGrid(g);			
			for(i = 0; i<g->L ; i++){
				for(j = 0; j<g->C ; j++){
					/*inicializa os valores de g->visited e g->grid*/
					g->visited[i][j] = 0; 
					if(fscanf(f, "%d", &g->grid[i][j])!=1){
						exit(-1);
					}		
				}
			}
			
			g->curr_E = g->initial_E;			
			g->best_E = 0;
			play(g, output);/*chama a funçao para resolver o jogo*/
			freeAll(g);/*liberta a memoria*/
		}else{/*mapa invalido*/		
			skipGrid(g, f);
			fo = fopen(output, "a");

			if(g->k >= g->L * g->C){
				fprintf(fo, "%d %d %d %d %d %d %d -1\n\n", g->L, g->C, g->goal,  g->l, g->c, g->k, g->initial_E);
			}else{
				fprintf(fo, "%d %d %d %d %d %d %d\n\n", g->L, g->C, g->goal,  g->l, g->c, g->k, g->initial_E);			
			}

			fclose(fo);	
			
		}
	}
	
	fclose(f);

	return;

}




int main (int argc, char * argv[]){	
	
	game g;

	if ( argc < 2 ) {
	    fprintf ( stderr, "ERROR: missing filename in argument!\n" );	    
	}

	
	
	fileToGame(argv[1], &g);
	
	
	
	return 0; 

}
