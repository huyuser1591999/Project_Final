#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Player
{
    int quantity_guest;
    char* name;
    struct Player* next;
} player;

void insert_player(player** root, int quantity_guest, char* name)
{
    player* new_player = (player*)malloc(sizeof(player));

    if(new_player == NULL)
    {
        exit(1);
    }

    new_player->next = NULL;
    new_player->quantity_guest = quantity_guest;
    new_player->name = malloc(24);
    strcpy(new_player->name, name);

    if(*root == NULL)
    {
        *root = new_player;
        return;
    }

    player* curr = *root;
    while (curr->next != NULL)
    {
        curr = curr->next;
    }
    curr->next = new_player;
}

void insertBeginList(player** root, int quantity_guest, char* name)
{
    player* new_player = (player*)malloc(sizeof(player));

    if(new_player == NULL)
    {
        printf("Pointer point to NULL.\n");
        exit(3);
    }

    new_player->quantity_guest = quantity_guest;
    new_player->name = malloc(24);
    strcpy(new_player->name, name);
    new_player->next = *root;

    *root = new_player;
}

void insertAfter(player* node, int quantity_guest, char* name)
{
    player* new_player = (player*)malloc(sizeof(player));
    if(new_player == NULL)
    {
        exit(5);
    }
    else {
        //do nothing
    }

    new_player->quantity_guest = quantity_guest;
    new_player->name = malloc(24);
    strcpy(new_player->name, name);
    new_player->next = node->next;
    node->next = new_player;
}

void insert_sorted(player** root, int quantity_guest, char* name)
{
    if(*root == NULL || (*root)->quantity_guest >= quantity_guest)
    {
        insertBeginList(root, quantity_guest, name);
        return;
    }

    player* curr = *root;
    while (curr->next != NULL)
    {
        if(curr->next->quantity_guest >= quantity_guest)
        {
            break;
        }
        curr = curr->next;
    }

    insertAfter(curr, quantity_guest, name);
    
}

void removeElement(player** root, int quantity_guest, char* name)
{
    if(*root == NULL)
    {
        return;
    }

    if((*root)->quantity_guest == quantity_guest)
    {
        player* to_remove = *root;
        *root = (*root)->next;
        return;
    }

    player* curr = *root;
    while (curr->next != NULL)
    {
        if(curr->next->quantity_guest == quantity_guest)
        {
            player* to_remove = curr->next;
            curr->next = curr->next->next;
            free(to_remove->name);
            free(to_remove);
            return;
        }
        curr = curr->next;
    }
    
}

void printNode(player** root)
{
    player* curr = *root;

    while (curr != NULL)
    {
        printf("\nName: %s\t\tNumber of predictions: %d\n", curr->name, curr->quantity_guest);
        curr = curr->next;
    }
}

void deallocate(player** root)
{
    player* curr = *root;
    while (curr != NULL)
    {
        player* delete_player = curr;
        curr = curr->next;
        free(delete_player->name);
        free(delete_player);
    }  
    *root = NULL;
    printf("Free the memory.\n");
}

int random(int minN, int maxN)
{
	return minN + rand() % (maxN + 1 - minN);
}

int* arrayMagicNumber(int* arr_magic_num)
{
    srand((int)time(0));
    for (int i = 0; i < 4; i++)
    {
        arr_magic_num[i] = random(0, 9);
    }
    return arr_magic_num;
    
}

int* arrayNumber(int number)
{
    int* arr = (int*)malloc(4 * sizeof(int));
    if(arr == NULL)
    {
        exit(1);
    }
    for(int i = 3; i >= 0; i--)
    {
        arr[i] = number % 10;
        number /= 10;
    }
    return arr;
}

char* resetMagicIcon(char* icon)
{
    for (int i = 0; i < 4; i++)
    {
        icon[i] = '-';
    }
    return icon;
}

int main()
{
    char name[24];
    int is_full;
    int magic_number;
    int quantity_guest;
    int input_number;
    char* arr_icon = (char*)malloc(4 * sizeof(char));
    // int* arr_magic_num = arrayNumber(magic_number);

    player* root = NULL;

    playAgain:

    printf("Enter your name: ");
    scanf(" %[^\n]s", name);

    quantity_guest = 0;  

    srand((int)time(0));
    magic_number = random(0, 9999);
    printf("%.4d\n", magic_number);
    
    arr_icon = resetMagicIcon(arr_icon);
    is_full = 0;
    int* arr_magic_num = arrayNumber(magic_number);
    do
    {
        printf("\nMagic number: ");
        for(int i = 0; i < 4; i++)
        {
            printf("%c", arr_icon[i]);
        }
        quantity_guest++;
        printf("\n\nGuest number: ");
        scanf(" %d", &input_number); 

        for(int i = 0; i < 4; i++)
        {
            if((arr_icon[i] == '-') && (input_number == arr_magic_num[i]))
            {
                arr_icon[i] = (char)(input_number + 48);
                is_full++;
            }
            else{
                //do nothing
            }
        }

        if(is_full == 4)
        {
            printf("\nCorrect number!\nYour magic number is %.4d.\n", magic_number);
            free(arr_magic_num);

            printf("\n\tThe lucky ratio history of the player\n");
            insert_sorted(&root, quantity_guest, name);
            printNode(&root);
            char options;
            printf("\nDo you want to play again?(y/n) ");
            scanf(" %c", &options);
            if(options == 'y')
            {
                goto playAgain;
            }
            else{
                // do nothing
            }
        }
        else{
            // do nothing
        }

    } while (is_full != 4);
    deallocate(&root);
    free(arr_icon);

    return 0;
}
