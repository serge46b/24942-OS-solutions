// Напишите программу, которая вставляет строки, введенные с клавиатуры, в список. Память под узлы списка выделяйте динамически с использованием malloc(3). Ввод завершается, когда в начале строки вводится точка (.). Затем все строки из списка выводятся на экран.
// Подсказка: Объявите массив символов размера, достаточного чтобы вместить самую длинную введенную строку. Используйте fgets(3), чтобы прочитать строку, и strlen(3), чтобы определить ее длину. Помните, что strlen(3) не считает нулевой символ, завершающий строку. После определения длины строки, выделите блок памяти нужного размера и внесите новый указатель в список.
// При сдаче этой программы на С++ запрещается использовать std::string и контейнеры STL для реализации списка.  Я понимаю, что это практически лишает смысла использование C++ в этой задаче.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for linked list node
struct Node {
    char *data;         
    struct Node *next;  
};

int main() {
    struct Node *head = NULL;  // Head of the linked list
    struct Node *current = NULL;  // Current node pointer
    char input[1000];       // Buffer for input (large enough for long strings)
    
    printf("Enter strings:\n");
    
    while (1) {
        printf("> ");
        fgets(input, sizeof(input), stdin);

        if (input[0] == '.') {
            break;
        }

        size_t len = strlen(input);
        if (len > 0 && input[len-1] == '\n') {
            input[len-1] = '\0';
            len--;
        }
        
        struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
        if (newNode == NULL) {
            printf("Memory allocation failed!\n");
            return 1;
        }
        
        
        newNode->data = (char*)malloc(len + 1);
        if (newNode->data == NULL) {
            printf("Memory allocation failed!\n");
            free(newNode);
            return 1;
        }
        
        
        strcpy(newNode->data, input);
        newNode->next = NULL;
        
        
        if (head == NULL) {
            head = newNode;
            current = newNode;
        } else {
            current->next = newNode;
            current = newNode;
        }
    }
    
    
    printf("\nAll entered strings:\n");
    current = head;
    while (current != NULL) {
        printf("%s\n", current->data);
        current = current->next;
    }
    
    
    current = head;
    while (current != NULL) {
        struct Node *temp = current;
        current = current->next;
        free(temp->data);
        free(temp);
    }
    
    return 0;
}

