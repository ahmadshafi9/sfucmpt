#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Contact {
    char *firstName;
    char *familyName;
    long long phoneNum; /* 10-digit phone number stored as a 64-bit integer */
    char *address;
    int age;
} Contact;

/* Function Prototypes */
int countContacts(Contact **contacts);
Contact *readNewContact();
Contact **appendContact(Contact **contacts, Contact *newContact);
Contact **insertContactAlphabetical(Contact **contacts, Contact *newContact);
Contact **removeContactByIndex(Contact **contacts);
int removeContactByFullName(Contact ***contacts);
void listContacts(Contact **contacts);
void saveContactsToFile(Contact **contacts, char *filename);
void printContactsToFile(Contact **contacts, char *filename);
Contact **loadContactsFromFile(Contact **addressBook, char *filename);
Contact **appendContactsFromFile(Contact **contacts, char *filename);
Contact **mergeContactsFromFile(Contact **contacts, char *filename);
Contact **editContact(Contact **contacts, int index);

/* Helper function prototypes */
void freeContact(Contact *contact);
void freeContacts(Contact **contacts);
int compareContacts(Contact *contact1, Contact *contact2);
int isDuplicateContact(Contact **contacts, Contact *newContact);
char *readString();
int readInteger();
long long readPhoneNumber();
void displayMenu();
void displayEditMenu();
char *allocateString(const char *str);

