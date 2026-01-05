#include <iostream>
using namespace std;

// Global Variables
int inventory500ml = 100;
int inventory1L = 100;
int inventory2L = 100;
int totalSales = 0;
int orderCounter = 0;
const int INVENTORY_ALERT_THRESHOLD = 20;

struct Customer {
    char name[50];
    char contact[50];
    char address[100];
    char username[50];
    char password[50];
};

struct Order {
    int orderId;
    char customerName[50];
    int bottleSize;
    int quantity;
    int totalCost;
    bool isPaid;
    bool isDelivered;
    char feedback[100];
    int priority; // 1: High, 2: Medium, 3: Low
};

Customer customers[100];
Order orders[100];
int customerCount = 0;
int orderCount = 0;
bool isLoggedIn = false;
int loggedInCustomerIndex = -1;

// Function Prototypes
void displayMenu();
void manageInventory();
void registerCustomer();
void customerLogin();
void processOrder();
void displayCustomerOrders();
void trackPaymentStatus();
void manageDelivery();
void searchOrder();
void searchCustomer();
void generateSalesReport();
void generateDailyStockReport();
void applyDiscount();
void cancelOrder();
void provideFeedback();
void setOrderPriority();
void inventoryAlert();
void exitSystem();

int main() {
    int choice;
    do {
        if (!isLoggedIn) {
            cout << "\n--- Customer Login ---\n";
            cout << "1. Register\n";
            cout << "2. Login\n";
            cout << "3. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;
            switch (choice) {
                case 1:
                    registerCustomer();
                    break;
                case 2:
                    customerLogin();
                    break;
                case 3:
                    exitSystem();
                    return 0;
                default:
                    cout << "Invalid choice. Please try again." << endl;
            }
        } else {
            displayMenu();
            cin >> choice;
            switch (choice) {
                case 1:
                    manageInventory();
                    break;
                case 2:
                    processOrder();
                    break;
                case 3:
                    displayCustomerOrders();
                    break;
                case 4:
                    trackPaymentStatus();
                    break;
                case 5:
                    manageDelivery();
                    break;
                case 6:
                    searchOrder();
                    break;
                case 7:
                    searchCustomer();
                    break;
                case 8:
                    generateSalesReport();
                    break;
                case 9:
                    generateDailyStockReport();
                    break;
                case 10:
                    applyDiscount();
                    break;
                case 11:
                    cancelOrder();
                    break;
                case 12:
                    provideFeedback();
                    break;
                case 13:
                    setOrderPriority();
                    break;
                case 14:
                    inventoryAlert();
                    break;
                case 15:
                    exitSystem();
                    return 0;
                default:
                    cout << "Invalid choice. Please try again." << endl;
            }
        }
    } while (true);

    return 0;
}

// Function Definitions
void displayMenu() {
    cout << "\n--- Mineral Water Supplying Company Management System ---\n";
    cout << "1. Manage Inventory\n";
    cout << "2. Process Order\n";
    cout << "3. Display Customer Orders\n";
    cout << "4. Track Payment Status\n";
    cout << "5. Manage Delivery\n";
    cout << "6. Search Order\n";
    cout << "7. Search Customer\n";
    cout << "8. Generate Sales Report\n";
    cout << "9. Generate Daily Stock Report\n";
    cout << "10. Apply Discount\n";
    cout << "11. Cancel Order\n";
    cout << "12. Provide Feedback\n";
    cout << "13. Set Order Priority\n";
    cout << "14. Inventory Alert\n";
    cout << "15. Exit\n";
    cout << "Enter your choice: ";
}

void manageInventory() {
    cout << "\n--- Manage Inventory ---\n";
    cout << "1. Restock 500ml\n";
    cout << "2. Restock 1L\n";
    cout << "3. Restock 2L\n";
    cout << "Enter your choice: ";
    int choice, quantity;
    cin >> choice;
    cout << "Enter quantity to restock: ";
    cin >> quantity;

    switch (choice) {
        case 1:
            inventory500ml += quantity;
            break;
        case 2:
            inventory1L += quantity;
            break;
        case 3:
            inventory2L += quantity;
            break;
        default:
            cout << "Invalid choice.\n";
    }
    cout << "Inventory updated.\n";
}

void registerCustomer() {
    cout << "\n--- Register Customer ---\n";
    cout << "Enter name: ";
    cin.ignore(); // Ignore the newline character left in the buffer
    cin.getline(customers[customerCount].name, 50);
    cout << "Enter contact: ";
    cin.getline(customers[customerCount].contact, 50);
    cout << "Enter address: ";
    cin.getline(customers[customerCount].address, 100);
    cout << "Enter username: ";
    cin.getline(customers[customerCount].username, 50);
    cout << "Enter password: ";
    cin.getline(customers[customerCount].password, 50);
    customerCount++;
    cout << "Customer registered successfully.\n";
}

