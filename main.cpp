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

//struct for muffin booth sim
struct Muffin {
    string name;
    string muffinType;

    Muffin(string n, string m) : name(n), muffinType(m) {}
};

//struct for bracelet booth sim
struct Bracelet {
    string name;
    string color;

    Bracelet(string n, string c) : name(n), color(c) {}
};

//struct for boba booth sim
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
//adds muffin customer
void addMuffinCustomer(deque<Muffin>&, string, string);
//serves muffin customer
void serveMuffinCustomer(deque<Muffin>&);
//outputs the muffin queue
void outputMuffin(deque<Muffin>&);

//bracelet
//adds bracelet customer
void addBraceletCustomer(vector<Bracelet>&, string, string);
//serves bracelet customer
void serveBraceletCustomer(vector<Bracelet>&);
//outputs the bracelet queue
void outputBracelet(vector<Bracelet>&);

//boba
//adds boba customer
void addBobaCustomer(stack<Boba>&, string, string);
//serves boba customer
void serveBobaCustomer(stack<Boba>&);
//outputs the boba queue
void outputBoba(stack<Boba>); //not by reference otherwise it will delete


int main() {
    //so randomization is always random
    srand(time(0));
    //names for coffee and also drink orders, mayb used for more in future
    string names[] = {"Mo", "Ali", "Omar", "Hannah", "Ben", "Sahil", "Najla", "Hanif", "Tom", "Nick", "Elizabeth", "Sarah"};
    //possible drink orders for coffee booth
    string drinkOrders[] = {"Espresso", "Americano", "Latte", "Mocha", "Cappucino", "Cold Brew", "Chai"};
    //possible muffins for muffin booth
    string muffins[] = {"Blueberry", "Poppyseed", "Chocolate", "Red Velvet", "Banana"};
    //possible bracelet colors for bracelet booth
    string bracelets[] = {"Red", "Orange", "Yellow", "Green", "Blue", "Purple"};
    //possible flavors for boba booth
    string flavors[] = {"Taro", "Lychee", "Mango", "Strawberry", "Honeydew", "Milk Tea"};

    //coffee booth queue
    Customer* head = nullptr;
    //muffin queue
    deque<Muffin> muffinQueue;
    //bracelet queue
    vector<Bracelet> braceletQueue;
    //boba queue(stack)
    stack<Boba> bobaQueue;
    
    //initialize the coffee queue (3 customers) also the muffin also the bracelet and also the boba
    for (int i = 0; i < 3; i++) {
        //add customer with random name and order to coffee booth
        addCustomer(head, names[rand() % 12], drinkOrders[rand() % 7]);
        //add customer with random name and order to muffin booth
        addMuffinCustomer(muffinQueue, names[rand() % 12], muffins[rand() % 5]);
        //add customer with random name and order to bracelet booth
        addBraceletCustomer(braceletQueue, names[rand() % 12], bracelets[rand() % 6]);
        //add customer with random name and order to boba booth
        addBobaCustomer(bobaQueue, names[rand() % 12], flavors[rand() % 6]);
    }

    //loop for 10 rounds
    for (int i = 1; i <= ROUNDS; i++) {
        cout << "Round " << i << ":\n";

        //coffee booth
        cout << "COFFEE BOOTH:\n";
        //always serve customer (Coffee)
        serveCustomer(head);
        //50 percent of adding a new customer using integer to deterine bool
        if (rand() % 2) {
            //add customer with random name and order to coffee booth
            addCustomer(head, names[rand() % 12], drinkOrders[rand() % 7]);
        }
        //output the coffe booth queue
        outputQueue(head);

        //muffin booth
        cout << "MUFFIN BOOTH:\n";
        //always serve customer (Muffin)
        serveMuffinCustomer(muffinQueue);
        if (rand() % 2) {
            //add customer with random name and order to muffin booth
            addMuffinCustomer(muffinQueue, names[rand() % 12], muffins[rand() % 5]);
        }
        //output the muffin booth queue
        outputMuffin(muffinQueue);

        cout << "BRACELET BOOTH:\n";
        //always serve customer (Bracelet)
        serveBraceletCustomer(braceletQueue);
        if (rand() % 2) {
            //add customer with random name and order to bracelet booth
            addBraceletCustomer(braceletQueue, names[rand() % 12], bracelets[rand() % 6]);
        }
        //output the bracelet booth queue
        outputBracelet(braceletQueue);

        //boba booth
        cout << "BOBA BOOTH:\n";
        //always serve customer (Boba)
        serveBobaCustomer(bobaQueue);
        if (rand() % 2) {
            //add customer with random name and order to boba booth
            addBobaCustomer(bobaQueue, names[rand() % 12], flavors[rand() % 6]);
        }
        //output the boba booth queue
        outputBoba(bobaQueue);
    }
    return 0;
}