int main() {
    Contact **addressBook = NULL;
    char filename[256];
    int choice;
    int index;

    /* Initialize the address book */
    addressBook = (Contact **)malloc(sizeof(Contact *));
    if (addressBook == NULL) {
        printf("Error: Memory allocation failed for initial addressBook\n");
        return 1;
    }
    addressBook[0] = NULL; /* NULL-terminate the array */

    do {
        displayMenu();
        choice = readInteger();

        switch (choice) {
            case 1: /* Append Contact */
                addressBook = appendContact(addressBook, readNewContact());
                break;
            case 2: /* Insert Contact in Alphabetical Order */
                addressBook = insertContactAlphabetical(addressBook, readNewContact());
                break;
            case 3: /* Remove Contact by Index */
                addressBook = removeContactByIndex(addressBook);
                break;
            case 4: /* Remove Contact by Full Name */
                removeContactByFullName(&addressBook);
                break;
            case 5: /* Find and Edit Contact */
                printf("Enter index of contact to edit (0-%d):\n", countContacts(addressBook) - 1);
                index = readInteger();
                addressBook = editContact(addressBook, index);
                break;
            case 6: /* List Contacts */
                listContacts(addressBook);
                break;
            case 7: /* Print Contacts to File with input file format */
                printf("Enter filename to save contacts in input format:\n");
                scanf("%255s", filename);
                getchar(); /* Consume newline */
                saveContactsToFile(addressBook, filename);
                break;
            case 8: /* Print Contacts to File (Human Readable) */
                printf("Enter filename to save contacts in human readable format:\n");
                scanf("%255s", filename);
                getchar(); /* Consume newline */
                printContactsToFile(addressBook, filename);
                break;
            case 9: /* Load Contacts from File Replacing Existing Contacts */
                printf("Enter filename to load contacts from (replacing existing):\n");
                scanf("%255s", filename);
                getchar(); /* Consume newline */
                addressBook = loadContactsFromFile(addressBook, filename);
                break;
            case 10: /* Append Contacts from File */
                printf("Enter filename to append contacts from:\n");
                scanf("%255s", filename);
                getchar(); /* Consume newline */
                addressBook = appendContactsFromFile(addressBook, filename);
                break;
            case 11: /* Merge Contacts from File */
                printf("Enter filename to merge contacts from:\n");
                scanf("%255s", filename);
                getchar(); /* Consume newline */
                addressBook = mergeContactsFromFile(addressBook, filename);
                break;
            case 12: /* Exit */
                printf("Exiting Address Book Application\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 12);

    /* Free all allocated memory before exiting */
    freeContacts(addressBook);
    return 0;
}

/* Count the number of contacts in a NULL-terminated array */
int countContacts(Contact **contacts) {
    int count = 0;
    if (contacts == NULL) {
        return 0;
    }
    while (contacts[count] != NULL) {
        count++;
    }
    return count;
}

/* Read a new contact from user input */
Contact *readNewContact() {
    Contact *newContact = (Contact *)malloc(sizeof(Contact));
    if (newContact == NULL) {
        printf("Error: Memory allocation failed for Contact in readNewContact\n");
        return NULL;
    }

    /* Initialize with NULL pointers to prevent issues during cleanup */
    newContact->firstName = NULL;
    newContact->familyName = NULL;
    newContact->address = NULL;
    
    /* Read first name */
    printf("Enter the first name:\n");
    newContact->firstName = readString();
    if (newContact->firstName == NULL) {
        printf("Error: unable to allocate memory for the first name string\n");
        freeContact(newContact);
        return NULL;
    }

    /* Read family name */
    printf("Enter the family name:\n");
    newContact->familyName = readString();
    if (newContact->familyName == NULL) {
        printf("Error: unable to allocate memory for the family name string\n");
        freeContact(newContact);
        return NULL;
    }

    /* Read address */
    printf("Enter the address:\n");
    newContact->address = readString();
    if (newContact->address == NULL) {
        printf("Error: unable to allocate memory for the address string\n");
        freeContact(newContact);
        return NULL;
    }

    /* Read phone number */
    printf("Enter 10-digit phone number that must not start with 0:\n");
    newContact->phoneNum = readPhoneNumber();

    /* Read age */
    printf("Enter the age:\n");
    newContact->age = 0;
    int attempts = 0;
    int validAge = 0;
    int age;

    while (!validAge && attempts < 5) {
        age = readInteger();
        if (age >= 1 && age <= 150) {
            newContact->age = age;
            validAge = 1;
        } else {
            attempts++;
            if (attempts < 5) {
                printf("Error: Invalid age. Try again:\n");
            }
        }
    }

    if (!validAge) {
        printf("Error: Could not read a valid age\n");
        newContact->age = 0;
    }

    return newContact;
}

/* Append a contact to the end of the contacts array */
Contact **appendContact(Contact **contacts, Contact *newContact) {
    int count;
    Contact **newContacts;

    if (newContact == NULL) {
        return contacts;
    }

    count = countContacts(contacts);
    
    /* Allocate space for one more contact pointer plus NULL terminator */
    newContacts = (Contact **)realloc(contacts, (count + 2) * sizeof(Contact *));
    if (newContacts == NULL) {
        printf("Error: Memory reallocation error in appendContact\n");
        freeContact(newContact);
        freeContacts(contacts);
        exit(1);
    }

    /* Append the new contact and NULL terminate */
    newContacts[count] = newContact;
    newContacts[count + 1] = NULL;

    printf("Contact appended successfully by appendContact\n");
    return newContacts;
}

/* Insert a contact in alphabetical order by family name and first name */
Contact **insertContactAlphabetical(Contact **contacts, Contact *newContact) {
    int count, i, j;
    Contact **newContacts;

    if (newContact == NULL) {
        return contacts;
    }

    count = countContacts(contacts);
    
    /* Allocate space for one more contact pointer plus NULL terminator */
    newContacts = (Contact **)realloc(contacts, (count + 2) * sizeof(Contact *));
    if (newContacts == NULL) {
        printf("Error: Memory reallocation error in insertContactAlphabetical\n");
        freeContact(newContact);
        freeContacts(contacts);
        exit(1);
    }

    /* Find the correct position for insertion */
    i = 0;
    while (i < count && 
           compareContacts(newContact, newContacts[i]) > 0) {
        i++;
    }

    /* Shift contacts to make room for the new contact */
    for (j = count; j > i; j--) {
        newContacts[j] = newContacts[j - 1];
    }

    /* Insert the new contact and NULL terminate */
    newContacts[i] = newContact;
    newContacts[count + 1] = NULL;

    printf("Contact was successfully added in alphabetical order\n");
    return newContacts;
}

/* Remove a contact by index */
Contact **removeContactByIndex(Contact **contacts) {
    int index, count, i;
    Contact **newContacts;

    if (contacts == NULL) {
        printf("Error: value of addressBook received in removeContactByIndex was NULL\n");
        return NULL;
    }

    count = countContacts(contacts);
    if (count == 0) {
        printf("Error: No contacts available to remove\n");
        return contacts;
    }

    printf("Removing a Contact by index\n");
    printf("Enter index to remove (0 based):\n");
    
    if (scanf("%d", &index) != 1) {
        printf("Error: Value of index supplied could not be read.\n");
        getchar(); /* Clear input buffer */
        return contacts;
    }
    getchar(); /* Consume newline */

    if (index < 0 || index >= count) {
        printf("Error: Index out of range in removeContactByIndex\n");
        return contacts;
    }

    /* Free the contact at the specified index */
    freeContact(contacts[index]);

    /* Shift the remaining contacts to fill the gap */
    for (i = index; i < count - 1; i++) {
        contacts[i] = contacts[i + 1];
    }

    /* Reallocate the array to the new size */
    newContacts = (Contact **)realloc(contacts, count * sizeof(Contact *));
    if (newContacts == NULL && count > 0) {
        printf("Error: Memory reallocation failed in removeContactByIndex\n");
        return contacts; /* Return original array if reallocation fails */
    }

    /* NULL terminate the array */
    newContacts[count - 1] = NULL;

    printf("Contact removed successfully by removeContactByIndex\n");
    return newContacts;
}

/* Remove a contact by full name */
int removeContactByFullName(Contact ***contacts) {
    char *firstName, *familyName;
    int count, i, j, found = 0;
    Contact **newContacts;

    if (contacts == NULL || *contacts == NULL) {
        printf("Error: value of contacts received in removeContactByFullName was NULL\n");
        return 0;
    }

    count = countContacts(*contacts);
    if (count == 0) {
        printf("Error: No contacts available to remove\n");
        return 0;
    }

    printf("Enter first name:\n");
    firstName = readString();
    if (firstName == NULL) {
        return 0;
    }

    printf("Enter family name:\n");
    familyName = readString();
    if (familyName == NULL) {
        free(firstName);
        return 0;
    }

    /* Search for the contact with matching names */
    for (i = 0; i < count; i++) {
        if (strcmp((*contacts)[i]->firstName, firstName) == 0 && 
            strcmp((*contacts)[i]->familyName, familyName) == 0) {
            found = 1;
            
            /* Free the found contact */
            freeContact((*contacts)[i]);

            /* Shift the remaining contacts to fill the gap */
            for (j = i; j < count - 1; j++) {
                (*contacts)[j] = (*contacts)[j + 1];
            }

            /* Reallocate the array to the new size */
            newContacts = (Contact **)realloc(*contacts, count * sizeof(Contact *));
            if (newContacts == NULL && count > 1) {
                printf("Error: Memory reallocation failed in removeContactByFullName\n");
                free(firstName);
                free(familyName);
                return 1; /* Contact was removed but reallocation failed */
            }

            *contacts = newContacts;
            /* NULL terminate the array */
            (*contacts)[count - 1] = NULL;

            printf("Contact '%s %s' removed successfully\n", firstName, familyName);
            break;
        }
    }

    if (!found) {
        printf("Contact '%s %s' not found\n", firstName, familyName);
    }

    free(firstName);
    free(familyName);
    return found ? 1 : 2;
}

/* List all contacts */
void listContacts(Contact **contacts) {
    int count, i;

    if (contacts == NULL) {
        printf("Error: contacts parameter is NULL in listContacts\n");
        return;
    }

    count = countContacts(contacts);
    if (count == 0) {
        printf("Error: No contacts available.\n");
        return;
    }

    for (i = 0; i < count; i++) {
        printf("%d. %s %s\n", i + 1, contacts[i]->firstName, contacts[i]->familyName);
        printf(" Phone: %lld\n", contacts[i]->phoneNum);
        printf(" Address: %s\n", contacts[i]->address);
        printf(" Age: %d\n", contacts[i]->age);
    }
}

/* Save contacts to a file in a format suitable for program loading */
void saveContactsToFile(Contact **contacts, char *filename) {
    FILE *file;
    int count, i;

    if (filename == NULL) {
        printf("Error: filename formal parameter passed value NULL in saveContactsToFile\n");
        return;
    }

    if (contacts == NULL) {
        printf("Error: contacts formal parameter passed value NULL in saveContactsToFile\n");
        return;
    }

    file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error: file not opened in saveContactsToFile\n");
        return;
    }

    count = countContacts(contacts);
    fprintf(file, "%d\n", count);

    for (i = 0; i < count; i++) {
        fprintf(file, "%s\n", contacts[i]->firstName);
        fprintf(file, "%s\n", contacts[i]->familyName);
        fprintf(file, "%s\n", contacts[i]->address);
        fprintf(file, "%lld\n", contacts[i]->phoneNum);
        fprintf(file, "%d\n", contacts[i]->age);
    }

    fclose(file);
    printf("Contacts saved to file: %s\n", filename);
}

/* Print contacts to a file in a human-readable format */
void printContactsToFile(Contact **contacts, char *filename) {
    FILE *file;
    int count, i;

    if (filename == NULL) {
        printf("Error: filename formal parameter passed value NULL in printContactsToFile\n");
        return;
    }

    if (contacts == NULL) {
        printf("Error: contacts formal parameter passed value NULL in printContactsToFile\n");
        return;
    }

    file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error: file not opened in printContactsToFile\n");
        return;
    }

    count = countContacts(contacts);

    fprintf(file, "Address Book Report\n");
    fprintf(file, "-------------------\n");

    for (i = 0; i < count; i++) {
        fprintf(file, "%d. %s %s\n", i + 1, contacts[i]->firstName, contacts[i]->familyName);
        fprintf(file, " Phone: %lld\n", contacts[i]->phoneNum);
        fprintf(file, " Address: %s\n", contacts[i]->address);
        fprintf(file, " Age: %d\n", contacts[i]->age);
    }

    fprintf(file, "-------------------\n");
    fprintf(file, "Total Contacts: %d\n", count);

    fclose(file);
    printf("Contacts printed to file: %s\n", filename);
}

/* Load contacts from a file, replacing existing contacts */
/* Load contacts from a file, replacing existing contacts */
/* Load contacts from a file, replacing existing contacts */
Contact **loadContactsFromFile(Contact **addressBook, char *filename) {
    FILE *file;
    Contact **newAddressBook;
    Contact *newContact;
    int numContacts, i;
    char buffer[256];
    char *token;

    if (filename == NULL) {
        printf("Error: filename parameter is NULL in loadContactsFromFile\n");
        return addressBook;
    }

    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: File to load not found\n");
        return NULL;
    }

    /* Read the number of contacts */
    if (fscanf(file, "%d", &numContacts) != 1) {
        printf("Error: Could not read number of contacts from file\n");
        fclose(file);
        return NULL;
    }
    fgetc(file); /* Consume newline */

    printf("Number of contacts: %d\n", numContacts);

    /* Create a new address book */
    newAddressBook = (Contact **)malloc((numContacts + 1) * sizeof(Contact *));
    if (newAddressBook == NULL) {
        printf("Error: Memory allocation error, addressBook in loadContactsFromFile\n");
        fclose(file);
        return NULL;
    }

    /* Free the old address book if it exists */
    if (addressBook != NULL) {
        freeContacts(addressBook);
    }

    /* Read each contact from the file */
    for (i = 0; i < numContacts; i++) {
        newContact = (Contact *)malloc(sizeof(Contact));
        if (newContact == NULL) {
            printf("Error: Memory allocation error, Contact %d in loadContactsFromFile\n", i);
            freeContacts(newAddressBook);
            fclose(file);
            return NULL;
        }

        /* Initialize with NULL pointers */
        newContact->firstName = NULL;
        newContact->familyName = NULL;
        newContact->address = NULL;

        /* Read first name on its own line */
        if (fgets(buffer, sizeof(buffer), file) == NULL) {
            printf("Error: Failed to read first name for contact %d\n", i);
            freeContact(newContact);
            freeContacts(newAddressBook);
            fclose(file);
            return NULL;
        }
        buffer[strcspn(buffer, "\n")] = '\0';
        printf("First Name: %s\n", buffer);
        newContact->firstName = allocateString(buffer);
        if (newContact->firstName == NULL) {
            printf("Error: Memory allocation error, memory for string in Contact %d not allocated\n", i);
            freeContact(newContact);
            freeContacts(newAddressBook);
            fclose(file);
            exit(1);
        }

        /* Read family name on its own line */
        if (fgets(buffer, sizeof(buffer), file) == NULL) {
            printf("Error: Failed to read family name for contact %d\n", i);
            freeContact(newContact);
            freeContacts(newAddressBook);
            fclose(file);
            return NULL;
        }
        buffer[strcspn(buffer, "\n")] = '\0';
        printf("Family Name: %s\n", buffer);
        newContact->familyName = allocateString(buffer);
        if (newContact->familyName == NULL) {
            printf("Error: Memory allocation error, memory for string in Contact %d not allocated\n", i);
            freeContact(newContact);
            freeContacts(newAddressBook);
            fclose(file);
            exit(1);
        }

        /* Read address on its own line */
        if (fgets(buffer, sizeof(buffer), file) == NULL) {
            printf("Error: Failed to read address for contact %d\n", i);
            freeContact(newContact);
            freeContacts(newAddressBook);
            fclose(file);
            return NULL;
        }
        buffer[strcspn(buffer, "\n")] = '\0';
        printf("Address: %s\n", buffer);
        newContact->address = allocateString(buffer);
        if (newContact->address == NULL) {
            printf("Error: Memory allocation error, memory for string in Contact %d not allocated\n", i);
            freeContact(newContact);
            freeContacts(newAddressBook);
            fclose(file);
            exit(1);
        }

        /* Read phone number on its own line */
        if (fgets(buffer, sizeof(buffer), file) == NULL) {
            printf("Error: Failed to read phone number for contact %d\n", i);
            freeContact(newContact);
            freeContacts(newAddressBook);
            fclose(file);
            return NULL;
        }
        buffer[strcspn(buffer, "\n")] = '\0';
        printf("Phone Number: %s\n", buffer);
        if (sscanf(buffer, "%lld", &newContact->phoneNum) != 1) {
            printf("Error: Invalid phone number for contact %d.\n", i);
            newContact->phoneNum = 0;
        }

        /* Read age on its own line */
        if (fgets(buffer, sizeof(buffer), file) == NULL) {
            printf("Error: Failed to read age for contact %d\n", i);
            freeContact(newContact);
            freeContacts(newAddressBook);
            fclose(file);
            return NULL;
        }
        buffer[strcspn(buffer, "\n")] = '\0';
        printf("Age: %s\n", buffer);
        if (sscanf(buffer, "%d", &newContact->age) != 1 || 
            newContact->age < 1 || newContact->age > 150) {
            printf("Error: Invalid age for contact %d.\n", i);
            newContact->age = 0;
        }

        /* Add the contact to the new address book */
        newAddressBook[i] = newContact;
    }

    /* NULL terminate the array */
    newAddressBook[numContacts] = NULL;

    fclose(file);
    printf("Contacts loaded from file: %s\n", filename);
    return newAddressBook;
}

