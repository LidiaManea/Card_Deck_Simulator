typedef struct card
{
    int number;
    char symbol[50];
} card;

typedef struct node
{
    void* data;
    struct node *prev, *next;
} node;

typedef struct list
{
    struct node* head;
    unsigned int data_size;
    unsigned int size;
} list;

void swap(struct card *a, struct card *b);
void exit1(list **set);
void free_shit(list *lista);
node* node_create(const void* new_data, unsigned int data_size);
list* list_create(unsigned int data_size);
node* get_nth_node(list* lista, unsigned int n);
node* get_n_node(node* nod, unsigned int n);
void add_nth_node(list* lista, unsigned int n, const void* new_data);
node* remove_nth_node(list* lista, unsigned int n);
unsigned int get_size(list* lista);
int is_valid(char *a, char *b);
void del(list *set, char param1[], char param2[]);
void add_cards(list *deck, char param1[], char param2[]);
void shuffle(list* lista);
void reverse_deck(list *set, char param[]);
void show_deck(list *set, char param[]);
void merge_decks(list* set, char param1[], char param2[]);
// void sort_deck(list *set, char param[]);
void free_node(node* nod);
void split(list* set, char param1[], char param2[]);
void free_list(list* lista);
void show_all(list *set);
void free_set(list *lista);
void free_data_list(list *lista);