//coffe definitions
//add customer to coffe booth queue
void addCustomer(Customer*& head, string name, string order) {
    //create new customer using parameters
    Customer* newCustomer = new Customer(name, order);
    cout << "\tAdded " << newCustomer->name << " to the coffee queue ordering a(n) " << order <<  "\n";
    //if there is no head (Empty)
    if (!head) {
        //set the front of the queue to the new customer
        head = newCustomer;
    }
    else {
        //set temp like we use for iterator to the first element
        Customer* temp = head;
        //go until there is no next node, so like the last node
        while(temp->next != nullptr) {
            temp = temp->next;
        }
        //then set the next node after the previous last one to our new node
        temp->next = newCustomer;
    }
}

void serveCustomer(Customer*& head) {
    //check if empty
    if (!head) {
        cout << "\tNo customers in coffee queue\n";
        return;
    }
    //set to the first node
    Customer* temp = head;
    //serve the first node (front of line/queue)
    cout << "\tServing " << temp->name << " a " << temp->order << ".\n";
    head = head->next;
    delete temp;
}

void outputQueue(Customer* head) {
    //check if empty
    if (!head) {
        cout << "\tThe coffee queue is empty\n";
        return;
    }
    //use this to output each node and data
    Customer* temp = head;
    cout << "\tCoffee queue:\n";
    int count = 1;
    while (temp) {
        cout << "\t\t" << count << ". " << temp->name << " ordered a " << temp->order << endl;
        temp = temp->next; //go to next ndoe
        count++;
    }
} 

//muffin definitions
void addMuffinCustomer(deque<Muffin>& queue, string name, string order) {
    //simplly add to the deque (back always if empty will be the front though)
    queue.push_back(Muffin(name, order));
    cout << "\tAdded " << name << " to the muffin queue ordering a " << order << " muffin\n";
}
void serveMuffinCustomer(deque<Muffin>& queue) {
    //check if its empty
    if (queue.empty()) {
        cout << "\tMuffin queue is empty.\n";
        return;
    }
    //set the one we serve to the front of the queue
    Muffin temp = queue.front();
    //serve output
    cout << "\tServing " << temp.name << " a " << temp.muffinType << " muffin.\n";
    queue.pop_front(); //delete from the queue
}
void outputMuffin(deque<Muffin>& queue) {
    //check if empty
    if (queue.empty()) {
        cout << "\tMuffin queue is empty.\n";
        return;
    }
    cout << "\tMuffin queue:\n";
    int count = 1;
    //go thru every struct we currently have in queue and output
    for (auto& customer: queue) {
        cout << "\t\t " << count << ". " << customer.name << " ordered a " << customer.muffinType << " muffin.\n";
        count++;
    }
}

//bracelet definitions
void addBraceletCustomer(vector<Bracelet>& queue, string name, string color) {
    //simple addition  to back of vector if empty it will be the front though
    queue.push_back(Bracelet(name,color));
    cout << "\tAdded " << name << " to the bracelet queue ordering a " << color << " bracelet\n";
}
void serveBraceletCustomer(vector<Bracelet>& queue) {
    //check if empty
    if (queue.empty()) {
        cout << "\tBracelet queue is empty.\n";
        return;
    }
    //set the one we are going to serve to the front of the queue
    Bracelet temp = queue.front();
    cout << "\tServing " << temp.name << " a " << temp.color << " bracelet.\n";
    queue.erase(queue.begin()); //delete after we output that we are serving it
}

void outputBracelet(vector<Bracelet>& queue) {
    //check if empty
    if (queue.empty()) {
        cout << "\tBracelet queue is empty.\n";
        return;
    }
    cout << "\tBracelet queue:\n";
    int count = 1;
    //go through each struct stored in the vector and output
    for (auto& customer: queue) {
        cout << "\t\t " << count << ". " << customer.name << " ordered a " << customer.color << " bracelet.\n";
        count++;
    }
}

//boba definitions
void addBobaCustomer(stack<Boba>& queue, string name, string flavor) {
    //simple addition using built in stack operators
    queue.push(Boba(name, flavor));
    cout << "\tAdded " << name << " to the boba queue ordering a " << flavor << " boba\n";
}

void serveBobaCustomer(stack<Boba>& queue) {
    //check if empty
    if (queue.empty()) {
        cout << "\tBoba queue is empty.\n";
        return;
    }
    //set the one we are going to serve to the top/first element in the queue
    Boba temp = queue.top();
    cout << "\tServing " << temp.name << " a " << temp.flavor << " boba.\n";
    queue.pop(); //after reading out its information we remove(pop) it from the stack
}

void outputBoba(stack<Boba> queue) { 
    //check if empty
    if (queue.empty()) {
        cout << "\tBoba queue is empty.\n";
        return;
    }
    cout << "\tBoba queue:\n";
    int count = 1;
    //while the stack is not empty
    while (!queue.empty()) {
        Boba customer = queue.top();
        //set to first in line or queue
        cout << "\t\t " << count << ". " << customer.name << " ordered a " << customer.flavor << " boba.\n";
        queue.pop(); //get rid of it, like a copy of it though
        count++;
    }
}
