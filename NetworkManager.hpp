#pragma once
#include <iostream>
namespace Net{
	struct Connection;
	class Node;
	class Component;

	//components give/take charge, like batteries
	class Component{
	public:
		Component(int cost) : cost(cost){};
		int cost = 0;
	};

	//this is a single point in a grid of connections, it holds the next connection and a component
	class Node{
	public:
		Node(Node* connection = nullptr);
		~Node();
		void setConnection(Node* node); // setting a new connection will sever destroy the whole previous line
		Component* component = nullptr; // what this holds
		Connection* connection = nullptr; // where this connects to
		void setComponent(Component* comp) { component = comp; } // set the component
	};


	//connections hold a going>, current charge and resistance of the line
	struct Connection{
		Connection(Node* going, int charge) : going(going), charge(charge){};
		~Connection();
		Node* going = nullptr;
		int charge = 0;
		int resistance = 1;
		void applyResistance() { charge-=resistance; }
	};
	//this class manages the nodes+connections
	class NetworkManager{
		Node* initial_node = nullptr;
		Node* current_node = nullptr; // where we've got to
	public:
		NetworkManager();
		~NetworkManager();
		void generate();
		bool traverse();
	};
}