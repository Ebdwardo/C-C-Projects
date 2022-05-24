//********************************************************************
// Name of Author: Eduardo Teodosio Campuzano
// Description: This main driver will ask the user for a number of cites and then based on user input
// it will calculate the shortest path between them all
//********************************************************************

#include "Graph.h"
#include <iostream>
#include <string>

using namespace std;

void getDepartureCityInfo(string& oneLine, string& depCityName);
void getArrCityInfo(string oneArrCityInfo, string& arrCityName, int& price, LinkedList* arrCityList);

int main()
{
    int count, price;       //a variable for number of nodes
    string oneLine, sourceCityName;
    cout << "Enter num of cities: ";
    cin >> count;
    cin.ignore(20, '\n');       //will be used in Linux testing

    //For each line, we will create a LinkedList for a specific departure city
    //it represents all its reachable arrival cities.
    //Here we use an array of City to store them
    City* cityArr = new City[count];

    //Initialize cityArr. set each node's d value to be very large 20000
    //initialize each arrival city list
    for(int i = 0; i< count; i++)
    {
        cityArr[i].d = 20000;
        cityArr[i].parent = nullptr;
        cityArr[i].arrCityList = new LinkedList();
    }

    //get input line by line
    for(int i = 0; i< count; i++)
    {
        cout << "\nEnter one City info.: " << endl;
        getline(cin, oneLine);
        getDepartureCityInfo(oneLine, sourceCityName);
        cityArr[i].cityName = sourceCityName;
        getArrCityInfo(oneLine, sourceCityName, price, cityArr[i].arrCityList);

    }

    cout << "Enter source city name: " << endl;
    getline(cin, sourceCityName);

    //create a MinHeap which capacity is double the size
    MinHeap* cityHeap = new MinHeap(count*2);

    //insert each City objects one by one inside cityHeap
    for (int i = 0; i < count; i++) {
        cityHeap->insert(cityArr[i]);
    }

    //create a Graph object by using its constructor
    Graph* graphObject = new Graph(count, cityHeap);

    //print the graph adjacency list before running Dijkstra algorithm
    cout << "\nPrint the graph before Dijkstra algorithm" << endl;
    graphObject->printGraph();

    //Do dijkstra search on the graph
    graphObject->dijkstra(sourceCityName);

    //print the Dijkstra shortest path result
    cout << "\nPrint the Dijkstra algorithm running result" << endl;
    graphObject->printDijkstraPath(sourceCityName);
}

//**************************************************************
//This function from one line, get all city info.
void getDepartureCityInfo(string& oneLine, string& depCityName){
    string delimiter = ",";
    int pos=oneLine.find(delimiter);
    string token = oneLine.substr(0, pos);
    depCityName = token;

    oneLine.erase(0,pos+1);
}

//****************************************************************************
//Get all the info for the arrival cities
void getArrCityInfo(string oneArrCityInfo, string& arrCityName, int& price, LinkedList* arrCityList)
{
    string delimiter = ",";
    string delimiter1 = "(", delimiter2 = ")";

    while (oneArrCityInfo.find(delimiter) != 0){
        if (oneArrCityInfo.empty()){
            break;
        }
        int pos=oneArrCityInfo.find(delimiter1);
        string token = oneArrCityInfo.substr(0,pos);
        arrCityName = token;

        oneArrCityInfo.erase(0, pos+delimiter1.length());

        pos = oneArrCityInfo.find(delimiter2);
        token = oneArrCityInfo.substr(0,pos);
        price = stoi(token);
        oneArrCityInfo.erase(0, pos+delimiter2.length()+1);

        arrCityList->addArrCity(arrCityName, price);
    }

}