/* Append contacts from a file to existing contacts */
Contact **appendContactsFromFile(Contact **contacts, char *filename) {
    FILE *file;
    Contact *newContact;
    int numContacts, i;
    char buffer[256];

    if (filename == NULL) {
        printf("Error: filename parameter is NULL in appendContactsFromFile\n");
        return contacts;
    }

    if (contacts == NULL) {
        printf("Error: contacts parameter is NULL in appendContactsFromFile\n");
        return NULL;
    }

    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: File to load not found\n");
        return contacts;
    }

    /* Read the number of contacts */
    if (fscanf(file, "%d", &numContacts) != 1) {
        printf("Error: Could not read number of contacts from file\n");
        fclose(file);
        return contacts;
    }
    fgetc(file); /* Consume newline */

    /* Read each contact from the file and append if not a duplicate */
    for (i = 0; i < numContacts; i++) {
        newContact = (Contact *)malloc(sizeof(Contact));
        if (newContact == NULL) {
            printf("Error: Memory allocation error, Contact %d in appendContactsFromFile\n", i);
            fclose(file);
            return contacts;
        }

        /* Initialize with NULL pointers */
        newContact->firstName = NULL;
        newContact->familyName = NULL;
        newContact->address = NULL;

        /* Read first name */
        if (fgets(buffer, sizeof(buffer), file) == NULL) {
            freeContact(newContact);
            fclose(file);
            return contacts;
        }
        buffer[strcspn(buffer, "\n")] = '\0';
        newContact->firstName = allocateString(buffer);
        if (newContact->firstName == NULL) {
            printf("Error: Memory allocation error for first name\n");
            freeContact(newContact);
            fclose(file);
            return contacts;
        }

        /* Read family name */
        if (fgets(buffer, sizeof(buffer), file) == NULL) {
            freeContact(newContact);
            fclose(file);
            return contacts;
        }
        buffer[strcspn(buffer, "\n")] = '\0';
        newContact->familyName = allocateString(buffer);
        if (newContact->familyName == NULL) {
            printf("Error: Memory allocation error for family name\n");
            freeContact(newContact);
            fclose(file);
            return contacts;
        }

        /* Read address */
        if (fgets(buffer, sizeof(buffer), file) == NULL) {
            freeContact(newContact);
            fclose(file);
            return contacts;
        }
        buffer[strcspn(buffer, "\n")] = '\0';
        newContact->address = allocateString(buffer);
        if (newContact->address == NULL) {
            printf("Error: Memory allocation error for address\n");
            freeContact(newContact);
            fclose(file);
            return contacts;
        }

        /* Read phone number */
        if (fscanf(file, "%lld", &newContact->phoneNum) != 1) {
            printf("Error: Invalid phone number.\n");
            newContact->phoneNum = 0;
        }
        fgetc(file); /* Consume newline */

        /* Read age */
        if (fscanf(file, "%d", &newContact->age) != 1 || 
            newContact->age < 1 || newContact->age > 150) {
            printf("Error: Invalid age.\n");
            newContact->age = 0;
        }
        fgetc(file); /* Consume newline */

        /* Check if the contact is a duplicate */
        if (!isDuplicateContact(contacts, newContact)) {
            contacts = appendContact(contacts, newContact);
        } else {
            /* Free the contact if it's a duplicate */
            freeContact(newContact);
        }
    }

    fclose(file);
    printf("Appended contacts from %s\n", filename);
    return contacts;
}

