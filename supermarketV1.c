#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ANSI color codes for text formatting
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

// Structure for date
typedef struct {
    int day, month, year;
} Date;

// Structure for product
typedef struct {
    int id;
    char name[100];
    float price;
    int quantity;
} Product;

// Structure for node of linked list
typedef struct node {
    Product product;
    struct node *next;
} Node;

// Function to add a product to the inventory
void addProduct(Node **head) {
    Node *newProduct = (Node *)malloc(sizeof(Node));
    if (newProduct == NULL) {
        printf(ANSI_COLOR_RED "Memory allocation failed.\n" ANSI_COLOR_RESET);
        return;
    }

    printf("Enter product ID: ");
    scanf("%d", &newProduct->product.id);
    printf("Enter product name: ");
    scanf("%s", newProduct->product.name);
    printf("Enter product price: ");
    scanf("%f", &newProduct->product.price);
    printf("Enter product quantity: ");
    scanf("%d", &newProduct->product.quantity);

    newProduct->next = *head;
    *head = newProduct;

    printf("----------------------------------\n");
    printf(ANSI_COLOR_GREEN "Product added successfully.\n" ANSI_COLOR_RESET);
    printf("----------------------------------\n");
}

// Function to view all products in the inventory
void viewProducts(Node *head) {
    if (head == NULL) {
        printf("-------------------------------------\n");
        printf(ANSI_COLOR_RED "Inventory is empty.\n" ANSI_COLOR_RESET);
        printf("-------------------------------------\n");
        return;
    }

    printf("-------------------------------------\n");
    printf("Product ID\tName\tPrice\tQuantity\n");
    while (head != NULL) {
        printf("%d\t     \t%s\t%.2f\t%d\n", head->product.id, head->product.name, head->product.price, head->product.quantity);
        head = head->next;
    }
    printf("\n");
    printf("-------------------------------------\n");
}

// Function to delete a product from the inventory
void deleteProduct(Node **head, int id) {
    Node *temp = *head;
    Node *prev = NULL;

    while (temp != NULL && temp->product.id != id) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("-------------------------------------\n");
        printf("Product with ID %d not found.\n", id);
        printf("-------------------------------------\n");
        return;
    }

    if (prev != NULL) {
        prev->next = temp->next;
    } else {
        *head = temp->next;
    }

    free(temp);
    printf("-------------------------------------\n");
    printf(ANSI_COLOR_GREEN "Product with ID %d deleted successfully.\n" ANSI_COLOR_RESET, id);
    printf("-------------------------------------\n");
}

// Function to generate a bill for the products in the inventory
void generateBill(Node *head) {
    if (head == NULL) {
        printf("-------------------------------------\n");
        printf(ANSI_COLOR_RED "Inventory is empty.\n" ANSI_COLOR_RESET);
        printf("-------------------------------------\n");
        return;
    }

    Date currentDate;
    printf("Enter current date (dd mm yyyy): ");
    scanf("%d %d %d", &currentDate.day, &currentDate.month, &currentDate.year);

    printf("Bill generated on %d/%d/%d:\n", currentDate.day, currentDate.month, currentDate.year);
    printf("*************************************\n");
    printf("Product ID\tName\tPrice\tQuantity\n");
    float total = 0.0;
    while (head != NULL) {
        printf("%d\t     \t%s\t%.2f\t%d\n", head->product.id, head->product.name, head->product.price, head->product.quantity);
        total += head->product.price * head->product.quantity;
        head = head->next;
    }
    printf("-------------------------------------\n");
    printf("Total               %.2f\n", total);
    printf("*************************************\n");
}

// Function to calculate the total sales from the inventory
float calculateTotalSales(Node *head) {
    float totalSales = 0;

    while (head != NULL) {
        totalSales += (head->product.price * head->product.quantity);
        head = head->next;
    }

    return totalSales;
}

// Function to search for a product by ID
void searchProduct(Node *head, int id) {
    while (head != NULL) {
        if (head->product.id == id) {
            printf("-------------------------------------\n");
            printf("Product found:\n");
            printf("Product ID\tName\tPrice\tQuantity\n");
            printf("%d\t     \t%s\t%.2f\t%d\n", head->product.id, head->product.name, head->product.price, head->product.quantity);
            printf("-------------------------------------\n");
            return;
        }
        head = head->next;
    }
    printf("-------------------------------------\n");
    printf("Product with ID %d not found.\n", id);
    printf("-------------------------------------\n");
}

// Function to update the details of a product
void updateProduct(Node *head, int id) {
    while (head != NULL) {
        if (head->product.id == id) {
            printf("-------------------------------------\n");
            printf("Enter new product name: ");
            scanf("%s", head->product.name);
            printf("Enter new product price: ");
            scanf("%f", &head->product.price);
            printf("Enter new product quantity: ");
            scanf("%d", &head->product.quantity);
            printf("-------------------------------------\n");
            printf(ANSI_COLOR_GREEN "Product details updated successfully.\n" ANSI_COLOR_RESET);
            printf("-------------------------------------\n");
            return;
        }
        head = head->next;
    }
    printf("-------------------------------------\n");
    printf("Product with ID %d not found.\n", id);
    printf("-------------------------------------\n");
}

