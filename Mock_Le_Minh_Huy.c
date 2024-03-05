#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Player
{
    float lucky_ratio;
    char name[24];
    struct Player* next;
} player;

void insert_player(player** root, float lucky_ratio, char* name)
{
    player* new_player = (player*)malloc(sizeof(player));

    if(new_player == NULL)
    {
        exit(1);
    }

    new_player->next = NULL;
    new_player->lucky_ratio = lucky_ratio;
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

void insertBeginList(player** root, float lucky_ratio, char* name)
{
    player* new_player = (player*)malloc(sizeof(player));

    if(new_player == NULL)
    {
        printf("Pointer point to NULL.\n");
        exit(3);
    }

    new_player->lucky_ratio = lucky_ratio;
    strcpy(new_player->name, name);
    new_player->next = *root;

    *root = new_player;
}

void insertAfter(player* node, float lucky_ratio, char* name)
{
    player* new_player = (player*)malloc(sizeof(player));
    if(new_player == NULL)
    {
        exit(5);
    }
    else {
        //do nothing
    }

    new_player->lucky_ratio = lucky_ratio;
    strcpy(new_player->name, name);
    new_player->next = node->next;
    node->next = new_player;
}

void insert_sorted(player** root, float lucky_ratio, char* name)
{
    if(*root == NULL || (*root)->lucky_ratio >= lucky_ratio)
    {
        insertBeginList(root, lucky_ratio, name);
        return;
    }

    player* curr = *root;
    while (curr->next != NULL)
    {
        if(curr->next->lucky_ratio >= lucky_ratio)
        {
            break;
        }
        curr = curr->next;
    }

    insertAfter(curr, lucky_ratio, name);
    
}

void removeElement(player** root, float lucky_ratio, char* name)
{
    if(*root == NULL)
    {
        return;
    }

    if((*root)->lucky_ratio == lucky_ratio)
    {
        player* to_remove = *root;
        *root = (*root)->next;
        return;
    }

    player* curr = *root;
    while (curr->next != NULL)
    {
        if(curr->next->lucky_ratio == lucky_ratio)
        {
            player* to_remove = curr->next;
            curr->next = curr->next->next;
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
        printf("\nPlayer: %s\t\tLucky ratio: %.4f\n", curr->name, curr->lucky_ratio);
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
    float lucky_ratio;
    // Declaring file pointer variable to store the value returned by fopen
    FILE *filePointer;
    // int* arr_magic_num = arrayNumber(magic_number);

    player* root = NULL;

    // Dynamic allocated memory for pointer point to struct
    player* my_player = (player*)malloc(sizeof(player));
    printf("Enter your name: ");
    scanf(" %[^\n]s", name);

    quantity_guest = 0;  

    srand((int)time(0));
    magic_number = random(0, 9999);
    printf("%.4d\n", magic_number);

    int flag = 0;

    arr_icon = resetMagicIcon(arr_icon);
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
        int* arr_guess_num = arrayNumber(input_number);
        is_full = 0;

        for(int i = 0; i < 4; i++)
        {
            if(arr_guess_num[i] == arr_magic_num[i])
            {
                arr_icon[i] = (char)(arr_guess_num[i] + 48);
                is_full++;
            }
            else{
                //do nothing
            }
        }

        if(is_full == 4)
        {
            lucky_ratio = (float)quantity_guest / 10000;
            printf("\nCorrect number!\nYour magic number is %.4d.\n", magic_number);
            free(arr_magic_num);
            free(arr_guess_num);

            my_player->lucky_ratio = lucky_ratio;
            strcpy(my_player->name, name);
            // Opening the file in write mode on binary file
            filePointer = fopen("List_Player.bin", "ab");

            // Check if the filePointer is valid
            if(filePointer == NULL)
            {
                perror("Error opening file");
                return 1;
            }
            else { //do nothing
            }

            // Write data to binary file
            flag = fwrite(my_player, sizeof(player), 1, filePointer);

            // Checking if the data is written 
            if(!flag)
            {
                printf("Write Operation Failure\n");
            }
            else
            {
                printf("Write Operation Successful\n");
            }

            // Close file and save
            fclose(filePointer);
            free(my_player);
            printf("Save data into file text.\n");

            // Open file for reading
            filePointer = fopen("List_Player.bin", "rb");

            // Check if the pointer is valid
            if(filePointer == NULL)
            {
                fprintf(stderr, "Unable to open file for reading");
                return 1;
            }
            // Dynamic allocate an array pointer to store data from file bin
            player* list_player = (player*)malloc(sizeof(player));

            while (fread(list_player, sizeof(player), 1, filePointer) == 1)
            {
                printf("get data from file.bin\n");
                lucky_ratio = list_player->lucky_ratio;
                strcpy(name, list_player->name);
                insert_sorted(&root, lucky_ratio, name);
            }
            
            
            
            printf("\n\tThe lucky ratio history of the player\n");
            // insert_sorted(&root, lucky_ratio, name);
            printNode(&root);
            // Close the file
            fclose(filePointer);

            free(list_player);
            
        }
        else{
            // do nothing
        }

    } while (is_full != 4);
    deallocate(&root);
    free(arr_icon);
    return 0;
}
