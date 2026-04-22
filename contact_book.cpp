#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_LENGTH 100

typedef struct Contact {
    char name[INPUT_LENGTH];
    char phone[INPUT_LENGTH];  
    char email[INPUT_LENGTH];
    char address [INPUT_LENGTH];
    char notes[INPUT_LENGTH];
} Contact;

void clear_terminal() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
    printf("\033[2J\033[H");
    fflush(stdout);
}

const char *FILENAME ="contact_book_data.csv";
Contact contact_array[100];

int add_new_entry() {
    FILE *fptr = fopen(FILENAME, "a");
    if (fptr == NULL) return 1;
    char name[INPUT_LENGTH], phone[INPUT_LENGTH], email[INPUT_LENGTH], address[INPUT_LENGTH], notes[INPUT_LENGTH];
    
    printf("Enter name: ");
    fgets(name, INPUT_LENGTH, stdin);
    name[strcspn(name, "\n")] = 0;
    printf("Enter phone: ");
    fgets(phone, INPUT_LENGTH, stdin);
    phone[strcspn(phone, "\n")] = 0;
    printf("Enter email: ");
    fgets(email, INPUT_LENGTH, stdin);
    email[strcspn(email, "\n")] = 0;
    printf("Enter address: ");
    fgets(address, INPUT_LENGTH, stdin);
    address[strcspn(address, "\n")] = 0;
    printf("Enter notes: ");
    fgets(notes, INPUT_LENGTH, stdin);
    notes[strcspn(notes, "\n")] = 0;

    fprintf(fptr, "%s,%s,%s,%s,%s\n", name, phone, email, address, notes);
    fclose(fptr);

    printf("Contact added successfully!\n");
    return 0;
}

int read_csv (Contact contact_array[]) {
    FILE *fptr = fopen (FILENAME, "r");
    if (fptr == NULL) return 0;
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
                strncpy(contact_array[i].phone, field, INPUT_LENGTH);
            } else if (column == 2) {
                strncpy(contact_array[i].email, field, INPUT_LENGTH);
            } else if (column == 3) {
                strncpy(contact_array[i].address, field, INPUT_LENGTH);
            } else if (column == 4) {
                strncpy(contact_array[i].notes, field, INPUT_LENGTH);
            }
            field = strtok (NULL, ",");
            column ++;
        }
        i++;
    }
    fclose(fptr);
    return i;
}

void show_details(Contact c) {
    char back_choice;
    while (1) {
        clear_terminal();
        printf("\n--- Detailed Contact Info ---\n");
        printf("Name:    %s\n", c.name);
        printf("Phone:   %s\n", c.phone);
        printf("Email:   %s\n", c.email);
        printf("Address: %s\n", c.address);
        printf("Notes:   %s\n", c.notes);
        printf("-----------------------------\n");
        printf("\nPress [Q] to back to contact list: ");
        scanf(" %c", &back_choice);
        while (getchar() != '\n');
        if (back_choice == 'q' || back_choice == 'Q') {
            break;
        }
    }
}

int compare_names(const void *a, const void *b) {
    Contact *contactA = (Contact *)a;
    Contact *contactB = (Contact *)b;
    return strcasecmp(contactA->name, contactB->name);
}

int list_contacts() {
    int count = read_csv(contact_array);
    qsort(contact_array, count, sizeof(Contact), compare_names);
    while (1) {
        clear_terminal(); 
        if (count <= 0) {
            printf("No contacts found.\n");
            printf("\nPress Enter to return to main menu...");
            getchar();
            return 0;
        }

        printf("\n--- Contact List ---\n");
        for (int i = 0; i < count; i++) {
            printf("%d. Name: %-15s | Phone: %s\n", i + 1, contact_array[i].name, contact_array[i].phone);
        }
        printf("\nEnter number for details or [Q] to back to main menu: ");
        char sub_input[INPUT_LENGTH];
        fgets(sub_input, INPUT_LENGTH, stdin);
        sub_input[strcspn(sub_input, "\n")] = 0;

        if (sub_input[0] == 'q' || sub_input[0] == 'Q') {
            break; 
        }

        int index = atoi(sub_input);
        if (index > 0 && index <= count) {
            show_details(contact_array[index - 1]);
        } else {
            printf("\nInvalid selection.\n");
            printf("Press Enter to return...");
            getchar();
        }
    }
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc >1) FILENAME = argv[1];
    char choice;
    while (1) {
        clear_terminal();
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