#include <iostream>
#include <deque>
#include <vector>
using namespace std;

const int ROUNDS = 10;

//node for coffee sim
struct Customer {
    string name;
    string order;
    Customer* next;

    Customer(string n, string o) : name(n), order(o), next(nullptr) {}
};

struct Muffin {
    string name;
    string muffinType;

    Muffin(string n, string m) : name(n), muffinType(m) {}
};

struct Bracelet {
    string name;
    string color;

    Bracelet(string n, string c) : name(n), color(c) {}
};

//all for coffee under
//add customer function
void addCustomer(Customer*&, string, string);
//serve/delete customer function
void serveCustomer(Customer*&);
//output the queue
void outputQueue(Customer*);

//muffin
void addMuffinCustomer(deque<Muffin>&, string, string);
void serveMuffinCustomer(deque<Muffin>&);
void outputMuffin(deque<Muffin>&);


int main() {
    srand(time(0));
    //names for coffee and also drink orders, mayb used for more in future
    string names[] = {"Mo", "Ali", "Omar", "Hannah", "Ben", "Sahil", "Najla", "Hanif", "Tom", "Nick", "Elizabeth", "Sarah"};
    string drinkOrders[] = {"Espresso", "Americano", "Latte", "Mocha", "Cappucino", "Cold Brew", "Chai"};
    string muffins[] = {"Blueberry", "Poppyseed", "Chocolate", "Red Velvet", "Banana"};

    //coffee booth queue
    Customer* head = nullptr;

    //muffin queue
    deque<Muffin> muffinQueue;
    
    //initialize the coffee queue (3 customers) also the muffin
    for (int i = 0; i < 3; i++) {
        addCustomer(head, names[rand() % 12], drinkOrders[rand() % 7]);
        addMuffinCustomer(muffinQueue, names[rand() % 12], muffins[rand() % 5]);
    }

    for (int i = 1; i <= ROUNDS; i++) {
        cout << "Round " << i << ":\n";

        //coffee booth
        cout << "COFFEE BOOTH:\n";
        serveCustomer(head);
        //50 percent of adding a new customer using integer to deterine bool
        if (rand() % 2) {
            addCustomer(head, names[rand() % 12], drinkOrders[rand() % 7]);
        }
        outputQueue(head);

        //muffin booth
        cout << "MUFFIN BOOTH:\n";
        serveMuffinCustomer(muffinQueue);
        if (rand() % 2) {
            addMuffinCustomer(muffinQueue, names[rand() % 12], muffins[rand() % 5]);
        }
        outputMuffin(muffinQueue);


    }

    return 0;
}

void addCustomer(Customer*& head, string name, string order) {
    Customer* newCustomer = new Customer(name, order);
    cout << "\tAdded " << newCustomer->name << " to the coffee queue!\n";
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
        cout << "\tNo customers in coffee queue\n";
        return;
    }
    Customer* temp = head;
    cout << "\tServing " << temp->name << " a " << temp->order << ".\n";
    head = head->next;
    delete temp;
}

void outputQueue(Customer* head) {
    if (!head) {
        cout << "\tThe coffee queue is empty\n";
        return;
    }
    Customer* temp = head;
    cout << "\tCoffee queue:\n";
    int count = 1;
    while (temp) {
        cout << "\t\t" << count << ". " << temp->name << " ordered a " << temp->order << endl;
        temp = temp->next;
        count++;
    }
} 


void addMuffinCustomer(deque<Muffin>& queue, string name, string order) {
    queue.push_back(Muffin(name, order));
    cout << "\tAdded " << name << " to the muffin queue ordering a " << order << " muffin\n";
}
void serveMuffinCustomer(deque<Muffin>& queue) {
    if (queue.empty()) {
        cout << "\tMuffin queue is empty.\n";
        return;
    }
    Muffin temp = queue.front();
    cout << "\tServing " << temp.name << " a " << temp.muffinType << " muffin.\n";
    queue.pop_front();
}
void outputMuffin(deque<Muffin>& queue) {
    if (queue.empty()) {
        cout << "\tMuffin queue is empty.\n";
        return;
    }
    cout << "\tMuffin queue:\n";
    int count = 1;
    for (auto& customer: queue) {
        cout << "\t\t " << count << ". " << customer.name << " ordered a " << customer.muffinType << " muffin.\n";
        count++;
    }
 
}