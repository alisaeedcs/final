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
void outputQueue(Customer*&);

int main() {
    //names for coffee and also drink orders, mayb used for more in future
    string names[] = {"Mo", "Ali", "Omar", "Hannah", "Ben", "Sahil", "Najla", "Hanif", "Tom", "Nick", "Elizabeth", "Sarah"};
    string drinkOrders[] = {"Espresso", "Americano", "Latte", "Mocha", "Cappucino", "Cold Brew", "Chai"};

    Customer* head = nullptr;
    
    //initialize the queue

}

void addCustomer(Customer*& head, string name, string order) {
    Customer* newCustomer = new Customer(name, order);
    if (!head) {
        head = newCustomer;
    }
    else {
        Customer* temp = head;
        while(temp->next) {
            temp = temp->next;
        }
        temp->next = newCustomer;
    }
}

void serveCustomer(Customer*& head) {
    if (!head) {
        cout << "No customers in queue\n";
        return;
    }
    Customer* temp = head;
    cout << "Serving " << temp->name << " a " << temp->order << ".\n";
    head = head->next;
    delete temp;
}

void outputQueue(Customer*& head) {
    if (!head) {
        cout << "The queue is empty\n";
        return;
    }
    cout << "Coffee queue:\n";
    int count = 1;
    while (head) {
        cout << "\t" << count << ". " << head->name << ". Order:"
        count++;
    }
} 
