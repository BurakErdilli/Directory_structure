#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 40
typedef struct tree {
    char directoryName[MAX];
    struct tree *child;
    struct tree *parent;
	struct tree *sibling;
    
}Tree;

Tree *chdir(Tree *selected,char directoryName[MAX]){ //chdir
	Tree *temp = (Tree*)malloc(sizeof(Tree));
	temp = selected->child;
	if(!strcmp(directoryName,"..")){
		if(selected->parent == NULL){
			printf("Superior directory does not exist!\n");
			return selected;
		}
		return selected->parent;
	}
	else
	{	
		while(temp != NULL){
			if(!strcmp(temp->directoryName,directoryName)){
				selected = temp;
				return selected;				
			}
			temp=temp->sibling;
		}
	}
}
Tree *root;									//root
Tree *addNode(char directoryName[MAX]){
	Tree *n = (Tree*)calloc(1,sizeof(Tree));
	strcpy(n->directoryName,directoryName);
	//
	n->sibling = NULL;
	n->child = NULL;
	n->parent = NULL;
	return n;
}
int main(){	
	printf("------OS Directory Structure Prototype--Burak Erdilli--19011046------\n");
	char input_a[MAX],input_b[MAX];
	Tree *selected = (Tree*)malloc(sizeof(Tree));
	root = addNode("root");
	selected = root;
	int exit = 0;
	while(exit!=1){
		scanf("%s",input_a);
		if(!strcmp(input_a, "mkdir")) {
            scanf("%s",input_b);
            mkdir(input_b,selected);

        }
        else if(!strcmp(input_a, "exit")){
        	exit = 1;
		}
		else if (!strcmp(input_a, "count")) {
        	printf("%d\n",count(selected->child));
        }
        else if (!strcmp(input_a, "chdir")) {
        	scanf("%s",input_b);
			selected = chdir(selected,input_b);
        }
        else if (!strcmp(input_a, "rmdir")) {
        	scanf("%s",input_b);
        	rmdir(selected,input_b);
        }
		else if (!strcmp(input_a, "dir")) {
        	dir(selected->child);
        	printf("\n");
        }
		else{
			printf("You've entered an unvalid command!!!\n");
		}
	}
	free(selected);
	return 0;
}

void dir(Tree *k){
	if(k==NULL)
		return;	
	while(k != NULL){
		printf("%s > ", k->directoryName);
		k=k->sibling;
	}
}
int count(Tree *k){
	int counter = 0;
	if(k==NULL)
		return;	
	while(k != NULL){
		counter++;
		k=k->sibling;
	}
	return counter;
}


void rmdir(Tree *k,char directoryName[MAX]){
	if(k->child==NULL)
		return;	
	Tree *tchild = (Tree*)malloc(sizeof(Tree));
	Tree *tPrevChild = (Tree*)malloc(sizeof(Tree));
	tchild = k->child;
	int ctr = 0;
	while(tchild != NULL){
		if(!strcmp(tchild->directoryName,directoryName)){
			if(tchild->child != NULL){
				printf("Folder is not empty. Error!\n");
				return;
			}
			
			if(tchild->sibling == NULL){
				tPrevChild->sibling = NULL;
				tchild = NULL;
				free(tchild);
				return;
			}
			if(tchild->sibling !=NULL){ 
				tPrevChild->sibling = tchild->sibling;
				tchild = NULL;
				free(tchild);
				return;
			}
			if (ctr==0){ 
				if(tchild->sibling != NULL){
					k->child = tchild->sibling;
				}
				else{
					k->child = NULL;
					free(tchild);
				}
			}
			
			printf("deleted");	
			return;	
		}
		ctr=1;
		tPrevChild = tchild;
		tchild=tchild->sibling;
		
	}
	printf("Directory not exist with that name.\n");
}
