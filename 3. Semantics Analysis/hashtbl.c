/* The authors of this work have released all rights to it and placed it
in the public domain under the Creative Commons CC0 1.0 waiver
(http://creativecommons.org/publicdomain/zero/1.0/).

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Retrieved from: http://en.literateprograms.org/Hash_table_(C)?oldid=19638
*/

/*
    This Library has been modified slightly to allow some extra functions such as
    debug information and printing the hashtable as table.
*/

#include "hashtbl.h"
#include "settings.h"
#include "types.h"
#include "general.h"
#include "sizes.h"

#include <string.h>
#include <stdio.h>


extern void yyerror(char *message);
extern char *reverse_types[];

static char *mystrdup(const char *s)
{
	char *b;
	if (!(b = malloc(strlen(s) + 1)))
		return NULL;
	strcpy(b, s);
	return b;
}

static hash_size def_hashfunc(const char *key)
{
	hash_size hash = 0;

	while (*key)
		hash += (unsigned char)*key++;

	return hash;
}

HASHTBL *hashtbl_create(hash_size size, hash_size (*hashfunc)(const char *))
{
	HASHTBL *hashtbl;

	if (!(hashtbl = malloc(sizeof(HASHTBL))))
		return NULL;

	if (!(hashtbl->nodes = calloc(size, sizeof(struct hashnode_s *))))
	{
		free(hashtbl);
		return NULL;
	}

	hashtbl->size = size;

	if (hashfunc)
		hashtbl->hashfunc = hashfunc;
	else
		hashtbl->hashfunc = def_hashfunc;

	return hashtbl;
}

void hashtbl_destroy(HASHTBL *hashtbl)
{
	hash_size n;
	struct hashnode_s *node, *oldnode;

	for (n = 0; n < hashtbl->size; ++n)
	{
		node = hashtbl->nodes[n];
		while (node)
		{
			free(node->key);
			oldnode = node;
			node = node->next;
			free(oldnode);
		}
	}
	free(hashtbl->nodes);
	free(hashtbl);
}

int hashtbl_insert(HASHTBL *hashtbl, const char *key, void *data, int scope)
{
	struct hashnode_s *node;
	hash_size hash = hashtbl->hashfunc(key) % hashtbl->size;

	if (HASHTBL_DEBUG && HASHTBL_SHOW_INSERT)
	{
		printf("HASHTBL_INSERT(): KEY = %s, HASH = %ld,  \tDATA = %s, SCOPE = %d\n", key, hash, (char *)data, scope);
	}

	node = hashtbl->nodes[hash];
	while (node)
	{
		if (!strcmp(node->key, key) && (node->scope == scope))
		{
			node->data = data;
			return 0;
		}
		node = node->next;
	}

	if (!(node = malloc(sizeof(struct hashnode_s))))
		return -1;
	if (!(node->key = mystrdup(key)))
	{
		free(node);
		return -1;
	}

	Type_Struct *ts = new(sizeof(Type_Struct)); // TODO: Check if required
	
	node->data = data;
	node->scope = scope;
	node->next = hashtbl->nodes[hash];
	node->ts = ts;

	hashtbl->nodes[hash] = node;

	return 0;
}

int hashtbl_remove(HASHTBL *hashtbl, const char *key, int scope)
{
	struct hashnode_s *node, *prevnode = NULL;
	hash_size hash = hashtbl->hashfunc(key) % hashtbl->size;

	node = hashtbl->nodes[hash];
	while (node)
	{
		if ((!strcmp(node->key, key)) && (node->scope == scope))
		{
			free(node->key);
			if (prevnode)
				prevnode->next = node->next;
			else
				hashtbl->nodes[hash] = node->next;
			free(node);
			return 0;
		}
		prevnode = node;
		node = node->next;
	}

	return -1;
}