void customerLogin() {
    cout << "\n--- Customer Login ---\n";
    char username[50];
    char password[50];
    cout << "Enter username: ";
    cin.ignore(); // Ignore the newline character left in the buffer
    cin.getline(username, 50);
    cout << "Enter password: ";
    cin.getline(password, 50);

    for (int i = 0; i < customerCount; i++) {
        bool usernameMatch = true;
        bool passwordMatch = true;

        // Compare the username
        for (int j = 0; username[j] != '\0' || customers[i].username[j] != '\0'; j++) {
            if (username[j] != customers[i].username[j]) {
                usernameMatch = false;
                break;
            }
        }

        // Compare the password
        for (int j = 0; password[j] != '\0' || customers[i].password[j] != '\0'; j++) {
            if (password[j] != customers[i].password[j]) {
                passwordMatch = false;
                break;
            }
        }

        if (usernameMatch && passwordMatch) {
            isLoggedIn = true;
            loggedInCustomerIndex = i;
            cout << "Login successful.\n";
            return;
        }
    }
    cout << "Invalid username or password.\n";
}

void processOrder() {
    if (!isLoggedIn) {
        cout << "Please log in first.\n";
        return;
    }

    cout << "\n--- Process Order ---\n";
    cout << "Enter bottle size (1 for 500ml, 2 for 1L, 3 for 2L): ";
    int bottleSize, quantity, price = 0;
    cin >> bottleSize;
    cout << "Enter quantity: ";
    cin >> quantity;

    switch (bottleSize) {
        case 1:
            if (inventory500ml >= quantity) {
                inventory500ml -= quantity;
                price = 10 * quantity;
            } else {
                cout << "Insufficient stock.\n";
                return;
            }
            break;
        case 2:
            if (inventory1L >= quantity) {
                inventory1L -= quantity;
                price = 20 * quantity;
            } else {
                cout << "Insufficient stock.\n";
                return;
            }
            break;
        case 3:
            if (inventory2L >= quantity) {
                inventory2L -= quantity;
                price = 30 * quantity;
            } else {
                cout << "Insufficient stock.\n";
                return;
            }
            break;
        default:
            cout << "Invalid bottle size.\n";
            return;
    }

    totalSales += price;
    orders[orderCount] = {++orderCounter, "", bottleSize, quantity, price, false, false, "", 0};
    for (int i = 0; i < 50; i++) {
        orders[orderCount].customerName[i] = customers[loggedInCustomerIndex].name[i];
    }
    orderCount++;
    cout << "Order processed. Total cost: " << price << "\n";
}

void displayCustomerOrders() {
    if (!isLoggedIn) {
        cout << "Please log in first.\n";
        return;
    }

    cout << "\n--- Display Customer Orders ---\n";
    bool found = false;
    for (int i = 0; i < orderCount; i++) {
        bool match = true;
        for (int j = 0; j < 50; j++) {
            if (orders[i].customerName[j] != customers[loggedInCustomerIndex].name[j]) {
                match = false;
                break;
            }
        }
        if (match) {
            cout << "Order ID: " << orders[i].orderId << ", Total Cost: " << orders[i].totalCost << "\n";
            found = true;
        }
    }
    if (!found) {
        cout << "No orders found for this customer.\n";
    }
}

void trackPaymentStatus() {
    cout << "\n--- Track Payment Status ---\n";
    for (int i = 0; i < orderCount; i++) {
        cout << "Order ID: " << orders[i].orderId << ", Payment Status: "
             << (orders[i].isPaid ? "Paid" : "Pending") << "\n";
    }
    cout << "Enter Order ID to update payment status: ";
    int orderId;
    cin >> orderId;
    for (int i = 0; i < orderCount; i++) {
        if (orders[i].orderId == orderId) {
            orders[i].isPaid = true;
            cout << "Payment status updated to Paid.\n";
            return;
        }
    }
    cout << "Order not found.\n";
}

void manageDelivery() {
    cout << "\n--- Manage Delivery ---\n";
    for (int i = 0; i < orderCount; i++) {
        cout << "Order ID: " << orders[i].orderId << ", Delivery Status: "
             << (orders[i].isDelivered ? "Delivered" : "Pending") << "\n";
    }
    cout << "Enter Order ID to update delivery status: ";
    int orderId;
    cin >> orderId;
    for (int i = 0; i < orderCount; i++) {
        if (orders[i].orderId == orderId) {
            orders[i].isDelivered = true;
            cout << "Delivery status updated to Delivered.\n";
            return;
        }
    }
    cout << "Order not found.\n";
}

void searchOrder() {
    cout << "\n--- Search Order ---\n";
    int orderId;
    cout << "Enter Order ID: ";
    cin >> orderId;
    for (int i = 0; i < orderCount; i++) {
        if (orders[i].orderId == orderId) {
            cout << "Order found. Total Cost: " << orders[i].totalCost << "\n";
            return;
        }
    }
    cout << "Order not found.\n";
}

