#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>

#include "List.h"
// Struct

typedef struct NodeObj *Node;

typedef struct NodeObj{
        Node prev;
        Node next;
        void *val;
}NodeObj;

typedef struct ListObj{
        Node front;
        Node back;
        Node pointer;
	int index;
        int length;
}ListObj;

// Constructors-Destructors
void freeNode(Node *pN);

List newList(void){
	// param: None
	// return: List
	// func: initialize a list

	List out = (List)calloc(1,sizeof(ListObj));
	out->front = NULL;
	out->back = NULL;
	out->pointer = NULL;
	out->index = -1;
	out->length = 0;
	return out;
}

void freeList(List *pL){
	// param: List
	// return: None
	// func: free the memory that the list is using

	if(pL == NULL || *pL == NULL){ 
		return;
	}
	clear(*pL);
	free(*pL);
	*pL = NULL;
	

}

Node newNode(void *value){
	// param: any (void pointer)
	// return: Node
	// func: create a new node

	Node out = (Node)malloc(sizeof(NodeObj));
	out->prev = NULL;
	out->next = NULL;
	out->val = value;
	return out;
}

void freeNode(Node *pN){
	// param: Node
	// return: None
	// func: free the memory that the node is using

	if(pN != NULL && *pN != NULL){
		free(*pN);
		*pN = NULL;
	}
}

// Access functions

int length(List L){
	// param: List
	// return: Int
	// func: return the length of the list, return -1 if there is no list

	if(L != NULL){
		return L->length;
	}
	return -1;
}

int index(List L){
	// param: List
	// return: Int
	// func: return the index that the cursor is at, return -1 if the cursor is not pointing at anything

	if(L == NULL){
		return -1;
	}else if(L->pointer == NULL){
		return -1;
	}else{
		return L->index;
	}
}

void *front(List L){
	// param: List
	// return: any (void pointer)
	// func: return the value at the front of the list

	if(length(L) > 0){
		return L->front->val;
	}
	printf("List Error- Called front(): List is empty... Exiting program\n");
	freeList(&L);
	exit(EXIT_FAILURE);
	return 0;
	
}

void *back(List L){
	// param: List
	// return: any (void pointer)
	// func: return the value at the back of the list

	if(length(L) > 0){
		return L->back->val;
	}
	printf("List Error- Called back(): List is empty... Exiting program\n");
	freeList(&L);
	exit(EXIT_FAILURE);
	return 0;
}

void *get(List L){
	// param: List
	// return: any (void pointer)
	// func: return the value that the cursor is pointing at

	if(L->length > 0 && L->index >= 0){
		return L->pointer->val;
	}
	if(L->length <= 0){
		printf("List Error- Called get(): List is empty... Exiting program\n");
	}else if(L->index < 0){
		printf("List Error- Called get(): Index out of range... Exiting program\n");
	}
	freeList(&L);
	exit(EXIT_FAILURE);
	return 0;
}

// Manipulation Procedures

void clear(List L){
	// param: List
	// return: None
	// func: remove all element in the list

	if(length(L) == 0){
		return;
	}
	deleteBack(L);
	clear(L);
}

void set(List L, void *x){
	// param: List, any (void pointer)
	// return: None
	// func: set the node, that the cursor is pointing to, to a new value

	memcpy(L->pointer->val,x,8);
}

void moveFront(List L){
	// param: List
	// return: None
	// func: set the cursor to point at the front

	if(L != NULL){
		L->pointer = L->front;
		L->index = 0;
	}
}

void moveBack(List L){
	// param: List
	// return: None
	// func: set the cursor to point at the back

	if(L != NULL){
		L->pointer = L->back;
		L->index = length(L) - 1;
	}
}

void movePrev(List L){
	// param: List
	// return: None
	// func: move the cursor one node back

	if(L->pointer != NULL){
		L->pointer = L->pointer->prev;
		if(L->pointer == NULL){
			L->index = -1;	
		}else{
			L->index--;
		}
	}
}

void moveNext(List L){
	// param: List
	// return: None
	// func: move the cursor one node forward

	if(L->pointer != NULL){
		L->pointer = L->pointer->next;
		if(L->pointer == NULL){
			L->index = -1;
		}else{
			L->index++;
		}
	}
}

void prepend(List L, void *x){
	// param: List, any (void pointer)
	// return: None
	// func: add a new node at the front

	if(L == NULL){
		printf("List Error- Called prepend(): No List... Exiting program\n");
		exit(EXIT_FAILURE);
	}
	Node new = newNode(x);
	if(length(L) == 0){
		L->front = L->back = new;
	}else{
		new->next = L->front;
		L->front->prev = new;
		L->front = new;
	}
	
	if(L->pointer != NULL){
		L->index++;
	}

	L->length++;
}

