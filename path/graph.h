class Node;
class Connection;

class Node{	
public:
	std::vector<Connection> connections;
	int id;
	vec3 position;

	//std::vector<Connection> getConnections(){ return connections;}
};

class Connection{
protected:
	float cost;
	Node fromNode;
	Node toNode;

public:
	Connection(float c, Node &fn, Node &tn) : cost(c),fromNode(fn),toNode(tn) {}

	float getCost(){ return cost; }
	Node getFromNode(){ return fromNode; }
	Node getToNode(){ return toNode; }
};
