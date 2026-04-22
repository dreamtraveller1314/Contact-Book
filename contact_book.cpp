#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_LENGTH 100

typedef struct Contact {
    char name[INPUT_LENGTH];
    char address [INPUT_LENGTH];
    char phone[INPUT_LENGTH];  
    char email[INPUT_LENGTH];
} Contact;

char *FILENAME = "contact_book_data.csv";
Contact contact_array[100];
