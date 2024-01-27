#include "Order.h";

///////////////////////////////////////////////////////////////////// 
//////////////////// OrdersList class //////////////////////////////
///////////////////////////////////////////////////////////////////

////Default constructor
OrdersList::OrdersList() {
    list_of_orders = new vector<Order*>();
}

//////Destructor for class "orderslist"
OrdersList::~OrdersList() {
    delete list_of_orders;
    list_of_orders = NULL;
    cout << "Orders List is now empty and destroyed" << endl;
}

//Adding an order to my list of orders
void OrdersList::add_to_order_list(Order* someOrder) {
    (*list_of_orders).push_back(someOrder);
}

//Removing an order from my list of orders
void OrdersList::remove(Order* anOrder) {
    for (int i = 0; i < (*list_of_orders).size();i++) {
        if (anOrder->get_order_type_id() == (*list_of_orders).at(i)->get_order_type_id()) {
            cout << "Now deleting your: " << anOrder->get_order_name() << " Order" << endl;
            (*list_of_orders).erase((*list_of_orders).begin() + i);
        }
    }
}

//Moving the position of an order in the list of orders
void OrdersList::move(int initial_position, int new_position) {
    if (initial_position >= 0 && initial_position < (*list_of_orders).size() && new_position >= 0 && new_position < (*list_of_orders).size()) {
        (*list_of_orders).insert((*list_of_orders).begin() + new_position, (*list_of_orders).at(initial_position));
        (*list_of_orders).erase((*list_of_orders).begin() + initial_position);
    }
    else if ((*list_of_orders).size() == new_position) {
        (*list_of_orders).push_back((*list_of_orders).at(initial_position));
        (*list_of_orders).erase((*list_of_orders).begin() + initial_position);
    }
    else {
        cout << "Invalid move request" << endl;
    }
}

//Printing the contents of my list of orders
void OrdersList::printList() {
    for (int i = 0; i < (*list_of_orders).size();i++) {
        cout << (i + 1) << ". " << (*list_of_orders).at(i)->get_order_name() << " Order" << endl;
    }
}

//Get the order from the orderslist
Order* OrdersList::get_order_from_list(int i) {
    return ((*list_of_orders).at(i));
}


//Execute the first order in the list
void OrdersList::execute_list() {
    switch (((*list_of_orders).front())->get_order_type_id()) {
    case 0:
        (static_cast<Deploy*>((*list_of_orders).front()))->execute();
        break;
    case 1:
        (static_cast<Advance*>((*list_of_orders).front()))->execute();
        break;
    case 2:
        (static_cast<Bomb*>((*list_of_orders).front()))->execute();
        break;
    case 3:
        (static_cast<Blockade*>((*list_of_orders).front()))->execute();
        break;
    case 4:
        (static_cast<Airlift*>((*list_of_orders).front()))->execute();
        break;
    case 5:
        (static_cast<Negotiate*>((*list_of_orders).front()))->execute();
        break;
    }
}

//Assignment Operators
OrdersList& OrdersList::operator = (const OrdersList& e) {
    this->list_of_orders = new vector<Order*>(*(e.list_of_orders));
    return *this;
}

//Copy Constructor
OrdersList::OrdersList(const OrdersList& e) {

    this->list_of_orders = new vector<Order*>(*(e.list_of_orders));
}





///////////////////////////////////////////////////////////////////// 
//////////////////// Order base class ////////////////////////////// 
///////////////////////////////////////////////////////////////////

// Default constructor for base Class "Order" 
Order::Order():name("") {
    is_valid = NULL;
    order_type = NULL;
    is_executed = NULL;
}

// Destructor for class "Order"
Order::~Order() {
    delete is_valid;
    delete order_type;
    delete is_executed;

    is_valid = NULL;
    order_type = NULL;
    is_executed = NULL;
}

//Assigning the order type id to my objects
void Order::set_order_type_id(int id) {
    order_type = new int(id);
}

//Retrieving the order type id to my objects
int Order::get_order_type_id() {
    return(*order_type);
}

