#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUCTS 100
#define MAX_NAME_LENGTH 50
#define MAX_ORDERS 50
#define MAX_USERNAME_LENGTH 20
#define MAX_PASSWORD_LENGTH 20

// Struct to represent a product
typedef struct {
    int product_id;
    char name[MAX_NAME_LENGTH];
    float price;
    int quantity;
} Product;

// Struct to represent an item in the shopping cart
typedef struct {
    int product_id;
    int quantity;
} CartItem;

// Struct to represent the shopping cart
typedef struct {
    CartItem items[MAX_PRODUCTS];
    int count;
} ShoppingCart;

// Struct to represent an order
typedef struct {
    ShoppingCart cart;
} Order;

// Queue data structure for order history
typedef struct {
    Order orders[MAX_ORDERS];
    int front;
    int rear;
} OrderQueue;

// Global array to store products
Product products[MAX_PRODUCTS];
int productCount = 0;

// Global variable to store order history
OrderQueue orderHistory;

// User credentials
char username[MAX_USERNAME_LENGTH] = "admin";
char password[MAX_PASSWORD_LENGTH] = "password";

// Function prototypes
int displayWelcomePage();
void signup();
int login();
void displayMenu();
void browseProducts();
void addToCart(int product_id, int quantity, ShoppingCart *cart);
void processOrder(ShoppingCart *cart);
void viewOrderHistory();
float calculateTotal(ShoppingCart *cart);

// Function to display the welcome page
int displayWelcomePage() {
    printf("Welcome to our Daily Needs Online Store!\n");
    printf("1. Login\n");
    printf("2. Signup\n");
    printf("Enter your choice: ");
    int choice;
    scanf("%d", &choice);
    switch (choice) {
        case 1:
            return login();
        case 2:
            signup();
            return login();
        default:
            printf("Invalid choice. Exiting...\n");
            return 0;
    }
}

// Function to handle user signup
void signup() {
    printf("Signup:\n");
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);
    printf("Signup successful!\n");
}

// Function to handle user login
int login() {
    printf("Login:\n");
    char inputUsername[MAX_USERNAME_LENGTH];
    char inputPassword[MAX_PASSWORD_LENGTH];
    printf("Username: ");
    scanf("%s", inputUsername);
    printf("Password: ");
    scanf("%s", inputPassword);
    if (strcmp(inputUsername, username) == 0 && strcmp(inputPassword, password) == 0) {
        printf("Login successful!\n");
        return 1;
    } else {
        printf("Invalid username or password. Exiting...\n");
        return 0;
    }
}

// Function to display the menu
void displayMenu() {
    printf("\nMenu:\n");
    printf("1. Browse Products\n");
    printf("2. Add to Cart\n");
    printf("3. Total Amount to be paid\n");
    printf("4. Process Order\n");
    printf("5. View Order History\n");
    printf("6. Exit\n");
}

// Function to browse products
void browseProducts() {
    printf("\nProducts:\n");
    printf("ID\tName\t\t\t\t\t\t\t\tPrice\tQuantity\n");
    for (int i = 0; i < productCount; ++i) {
        printf("%d\t%s\t\t\t%.2f\t%d\n", products[i].product_id, products[i].name, products[i].price, products[i].quantity);
    }
}

// Function to add a product to the cart
void addToCart(int product_id, int quantity, ShoppingCart *cart) {
    // Find the product in the array
    for (int i = 0; i < productCount; ++i) {
        if (products[i].product_id == product_id) {
            // Check if the requested quantity is available
            if (products[i].quantity >= quantity) {
                // Add the product to the cart
                cart->items[cart->count].product_id = product_id;
                cart->items[cart->count].quantity = quantity;
                ++cart->count;
                printf("Product added to cart.\n");
                return;
            } else {
                printf("Not enough stock available for this product.\n");
                return;
            }
        }
    }
    printf("Product not found.\n");
}