void *hashtbl_get(HASHTBL *hashtbl, int scope)
{
	int rem;
	hash_size n;
	struct hashnode_s *node, *oldnode;

	int found = 0;

	for (n = 0; n < hashtbl->size; ++n)
	{
		node = hashtbl->nodes[n];
		while (node)
		{
			if (node->scope == scope)
			{
				if (HASHTBL_DEBUG && HASHTBL_SHOW_GET)
				{
					if (HASHTBL_SHOW_GET_AS_TABLE)
					{
						if (!found)
						{
							printf("-------------- Scope %-2d ---------------\n", scope);
							printf("Name------------------ Type----------- Value-----------\n");
							found++;
						}

						printf("%-22s %-16s %-16s\n", node->key, reverse_types[node->ts->type], (char *)node->data);
					}
					else
					{
						printf("HASHTBL_GET():\tSCOPE = %d, KEY = %s,  \tDATA = %s\n", node->scope, node->key, (char *)node->data);
					}
				}
				oldnode = node;
				node = node->next;
				rem = hashtbl_remove(hashtbl, oldnode->key, scope);
			}
			else
				node = node->next;
		}
	}

	if (HASHTBL_DEBUG && HASHTBL_SHOW_GET && HASHTBL_SHOW_GET_AS_TABLE && found)
	{
		printf("---------- End of Scope %-2d ------------\n\n", scope);
	}
	if (rem == -1 && HASHTBL_DEBUG && HASHTBL_SHOW_GET && !HASHTBL_SHOW_GET_AS_TABLE)
		printf("HASHTBL_GET():\tThere are no elements in the hash table with this scope!\n\t\tSCOPE = %d\n", scope);

	return NULL;
}

Type_Struct *ht_extract_ts(struct hashnode_s *node){ // TODO: check why its is needed exactly.
	if(node==NULL){
		printf("erm... WTF DUDE - TODO: FIX THIS TOO\n");
		return NULL;
	}
	Type_Struct *result = new(sizeof(Type_Struct));
	printf("%d\n", node->ts->type);
	*result = *(node->ts);
	
	return result;
	// result->next = NULL;
}

struct hashnode_s *ht_lookup(HASHTBL *hashtbl, int scope, char *key){
	int s;
	struct hashnode_s *node;
	hash_size hash = hashtbl->hashfunc(key)%hashtbl->size;
	
	for(s = scope; s >= 0; s--){
		node = hashtbl->nodes[hash];
		while(node) {
			if(!strcmp(node->key, key) && (node->scope == s)) {
				printf("\t\t\t\t\tKey %s found in scope %d\n", key, s);
				return node;
			}
			node=node->next;
		}
	}
	
	printf("\t\t\t\t\tThere is no entry with the name: %s\n\t\t\t\t\tChecking for enumeration value...\n", key);
	
	// node = ht_lookup_enums(hashtbl, scope, key);
	// if(node == NULL){
	// 	sem_error = 1;
	// 	yyerror("There is no such entry into the symbol table");
	// 	return NULL;
	// }
	
	return NULL;
}


void ht_complex_insert(HASHTBL *hashtbl, const char *key, Type_Struct *ts, int scope){
	
	struct hashnode_s *node;
	hash_size hash = hashtbl->hashfunc(key)%hashtbl->size;
	
	Type type = ts->type;
	switch (type){
		case INT: 
			printf("TYPE = INT, DATA = %d\n", 0);
			break;
		case FLOAT: 
			printf("TYPE = FLOAT, DATA = %lf\n", 0.0f);
			break;
		case CHAR: 
			printf("TYPE = CHAR, DATA = %c\n", 'Z');
			break;
		case CLASS:
			printf("TYPE = CLASS");
			break;
		default:
			printf("TYPE = %d, DATA = %s\n", type, "test");
			break;
	} 
	
	
	node = hashtbl->nodes[hash];
	while(node) {
		if(!strcmp(node->key, key) && (node->scope == scope)) {
			char buffer[254];
			sprintf(buffer, "There is already an entry %s with the same name\n", key);
			yyerror(buffer);
		}
		node=node->next;
	}

	node = new(sizeof(struct hashnode_s));
	
	if(!(node->key=mystrdup(key))) {
		free(node);
		printf("mystrdup issue");
		exit(1);
	}
	
	node->ts = new(sizeof(Type_Struct));
	*(node->ts) = *(ts);
	
	node->scope = scope;
	
	// if (ts->type == ENUMERATION){
	// 	node->isConst = CONST;
	// }else{
	// 	node->isConst = NO_CONST;
	// }
	
	printf("\t\t\t\t\tHT_COMPLEX_INSERT(): KEY = %s, HASH = %ld, SCOPE = %d, SIZE = %d, TYPE = %d \n", node->key, hash, node->scope, node->ts->size, node->ts->type);
	
	node->next = hashtbl->nodes[hash];
	hashtbl->nodes[hash] = node;

}

List *ht_var_insert(HASHTBL *hashtbl, List *list, Type_Struct *ts, int scope){
	Data data;
	List *curr = list;
	
	while( curr != NULL){
		ht_complex_insert(hashtbl, curr->key, ts, scope);
	
		curr = curr->next;
	}
	
	return list;
}