/* Merge contacts from a file into existing contacts in alphabetical order */
Contact **mergeContactsFromFile(Contact **contacts, char *filename) {
    FILE *file;
    Contact *newContact;
    int numContacts, i;
    char buffer[256];

    if (filename == NULL) {
        printf("Error: filename parameter is NULL in mergeContactsFromFile\n");
        return contacts;
    }

    if (contacts == NULL) {
        printf("Error: contacts parameter is NULL in mergeContactsFromFile\n");
        return NULL;
    }

    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: File to load not found\n");
        return contacts;
    }

    /* Read the number of contacts */
    if (fscanf(file, "%d", &numContacts) != 1) {
        printf("Error: Could not read number of contacts from file\n");
        fclose(file);
        return contacts;
    }
    fgetc(file); /* Consume newline */

    /* Read each contact from the file and merge if not a duplicate */
    for (i = 0; i < numContacts; i++) {
        newContact = (Contact *)malloc(sizeof(Contact));
        if (newContact == NULL) {
            printf("Error: Memory allocation error, Contact %d in mergeContactsFromFile\n", i);
            fclose(file);
            return contacts;
        }

        /* Initialize with NULL pointers */
        newContact->firstName = NULL;
        newContact->familyName = NULL;
        newContact->address = NULL;

        /* Read first name */
        if (fgets(buffer, sizeof(buffer), file) == NULL) {
            freeContact(newContact);
            fclose(file);
            return contacts;
        }
        buffer[strcspn(buffer, "\n")] = '\0';
        newContact->firstName = allocateString(buffer);
        if (newContact->firstName == NULL) {
            printf("Error: Memory allocation error for first name\n");
            freeContact(newContact);
            fclose(file);
            return contacts;
        }

        /* Read family name */
        if (fgets(buffer, sizeof(buffer), file) == NULL) {
            freeContact(newContact);
            fclose(file);
            return contacts;
        }
        buffer[strcspn(buffer, "\n")] = '\0';
        newContact->familyName = allocateString(buffer);
        if (newContact->familyName == NULL) {
            printf("Error: Memory allocation error for family name\n");
            freeContact(newContact);
            fclose(file);
            return contacts;
        }

        /* Read address */
        if (fgets(buffer, sizeof(buffer), file) == NULL) {
            freeContact(newContact);
            fclose(file);
            return contacts;
        }
        buffer[strcspn(buffer, "\n")] = '\0';
        newContact->address = allocateString(buffer);
        if (newContact->address == NULL) {
            printf("Error: Memory allocation error for address\n");
            freeContact(newContact);
            fclose(file);
            return contacts;
        }

        /* Read phone number */
        if (fscanf(file, "%lld", &newContact->phoneNum) != 1) {
            printf("Error: Invalid phone number.\n");
            newContact->phoneNum = 0;
        }
        fgetc(file); /* Consume newline */

        /* Read age */
        if (fscanf(file, "%d", &newContact->age) != 1 || 
            newContact->age < 1 || newContact->age > 150) {
            printf("Error: Invalid age.\n");
            newContact->age = 0;
        }
        fgetc(file); /* Consume newline */

        /* Check if the contact is a duplicate */
        if (!isDuplicateContact(contacts, newContact)) {
            contacts = insertContactAlphabetical(contacts, newContact);
        } else {
            /* Free the contact if it's a duplicate */
            freeContact(newContact);
        }
    }

    fclose(file);
    printf("Appended contacts from %s\n", filename);
    return contacts;
}

