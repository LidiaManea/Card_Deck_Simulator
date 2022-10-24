#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "meh.h"

#define MAX_STRING_SIZE 64

node* node_create(const void* new_data, unsigned int data_size) {
    node* nod = malloc(sizeof(node));
    nod->data = malloc(data_size);
    nod->next = NULL;
    nod->prev = NULL;
    memcpy(nod->data, new_data, data_size);
    return nod;
}

list* list_create(unsigned int data_size)
{
    list* lista = malloc(sizeof(list));
    lista->head = NULL;
    lista->size = 0;
    lista->data_size = data_size;
    return lista;

}

unsigned int get_size_(node* nod) {
    struct node *nod2 = nod;
    unsigned int count = 0;
    while(nod2 != NULL) {
        count++;
        nod2 = nod2->next;
    }
    return count;
}

node* get_nth_node(list* lista, unsigned int n)
{
    node* nod;
    nod = lista->head; 
    for(unsigned int i = 0; i < n; ++i)
        nod = nod->next;
    return nod;
}

void add_nth_node(list* lista, unsigned int n, const void* new_data)
{
    if(n >= lista->size) {
        if(lista->size == 0) {
            node *nod1 = node_create(new_data, lista->data_size);
            lista->head = nod1;
            lista->size++;
        } else {
            node *nod1 = lista->head;
            for(unsigned int i = 0; i < lista->size - 1; ++i)
                nod1 = nod1->next;
            node *nod = node_create(new_data, lista->data_size);
            lista->size++;
            nod1->next = nod;
            nod->prev = nod1;
            nod->next = NULL;
        }
    } else {
    	if(n == 0) {
    		node *nod1 = node_create(new_data, lista->data_size);
    		nod1->next = lista->head;
            lista->head->prev = nod1;
    		lista->head = nod1;
    		lista->size++;
    	} else {
            node *curr = lista->head;
            for(unsigned int i = 0; i < n - 1; ++i)
                curr = curr->next;
            node *nod = node_create(new_data, lista->data_size);
            lista->size++;
            nod->next = curr->next;
            nod->prev = curr;
            curr->next = nod;
            nod->next->prev = nod;
        }
    }

}

node* remove_nth_node(list* lista, unsigned int n)
{
    node *previous;
    node *nod1;
    node *nod2;
    nod1 = lista->head;
    if(n == 0 && lista->head->next) {
    		lista->size--;
    		nod2 = nod1;
    		lista->head = nod1->next;
            lista->head->prev = NULL;
    		return nod2;
    }
    else if(n == 0 && !lista->head->next) {
        	lista->size--;
    		lista->head = NULL;
    		return nod1;
    }
    else if(n < lista->size - 1)	
    {   for(unsigned int i = 0; i < n - 1; ++i)
    			nod1 = nod1->next;
    	lista->size--;
    	previous = nod1->next;
    	nod1->next = nod1->next->next;
        previous->next->prev = nod1;
    	previous->next = NULL;
        previous->prev = NULL;
    	return previous; 
    }
    else {
    	while(nod1->next) {
            nod1 = nod1->next;
        }
        lista->size--;
        nod1->prev->next = NULL;
        return nod1;
    }
}

unsigned int get_size(list* lista)
{
    unsigned int count = 0;
    node* nod;
    nod = lista->head;
    while(nod != NULL) {
        count++;
        nod = nod->next;
    }
    return count;
}

void free_node(node* nod)
{
    free(nod->data);
    free(nod);

}

void free_list(list* lista)
{
    struct node *nod;

    if (!(lista)) {
        return;
    }
     while (get_size(lista)){
        nod = remove_nth_node(lista, 0);
        free_node(nod);
    }
    free(lista);
}

void free_set(list *lista) {
    if (!lista) {
        return;
    }
    struct node *nod = lista->head, *prev;

    while (nod != NULL){
        prev = nod;
        free_list((list*)nod->data);
        nod = nod->next;
        free(prev);
    }
    free(lista);
    lista = NULL;
}


void exit1(list **set) {
    if(!(*set))
        return;
    struct node* curr_deck = (*set)->head;
    while(curr_deck != NULL) {
        struct node *remove_deck = curr_deck;
        while(get_size_(remove_deck)) {
            struct node *remove_card = remove_nth_node((list *)curr_deck, 0);
            free(remove_card->data);
            free(remove_card);
        }
        curr_deck = curr_deck->next;
        free(remove_deck);
    }
    free((*set));
}

void free_data_list(list *lista) {
    if(!lista)
        return;
    struct node *nod = lista->head;
    while(nod != NULL) {
        node *newnod = nod->next;
        free(nod);
        nod = newnod;
    }
}