//Retrieve a boolean for validation status
bool Order::get_validity_status() {
    return(*is_valid);
}

//Assigning a boolean for the validation status
void Order::set_validity_status(bool b) {
    is_valid = new bool(b);
}
//Assigning a boolean for the execution status
void Order::set_execute_status(bool b) {
    is_executed = new bool(b);
}

//Retrieving a boolean for the execution status
bool Order::get_execute_status() {
    return (*is_executed);
}

//Assigning a name to my Order object
void Order::setName(const string& s) {
    name = s;
}

//Retrieving the name for my Order object
string Order::get_order_name() {
    return(name);
}

//Stream insertion operator for Order Class
ostream& operator << (ostream& strm, Order& o) {
    string s = "An order";
    return strm << s;
}


//Assignment Operator
Order& Order::operator = (const Order& e) {
    this->is_valid = new bool(*(e.is_valid));
    this->order_type = new int(*(e.order_type));
    name = e.name;
    this->is_executed = new bool(*(e.is_executed));
    return *this;
}

//Copy constructor
Order::Order(const Order& e):name(e.name) {
    this->is_valid = new bool(*(e.is_valid));
    this->order_type = new int(*(e.order_type));
    this->is_executed = new bool(*(e.is_executed));
}




///////////////////////////////////////////////////////////////////// 
//////////////////// Deploy subclass ///////////////////////////////
///////////////////////////////////////////////////////////////////

// Default constructor for subclass "Deploy" 
Deploy::Deploy() : Order() {
    cout << "Creating a Deploy Order" << endl;
    set_order_type_id(0);
    set_validity_status(true);
    setName("Deploy");
}

// Destructor for class "Deploy"
Deploy::~Deploy() {
    cout << "Destroying Deploy Order" << endl;
}

//Validating the order
void Deploy::validate() {
    if (get_validity_status()) {
        cout << "Valid Order" << endl;
    }
    else {
        cout << "Not Valid Order" << endl;
        set_validity_status(false);
    }
}

//Executing the order 
void Deploy::execute() {
    validate();
    if (get_validity_status()) {
        if (true) {
            cout << "Deploy Executed + some game action" << endl;

        }
        else {
            cout << "Order won't execute  " << endl;
        }
    }
    else {
        cout << "Not Valid Order" << endl;
    }
}

//Stream insertion operator overloaded 
ostream& operator << (ostream& strm, Deploy& deploy) {
    string s = "[...Deploy order details..]";
    if (deploy.get_execute_status()) {
        return strm << s + " [...some game action...]";
    }
    else {
        return strm << s;
    }
}

//Assignment Operator
Deploy& Deploy::operator = (const Deploy& e) {
    Order::operator=(e);
    return *this;
}

//Copy Constructor
Deploy::Deploy(const Deploy& e) : Order(e) {
}






///////////////////////////////////////////////////////////////////// 
//////////////////// Advance subclass //////////////////////////////
///////////////////////////////////////////////////////////////////

// Default constructor for subclass "Advance" 
Advance::Advance() : Order() {
    cout << "Creating a Advance Order" << endl;
    set_order_type_id(1);
    set_validity_status(true);
    setName("Advance");
}

// Destructor for class "Advance"
Advance::~Advance() {
    cout << "Destroying advance order" << endl;
}

//Validating the order
void Advance::validate() {
    if (get_validity_status()) {
        cout << "Valid order" << endl;
    }
    else {
        cout << "Not valid order" << endl;
        set_validity_status(false);
    }
}

//Executing the order 
void Advance::execute() {
    validate();
    if (get_validity_status()) {
        if (true) {
            cout << "Advance Executed + some game action" << endl;

        }
        else {
            cout << "Order won't execute  " << endl;
        }
    }
    else {
        cout << "Not Valid Order" << endl;
    }
}

//Stream insertion operator overloaded 
ostream& operator << (ostream& strm, Advance& advance) {
    string s = "[...Advance order details..]";
    if (advance.get_execute_status()) {
        return strm << s + " [...some game action...]";
    }
    else {
        return strm << s;
    }
}