// Function to backup the inventory to a file
void backupInventory(Node *head) {
    FILE *fp = fopen("inventory_backup.txt", "w");

    if (fp == NULL) {
        printf("-------------------------------------\n");
        printf(ANSI_COLOR_BLUE "Error creating backup file.\n" ANSI_COLOR_RESET);
        printf("-------------------------------------\n");
        return;
    }

    while (head != NULL) {
        fprintf(fp, "%d %s %.2f %d\n", head->product.id, head->product.name, head->product.price, head->product.quantity);
        head = head->next;
    }

    fclose(fp);
    printf("-------------------------------------\n");
    printf(ANSI_COLOR_GREEN "Inventory backup created successfully.\n" ANSI_COLOR_RESET);
    printf("-------------------------------------\n");
}

// Function to restore the inventory from a backup file
void restoreInventory(Node **head) {
    FILE *fp = fopen("inventory_backup.txt", "r");
    if (fp == NULL) {
        printf(ANSI_COLOR_RED "Backup file not found.\n" ANSI_COLOR_RESET);
        return;
    }

    Node *current = *head;
    Node *prev = NULL;

    while (current != NULL) {
        prev = current;
        current = current->next;
        free(prev);
    }

    int id, quantity;
    float price;
    char name[100];
    while (fscanf(fp, "%d %s %f %d", &id, name, &price, &quantity) != EOF) {
        Node *newProduct = (Node *)malloc(sizeof(Node));
        if (newProduct == NULL) {
            printf(ANSI_COLOR_RED "Memory allocation failed.\n" ANSI_COLOR_RESET);
            return;
        }
        newProduct->product.id = id;
        strcpy(newProduct->product.name, name);
        newProduct->product.price = price;
        newProduct->product.quantity = quantity;
        newProduct->next = *head;
        *head = newProduct;
    }

    fclose(fp);
    printf("-------------------------------------\n");
    printf(ANSI_COLOR_GREEN "Inventory restored successfully.\n" ANSI_COLOR_RESET);
    printf("-------------------------------------\n");
}

// Function for employee details
void emp() {
    printf("-------------------------------------\n");
    printf("Employees leave\n");
    for (int i = 1; i <= 10; i++) {
        printf("no%d\tNo\n", i);
    }
    printf("-------------------------------------\n");
}

// Function for sales information
void sale() {
    printf(ANSI_COLOR_MAGENTA "\nAthula onnum illa keela potru!\n\n" ANSI_COLOR_RESET);
    printf("-------------------------------------\n");
}

int main() {
    Node *inventory = NULL;
    int choice;

    do {
        printf("\n-- " ANSI_COLOR_CYAN "Inventory Management System" ANSI_COLOR_RESET " --\n");
        printf(ANSI_COLOR_GREEN "1. Add Product\n");
        printf("2. View Products\n");
        printf("3. Delete Product\n");
        printf("4. Generate Bill\n");
        printf("5. Calculate Total Sales\n");
        printf("6. Search Product\n");
        printf("7. Update Product\n");
        printf("8. Backup & Restore Inventory\n");
        printf("9. Management Info\n");
        printf("0. Exit\n" ANSI_COLOR_RESET);
        printf("-------------------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        printf("-------------------------------------\n");

        switch (choice) {
            case 1:
                addProduct(&inventory);
                break;
            case 2:
                viewProducts(inventory);
                break;
            case 3:
                printf("Enter product ID to delete: ");
                int id;
                scanf("%d", &id);
                deleteProduct(&inventory, id);
                break;
            case 4:
                generateBill(inventory);
                break;
            case 5:
                printf("Total Sales: %.2f\n", calculateTotalSales(inventory));
                break;
            case 6:
                printf("Enter product ID to search: ");
                scanf("%d", &id);
                searchProduct(inventory, id);
                break;
            case 7:
                printf("Enter product ID to update: ");
                scanf("%d", &id);
                updateProduct(inventory, id);
                break;
            case 8:
                printf(ANSI_COLOR_YELLOW "1. Backup Inventory\n");
                printf("2. Restore Inventory\n" ANSI_COLOR_RESET);
                printf("-------------------------------------\n");
                printf("Enter your choice: ");
                int zz;
                scanf("%d", &zz);
                printf("-------------------------------------\n");
                switch(zz) {
                    case 2:
                        restoreInventory(&inventory);
                        break;
                    case 1:
                        backupInventory(inventory);
                        break;
                }
                break;
            case 9:
                printf("Enter password: ");
                int pass;
                scanf("%d",&pass);
                if (pass == 189) {
                    printf(ANSI_COLOR_GREEN "Access granted\n" ANSI_COLOR_RESET);
                    printf("-------------------------------------\n");
                    printf(ANSI_COLOR_YELLOW "1. Sales and Income\n");
                    printf("2. Employees Details\n" ANSI_COLOR_RESET);
                    printf("-------------------------------------\n");
                    printf("Enter your choice: ");
                    int xx;
                    scanf("%d", &xx);
                    printf("-------------------------------------\n");

                    switch(xx) {
                        case 1:
                            sale();
                            break;
                        case 2:
                            emp();
                            break;
                    }
                }
                else
                    printf(ANSI_COLOR_RED "Password incorrect\n" ANSI_COLOR_RESET);
                break;
            case 0:
                printf(ANSI_COLOR_RED "Exiting...\n" ANSI_COLOR_RESET);
                break;
            default:
                printf(ANSI_COLOR_RED "Invalid choice. Please try again.\n" ANSI_COLOR_RESET);
                break;
        }
    } while (choice != 0);
    return 0;
}