/* Edit a contact by index */
Contact **editContact(Contact **contacts, int index) {
    int choice, count, validAge;
    long long phoneNum;
    char *newValue;
    int attempts, age;

    if (contacts == NULL) {
        printf("Error: contacts parameter is NULL in editContact\n");
        return NULL;
    }

    count = countContacts(contacts);
    if (count == 0) {
        printf("No contacts available to edit\n");
        return contacts;
    }

    if (index < 0 || index >= count) {
        printf("Error: Invalid Index\n");
        return contacts;
    }

    printf("Editing contact: %s %s\n", contacts[index]->firstName, contacts[index]->familyName);

    do {
        displayEditMenu();
        choice = readInteger();

        switch (choice) {
            case 1: /* Edit First Name */
                printf("Enter new first name:\n");
                newValue = readString();
                if (newValue != NULL) {
                    free(contacts[index]->firstName);
                    contacts[index]->firstName = newValue;
                } else {
                    printf("Error: Memory allocation error for string in editContact\n");
                    exit(1);
                }
                break;
            case 2: /* Edit Last Name */
                printf("Enter new family name:\n");
                newValue = readString();
                if (newValue != NULL) {
                    free(contacts[index]->familyName);
                    contacts[index]->familyName = newValue;
                } else {
                    printf("Error: Memory allocation error for string in editContact\n");
                    exit(1);
                }
                break;
            case 3: /* Edit Address */
                printf("Enter new address:\n");
                newValue = readString();
                if (newValue != NULL) {
                    free(contacts[index]->address);
                    contacts[index]->address = newValue;
                } else {
                    printf("Error: Memory allocation error for string in editContact\n");
                    exit(1);
                }
                break;
            case 4: /* Edit Phone Number */
                printf("Enter new 10-digit phone number that must not start with 0:\n");
                phoneNum = readPhoneNumber();
                contacts[index]->phoneNum = phoneNum;
                break;
            case 5: /* Edit Age */
                printf("Enter new age:\n");
                validAge = 0;
                attempts = 0;
                
                while (!validAge && attempts < 5) {
                    age = readInteger();
                    if (age >= 1 && age <= 150) {
                        contacts[index]->age = age;
                        validAge = 1;
                    } else {
                        attempts++;
                        if (attempts < 5) {
                            printf("Error: Invalid age. Try again:\n");
                        }
                    }
                }
                
                if (!validAge) {
                    printf("Error: Could not read a valid age\n");
                }
                break;
            case 6: /* Return to Main Menu */
                printf("Returning to main menu\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);

    return contacts;
}

/* Helper Functions */

/* Free a single contact */
void freeContact(Contact *contact) {
    if (contact == NULL) {
        return;
    }
    
    free(contact->firstName);
    free(contact->familyName);
    free(contact->address);
    free(contact);
}

/* Free all contacts in a NULL-terminated array */
void freeContacts(Contact **contacts) {
    int i = 0;
    
    if (contacts == NULL) {
        return;
    }
    
    while (contacts[i] != NULL) {
        freeContact(contacts[i]);
        i++;
    }
    
    free(contacts);
}

/* Compare two contacts for alphabetical ordering */
int compareContacts(Contact *contact1, Contact *contact2) {
    int result;
    
    if (contact1 == NULL || contact2 == NULL) {
        return 0;
    }
    
    /* Compare by family name first */
    result = strcmp(contact1->familyName, contact2->familyName);
    if (result != 0) {
        return result;
    }
    
    /* If family names are the same, compare by first name */
    return strcmp(contact1->firstName, contact2->firstName);
}

/* Check if a contact already exists in the contacts array */
int isDuplicateContact(Contact **contacts, Contact *newContact) {
    int i = 0;
    
    if (contacts == NULL || newContact == NULL) {
        return 0;
    }
    
    while (contacts[i] != NULL) {
        if (strcmp(contacts[i]->firstName, newContact->firstName) == 0 &&
            strcmp(contacts[i]->familyName, newContact->familyName) == 0 &&
            contacts[i]->phoneNum == newContact->phoneNum) {
            return 1; /* Duplicate found */
        }
        i++;
    }
    
    return 0; /* No duplicate found */
}

/* Read a string from standard input */
char *readString() {
    char buffer[256];
    char *str;
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return NULL;
    }
    
    /* Remove newline character */
    buffer[strcspn(buffer, "\n")] = '\0';
    
    /* Allocate memory for the string */
    str = allocateString(buffer);
    
    return str;
}

/* Read an integer from standard input */
int readInteger() {
    char buffer[256];
    int value;
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 0;
    }
    
    if (sscanf(buffer, "%d", &value) != 1) {
        return 0;
    }
    
    return value;
}

/* Read a phone number from standard input */
long long readPhoneNumber() {
    char buffer[256];
    long long value;
    int valid = 0;
    
    while (!valid) {
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            return 0;
        }
        
        if (sscanf(buffer, "%lld", &value) != 1) {
            printf("Error: Invalid phone number. Try again:\n");
            continue;
        }
        
        /* Check if the number is 10 digits and doesn't start with 0 */
        if (value >= 1000000000LL && value <= 9999999999LL) {
            valid = 1;
        } else {
            printf("Error: Phone number must be 10 digits and not start with 0. Try again:\n");
        }
    }
    
    return value;
}

