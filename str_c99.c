#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<assert.h>
#define MAX_CHARACTERS 1005
#define MAX_PARAGRAPHS 5

extern char *strtok_r(char *, const char *, char **);

char* kth_word_in_mth_sentence_of_nth_paragraph(char**** document, int k, int m, int n) {
	return document[n-1][m-1][k-1];
}

char** kth_sentence_in_mth_paragraph(char**** document, int k, int m) { 
	return document[m-1][k-1];
}

char*** kth_paragraph(char**** document, int k) {
	return document[k-1];
}

void get_sentence(char ***st, char *s)
{
	char *tmp;
	char *token;
	char *sv_ptr;
	int s_size; /* The sentence size in number of words */
	int w_count = 0; /* words counter */

	s_size = 8;
	(*st) = (char **) malloc(s_size * sizeof(char *));

	tmp = (char *) malloc(strlen(s) * sizeof(char));
	memcpy(tmp, s, strlen(s));

	token = strtok_r(tmp, " ", &sv_ptr);

	while (token != NULL){
		(*st)[w_count] = malloc(strlen(token) * sizeof(char));
		memcpy((*st)[w_count], token, strlen(token));
		w_count++;

		if (w_count == s_size){
			s_size *= 2;
			(*st) = realloc((*st), s_size * sizeof(char *));
		}

		token = strtok_r(NULL, " ", &sv_ptr);
	}
	(*st) = realloc((*st), w_count * sizeof(char *));
}

void get_paragraph(char ****p, char *s)
{
	char *tmp;
	char *token;
	char *sv_ptr;
	int p_size; /* The size of paragraph, in number of sentences */
	int s_count = 0; /* Count the actual number of sentences */

	p_size = 4; /* Start with 4 sentences, and double size on need */

	tmp = (char *) malloc(strlen(s) * sizeof(char));
	memcpy(tmp, s, strlen(s));
	(*p) = (char ***) malloc(p_size*sizeof(char *));

	token = strtok_r(tmp, ".", &sv_ptr);
	while (token != NULL){
		get_sentence(&(*p)[s_count], token);
		s_count++;
		if (s_count == p_size){
			p_size *= 2;
			/* Double the size of the array if reach the actual size */
			(*p) = realloc((*p), p_size*sizeof(char *));
		}
		token = strtok_r(NULL, ".", &sv_ptr);
	}
	/* Reduce the size of the array to reduce memory consumption */
	(*p) = realloc((*p), s_count * sizeof(char *));
}

char**** get_document(char *s){
	char ****d;
	char *token;
	char *sv_ptr;
	char *tmp;
	int i = 0;
	tmp = malloc(strlen(s) * sizeof(char));
	memcpy(tmp, s, strlen(s));
	d = (char ****) calloc(MAX_PARAGRAPHS, sizeof(char *));
	token = strtok_r(tmp, "\n", &sv_ptr);
	while (token != NULL){
		get_paragraph(&d[i],token);
		i++;
		token = strtok_r(NULL, "\n", &sv_ptr);
	}
	d = realloc(d, i * sizeof(char *));
	return d;
}


char* get_input_text() {	
	int paragraph_count;
	scanf("%d", &paragraph_count);

	char p[MAX_PARAGRAPHS][MAX_CHARACTERS], doc[MAX_CHARACTERS];
	memset(doc, 0, sizeof(doc));
	getchar();
	for (int i = 0; i < paragraph_count; i++) {
		scanf("%[^\n]%*c", p[i]);
		strcat(doc, p[i]);
		if (i != paragraph_count - 1)
			strcat(doc, "\n");
	}

	char* returnDoc = (char*)malloc((strlen (doc)+1) * (sizeof(char)));
	strcpy(returnDoc, doc);
	return returnDoc;
}

void print_word(char* word) {
	printf("%s", word);
}

void print_sentence(char** sentence) {
	int word_count;
	scanf("%d", &word_count);
	for(int i = 0; i < word_count; i++){
		printf("%s", sentence[i]);
		if( i != word_count - 1)
			printf(" ");
	}
} 

void print_paragraph(char*** paragraph) {
	int sentence_count;
	scanf("%d", &sentence_count);
	for (int i = 0; i < sentence_count; i++) {
		print_sentence(*(paragraph + i));
		printf(".");
	}
}

int main() 
{
	char* text = get_input_text();
	char**** document = get_document(text);

	int q;
	scanf("%d", &q);

	printf("\n");
	printf("\n");
	while (q--) {
		int type;
		scanf("%d", &type);

		if (type == 3){
			int k, m, n;
			scanf("%d %d %d", &k, &m, &n);
			char* word = kth_word_in_mth_sentence_of_nth_paragraph(document, k, m, n);
			print_word(word);
		}

		else if (type == 2){
			int k, m;
			scanf("%d %d", &k, &m);
			char** sentence = kth_sentence_in_mth_paragraph(document, k, m);
			print_sentence(sentence);
		}

		else{
			int k;
			scanf("%d", &k);
			char*** paragraph = kth_paragraph(document, k);
			print_paragraph(paragraph);
		}
		printf("\n");
	}     
}
