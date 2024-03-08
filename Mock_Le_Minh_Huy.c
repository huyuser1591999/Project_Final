#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Declare struct with name "Player" and use typedef to defining an alias "player"
typedef struct Player
{
    int magic_number;
    float lucky_ratio;
    char name[24];
    struct Player* next;
} player;

// Function check the filePointer is valid
void checkFilePointer(FILE* filePointer);

// Function check the pointer of struct player is valid
void checkPlayerPointer(player* pointer);

// Function add a new player in the begining of list
void insertBeginList(player** root, int magic_number, float lucky_ratio, char* name);

// Function add a new player after a player
void insertAfter(player* node, int magic_number, float lucky_ratio, char* name);

// Function add a new player according to the decrease order of the lucky ratio
void insertSorted(player** root, int magic_number, float lucky_ratio, char* name);

// Function display list of player, with 5 highest player
void printList(player** root);

// Function free the memory of each player in the list
void deallocate(player** root);

// Function return a random number with minN <= number <= maxN
int random(int minN, int maxN);

// Function return a pointer point to an array. This array is array of 4 digits number.
// Each element is 1 digit. "number" argument is the number that want to convert to array
int* arrayNumber(int number);

// Main function of program
int main()
{
    // Declare variable to store option of player
    char options;

    // Declare variable to store name of player
    char name[24];

    // Declare variable to store magic number when program generates it
    int magic_number;

    // Declare variable to store guess number from player
    int input_number;

    // Declare a pointer point to an array of magic number 4 digits. Each element is a digit
    int* arr_magic_num;

    // Declare a pointer point to an array of guess number 4 digits. Each element is a digit
    int* arr_guess_num;

    // Declare variable to store the lucky ratio of the player
    float lucky_ratio;

    // Declaring file pointer variable to store the value returned by fopen
    FILE* filePointer;

    // Label "Replay".
    Replay:

    // Declare a head of linked list player 
    player* root = NULL;

    // Declare variable 'arr_icon' and initialize it with "----" to display on screen when the game start 
    char arr_icon[4] = {'-','-','-','-'};

    // Declare variable to check that is 4 digit of magic number equal guess number
    int is_full = 0;

    // Declare variable to count times when player guest
    int quantity_guest = 0;

    // Dynamic allocated memory for pointer point to struct
    player* my_player = (player*)malloc(sizeof(player));

    // Use function checkPlayerPointer() to check is pointer valid
    checkPlayerPointer(my_player);

    // Dynamic allocated memory for pointer point to struct to get data from file
    player* file_player = (player*)malloc(sizeof(player));

    // Use function checkPlayerPointer() to check is pointer valid
    checkPlayerPointer(file_player);

    // Assigning value random of magic number to variable magic number using function radom()
    magic_number = random(1000, 9999);

    // Using function arrayNumber() to assign each digit of magic number into array of magic number
    arr_magic_num = arrayNumber(magic_number);

    printf("\n\t\tGUESS MAGIC NUMBER GAME\n");

    // Label "nameAgain"
    nameAgain:

    // Request the player enter name
    printf("\nEnter your name: ");
    scanf(" %[^\n]s", name);

    // Use for loop to check that if there are some invalid character in player name
    for (int i = 0; i < strlen(name); i++)
    {
        // Condition true when name has some invalid character
        if((name[i] < 65 && name[i] != 32) || (name[i] > 90 && name[i] < 97) || (name[i] > 122))
        {
            printf("\nInvalid character in your name!\nType again.\n");

            // Go to label "nameAgain" and request player enter name
            goto nameAgain;
        }
        else{
            // do nothing
        }
    }
    
    // Check that the name input from user is valid
    if(strlen(name) > 24)
    {
        printf("\nInvalid length name!\nType again.\n");

        // Go to label "nameAgain" and request player enter name
        goto nameAgain;
    }
    else{
        // do nothing
    }

    // Loop program when the player guess the magic number
    do
    {
        // Display 4 digits with content "----". If the player guess correct, it will be changed
        printf("\nMagic number: ");
        for(int i = 0; i < 4; i++)
        {
            printf("%c", arr_icon[i]);
        }

        // Label "guessAgain"
        guessAgain:
        
        // Request the player guess the magic number
        printf("\n\nGuess integer number: ");
        scanf(" %d", &input_number); 
        
        // Increase this variable each times the player guess
        quantity_guest++;
        
        // Check that the guess number is valid or invalid
        if(input_number < 1000 || input_number > 9999)
        {
            printf("\nInvalid guess number!\nThe number has 4 digits. Guess again.\n");

            // Go to label "guessAgain" and request player enter guess number
            goto guessAgain;
        }
        else{
            // do nothing
        }

        // Using funtion arrayNumber() to assign each digit of guess number into array of guess number
        arr_guess_num = arrayNumber(input_number);

        // Reset is_full every time the player has to guess again
        is_full = 0;

        // Using for loop to get each digit in array of magic number and guess number, and then compare these
        for(int i = 0; i < 4; i++)
        {
            // Compare each digit 
            if(arr_guess_num[i] == arr_magic_num[i]) 
            {
                // Assign each digit of guess number if condition of if is True. Need plus 48 and cast type char base on ASCII table
                arr_icon[i] = (char)(arr_guess_num[i] + 48);

                // Increase 1 value if 1 digits has assigned.
                is_full++;
            }
            else{
                //do nothing
            }
        }

        // Check that is 4 digits has assigned enough.
        if(is_full == 4)
        {
            // Calculate the lucky ratio of player
            lucky_ratio = ((float)1 / quantity_guest) * 100;

            printf("\nCorrect number!\nYour magic number is %.4d.\n", magic_number);

            // Free the memory 
            free(arr_magic_num);
            free(arr_guess_num);

            // Assign data of player into struct player
            my_player->lucky_ratio = lucky_ratio;
            my_player->magic_number = magic_number;
            strcpy(my_player->name, name);

            // Opening the file in write mode on binary file. Use mode "ab" to continues store data of player
            filePointer = fopen("List_Player.bin", "ab");

            // Check if the filePointer is valid
            checkFilePointer(filePointer);

            // Write data to binary file
            fwrite(my_player, sizeof(player), 1, filePointer);

            // Close file and save
            fclose(filePointer);

            // Free the memory
            free(my_player);

            // Open file for reading and get data of previous player
            filePointer = fopen("List_Player.bin", "rb");

            // Check if the pointer is valid
            checkFilePointer(filePointer);

            // Using while loop to get each data of player from file "List_Player.bin"
            while (fread(file_player, sizeof(player), 1, filePointer) == 1)
            {
                // Assign data to pointer of struct "my_player"
                lucky_ratio = file_player->lucky_ratio;
                magic_number = file_player->magic_number;
                strcpy(name, file_player->name);

                // Insert data from pointer "my_player" into linked list according to the increase order of lucky ratio
                insertSorted(&root, magic_number, lucky_ratio, name);
            }

            // Close the file
            fclose(filePointer);
            
        }
        else{
            // do nothing
        }
    
    } while (is_full != 4); // Check that is 4 digits has assigned enough. If not, continues do{} while() loop

    // Show the lucky ratio history of the program, with 5 highest player
    printf("\n---------------------------------------------------------------------------------\n");
    printf("\n\t\tThe lucky ratio history of the player\n");

    // Using function printList() to display each player in the list
    printList(&root);

    printf("\n---------------------------------------------------------------------------------\n");

    printf("\nDo you want to replay?(y/n) ");
    scanf(" %c", &options);

    if(options == 'y')
    {
        goto Replay;
    }
    else{
        // do nothing
    }

    // Free the memory of the list player
    deallocate(&root);

    return 0;
}

