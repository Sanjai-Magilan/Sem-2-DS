#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for date
typedef struct {
    int day, month, year;
} Date;

// Structure for product details
typedef struct {
    int id;
    char name[100];
    float price;
    int quantity;
} Product;

// Structure for a node in the inventory linked list
typedef struct node {
    Product product;
    struct node *next;
} Node;

// Function prototypes
void addProduct(Node **head);
void viewProducts(Node *head);
void deleteProduct(Node **head, int id);
void generateBill(Node *head);
float calculateTotalSales(Node *head);
// ... other function prototypes

// Function to add a product to the inventory
void addProduct(Node **head) {
    Node *newProduct = (Node*)malloc(sizeof(Node));
    if (newProduct == NULL) {
        printf("Memory allocation failed.\n");
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
    printf("Product added successfully.\n");
    printf("----------------------------------\n");
}

// Function to view all products in the inventory
void viewProducts(Node *head) {
    if (head == NULL) {
        printf("Inventory is empty.\n");
        return;
    }

    printf("Product ID\tName\tPrice\tQuantity\n");
    while (head != NULL) {
        printf("%d\t     \t %s \t%.2f\t %d\n", head->product.id, head->product.name, head->product.price, head->product.quantity);
        head = head->next;
    }
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

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
        printf("Product with ID %d not found.\n", id);
        return;
    }

    if (prev != NULL) {
        prev->next = temp->next;
    } else {
        *head = temp->next;
    }

    free(temp);
    printf("Product with ID %d deleted successfully.\n", id);
}

// Function to generate a bill with date and time
void generateBill(Node *head) {
    if (head == NULL) {
        printf("Inventory is empty.\n");
        return;
    }

    Date currentDate;
    printf("Enter current date (dd mm yyyy): ");
    scanf("%d %d %d", &currentDate.day, &currentDate.month, &currentDate.year);

    printf("Bill generated on %d/%d/%d:\n", currentDate.day, currentDate.month, currentDate.year);
    printf("*************************************\n");
    printf("Product ID\tName\tPrice\tQuantity\n");
    float total=0.0;
    while (head != NULL) {
        printf("%d\t     \t %s \t%.2f\t %d\n", head->product.id, head->product.name, head->product.price, head->product.quantity);
        total+=head->product.price*head->product.quantity;
        head = head->next;
    }
    printf("-------------------------------------\n");
    printf("Total               %.2f\n",total);
    printf("*************************************\n");
}

// Function to calculate total sales for the day
float calculateTotalSales(Node *head) {
    float totalSales = 0;

    while (head != NULL) {
        totalSales += (head->product.price * head->product.quantity);
        head = head->next;
    }

    return totalSales;
}

// Main function
int main() {
    Node *head = NULL;
    int choice, productId;

    do {
        printf("\n-- Inventory Management System --\n");
        printf("1. Add Product\n");
        printf("2. View Products\n");
        printf("3. Delete Product\n");
        printf("4. Generate Bill\n");
        printf("5. Calculate Total Sales\n");
        printf("6. Exit\n");
        printf("----------------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        printf("----------------------------------\n");

        switch (choice) {
            case 1:
                addProduct(&head);
                break;
            case 2:
                viewProducts(head);
                break;
            case 3:
                printf("Enter product ID to delete: ");
                scanf("%d", &productId);
                deleteProduct(&head, productId);
                break;
            case 4:
                generateBill(head);
                break;
            case 5:
                printf("\nTotal sales for the day: %.2f\n", calculateTotalSales(head));
                break;
            case 6:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please enter a number between 1 and 6.\n");
        }
    } while (choice != 6);

    // Free memory before exiting
    Node *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}