void searchCustomer() {
    cout << "\n--- Search Customer ---\n";
    char name[50];
    cout << "Enter customer name: ";
    cin.ignore(); // Ignore the newline character left in the buffer
    cin.getline(name, 50);
    for (int i = 0; i < customerCount; i++) {
        bool match = true;
        for (int j = 0; j < 50; j++) {
            if (customers[i].name[j] != name[j]) {
                match = false;
                break;
            }
        }
        if (match) {
            cout << "Customer found. Contact: " << customers[i].contact
                 << ", Address: " << customers[i].address << "\n";
            return;
        }
    }
    cout << "Customer not found.\n";
}

void generateSalesReport() {
    cout << "\n--- Generate Sales Report ---\n";
    cout << "Total Sales: " << totalSales << "\n";
}

void generateDailyStockReport() {
    cout << "\n--- Generate Daily Stock Report ---\n";
    cout << "500ml: " << inventory500ml << "\n";
    cout << "1L: " << inventory1L << "\n";
    cout << "2L: " << inventory2L << "\n";
}

void applyDiscount() {
    cout << "\n--- Apply Discount ---\n";
    int orderId, discount;
    cout << "Enter Order ID: ";
    cin >> orderId;
    cout << "Enter discount percentage: ";
    cin >> discount;
    for (int i = 0; i < orderCount; i++) {
        if (orders[i].orderId == orderId) {
            int discountAmount = (orders[i].totalCost * discount) / 100;
            orders[i].totalCost -= discountAmount;
            totalSales -= discountAmount;
            cout << "Discount applied. New total cost: " << orders[i].totalCost << "\n";
            return;
        }
    }
    cout << "Order not found.\n";
}

void cancelOrder() {
    cout << "\n--- Cancel Order ---\n";
    int orderId;
    cout << "Enter Order ID: ";
    cin >> orderId;
    for (int i = 0; i < orderCount; i++) {
        if (orders[i].orderId == orderId) {
            switch (orders[i].bottleSize) {
                case 1:
                    inventory500ml += orders[i].quantity;
                    break;
                case 2:
                    inventory1L += orders[i].quantity;
                    break;
                case 3:
                    inventory2L += orders[i].quantity;
                    break;
            }
            totalSales -= orders[i].totalCost;
            for (int j = i; j < orderCount - 1; j++) {
                orders[j] = orders[j + 1];
            }
            orderCount--;
            cout << "Order canceled and inventory restocked.\n";
            return;
        }
    }
    cout << "Order not found.\n";
}

void provideFeedback() {
    if (!isLoggedIn) {
        cout << "Please log in first.\n";
        return;
    }

    cout << "\n--- Provide Feedback ---\n";
    int orderId;
    cout << "Enter Order ID: ";
    cin >> orderId;
    for (int i = 0; i < orderCount; i++) {
        if (orders[i].orderId == orderId) {
            cout << "Enter your feedback: ";
            cin.ignore(); // Ignore the newline character left in the buffer
            cin.getline(orders[i].feedback, 100);
            cout << "Feedback recorded.\n";
            return;
        }
    }
    cout << "Order not found.\n";
}

void setOrderPriority() {
    cout << "\n--- Set Order Priority ---\n";
    int orderId, priority;
    cout << "Enter Order ID: ";
    cin >> orderId;
    cout << "Enter priority level (1: High, 2: Medium, 3: Low): ";
    cin >> priority;
    for (int i = 0; i < orderCount; i++) {
        if (orders[i].orderId == orderId) {
            orders[i].priority = priority;
            cout << "Order priority set to " << priority << ".\n";
            return;
        }
    }
    cout << "Order not found.\n";
}

void inventoryAlert() {
    cout << "\n--- Inventory Alert ---\n";
    if (inventory500ml < INVENTORY_ALERT_THRESHOLD) {
        cout << "Alert: 500ml inventory is low. Current stock: " << inventory500ml << "\n";
    }
    if (inventory1L < INVENTORY_ALERT_THRESHOLD) {
        cout << "Alert: 1L inventory is low. Current stock: " << inventory1L << "\n";
    }
    if (inventory2L < INVENTORY_ALERT_THRESHOLD) {
        cout << "Alert: 2L inventory is low. Current stock: " << inventory2L << "\n";
    }
    if (inventory500ml >= INVENTORY_ALERT_THRESHOLD && inventory1L >= INVENTORY_ALERT_THRESHOLD && inventory2L >= INVENTORY_ALERT_THRESHOLD) {
        cout << "All inventory levels are above the alert threshold.\n";
    }
}

void exitSystem() {
    cout << "\n--- Exiting System ---\n";
    cout << "Total Sales: " << totalSales << "\n";
    cout << "Remaining Inventory:\n";
    cout << "500ml: " << inventory500ml << "\n";
    cout << "1L: " << inventory1L << "\n";
    cout << "2L: " << inventory2L << "\n";
}
