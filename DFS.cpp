//Programmer: Sadeem Khan
//Programmer ID: 1549921

#include <fstream>
#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include <string>
#include <vector>
using namespace std;

struct Node
{
  string name;

  bool isVisited;
  list<int> neighbors;
};

queue<int> doDepthFirstSearch(int iOriginNode, vector<Node>& database)
{
  queue<int> searchOrder; // return this queue of indices
  stack<int> toDoList; // create another queue of ints to store the "to-do" list

  for (int i = 0; i < database.size(); i++) database[i].isVisited = false; // initialize each node in database: set to "not visited" --- false is not visited

  toDoList.push(iOriginNode); // push start node's index onto the "to-do" list
  while (!toDoList.empty()) // while the "to-do" list is not empty
  {
    //  peek/pop a node's index from the "to-do" list
    int i = toDoList.top();
    toDoList.pop();

    if (database[i].isVisited == false) // if that node has not yet been visited
    {
      database[i].isVisited = true; // mark the node as visited
      searchOrder.push(i); //  push node's index onto the result queue

      for (list<int>::reverse_iterator rit = database[i].neighbors.rbegin(); rit != database[i].neighbors.rend(); ++rit) // for each of that node's neighbors (in reverse order) -- rit == reverse iterator
      {
        // if neighbor has not yet been visited 
        if (database[*rit].isVisited == false) toDoList.push(*rit); // push neighbor's index onto the "to-do" list
      }
    }
  }
  return searchOrder; // return the result queue
}

int main()
{
  // Identification
  cout << "Programmer: Sadeem Khan\n";
  cout << "Programmer's ID: 1549921\n";
  cout << "File: " << __FILE__ << endl;

  ifstream fin;
  fin.open("cities.txt");
  if (!fin.good()) throw "I/O error";  

  // process the input file
  vector<Node> database;
  while (fin.good()) // EOF loop
  {
    string fromCity, toCity;

    // read one edge
    getline(fin, fromCity);
    getline(fin, toCity);
    fin.ignore(1000, 10); // skip the line with distance
    fin.ignore(1000, 10); // skip the separator

    // add vertices for new cities included in the edge
    int iToNode = -1, iFromNode = -1, i;
    for (i = 0; i < database.size(); i++) // seek "to" city
      if (database[i].name == fromCity)
        break;
    if (i == database.size()) // not in database yet
    {
      // store the node if it is new
      Node fromNode = {fromCity};
      database.push_back(fromNode);
    }
    iFromNode = i; 

    for (i = 0; i < database.size(); i++) // seek "from" city
      if (database[i].name == toCity)
        break;
    if (i == database.size()) // not in vector yet
    {
      // store the node if it is new
      Node toNode = {toCity};
      database.push_back(toNode);
    }
    iToNode = i; 

    // store bi-directional edges
    database[iFromNode].neighbors.push_back(iToNode);
    database[iToNode].neighbors.push_back(iFromNode);
  }
  fin.close();
  cout << "Input file processed\n\n";

  while (true)
  {
    // get the start city for the search
    string startCity;
    cout << "\nEnter the start city [blank to exit]: ";
    getline(cin, startCity);
    if (startCity.length() == 0) break;

    // find the start city
    int i;
    for (i = 0; i < database.size(); i++)
      if (database[i].name == startCity)
        break;

    // DFS result by copy-pop
    cout << "DFS";
    for (queue<int> q = doDepthFirstSearch(i, database); !q.empty(); q.pop())
      cout  << '-'<< database[q.front()].name;
    cout << endl;
  }
}