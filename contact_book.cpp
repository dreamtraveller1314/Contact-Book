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

int add_new_entry() {
    FILE *fptr = fopen(FILENAME, "a");
    if (fptr == NULL) return 1;
    char name[INPUT_LENGTH], address[INPUT_LENGTH], phone[INPUT_LENGTH], email[INPUT_LENGTH];
    
    printf("Enter name: ");
    fgets(name, INPUT_LENGTH, stdin);
    name[strcspn(name, "\n")] = 0;
    printf("Enter address: ");
    fgets(address, INPUT_LENGTH, stdin);
    address[strcspn(address, "\n")] = 0;
    printf("Enter phone: ");
    fgets(phone, INPUT_LENGTH, stdin);
    phone[strcspn(phone, "\n")] = 0;
    printf("Enter email: ");
    fgets(email, INPUT_LENGTH, stdin);
    email[strcspn(email, "\n")] = 0;

    fprintf(fptr, "%s,%s,%s,%s\n", name, address, phone, email);
    fclose(fptr);

    printf("Contact added successfully!\n");
    return 0;
}