// Function check the filePointer is valid.
void checkFilePointer(FILE* filePointer)
{
    // Check that is filePointer point to NULL
    if(filePointer == NULL)
    {
        // Display warning 
        perror("Error opening file.\n");

        // Warning exit program failure because filePointer point to NULL
        exit(1);
    }
    else { 
        //do nothing
    }
}

// Function check the pointer of struct player is valid
void checkPlayerPointer(player* pointer)
{
    // Check that is pointer point to NULL
    if (pointer == NULL) 
    {
        // Display warning 
		printf("Memory not allocated.\n");

        // Warning exit program failure because pointer point to NULL
		exit(1);
	}
    else { 
        //do nothing
    }
}

// Function add a new player in the begining of list
void insertBeginList(player** root, int magic_number, float lucky_ratio, char* name)
{
    // Dynamic allocate memory for new_player
    player* new_player = (player*)malloc(sizeof(player));

    // Use function checkPlayerPointer() to check is new_player is valid
    checkPlayerPointer(new_player);

    // Assign data from argument into node new_player
    new_player->lucky_ratio = lucky_ratio;
    new_player->magic_number = magic_number;
    strcpy(new_player->name, name);
    new_player->next = *root;

    // Assign head of list is new_player
    *root = new_player;
}

// Function add a new player after a player
void insertAfter(player* node, int magic_number, float lucky_ratio, char* name)
{
    // Dynamic allocate memory for new_player
    player* new_player = (player*)malloc(sizeof(player));

    // Use function checkPlayerPointer() to check is new_player is valid
    checkPlayerPointer(new_player);

    // Assign data from argument into node new_player
    new_player->lucky_ratio = lucky_ratio;
    new_player->magic_number = magic_number;
    strcpy(new_player->name, name);

    // Assign address of node next to new_player is address of node next to node pass to function as an argument
    new_player->next = node->next;

    // Assign address of node next to node pass to function as an argument is address of new_player
    node->next = new_player;
}

