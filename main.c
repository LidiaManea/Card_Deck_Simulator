#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "meh.h"

int main()
{
    list *set;
    set = list_create(sizeof(list));
    char command[50], line[100], param[10][50];
    scanf("%s", command);
    int garbage;
    while (strcmp(command, "EXIT")) {
        for(unsigned int i = 0; i < 10; ++i)
            param[i][0] = '\0';
        fgets(line, 100, stdin);
        int nofc = sscanf(line, "%s %s %s %s", param[0], param[1], param[2], param[3]);
        if(strcmp(command, "ADD_DECK") == 0 && nofc == 1) {
                garbage = sscanf(line, "%s", param[0]);
                int a = atoi(param[0]);
                list *deck  = list_create(sizeof(card));
                int i = 0;
                while(i < a) {
                    fgets(line, 100, stdin);
                    garbage = sscanf(line, "%s %s", param[1], param[2]);
                    if(is_valid(param[1], param[2]) == 1) {
                        add_cards(deck, param[1], param[2]);
                        i++;
                    } else {
                        printf("The provided card is not a valid one.\n");
                    }
                line[0] = garbage;
                for(unsigned int i = 0; i < 100; ++i) {
                    line[i] = '\0';
                }            
                }
                add_nth_node(set, set->size, deck);
                printf("The deck was successfully created with %d cards.\n", a);

                free(deck);
            }
        else if(strcmp(command, "DEL_DECK") == 0 && nofc == 1) {
                garbage = sscanf(line, "%s", param[0]);
                unsigned int a = atoi(param[0]);
                if(a >= set->size) {
                    printf("The provided index is out of bounds for the deck list.\n"); 
                } else {
                node *kiss = remove_nth_node(set, a);
                free_list(kiss->data);
                free(kiss);
                printf("The deck %d was successfully deleted.\n", a);
                }
            }
        else if(strcmp(command, "DEL_CARD") == 0 && nofc == 2) {
                garbage = sscanf(line, "%s %s", param[0], param[1]);
                unsigned int a = atoi(param[0]);
                unsigned int b = atoi(param[1]);
                if(a >= set->size) {
                    printf("The provided index is out of bounds for the deck list.\n");
                } else {
                    node *nod = get_nth_node(set, a);
                    if(b >= get_size((list *)nod->data)) {
                        printf("The provided index is out of bounds for deck %d.\n", a);
                    } else {
                        del(set, param[0], param[1]);
                    }
                }
        }
        else if(strcmp(command, "ADD_CARDS") == 0 && nofc == 2) {
                garbage = sscanf(line, "%s %s", param[0], param[1]);
                unsigned int a = atoi(param[0]);
                unsigned int b = atoi(param[1]);
                if(a >= set->size) {
                    printf("The provided index is out of bounds for the deck list.\n");
                } else {
                    struct node *pack = get_nth_node(set, a);
                    list *lista = (list *)pack->data;
                    unsigned int i = 0;
                    while(i < b) {
                        fgets(line, 100, stdin);
                        garbage = sscanf(line, "%s %s", param[2], param[3]);
                        if(is_valid(param[2], param[3]) == 0) {
                            printf("The provided card is not a valid one.\n");
                        } else {
                            add_cards(lista, param[2], param[3]);
                            i++;
                        }
                        line[0] = garbage;
                        for(unsigned int i = 0; i < 100; ++i) {
                            line[i] = '\0'; 
                        }
                    }
                    printf("The cards were successfully added to deck %d.\n", a);
           }
        }
        else if(strcmp(command, "DECK_NUMBER") == 0 && nofc == EOF) {
            unsigned int count = get_size(set);
            printf("The number of decks is %d.\n", count);
        }
        else if(strcmp(command, "DECK_LEN") == 0 && nofc == 1) {
                garbage = sscanf(line, "%s", param[0]);
                unsigned int a = atoi(param[0]);
                if(a >= set->size) {
                    printf("The provided index is out of bounds for the deck list.\n");
                }
                else {
                    struct node *pack = get_nth_node(set, a);
                    struct list *lista = (list *)pack->data;
                    unsigned int count = get_size(lista);
                    printf("The length of deck %d is %d.\n", a, count);
                }
            }
        else if(strcmp(command, "SHUFFLE_DECK") == 0 && nofc == 1) {
                garbage = sscanf(line, "%s", param[0]);
                unsigned int a = atoi(param[0]);
                if(a >= set->size) {
                    printf("The provided index is out of bounds for the deck list.\n");               
                } else {
                struct node *pack = get_nth_node(set, a);
                struct list *lista = (list *)pack->data;
                shuffle(lista);
                printf("The deck %d was successfully shuffled.\n", a);
            }
        }
        else if(strcmp(command, "MERGE_DECKS") == 0 && nofc == 2) {
                garbage = sscanf(line, "%s %s", param[0], param[1]);
                unsigned int a = atoi(param[0]);
                unsigned int b = atoi(param[1]);
                if(a >= set->size || b >= set->size) {
                    printf("The provided index is out of bounds for the deck list.\n");               
                } else {
                merge_decks(set, param[0], param[1]);
                printf("The deck %d and the deck %d were successfully merged.\n", a, b);
            }
        }
        else if(strcmp(command, "SPLIT_DECK") == 0 && nofc == 2) {
                garbage = sscanf(line, "%s %s", param[0], param[1]);
                unsigned int a = atoi(param[0]);
                unsigned int b = atoi(param[1]);
                if(a >= set->size) {
                    printf("The provided index is out of bounds for the deck list.\n");                    
                } else {
                    node *nod = get_nth_node(set, a);
                    if(b >= ((list *)nod->data)->size) {
                        printf("The provided index is out of bounds for deck %d.\n", a);
                    } else {
                        split(set, param[0], param[1]);
                        printf("The deck %d was successfully split by index %d.\n", a, b);
                    }
                }
        }
        else if(strcmp(command, "REVERSE_DECK") == 0 && nofc == 1) {
                garbage = sscanf(line, "%s", param[0]);
                unsigned int a = atoi(param[0]);
                if(a >= set->size) {
                    printf("The provided index is out of bounds for the deck list.\n");
                } else {
                reverse_deck(set, param[0]);
                printf("The deck %d was successfully reversed.\n", a);
            }
        }
        else if(strcmp(command, "SHOW_DECK") == 0 && nofc == 1) {
                garbage = sscanf(line, "%s", param[0]);
                unsigned int a = atoi(param[0]);
                if(a >= set->size) {
                    printf("The provided index is out of bounds for the deck list.\n");
                } else {
                    show_deck(set, param[0]);
                }
            }
        // else if(strcmp(command, "SORT_DECK") == 0 && nofc == 1) {
        //         garbage = sscanf(line, "%s", param[0]);
        //         unsigned int a = atoi(param[0]);
        //         if(a >= set->size) {
        //             printf("The provided index is out of bounds for the deck list.\n");
        //         } else {

        //         }
        // } 
        else  {
            if(strcmp(command, "SHOW_ALL") == 0 && nofc == EOF) {
                show_all(set);
                // sort_deck(set, param[0]);
            }
            else {
                printf("Invalid command. Please try again.\n");
            }
        }
    scanf("%s", command);
    line[0] = garbage;
    for(unsigned int i = 0; i < 100; ++i) {
        line[i] = '\0';
    }
    }
    free_set(set);
    return 0;
}