//Assignment Operator
Advance& Advance::operator= (const Advance& e) {
    Order::operator=(e);
    return *this;
}

//Copy Constructor
Advance::Advance(const Advance& e) : Order(e) {
}






///////////////////////////////////////////////////////////////////// 
//////////////////// Bomb subclass /////////////////////////////////
///////////////////////////////////////////////////////////////////

// Default constructor for subclass "Bomb" 
Bomb::Bomb() : Order() {
    cout << "Creating a Bomb Order" << endl;
    set_order_type_id(2);
    set_validity_status(true);
    setName("Bomb");
}

// Destructor for class "Bomb"
Bomb::~Bomb() {
    cout << "Destroying bomb order" << endl;
}

//Validating the order
void Bomb::validate() {
    if (get_validity_status()) {
        cout << "Valid order" << endl;
    }
    else {
        cout << "Not valid order" << endl;
        set_validity_status(false);
    }
}

//Executing the order 
void Bomb::execute() {
    validate();
    if (get_validity_status()) {
        if (true) {
            cout << "Bomb Executed + some game action" << endl;

        }
        else {
            cout << "Order won't execute  " << endl;
        }
    }
    else {
        cout << "Not Valid Order" << endl;
    }
}

//Stream insertion operator overloaded 
ostream& operator << (ostream& strm, Bomb& bomb) {
    string s = "[...Bomb order details..]";
    if (bomb.get_execute_status()) {
        return strm << s + " [...some game action...]";
    }
    else {
        return strm << s;
    }
}


//Assignment Operator
Bomb& Bomb::operator = (const Bomb& e) {
    Order::operator=(e);
    return *this;
}

//Copy Constructor
Bomb::Bomb(const Bomb& e) : Order(e) {
}





///////////////////////////////////////////////////////////////////// 
//////////////////// Blockade subclass /////////////////////////////
///////////////////////////////////////////////////////////////////

// Default constructor for subclass "Blockade" 
Blockade::Blockade() : Order() {
    cout << "Creating a Blockade Order" << endl;
    set_order_type_id(3);
    set_validity_status(true);
    setName("Blockade");
}

// Destructor for class "Blockade"
Blockade::~Blockade() {
    cout << "Destroying blockade order" << endl;
}

//Validating the order
void Blockade::validate() {
    if (get_validity_status()) {
        cout << "Valid order" << endl;
    }
    else {
        cout << "Not valid order" << endl;
        set_validity_status(false);
    }
}

//Executing the order 
void Blockade::execute() {
    validate();
    if (get_validity_status()) {
        if (true) {
            cout << "Blockade Executed + some game action" << endl;

        }
        else {
            cout << "Order won't execute  " << endl;
        }
    }
    else {
        cout << "Not Valid Order" << endl;
    }
}

//Stream insertion operator overloaded 
ostream& operator << (ostream& strm, Blockade& blockade) {
    string s = "[...Blockade order details..]";
    if (blockade.get_execute_status()) {
        return strm << s + " [...some game action...]";
    }
    else {
        return strm << s;
    }
}

//Assignment Operator
Blockade& Blockade::operator = (const Blockade& e) {
    Order::operator=(e);
    return *this;
}

//Copy Constructor
Blockade::Blockade(const Blockade& e) : Order(e) {
}







///////////////////////////////////////////////////////////////////// 
//////////////////// Airlift subclass //////////////////////////////
///////////////////////////////////////////////////////////////////

// Default constructor for subclass "Airlift" 
Airlift::Airlift() : Order() {
    cout << "Creating a Airlift Order" << endl;
    set_order_type_id(4);
    set_validity_status(true);
    setName("Airlift");
}

// Destructor for class "Airlift"
Airlift::~Airlift() {
    cout << "Destroying airlift order" << endl;
}

//Validating the order
void Airlift::validate() {
    if (get_validity_status()) {
        cout << "Valid order" << endl;
    }
    else {
        cout << "Not valid order" << endl;
        set_validity_status(false);
    }
}

