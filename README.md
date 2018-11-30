# SDN
Project to demonstrate a Software Defined Network

Application Layer:

The generation of a randomized key that will represent authentication. A number below 50 can represent an authorized value. A number above 50 will represent an unauthorized value.

SDN Controller:


The controller in a Software Defined Network is in charge of routing packets to devices on a network. In this project, a simplified idea is to route a packet containing an authorized value to devices on a networked. In our project, the controller will utilized Dijkstra's algorithm to route to different devices on a network. In a larger instance of a SDN, the controller may run a different routing method such as an OpenFlow implementation.


Device:

To demonstrate the advantage of an SDN, which is that each node in an SDN has a rich set of functions it can execute without having to rely on another physical device, the device program will contain a simple firewall function that will either accept authorized values or block unauthorized values. The device will contain a queue to store accepted values that will be removed after a certain amount of time to allow more values to be inserted. Each device will contain a value that represents the distance within the network from another node for the controller to apply Dijkstra's algorithm and build the routing table.


Defined terms:

Authenticator ->  The application layer contains an authentication function which will generate random keys.

Controller -> A server application running on a computer utilizing sockets to send data to another computer on the same network that will run the device program.

Device/Node/Router -> A client application running on a computer which will handle the packets received to determine whether it is an authorized value or not.

Dijkstra's algorithm -> Dijkstra's algorithm is an algorithm for finding the shortest paths between nodes (devices or routers) in a graph, or in this case, a network.


Personal notes:

to run server.c:
gcc server.c -o serv -lpthread
./serv


to run clients (on different terminals):
./cli
./cli2
