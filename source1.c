#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "meh.h"

void swap(struct card *a, struct card *b){
    struct card *c = a;
    a = b;
    b = c;
}

int is_valid(char a[], char b[]){
    int c = atoi(a);
    if(c <= 0 || c >= 15)
        return 0;
    if(strcmp(b, "HEART") != 0 && strcmp(b, "CLUB") != 0 && strcmp(b, "DIAMOND") != 0 && strcmp(b, "SPADE") != 0)
        return 0;
    return 1;
}

void add_cards(list *deck, char param1[], char param2[]){
    struct card *parameters = malloc(sizeof(card));
    parameters->number = atoi(param1);
    strcpy(parameters->symbol, param2);
    add_nth_node(deck, deck->size, parameters);
    free(parameters);
}

void del(list *set, char param1[], char param2[]){
    int a = atoi(param1);
    unsigned int b = atoi(param2);
    node *nod = get_nth_node(set, a);
    list *lista = (list *)nod->data;
    if(b >= lista->size) {
        printf("The provided index is out of bounds for deck %d.\n", a);
    }
    else {
    node *nod2 = remove_nth_node(lista, b);
    free_node(nod2);
    if(lista->size == 0) {
        node *nod3 = remove_nth_node(set, a);
        free_node(nod3);
    }
    printf("The card was successfully deleted from deck %d.\n", a);
    }
}

void shuffle(list* lista){
    unsigned int count = get_size(lista);
    if(count == 0)
        return;
    for(unsigned int i = 0; i < count / 2; ++i) {
        add_nth_node(lista, count, lista->head->data);
        free(lista->head->data);
        node *kiss = remove_nth_node(lista, 0);
        free(kiss);
        }
    }

void merge_decks(list* set, char param1[], char param2[]) {
    int a = atoi(param1);
    int b = atoi(param2);
    struct node *pack1 = get_nth_node(set, a);
    struct node *pack2 = get_nth_node(set, b);
    struct list *lista1 = (list *)pack1->data;
    struct list *lista2 = (list *)pack2->data;
    struct node *nod1 = lista1->head;
    struct node *nod2 = lista2->head;
    struct list *new_list = list_create(sizeof(card));
    unsigned int i = 0;
    while(nod1 != NULL && nod2 != NULL) {
        add_nth_node(new_list, i++, (card *)(nod1->data));
        add_nth_node(new_list, i++, (card *)(nod2->data));
        nod1 = nod1->next;
        nod2 = nod2->next;
        node *kiss1 = remove_nth_node(lista1, 0);
        free_node(kiss1);
        node *kiss2 = remove_nth_node(lista2, 0);
        free_node(kiss2);        
    }
    if(nod1 != NULL && nod2 == NULL) {
        while(nod1 != NULL) {
            add_nth_node(new_list, i++, (card *)(nod1->data));
            nod1 = nod1->next;
            node *kiss1 = remove_nth_node(lista1, 0);
            free_node(kiss1);
        }
    }
    if(nod2 != NULL && nod1 == NULL) {
        while(nod2 != NULL) {
            add_nth_node(new_list, i++, (card *)(nod2->data));
            nod2 = nod2->next;
            node *kiss2 = remove_nth_node(lista2, 0);
            free_node(kiss2); 
        }
    }
    if(a < b) {
        struct node *kiss1 = remove_nth_node(set, b);
        struct node *kiss2 = remove_nth_node(set, a); 
        free_node(kiss1);
        free_node(kiss2);
    }
    if(a > b) {
        struct node *kiss1 = remove_nth_node(set, a);
        struct node *kiss2 = remove_nth_node(set, b);
        free_node(kiss1);
        free_node(kiss2);
    }
    add_nth_node(set, set->size, new_list);
    free(new_list);
}


void split(list *set, char param1[], char param2[]) {
    unsigned int x = atoi(param1);
    unsigned int y = atoi(param2);
    node *deck = get_nth_node(set, x);
    list* lista = list_create(sizeof(card));
    list *pack = (list *)deck->data;
    unsigned int i = 0;
    if(y >= pack->size || y <= 0) {
        free(lista);
    } else {
    node *nod = get_nth_node(pack, y);
    while(nod != NULL) {
        add_nth_node(lista, i++, (card *)(nod->data));
        nod = nod->next;
        struct node *kiss = remove_nth_node(pack, y);
        free_node(kiss);
    }
    add_nth_node(set, x + 1, lista);
    free(lista);
    }
}

void reverse_deck(list *set, char param[]) {
    unsigned int a = atoi(param);
    node *deck = get_nth_node(set, a);
    list *pack = (list *)deck->data;
    list *lista = list_create(sizeof(card));
    unsigned int s = pack->size;
    unsigned int i = 0;
    if(s == 0) {
        free(lista);
    } else {
    node *nod = pack->head;
    while(nod->next != NULL) {
        nod = nod->next;
    }
    while(nod != NULL) {
        add_nth_node(lista, i++, (card *)(nod->data));
        nod = nod->prev;
        node *kiss = remove_nth_node(pack, s - 1);
        free_node(kiss);
        s--;
    }
    node *kiss = remove_nth_node(set, a);
    free_node(kiss);
    add_nth_node(set, a, lista);
    free(lista);
}
}

// void sort_deck(list *set, char param[]) {
//     unsigned int a = atoi(param);
//     node *deck = get_nth_node(set, a);
//     list *pack = (list *)deck->data;

// }

void show_deck(list *set, char param[]) {
    unsigned int a = atoi(param);
    node *deck = get_nth_node(set, a);
    list *lista = (list *)deck->data;
    printf("Deck %d:\n", a);
    if(lista->size == 0)
       return;
    node *nod = lista->head;
    unsigned int i = 0;
    while(nod != NULL) {
        printf("\t%d %s\n", ((card *)nod->data)->number, ((card *)nod->data)->symbol);
        nod = nod->next;
        i++;
    }
}

void show_all(list *set) {
    unsigned int i = 0;
    if(set->size == 0)
        return;
    node *deck = set->head;
    while(deck != NULL) {
        if(((list *)(deck->data))->size == 0) {
            printf("Deck %d:\n", i);
        } else {
        printf("Deck %d:\n", i);
        list *lista = (list *)deck->data;
        node *hihi = lista->head;
        while(hihi != NULL) {
            printf("\t%d %s\n", ((card *)(hihi->data))->number, ((card *)(hihi->data))->symbol);
            hihi = hihi->next;
        } }
        i++;
        deck = deck->next;
        }
}

void free_shit(list *lista) {
    if(!lista)
        return;
    node *nod = lista->head;
    free(lista);
    free(nod);
}