// Function to process the order
void processOrder(ShoppingCart *cart) {
    if (cart->count == 0) {
        printf("Cart is empty.\n");
        return;
    }

    // Move the order from the shopping cart to the order history queue
    orderHistory.orders[orderHistory.rear].cart = *cart;
    orderHistory.rear = (orderHistory.rear + 1) % MAX_ORDERS;

    // Update front if queue is full
    if (orderHistory.rear == orderHistory.front) {
        orderHistory.front = (orderHistory.front + 1) % MAX_ORDERS;
    }

    cart->count = 0;
    printf("Order processed successfully.\n");
}

// Function to view order history
void viewOrderHistory() {
    printf("\nOrder History:\n");
    if (orderHistory.front == orderHistory.rear) {
        printf("No orders in the order history.\n");
        return;
    }

    for (int i = orderHistory.front; i != orderHistory.rear; i = (i + 1) % MAX_ORDERS) {
        printf("Order %d:\n", i + 1);
        printf("Products:\n");
        for (int j = 0; j < orderHistory.orders[i].cart.count; ++j) {
            int product_id = orderHistory.orders[i].cart.items[j].product_id;
            int quantity = orderHistory.orders[i].cart.items[j].quantity;
            printf("Product ID: %d, Quantity: %d\n", product_id, quantity);
        }
    }
}

// Function to calculate total amount needed to be paid after processing the order
float calculateTotal(ShoppingCart *cart) {
    float total = 0.0;
    for (int i = 0; i < cart->count; ++i) {
        int product_id = cart->items[i].product_id;
        int quantity = cart->items[i].quantity;
        for (int j = 0; j < productCount; ++j) {
            if (products[j].product_id == product_id) {
                total += products[j].price * quantity;
                break;
            }
        }
    }
    return total;
}

int main() {
    if (!displayWelcomePage())
        return 0;

    // Adding 10 sample products
    products[productCount++] = (Product){101, "B NATURAL TENDER COCONUT WATER 750ML      ", 89.0, 100};
    products[productCount++] = (Product){104, "BINGO MAD ANGLES ACHARI MASTI CHIPS 130GM", 75.0, 200};
    products[productCount++] = (Product){145, "MATTEL UNO PLAYING CARDS                  ", 143.0, 300};
    products[productCount++] = (Product){176, "DETTOL COLOGNE FRESH SOAP 150GM            ", 188.0, 400};
    products[productCount++] = (Product){135, "MAMAEARTH VITC FACEWASH 50ML              ", 99.0, 500};
    products[productCount++] = (Product){465, "NIVEA SOFT MOUSTURIZING CREAM 100ML      ", 189.0, 600};
    products[productCount++] = (Product){732, "FROOTI MANGO DRINK 125ML                  ", 10.0, 700};
    products[productCount++] = (Product){189, "MOGU MOGU LYCHEE FRUIT DRINK 300ML      ", 70.0, 800};
    products[productCount++] = (Product){926, "HIDE&SEEK CHOCOCHIP BISUCIT 200GM        ", 45.0, 900};
    products[productCount++] = (Product){860, "KELLOGG'S CHOCOS 250GM'                   ", 180.0, 1000};

    int choice;
    ShoppingCart cart = {0};
    orderHistory.front = 0;
    orderHistory.rear = 0;

    do {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                browseProducts();
                break;
            case 2:
                int product_id, quantity;
                printf("Enter product ID: ");
                scanf("%d", &product_id);
                printf("Enter quantity: ");
                scanf("%d", &quantity);
                addToCart(product_id, quantity, &cart);
                break;
            case 3:
            	printf("Total amount to be paid: $%.2f\n", calculateTotal(&cart));
                printf("Exiting...\n");
                break;
            case 4:
            	 processOrder(&cart);
                break;  
            case 5:
            	viewOrderHistory();
                break;
                
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);

    return 0;
}


