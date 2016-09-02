#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef enum{ FALSE, TRUE } bool;

typedef struct {
	char name[101], inst[21];
	int id;
} person_t;

void print_people(person_t *people, int size){
	int i;
	for(i = 0; i < size; i++)
		printf("%s %d %s\n", people[i].inst,
				people[i].id,
				people[i].name);
}

//Troca a posição de people[i] com people[j] no vetor.
void swap_people(person_t *people, int i, int j){
	person_t aux;
	aux = people[i];
	people[i] = people[j];
	people[j] = aux;
}

//Retorna TRUE se o id de people[i] for maior do que o de people[j]
bool id_higher(person_t *people, int i, int j){
	return people[i].id > people[j].id ? TRUE : FALSE;
}

//Retorna TRUE se o nome de people[i] for maior do que o de people[j]
bool name_higher(person_t *people, int i, int j){
	return strcmp(people[i].name, people[j].name) > 0 ? TRUE : FALSE;
}

//Ordenamento crescente. Bubble sort clássico
void sort_people(person_t *people, int size, bool (*higher)(person_t *, int, int)){
	int i;
	bool swapped;

	do{
		swapped = FALSE;
		for(i = 1; i < size; i++){
			if(higher(people, i-1, i)){
				swap_people(people, i-1, i);
				swapped = TRUE;
			}
		}
	} while(swapped);
}

int main(int argc, char *argv[]){
	bool s = FALSE;
	char string[101], inst[21];
	person_t *people = NULL;
	int i, n = 0;

	while(scanf("%s", string) != EOF){
		if(strcmp(string, "FEDERAL") == 0){
			strcpy(inst, "FEDERAL");
			continue;
		}
		if(strcmp(string, "CAASO") == 0){
			strcpy(inst, "CAASO");
			continue;
		}
		if(strcmp(string, "ID") == 0 || strcmp(string, "NAME") == 0) break;
	
		if(!s){
			people = (person_t *) realloc(people, sizeof(person_t) * (n+1));
			strcpy(people[n].inst, inst);
			people[n].id = atoi(string);
		} else {
			strcpy(people[n].name, string);

			//Para ler o resto do nome, até o próximo '\n'
			for(i = 0; people[n].name[i] != '\0'; i++);	//Busca o final do nome que já foi copiado.
			for(; (people[n].name[i] = fgetc(stdin)) != '\n';i++);	//Copia o resto do nome a partir dali.
			people[n].name[i] = '\0';	//Substitui o '\n' por '\0'
			n++;
		}
		s = !s;
	}

	if(strcmp(string, "ID") == 0)
		sort_people(people, n, id_higher);
	else if(strcmp(string, "NAME") == 0)
		sort_people(people, n, name_higher);

	print_people(people, n);
	free(people);	

	return 0;
}