/* Display the main menu */
void displayMenu() {
    printf("\nAddress Book Application\n");
    printf("-----------------------\n");
    printf("1. Append Contact\n");
    printf("2. Insert Contact in Alphabetical Order\n");
    printf("3. Remove Contact by Index\n");
    printf("4. Remove Contact by Full Name\n");
    printf("5. Find and Edit Contact\n");
    printf("6. List Contacts\n");
    printf("7. Print Contacts to File (Input Format)\n");
    printf("8. Print Contacts to File (Human Readable)\n");
    printf("9. Load Contacts from File (Replace Existing)\n");
    printf("10. Append Contacts from File\n");
    printf("11. Merge Contacts from File\n");
    printf("12. Exit\n");
    printf("Enter your choice: ");
}

/* Display the edit menu */
void displayEditMenu() {
    printf("\nEdit Contact Menu\n");
    printf("----------------\n");
    printf("1. Edit First Name\n");
    printf("2. Edit Last Name\n");
    printf("3. Edit Address\n");
    printf("4. Edit Phone Number\n");
    printf("5. Edit Age\n");
    printf("6. Return to Main Menu\n");
    printf("Enter your choice: ");
}

/* Allocate memory for a string and copy the contents */
char *allocateString(const char *str) {
    char *newStr;
    
    if (str == NULL) {
        return NULL;
    }
    
    newStr = (char *)malloc(strlen(str) + 1);
    if (newStr == NULL) {
        return NULL;
    }
    
    strcpy(newStr, str);
    return newStr;
}    