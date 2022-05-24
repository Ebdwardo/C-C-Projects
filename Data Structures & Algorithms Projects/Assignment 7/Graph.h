//********************************************************************
// Name of Author: Eduardo Teodosio Campuzano
// Description: This is the header file that defines a directed graph
//********************************************************************

#include "MinHeap.h"
#include <string>



using namespace std;

class Graph
{
   private:
   int numOfNode;        //number of nodes in the graph
   MinHeap* cityHeap;
   MinHeap* heapAfterDij; //a min-heap of departure City objects

   //feel free to add other necessary functions
   public:
   Graph(int numOfNode, MinHeap* cityHeap);
   void destructor();
   void printGraph();
   void initialize_single_source(string sourceCityName);
   void relax(City u, City v);
   int findOneCity(string aCityName);

   void dijkstra(string sourceCityName);
   void printDijkstraPath(string sourceCityName);
};

//*******************************************************************
//Constructor
Graph::Graph(int numOfNode, MinHeap* cityHeap)
{
   this->numOfNode = numOfNode;
   this->cityHeap = cityHeap;
}

//*******************************************************************
//Destructor Graph::~Graph()
void Graph::destructor()
{
   delete [] cityHeap;
   cityHeap = NULL;
   numOfNode = 0;
}

void Graph::printGraph() {
    cityHeap->printHeap();
}

// sets all parents to null and makes the source city d = 0
void Graph::initialize_single_source(string sourceCityName) {
    City* temp = cityHeap->getCityArr();
    int sourceIndex = findOneCity(sourceCityName);
    for (int i = 0; i < numOfNode; i++) {
        temp[i].parent = nullptr;
    }
    temp[sourceIndex].d = 0;
    cityHeap->decreaseKey(sourceIndex, temp[sourceIndex]);

}

//compares 2 cities and updates the shortest path and parents
void Graph::relax(City u, City v) {
    City* U = new City;
    U->cityName = u.cityName;
    U->arrCityList = u.arrCityList;
    U->d = u.d;
    U->parent = u.parent;
    if (v.d > u.d + u.arrCityList->findArrCity(v.cityName)->price){
        v.d = u.d + u.arrCityList->findArrCity(v.cityName)->price;
        v.parent = U;
    }
    cityHeap->swapCity(v);
}

// finds a city in the heap
int Graph::findOneCity(string aCityName) {
    return cityHeap->isFound(aCityName);
}

//*******************************************************************
//This function performs the dijkstra's shortest path algorithm
void Graph::dijkstra(string sourceCityName){
   initialize_single_source(sourceCityName);
   MinHeap* temp = cityHeap;
   heapAfterDij = new MinHeap(2*numOfNode);
   while (temp->getSize() != 0){
       City u = temp->extractHeapMin();
       heapAfterDij->insert(u);
       City v;
       if (u.arrCityList->getSize() != 0){
           ArrCity* citysArray = u.arrCityList->getHead();
           ArrCity* linkedList = u.arrCityList->getHead();
           while (linkedList != nullptr){
               if (heapAfterDij->isFound(linkedList->arrCityName) == -1){
                   v = temp->getCityObject(findOneCity(linkedList->arrCityName));
                   citysArray = linkedList;
                   break;
               }
               else {
                   linkedList = linkedList->next;
               }
           }
           while (citysArray != nullptr){
               if (v.cityName != "")
                   relax(u, v);
               if (citysArray->next != nullptr){
                   if (heapAfterDij->isFound(citysArray->next->arrCityName) != -1){
                       citysArray = citysArray->next;
                   }
                   else{
                       if (citysArray->next != nullptr){
                           v = temp->getCityObject(findOneCity(citysArray->next->arrCityName));
                       }
                   }
               }
               citysArray = citysArray->next;
           }
       }
   }

}

//*********************************************************************************
//This function prints the cheapest price and path after the Dijkstra's algorithm
void Graph::printDijkstraPath(string sourceCityName)
{
    cout << "\nSource City: " << sourceCityName << endl;
    cout << left;
    cout << setw(15) << "\nArrival City"
        << setw(15) << "Lowest Price"
        << setw(15) << "Shortest Path" << endl;

    for (int i = 0; i < numOfNode; i++) {
        string shortestPath[10];

        City* node = heapAfterDij->getCityObject(i).parent;
        City arrival = heapAfterDij->getCityObject(i);
        string path;


        cout << left;
        cout << setw(15) << heapAfterDij->getCityObject(i).cityName
             << setw(15) << heapAfterDij->getCityObject(i).d;

        for (int j = 0; j < numOfNode ; j++) {
            if (node != nullptr){
                shortestPath[j] = arrival.cityName;
            }
            else{
                if (arrival.cityName == sourceCityName){
                    shortestPath[j] = arrival.cityName;
                    break;
                }
            }
            if (node != nullptr){
                if (heapAfterDij->isFound(node->cityName) != -1){
                    arrival = heapAfterDij->getCityObject(heapAfterDij->isFound(node->cityName));
                }
                node = arrival.parent;
            }
        }
        for (int j = shortestPath->length()-2; j >= 1 ; j--) {
            if (shortestPath[j] != "")
                path +=  shortestPath[j] + "->" ;
        }
        cout << setw(15) << path + shortestPath[0];
        cout << endl;

    }


}
