#include "NetworkManager.hpp"

Net::Node::Node(Node* node)
{
	if(node){
		setConnection(node);
	}
}

Net::Node::~Node()
{
	delete component;
	delete connection;
}

Net::Connection::~Connection()
{
	delete going;
}

void Net::Node::setConnection(Node* node) 
{
	if(connection)
	{
		delete connection;	
	}
	this->connection = new Connection(node, 0);
}

Net::NetworkManager::~NetworkManager()
{
	delete initial_node;
}

Net::NetworkManager::NetworkManager()
{
	generate();
}

void Net::NetworkManager::generate()
{
	//construct some abitrary connection with a battery at one end
	Component* battery = new Component(10);
	initial_node = new Node();
	initial_node->setComponent(battery);
	auto* previous = initial_node;
	for(int i = 0; i < 5; i++)
	{
		auto* now = new Node();
		previous->setConnection(now);
		previous = now;
	}
	//set it back in a loop
	current_node = initial_node;
}

bool Net::NetworkManager::traverse()
{
	std::cout << "On Node: " << current_node << " - Charge: " << current_node->connection->charge << std::endl;
	if(current_node->component)
	{
		//apply the cost fo the component
		std::cout << "Component charge: " << current_node->component->cost << std::endl;
		current_node->connection->charge += current_node->component->cost;
	}

	//apply resistance
	std::cout << "Resistance cost: " << current_node->connection->resistance << std::endl;
	current_node->connection->applyResistance();
	//if we've then run out of charge, then we stop the loop
	if(current_node->connection->charge <= 0)
	{
		std::cout << "this connection died, there's no charge left" << std::endl;
		return false;
	}
	//if not we pass on the charge and continue
	Node* curr_node = current_node;
	current_node = curr_node->connection->going; //advance down the line
	if(current_node)
	{
		if(current_node->connection)
		{
			current_node->connection->charge = curr_node->connection->charge;
			curr_node->connection->charge = 0; // this charge has now been passed onto the next connection
			return true;
		}
		else
		{
			std::cout << "we found a loose connection >:(" << std::endl;
			return false;
		}
	}
	return false;
}