// Function add a new player according to the decrease order of the lucky ratio
void insertSorted(player** root, int magic_number, float lucky_ratio, char* name)
{
    // Check that if the list is empty or lucky_ratio of player head is smaller than lucky_ratio of new_player
    if(*root == NULL || (*root)->lucky_ratio <= lucky_ratio)
    {
        // Use function insertBeginList() add a new player in the begining of list
        insertBeginList(root, magic_number, lucky_ratio, name);

        // Return function main()
        return;
    }

    // Assign address of player head list to pointer curr
    player* curr = *root;

    // Use while loop to loop throught the list. If curr->next == NULL, curr is the last player in list
    while (curr->next != NULL)
    {
        // Check that if there is a node player had lucky_ratio smaller than lucky_ratio of new_player
        if(curr->next->lucky_ratio <= lucky_ratio)
        {
            // Exit while loop
            break;
        }

        // Assign address of current player is address of next player
        curr = curr->next;
    }

    // Use function insertAfter() add a new player after current player
    insertAfter(curr, magic_number, lucky_ratio, name);
}

// Function display list of player, with 5 highest player
void printList(player** root)
{
    // Assign address of player head list to pointer curr
    player* curr = *root;

    // Declare variable "count" to get 5 highest player
    int count = 0;

    // Use while loop to loop throught the list. If curr == NULL, the program has loop throught all player of list
    while (curr != NULL)
    {
        // Display 5 highest player
        printf("\nMagic Number: %d\tPlayer: %-20s\tLucky ratio: %.2f %%\n", curr->magic_number, curr->name, curr->lucky_ratio);

        // Assign address of current player is address of next player
        curr = curr->next;

        // Increase variable "count" by 1 after a player has been displayed
        count++;

        // Check that if the program has display enough 5 player
        if(count == 5)
        {
            // Return function main()
            return;
        }
        else{
            // do nothing
        }
    }
}

// Function free the memory of each player in the list
void deallocate(player** root)
{
    // Assign address of player head list to pointer curr
    player* curr = *root;

    // Use while loop to loop throught the list. If curr == NULL, the program has loop throught all player of list
    while (curr != NULL)
    {
        // Declare another pointer to point the address of current player
        player* delete_player = curr;

        // Assign address of current player is address of next player
        curr = curr->next;

        // Free the memory of node player 
        free(delete_player);
    } 

    // After while loop. Assign head of list is NULL. List is empty
    *root = NULL;
}

// Function return a random number with minN <= number <= maxN
int random(int minN, int maxN)
{
    // Initialize random number generator
    srand((int)time(0));
	return minN + rand() % (maxN + 1 - minN);
}

// Function return a pointer point to an array. This array is array of 4 digits number.
// Each element is 1 digit. "number" argument is the number that want to convert to array
int* arrayNumber(int number)
{
    // Dynamic allocated memory for a pointer "arr" 
    int* arr = (int*)malloc(4 * sizeof(int));

    // Check that if pointer is invalid
    if(arr == NULL)
    {
        exit(1);
    }

    // Use for loop to assign each digit of "number" equal to each element in array
    for(int i = 3; i >= 0; i--)
    {
        arr[i] = number % 10;
        number /= 10;
    }

    // Return a pointer 
    return arr;
}