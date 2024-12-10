#include <iostream>
using namespace std;

const int ROUNDS = 10;

//node for coffee sim
struct Customer {
    string name;
    string order;
    Customer* next;

    Customer(string n, string o) : name(n), order(o), next(nullptr) {}
};

//add customer function
void addCustomer(Customer*&, string, string);

//serve/delete customer function
void serveCustomer(Customer*&);

//output the queue
void outputQueue(Customer*);

int main() {
    srand(time(0));
    //names for coffee and also drink orders, mayb used for more in future
    string names[] = {"Mo", "Ali", "Omar", "Hannah", "Ben", "Sahil", "Najla", "Hanif", "Tom", "Nick", "Elizabeth", "Sarah"};
    string drinkOrders[] = {"Espresso", "Americano", "Latte", "Mocha", "Cappucino", "Cold Brew", "Chai"};

    Customer* head = nullptr;
    
    //initialize the queue (3 customers)
    for (int i = 0; i < 3; i++) {
        addCustomer(head, names[rand() % 12], drinkOrders[rand() % 7]);
    }

    cout << "Pre-Simulation beginning:\n";
    outputQueue(head);
    //start simulation
    for (int i = 1; i <= ROUNDS; i++) {
        cout << "Round " << i << ":\n";
        
        if (head) {
            serveCustomer(head);
        }
        else {

        }
    }

    return 0;
}

void addCustomer(Customer*& head, string name, string order) {
    Customer* newCustomer = new Customer(name, order);
    cout << "\tAdded " << newCustomer->name << " to the queue!\n";
    if (!head) {
        head = newCustomer;
    }
    else {
        Customer* temp = head;
        while(temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newCustomer;
    }
}

void serveCustomer(Customer*& head) {
    if (!head) {
        cout << "\tNo customers in queue\n";
        return;
    }
    Customer* temp = head;
    cout << "\tServing " << temp->name << " a " << temp->order << ".\n";
    head = head->next;
    delete temp;
}

void outputQueue(Customer* head) {
    if (!head) {
        cout << "The queue is empty\n";
        return;
    }
    Customer* temp = head;
    cout << "Coffee queue:\n";
    int count = 1;
    while (temp) {
        cout << "\t" << count << ". " << temp->name << ". Order: " << temp->order << endl;
        temp = temp->next;
        count++;
    }
} 
