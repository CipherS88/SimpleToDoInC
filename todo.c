/**
A simple To-Do List Manager in C.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 


#define MAX_DESC_LEN 256
#define FILENAME "tasks.txt"




typedef enum {
    PENDING,
    COMPLETED
} Status;


typedef struct Task {
    int id;                        
    char description[MAX_DESC_LEN]; 
    Status status;                 
    struct Task* next;             
} Task;


Task* g_head = NULL;   
int g_nextTaskId = 1; 


void printMenu();
void clearScreen();
void pressEnterToContinue();
void handleInvalidInput();
void safeFgets(char* buffer, int size);
char* getStatusString(Status s);

Task* createTask(int id, const char* description, Status status);
void freeList();

void addTask();
void viewTasks();
void markTaskComplete();
void editTask();
void deleteTask();

void saveTasksToFile();
void loadTasksFromFile();




int main() {
    int choice = 0;
    loadTasksFromFile();

    while (1) {
        clearScreen();
        printMenu();
        printf("Enter your choice (1-7): ");
        if (scanf("%d", &choice) != 1) {
            handleInvalidInput();
            choice = 0; 
        } else {
            handleInvalidInput(); 
        }

        switch (choice) {
            case 1:
                addTask();
                break;
            case 2:
                viewTasks();
                break;
            case 3:
                markTaskComplete();
                break;
            case 4:
                editTask();
                break;
            case 5:
                deleteTask();
                break;
            case 6:
                saveTasksToFile();
                break;
            case 7:
                printf("Saving and exiting...\n");
                saveTasksToFile(); 
                freeList();        
                exit(0);           
            default:
                printf("\nInvalid choice. Please enter a number between 1 and 7.\n");
        }

        pressEnterToContinue();
    }

    return 0;
}

void printMenu() {
    printf("==============================\n");
    printf("      C To-Do List Manager    \n");
    printf("==============================\n");
    printf("1. Add New Task\n");
    printf("2. View All Tasks\n");
    printf("3. Mark Task as Complete\n");
    printf("4. Edit Task Description\n");
    printf("5. Delete Task\n");
    printf("6. Save Tasks to File\n");
    printf("7. Save and Exit\n");
    printf("------------------------------\n");
}


void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}


void pressEnterToContinue() {
    printf("\nPress Enter to continue...");

    while (getchar() != '\n'); 
}


void handleInvalidInput() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void safeFgets(char* buffer, int size) {
    if (fgets(buffer, size, stdin) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';
    }
}

char* getStatusString(Status s) {
    return (s == COMPLETED) ? "COMPLETED" : "PENDING";
}

//CoreLogicFunctions
Task* createTask(int id, const char* description, Status status) {
    Task* newTask = (Task*)malloc(sizeof(Task));
    if (newTask == NULL) {
        printf("Error: Memory allocation failed!\n");
        return NULL;
    }
    newTask->id = id;
    strncpy(newTask->description, description, MAX_DESC_LEN - 1);
    newTask->description[MAX_DESC_LEN - 1] = '\0'; 
    newTask->status = status;
    newTask->next = NULL;
    return newTask;
}
void freeList() {
    Task* current = g_head;
    Task* temp;
    while (current != NULL) {
        temp = current;
        current = current->next;
        free(temp);
    }
    g_head = NULL;
}
void addTask() {
    char description[MAX_DESC_LEN];
    printf("\nEnter task description: ");
    safeFgets(description, MAX_DESC_LEN);

    if (strlen(description) == 0) {
        printf("Task description cannot be empty.\n");
        return;
    }


    Task* newTask = createTask(g_nextTaskId, description, PENDING);
    if (newTask == NULL) return;

    g_nextTaskId++; 
    if (g_head == NULL) {
        g_head = newTask;
    } else {
        Task* current = g_head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newTask;
    }
    printf("Task #%d added successfully.\n", newTask->id);
}
void viewTasks() {
    printf("\n--- All Tasks ---\n");
    if (g_head == NULL) {
        printf("No tasks in the list.\n");
        return;
    }

    printf("%-5s | %-10s | %s\n", "ID", "Status", "Description");
    printf("--------------------------------------------------\n");

    Task* current = g_head;
    while (current != NULL) {
        printf("%-5d | %-10s | %s\n",
               current->id,
               getStatusString(current->status),
               current->description);
        current = current->next;
    }
}


void markTaskComplete() {
    viewTasks(); 
    if (g_head == NULL) return;

    int id;
    printf("\nEnter Task ID to mark as complete: ");
    if (scanf("%d", &id) != 1) {
        handleInvalidInput();
        printf("Invalid ID.\n");
        return;
    }
    handleInvalidInput();

    Task* current = g_head;
    while (current != NULL) {
        if (current->id == id) {
            current->status = COMPLETED;
            printf("Task #%d marked as complete.\n", id);
            return;
        }
        current = current->next;
    }
    printf("Task #%d not found.\n", id);
}


void editTask() {
    viewTasks();
    if (g_head == NULL) return;

    int id;
    printf("\nEnter Task ID to edit: ");
    if (scanf("%d", &id) != 1) {
        handleInvalidInput();
        printf("Invalid ID.\n");
        return;
    }
    handleInvalidInput();

    Task* current = g_head;
    while (current != NULL) {
        if (current->id == id) {
            char newDescription[MAX_DESC_LEN];
            printf("Enter new description for Task #%d: ", id);
            safeFgets(newDescription, MAX_DESC_LEN);

            if (strlen(newDescription) == 0) {
                printf("Description cannot be empty.\n");
                return;
            }

            strncpy(current->description, newDescription, MAX_DESC_LEN - 1);
            current->description[MAX_DESC_LEN - 1] = '\0';
            printf("Task #%d description updated.\n", id);
            return;
        }
        current = current->next;
    }
    printf("Task #%d not found.\n", id);
}



void deleteTask() {
    viewTasks();
    if (g_head == NULL) return;
    int id;
    printf("\nEnter Task ID to delete: ");
    if (scanf("%d", &id) != 1) {
        handleInvalidInput();
        printf("Invalid ID.\n");
        return;
    }
    handleInvalidInput();
    Task* current = g_head;
    Task* prev = NULL;
    while (current != NULL && current->id != id) {
        prev = current;
        current = current->next;
    }
    if (current == NULL) {
        printf("Task #%d not found.\n", id);
        return;
    }
    if (prev == NULL) {
        g_head = current->next;
    } else {
        prev->next = current->next;
    }

    free(current); 
    printf("Task #%d deleted successfully.\n", id);
}

//File I/O Functions


void saveTasksToFile() {
    FILE* file = fopen(FILENAME, "w"); // Open in write mode
    if (file == NULL) {
        printf("Error: Could not open file %s for writing.\n", FILENAME);
        return;
    }

    Task* current = g_head;
    while (current != NULL) {

        fprintf(file, "%d|%d|%s\n",
                current->id,
                current->status,
                current->description);
        current = current->next;
    }

    fclose(file);
    printf("Tasks saved to %s.\n", FILENAME);
}


void loadTasksFromFile() {
    FILE* file = fopen(FILENAME, "r"); // Open in read mode
    if (file == NULL) {

        printf("No existing task file found. Starting fresh.\n");
        return;
    }

 
    freeList();
    g_head = NULL;
    g_nextTaskId = 1; 

    char line[MAX_DESC_LEN + 20]; 
    int maxId = 0;

    while (fgets(line, sizeof(line), file) != NULL) {
        int id, statusInt;
        char description[MAX_DESC_LEN];

        if (sscanf(line, "%d|%d|%[^\n]", &id, &statusInt, description) == 3) {
            
            Task* newTask = createTask(id, description, (Status)statusInt);
            if (newTask == NULL) continue; 
            if (g_head == NULL) {
                g_head = newTask;
            } else {
                Task* current = g_head;
                while (current->next != NULL) {
                    current = current->next;
                }
                current->next = newTask;
            }

            if (id > maxId) {
                maxId = id;
            }
        }
    }
    
    g_nextTaskId = maxId + 1;

    fclose(file);
    printf("Tasks loaded from %s.\n", FILENAME);
}
