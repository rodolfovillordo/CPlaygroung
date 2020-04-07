#include  <stdio.h>
#include <stdlib.h>
#include <string.h>

#define	MAX_PARAGRAPHS 5

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

char**** get_doc(char *s){
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
		printf("%s\n", token);
		i++;
		token = strtok_r(NULL, "\n", &sv_ptr);
	}
	d = realloc(d, i * sizeof(char *));
	return d;
}
int main(void)
{
	char *s;
	char ****doc;

	s = malloc(34*sizeof(char));
	s = "String test. \n with line break.";
	doc = get_doc(s);

	printf("\n doc[0][0][1] = %s\n", doc[1][0][2]);
	return 0;
}
