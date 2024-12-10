#include <iostream>
#include <deque>
#include <vector>
#include <stack>
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

struct Boba {
    string name;
    string flavor;

    Boba(string n, string f) : name(n), flavor(f) {}
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

//bracelet
void addBraceletCustomer(vector<Bracelet>&, string, string);
void serveBraceletCustomer(vector<Bracelet>&);
void outputBracelet(vector<Bracelet>&);

//boba
void addBoba(stack<Boba>&, string, string);
void serveBobaCustomer(stack<Boba>&);
void outputBoba(stack<Boba>&);


int main() {
    srand(time(0));
    //names for coffee and also drink orders, mayb used for more in future
    string names[] = {"Mo", "Ali", "Omar", "Hannah", "Ben", "Sahil", "Najla", "Hanif", "Tom", "Nick", "Elizabeth", "Sarah"};
    string drinkOrders[] = {"Espresso", "Americano", "Latte", "Mocha", "Cappucino", "Cold Brew", "Chai"};
    string muffins[] = {"Blueberry", "Poppyseed", "Chocolate", "Red Velvet", "Banana"};
    string bracelets[] = {"Red", "Orange", "Yellow", "Green", "Blue", "Purple"};
    string flavors[] = {"Taro", "Lychee", "Mango", "Strawberry", "Honeydew", "Milk Tea"};

    //coffee booth queue
    Customer* head = nullptr;
    //muffin queue
    deque<Muffin> muffinQueue;
    //bracelet queue
    vector<Bracelet> braceletQueue;
    //boba queue(stack)
    stack<Boba> bobaQueue;
    
    //initialize the coffee queue (3 customers) also the muffin
    for (int i = 0; i < 3; i++) {
        addCustomer(head, names[rand() % 12], drinkOrders[rand() % 7]);
        addMuffinCustomer(muffinQueue, names[rand() % 12], muffins[rand() % 5]);
        addBraceletCustomer(braceletQueue, names[rand() % 12], bracelets[rand() % 6]);
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

        cout << "BRACELET BOOTH:\n";
        serveBraceletCustomer(braceletQueue);
        if (rand() % 2) {
            addBraceletCustomer(braceletQueue, names[rand() % 12], bracelets[rand() % 6]);
        }
        outputBracelet(braceletQueue);
    }

    return 0;
}


//coffe definition
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

//muffin definitions
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

//bracelet definitions
void addBraceletCustomer(vector<Bracelet>& queue, string name, string color) {
    queue.push_back(Bracelet(name,color));
    cout << "\tAdded " << name << " to the bracelet queue ordering a " << color << " bracelet\n";
}
void serveBraceletCustomer(vector<Bracelet>& queue) {
    if (queue.empty()) {
        cout << "\tBracelet queue is empty.\n";
        return;
    }
    Bracelet temp = queue.front();
    cout << "\tServing " << temp.name << " a " << temp.color << " bracelet.\n";
    queue.erase(queue.begin());
}

void outputBracelet(vector<Bracelet>& queue) {
    if (queue.empty()) {
        cout << "\tBracelet queue is empty.\n";
        return;
    }
    cout << "\tBracelet queue:\n";
    int count = 1;
    for (auto& customer: queue) {
        cout << "\t\t " << count << ". " << customer.name << " ordered a " << customer.color << " bracelet.\n";
        count++;
    }
}

//boba definitions
void addBoba(stack<Boba>& queue, string name, string flavor) {
    queue.push(Boba(name, flavor));
    cout << "\tAdded " << name << " to the boba queue ordering a " << flavor << " boba\n";
}

void serveBobaCustomer(stack<Boba>& queue) {
    if (queue.empty()) {
        cout << "\tBoba queue is empty.\n";
        return;
    }
    Boba temp = queue.top();
    cout << "\tServing " << temp.name << " a " << temp.flavor << " boba.\n";
    queue.pop();
}

void outputBoba(stack<Boba>& queue) { 
    if (queue.empty()) {
        cout << "\tBoba queue is empty.\n";
        return;
    }
    cout << "\tBoba queue:\n";
    int count = 1;

}
