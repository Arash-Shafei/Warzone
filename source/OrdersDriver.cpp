#include "Order.h"
#include "OrdersDriver.h"
#include <iostream>
using namespace std;

void testOrdersList() {
	//Creating our Players
	cout << "*********Creating Players*********" << endl;
	Player_Demo* p1 = new Player_Demo();
	Player_Demo* p2 = new Player_Demo();
	Player_Demo* p3 = new Player_Demo();
	cout << endl;

	//Creating orders for Player's OrdersList
	cout << "*********Creating Orders for our Players*********" << endl;
	cout << endl;
	cout << "*********Creating Orders for Player 1*********" << endl;
	p1->createOrder(0);
	p1->createOrder(2);
	p1->createOrder(4);
	cout << endl;
	cout << "*********Creating Orders for Player 2*********" << endl;
	p2->createOrder(1);
	p2->createOrder(3);
	p2->createOrder(4);
	cout << endl;
	cout << "*********Creating Orders for Player 3*********" << endl;
	p3->createOrder(0);
	p3->createOrder(1);
	p3->createOrder(3);
	cout << endl;


	//Printing Player's OrdersList
	cout << "*********Printing the OrdersList for our Players*********" << endl;
	cout << endl;
	cout << "*********Printing the OrdersList for Player 1*********" << endl;
	p1->player_order_list->printList();
	cout << endl;
	cout << "*********Printing the OrdersList for Player 2*********" << endl;
	p2->player_order_list->printList();
	cout << endl;
	cout << "*********Printing the OrdersList for Player 3*********" << endl;
	p3->player_order_list->printList();
	cout << endl;


	//Moving orders in  Player's OrdersList
	cout << "*********Moving Order 1 to position 2*********" << endl;
	p1->player_order_list->move(0, 2);
	cout << endl;
	cout << "*********Moving Order 1 to position 3*********" << endl;
	p2->player_order_list->move(0, 3);
	cout << endl;
	cout << "*********Moving Order 1 to position 1*********" << endl;
	p3->player_order_list->move(0, 1);
	cout << endl;

	//Printing Player's OrdersList
	cout << "*********Printing the OrdersList for our Players*********" << endl;
	cout << endl;
	cout << "*********Printing the OrdersList for Player 1*********" << endl;
	p1->player_order_list->printList();
	cout << endl;
	cout << "*********Printing the OrdersList for Player 2*********" << endl;
	p2->player_order_list->printList();
	cout << endl;
	cout << "*********Printing the OrdersList for Player 3*********" << endl;
	p3->player_order_list->printList();
	cout << endl;

	//Removing Orders from Player's OrdersList
	cout << "*********Removing orders from Player's OrdersList*********" << endl;
	cout << endl;
	cout << "*********Removing order 1 from Player 1 OrdersList*********" << endl;
	p1->player_order_list->remove(p1->player_order_list->get_order_from_list(0));
	cout << endl;
	cout << "*********Removing order 3 from Player 2 OrdersList*********" << endl;
	p2->player_order_list->remove(p2->player_order_list->get_order_from_list(2));
	cout << endl;
	cout << "*********Removing order 2 from Player 3 OrdersList*********" << endl;
	p3->player_order_list->remove(p3->player_order_list->get_order_from_list(1));
	cout << endl;

	//Printing Player's OrdersList
	cout << "*********Printing the OrdersList for our Players*********" << endl;
	cout << endl;
	cout << "*********Printing the OrdersList for Player 1*********" << endl;
	p1->player_order_list->printList();
	cout << endl;
	cout << "*********Printing the OrdersList for Player 2*********" << endl;
	p2->player_order_list->printList();
	cout << endl;
	cout << "*********Printing the OrdersList for Player 3*********" << endl;
	p3->player_order_list->printList();
	cout << endl;

	//Execute some orders
	cout << "*********Executing order for Player 1*********" << endl;
	cout << endl;
	p1->player_order_list->execute_list();
	p2->player_order_list->execute_list();
	p3->player_order_list->execute_list();

	cout << endl;
}