void append(List L, void *x){
	// param: List, any (void pointer)
	// return: None
	// func: add a new node at the back

	if(L == NULL){
		printf("List Error- Called append(): No List... Exiting program\n");
		exit(EXIT_FAILURE);
	}
	Node new = newNode(x);
	if(length(L) == 0){
		L->front = L->back = new; 
	}else{
		new->prev = L->back;
		L->back->next = new;
		L->back = new;
	}
	L->length++;
}

void insertBefore(List L, void *x){
	// param: List, any (void pointer)
	// return: None
	// func: insert a new node before the cursor 

	if(length(L) <= 0){
		printf("List error- Called insertBefore(): List is empty... Exiting program\n");
		freeList(&L);
		exit(EXIT_FAILURE);
	}else if(index(L) < 0){
		printf("List error- Called insertBefore(): Index out of range... Exiting program\n");
		freeList(&L);
		exit(EXIT_FAILURE);
	}

	Node new = newNode(x);

	if(L->pointer == L->front){
		new->next = L->pointer;
		L->pointer->prev = new;
		L->front = new;
	}else{
		Node prev = L->pointer->prev;
		prev->next = new;

		new->next = L->pointer;
		new->prev = prev;

		L->pointer->prev = new;
	}
	
	L->index++;
	L->length++;


}

void insertAfter(List L, void *x){
	// param: List, any (void pointer)
	// return: None
	// func: insert a new node after the cursor

	if(length(L) <= 0){
		printf("List error- Called insertAfter(): List is empty... Exiting program\n");
		freeList(&L);
		exit(EXIT_FAILURE);
	}else if(index(L) < 0 ){
		printf("List error- Called insertAfter(): Index out of range... Exiting program\n");
		freeList(&L);
		exit(EXIT_FAILURE);
	}

	Node new = newNode(x);

	if(L->pointer == L->back){
		new->prev = L->pointer;
		L->pointer->next = new;
		L->back = new;
	}else{
		Node next = L->pointer->next;
		next->prev = new;

		new->prev = L->pointer;
		new->next = next;

		L->pointer->next = new;
	}
	L->length++;
}

void deleteFront(List L){
	// param: List
	// return: None
	// func: delete the node at the front

	if(length(L) == 0){
		printf("List error- Called deleteFront(): List is empty... Exiting program\n");
		freeList(&L);
		exit(EXIT_FAILURE);
	}
	Node delete = L->front;

	if(L->pointer != L->front){
		L->index--;
	}else{
		L->index = -1;
	}

	if(length(L) > 1){
		L->front = L->front->next;
		L->front->prev = NULL;
	}else{
		L->front = L->back = NULL;
	}

	L->length--;
	freeNode(&delete);	
}

void deleteBack(List L){
	// param: List
	// return: None
	// func: delete the node at the back

	if(length(L) == 0){
		printf("List error- Called deleteBack(): List is empty... Exiting program\n");
		freeList(&L);
		exit(EXIT_FAILURE);
	}
	Node delete = L->back;
	if(L->pointer == L->back){
		L->index = -1;
	}

	if(length(L) > 1){
		L->back = L->back->prev;
		L->back->next = NULL;
	}else{
		L->front = L->back = NULL;
	}
	L->length--;
	freeNode(&delete);
}

void delete(List L){
	// param: List
	// return: None
	// func: delete the node that the cursor is pointing at

	if(L->pointer != NULL){
		Node delete = L->pointer;
		Node prev;
		Node next;
		if(L->pointer == L->front){
			next = L->pointer->next;
			L->front = next;
			if(next){
				next->prev = NULL;
			}
		}else if(L->pointer == L->back){
			prev = L->pointer->prev;
			L->back = prev;
			if(prev){
				prev->next = NULL;
			}
		}else{
			prev = L->pointer->prev;
			next = L->pointer->next;
	
			prev->next = next;
			next->prev = prev;
		}

		L->pointer = NULL;
		L->index = -1;
		L->length--;
		freeNode(&delete);
	}
}


// Other operation
List copyList(List L){
	// param: List
	// return: List
	// func: copy a List

	if(L != NULL){
		List out = newList();
		Node copier = L->front;
		while(copier != NULL){
			append(out,copier->val);
			copier = copier->next;
		}
	return out;
	}
	return NULL;
		
}

List concatList(List A, List B){
	// param: List 
	// return: List
	// func: concat the two list, A first then B

	List new = newList();
	Node pointer = A->front;
	while(pointer){
		append(new,pointer->val);
		pointer = pointer->next;
	}
	pointer = B->front;
	while(pointer){
		append(new,pointer->val);
		pointer = pointer->next;
	}
	return new;
}
