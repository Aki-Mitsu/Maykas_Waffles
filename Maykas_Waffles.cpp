#include <iostream>
#include <iomanip>
#include <string>
#include <limits>

using namespace std;

struct MenuItem {
    string name;
    double price;
};

struct OrderItem {
    string flavor;
    double unitPrice;
    int quantity;
};

const int MENU_COUNT = 10;
const int MAX_ORDERS = 10;

const MenuItem MENU[MENU_COUNT] = {
    {"Plain Waffle",         50.00},
    {"Chocolate Waffle",     60.00},
    {"Vanilla Waffle",       55.00},
    {"Cheese Waffle",        70.00},
    {"Peanut Butter Waffle", 70.00},
    {"Strawberry Waffle",    75.00},
    {"Cinnamon Waffle",      60.00},
    {"Ube Waffle",           80.00},
    {"Banana Waffle",        70.00},
    {"Matcha Waffle",        90.00}
};

OrderItem orders[MAX_ORDERS];
int currentSize = 0;

// Safely reads an integer from cin and clears invalid input
int getValidInt(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            return value;
        }
        cout << "Invalid input. Please enter a valid number.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

void displayMenu() {
    cout << "\n--- Waffle Menu ---\n";
    cout << fixed << setprecision(2);
    for (int i = 0; i < MENU_COUNT; i++) {
        cout << setw(2) << (i + 1) << ". " 
             << left << setw(22) << MENU[i].name 
             << right << " - ₱" << MENU[i].price << "\n";
    }
}

double calculateTotal() {
    double total = 0.0;
    for (int i = 0; i < currentSize; i++) {
        total += orders[i].unitPrice * orders[i].quantity;
    }
    return total;
}

void showTotal() {
    cout << fixed << setprecision(2);
    cout << "\nTotal Order Amount: ₱" << calculateTotal() << "\n";
}

void viewOrders() {
    if (currentSize == 0) {
        cout << "\nYou haven't placed any orders yet.\n";
        return;
    }

    cout << "\n--- Current Orders ---\n";
    cout << fixed << setprecision(2);
    for (int i = 0; i < currentSize; i++) {
        double subtotal = orders[i].unitPrice * orders[i].quantity;
        cout << (i + 1) << ". " << orders[i].flavor 
             << " (x" << orders[i].quantity << ") - ₱" << subtotal << "\n";
    }
}

void placeOrder() {
    displayMenu();
    int choice = getValidInt("\nChoose a waffle flavor (1-" + to_string(MENU_COUNT) + "): ");

    if (choice < 1 || choice > MENU_COUNT) {
        cout << "\nInvalid selection. Please choose a number from the menu.\n";
        return;
    }

    int quantity = getValidInt("Quantity: ");
    if (quantity <= 0) {
        cout << "\nQuantity must be at least 1.\n";
        return;
    }

    MenuItem selected = MENU[choice - 1];

    // Check if the flavor is already in the order list; if so, combine quantities
    for (int i = 0; i < currentSize; i++) {
        if (orders[i].flavor == selected.name) {
            orders[i].quantity += quantity;
            cout << "\nAdded " << quantity << " more " << selected.name 
                 << " (Total: x" << orders[i].quantity << ").\n";
            showTotal();
            return;
        }
    }

    if (currentSize >= MAX_ORDERS) {
        cout << "\nSorry, the order list is full (maximum " << MAX_ORDERS << " items).\n";
        return;
    }

    orders[currentSize] = {selected.name, selected.price, quantity};
    currentSize++;

    cout << "\nAdded: " << selected.name << " - x" << quantity << "\n";
    showTotal();
}

void updateOrder() {
    if (currentSize == 0) {
        cout << "\nYou haven't placed any orders yet.\n";
        return;
    }

    viewOrders();
    int entry = getValidInt("\nEnter the order number to update: ");

    if (entry < 1 || entry > currentSize) {
        cout << "\nInvalid order number.\n";
        return;
    }

    displayMenu();
    int newChoice = getValidInt("\nChoose a new waffle flavor (1-" + to_string(MENU_COUNT) + "): ");

    if (newChoice < 1 || newChoice > MENU_COUNT) {
        cout << "\nInvalid selection.\n";
        return;
    }

    int newQuantity = getValidInt("New quantity: ");
    if (newQuantity <= 0) {
        cout << "\nQuantity must be at least 1.\n";
        return;
    }

    MenuItem selected = MENU[newChoice - 1];
    orders[entry - 1] = {selected.name, selected.price, newQuantity};

    cout << "\nUpdated to: " << selected.name << " - x" << newQuantity << "\n";
    showTotal();
}

void cancelOrder() {
    if (currentSize == 0) {
        cout << "\nYou haven't placed any orders yet.\n";
        return;
    }

    viewOrders();
    int entry = getValidInt("\nEnter the order number to cancel: ");

    if (entry < 1 || entry > currentSize) {
        cout << "\nInvalid order number.\n";
        return;
    }

    string removedFlavor = orders[entry - 1].flavor;
    for (int i = entry - 1; i < currentSize - 1; i++) {
        orders[i] = orders[i + 1];
    }

    currentSize--;
    cout << "\nRemoved " << removedFlavor << " from your order.\n";
    showTotal();
}

void completeOrder() {
    if (currentSize == 0) {
        cout << "\nNo orders placed. Exiting system.\n";
        return;
    }

    cout << "\n==============================\n";
    cout << "       ORDER RECEIPT          \n";
    cout << "==============================\n";
    viewOrders();
    cout << "------------------------------";
    showTotal();
    cout << "==============================\n";
    cout << "Thank you for your order! Your waffles will be ready soon.\n";
}

void runSystem() {
    while (true) {
        cout << "\n=== Mayka's Waffles ===\n";
        cout << "1. Place Order\n";
        cout << "2. View Orders\n";
        cout << "3. Update Order\n";
        cout << "4. Cancel Order\n";
        cout << "5. Complete Order\n";

        int choice = getValidInt("\nEnter an option (1-5): ");

        switch (choice) {
            case 1:
                placeOrder();
                break;
            case 2:
                viewOrders();
                if (currentSize > 0) showTotal();
                break;
            case 3:
                updateOrder();
                break;
            case 4:
                cancelOrder();
                break;
            case 5:
                completeOrder();
                return;
            default:
                cout << "\nInvalid choice. Please enter a number from 1 to 5.\n";
                break;
        }
    }
}

int main() {
    runSystem();
    return 0;
}