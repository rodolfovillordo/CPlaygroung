#include <stdlib.h>
#include <stdio.h>

#define INDEX(c) ( (c) - 'a' )
struct node {
	char c;
	int w; /* 0 false, 1 true */
	struct node *cldn[26];
};

int DEL_FLAG = 0;

int insert(struct node *t, char *word);
int delete(struct node *t, char *word);
int look_up(struct node *t, char *word);

void ini_node(struct node *n)
{
	n->c = 0;
	n->w = 0;
	for (int i = 0; i < 26; i++)
		n->cldn[i] = NULL;
}

int main (void)
{
	struct node trie[26];
	for (int i = 0; i < 26; i++)
		ini_node(&trie[i]);


	insert(trie, "add");
	insert(trie, "and");
	insert(trie, "not");
	insert(trie, "cave");
	insert(trie, "can");

	if (look_up(trie, "can"))
		printf("present: can\n");
	if (look_up(trie, "zelot"))
		printf("present: zelot\n");
	if (look_up(trie, "an"))
		printf("present: zelot\n");
	if(delete(trie, "zetta"))
		printf("DEL: zetta\n");
	if(delete(trie, "an"))
		printf("DEL: an\n");
	if(delete(trie, "add"))
		printf("DEL: add\n");

	return 0;
}


int insert(struct node *t, char *w)
{
	struct node *r;

	if (*w == '\0')
		return 1;

	r = &t[INDEX(*w)];	
	while (*w){
		if (r->c == 0)
			r->c = (char) *w;
		w++;
		if (*w == '\0'){
			r->w = 1;
			return 0;
		}
		if (r->cldn[INDEX(*w)] == NULL){
			r->cldn[INDEX(*w)] = (struct node *) malloc(sizeof(struct node));
			ini_node(r->cldn[INDEX(*w)]);
		}
		r = r->cldn[INDEX(*w)];
	}
	return 1;

}

int look_up(struct node *t, char *w)
{
	struct node *r;
	
	if (*w == '\0')
		return 1;

	r = &t[INDEX(*w)];

	while (*w) {
		if (r->c == 0)
			return 0;
		w++;
		if (*w == '\0')
			return  r->w? 1 : 0;
		
		r = r->cldn[INDEX(*w)];
		if (r == NULL)
			return 0;
	}
}

int has_children(struct node *t)
{
	if(t == NULL)
		return 0;
	for (int i = 0; i < 26; i++){
		if (t->cldn[i] != NULL)
			return 1;
	}
	return 0;
}

int r_delete(struct node **t, char *w)
{
	/* w not null and empty string */
	if ( w && *w == '\0')
		return 0;
	if ( *(w+1) == '\0'){
		if( (*t)->w ){
			(*t)->w = 0;
			DEL_FLAG = 1;
		}
	} else {
		w++;
		if ((*t)->cldn[INDEX(*w)]){
			t = &(*t)->cldn[INDEX(*w)];
			r_delete(t, w);
		}
	}
	if ( DEL_FLAG && !has_children(*t)){
		free(*t);
		(*t) = NULL;
	}
	return DEL_FLAG;
}

int delete(struct node *t, char *word)
{
	int i = 0;
	struct node *root;
	DEL_FLAG = 0;
	if ( word && *word ){
		i = INDEX(*word);
	}
	root = &t[i];
	r_delete(&root, word);		

	return DEL_FLAG;
}

