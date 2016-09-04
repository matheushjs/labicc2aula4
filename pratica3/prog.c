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
bool id_lower(person_t *l, person_t *r){
	return l->id < r->id ? TRUE : FALSE;
}

//Retorna TRUE se o nome de people[i] for maior do que o de people[j]
bool name_lower(person_t *l, person_t *r){
	return strcmp(l->name, r->name) < 0 ? TRUE : FALSE;
}

int it_limit, it = 0;
bool (*lower)(person_t *, person_t *);
void merge(person_t *main, int n, person_t *left, int llim, person_t *right, int rlim){
	int i, l = 0, r = 0;
	for(i = 0; i < n; i++){
		if(r >= rlim || (l < llim && lower(left+l, right+r)))
			main[i] = left[l++];
		else
			main[i] = right[r++];
	}
	it++;
}

//Ordena o vetor de pessoas de forma crescente.
//Merge sort.
void sort_people(person_t *people, int n){
	int mid = n/2;
	person_t *left, *right;
	if(n < 2) return;

	left = (person_t *) malloc(sizeof(person_t) * (mid));
	right = (person_t *) malloc(sizeof(person_t) * (n-mid));
	memcpy(left, people, sizeof(person_t) * mid);
	memcpy(right, people+mid, sizeof(person_t) * (n-mid));
	
	sort_people(left, mid);
	sort_people(right, n-mid);
	
	if(it < it_limit){
		merge(people, n, left, mid, right, n-mid);
	} else {
		memcpy(people, left, sizeof(person_t) * mid);
		memcpy(people+mid, right, sizeof(person_t) * (n-mid));
	}

	free(left);
	free(right);
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

	scanf("%d", &it_limit);
	if(strcmp(string, "ID") == 0){
		lower = id_lower;
		sort_people(people, n);
	}
	else if(strcmp(string, "NAME") == 0){
		lower = name_lower;
		sort_people(people, n);
	}
	
	print_people(people, n);
	free(people);	
	return 0;
}
