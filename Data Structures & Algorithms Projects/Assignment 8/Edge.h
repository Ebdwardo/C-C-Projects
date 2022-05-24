//********************************************************************
// Name of Author: Eduardo Teodosio Campuzano
// Description: this header file defines an edge in the graph. Each edge
//              has 3 attributes, namely two Cities and the air ticket
//              price between them.
//********************************************************************

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

//City represents one vertex of the graph
struct City
{
    City() {

    }
    string cityName;
    int rank;
    struct City* parent;

   //constructor
   City(string name)
   {
       cityName = name;
       rank = 0;
       parent = NULL;
   }
};

//class Edge represents one edge of the graph which connects two City objects
class Edge
{
   private:
    struct City* city1;
    struct City* city2;
    double price;

   public:
   Edge(City* city1, City* city2, double price);
   ~Edge();
   City* getCity1();
   City* getCity2();
   double getPrice();
   void printEdge();

    Edge();
};

//constructor
Edge::Edge(City* city1, City* city2, double price)
{
    this->price = price;
    this->city1 = city1;
    this->city2 = city2;
}

//Destructor
Edge::~Edge()
{
    delete city1;
    delete city2;
}

//Accessor for city1
City* Edge::getCity1()
{
    return city1;
}

//Accessor for city2
City* Edge::getCity2()
{
    return city2;
}

//Accessor for price
double Edge::getPrice()
{
    return price;
}

void Edge::printEdge()
{
   cout << left;
   cout << setw(15) << city1->cityName
   << setw(8) << "<--->"
   << setw(15) << city2->cityName
   << setw(3) << " = "
   << setw(8) << right << fixed << setprecision(2) << getPrice()
   << endl;
}

Edge::Edge() {

}