//Executing the order 
void Airlift::execute() {
    validate();
    if (get_validity_status()) {
        if (true) {
            cout << "Airlift Executed + some game action" << endl;

        }
        else {
            cout << "Order won't execute  " << endl;
        }
    }
    else {
        cout << "Not Valid Order" << endl;
    }
}

//Stream insertion operator overloaded 
ostream& operator << (ostream& strm, Airlift& airlift) {
    string s = "[...Airlift order details..]";
    if (airlift.get_execute_status()) {
        return strm << s + " [...some game action...]";
    }
    else {
        return strm << s;
    }
}

//Assignment Operator
Airlift& Airlift::operator = (const Airlift& e) {
    Order::operator=(e);
    return *this;
}

//Copy Constructor
Airlift::Airlift(const Airlift& e) : Order(e) {
}




///////////////////////////////////////////////////////////////////// 
//////////////////// Negotiate subclass ////////////////////////////
///////////////////////////////////////////////////////////////////

// Default constructor for  subClass "Negotiate" 
Negotiate::Negotiate() : Order() {
    cout << "Creating a Negotiate Order" << endl;
    set_order_type_id(5);
    set_validity_status(true);
    setName("Negotiate");
}

// Destructor for class "Negotiate"
Negotiate::~Negotiate() {
    cout << "Destroying negotiate order" << endl;
}

//Validating the order
void Negotiate::validate() {
    if (get_validity_status()) {
        cout << "Valid order" << endl;
    }
    else {
        cout << "Not valid order" << endl;
        set_validity_status(false);
    }
}

//Executing the order 
void Negotiate::execute() {
    validate();
    if (get_validity_status()) {
        if (true) {
            cout << "Negotiate Executed + some game action" << endl;
        }
        else {
            cout << "Order won't execute  " << endl;
        }
    }
    else {
        cout << "Not Valid Order" << endl;;
    }
}

//Stream insertion operator overloaded 
ostream& operator << (ostream& strm, Negotiate& negotiate) {
    string s = "[...Negotiate order details..]";
    if (negotiate.get_execute_status()) {
        return strm << s + " [...some game action...]";
    }
    else {
        return strm << s;
    }
}

//Assignment Operator
Negotiate& Negotiate::operator = (const Negotiate& e) {
    Order::operator=(e);
    return *this;
}

//Copy Constructor
Negotiate::Negotiate(const Negotiate& e) : Order(e) {
}






///////////////////////////////////////////////////////////////////// 
//////////////////// Player class ////////////////////////////
///////////////////////////////////////////////////////////////////

//Constructor for Player class
Player_Demo::Player_Demo() {
    player_order_list = new OrdersList();
    players_hand = new Hand();
}

//Destructor for Player class
Player_Demo::~Player_Demo() {
    delete player_order_list;
    player_order_list = NULL;
    cout << "Player order list destroyed" << endl;

    delete players_hand;
    players_hand = NULL;
    cout << "Players hand destroyed" << endl;
}


//Create an order for the player
void Player_Demo::createOrder(int id) {
    switch (id) {
    case 0:
        player_order_list->add_to_order_list(new Deploy());
        break;
    case 1:
        player_order_list->add_to_order_list(new Advance());
        break;
    case 2:
        player_order_list->add_to_order_list(new Bomb());
        break;
    case 3:
        player_order_list->add_to_order_list(new Blockade());
        break;
    case 4:
        player_order_list->add_to_order_list(new Airlift());
        break;
    case 5:
        player_order_list->add_to_order_list(new Negotiate());
        break;
    }
}

//Assignment Operator for Player class
Player_Demo& Player_Demo::operator=(const Player_Demo& e) {
    this->player_order_list = new OrdersList(*(e.player_order_list));
    this->players_hand = new Hand(*(e.players_hand));
    return *this;
}

//Copy Constructor for Player class
Player_Demo::Player_Demo(const Player_Demo& e) {
    this->player_order_list = new OrdersList(*(e.player_order_list));
    this->players_hand = new Hand(*(e.players_hand));
}

