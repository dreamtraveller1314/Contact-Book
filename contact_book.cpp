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

const char *FILENAME ="contact_book_data.csv";
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

int read_csv (Contact contact_array[]) {
    FILE *fptr = fopen (FILENAME, "r");
    if (fptr == NULL) return 1;
    char buffer [500];
    int i = 0;
    while (fgets(buffer, sizeof(buffer), fptr)&& i<100) {
        buffer[strcspn(buffer, "\n")] = 0;
        char *field = strtok (buffer, ",");
        int column = 0;
        while (field != NULL){
            if (column == 0) {
                strncpy(contact_array[i].name, field, INPUT_LENGTH);
            } else if (column == 1) {
                strncpy(contact_array[i].address, field, INPUT_LENGTH);
            } else if (column == 2) {
                strncpy(contact_array[i].phone, field, INPUT_LENGTH);
            } else if (column == 3) {
                strncpy(contact_array[i].email, field, INPUT_LENGTH);
            }
            field = strtok (NULL, ",");
            column ++;
        }
        i++;
    }
    fclose(fptr);
    return 0;
}

void print_contact(const Contact *contact) {
    printf("Name: %s | Phone: %s\n", contact->name, contact->phone);
}

int list_contacts() {
    int count = read_csv(contact_array);
    if (count == 0) {
        printf("No contacts found or file empty.\n");
        return 0;
    }
    printf("\n--- Contact List ---\n");
    for (int i = 0; i < count; i++) {
        print_contact(&contact_array[i]);
    }
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc >1) FILENAME = argv[1];
    char choice;
    while (1) {
        printf("\n[A]dd, [L]ist, [Q]uit: ");
        if (scanf(" %c", &choice) != 1) break; 
        getchar();
        if (choice == 'a' || choice == 'A') add_new_entry();
        else if (choice == 'l' || choice == 'L') list_contacts();
        else if (choice == 'q' || choice == 'Q') break;
        else printf(" %c is not a known command.\n", choice);
    }
    return 0;
}