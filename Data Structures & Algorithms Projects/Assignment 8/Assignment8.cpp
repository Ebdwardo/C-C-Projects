//************************************************************************
// Name: Eduardo Teodosio Campuzano
// Description: this is the main program that reads input from keyboard,
// it then uses disjoint set data structure to perform Kruskal MST algorithm
// on the graph.
//**************************************************************************

#include "Graph.h"

using namespace std;

void getArrCityInfo(string& oneArrCityInfo, string& arrCityName, double& price);
int searchCity(City* oneCityArray,int size, string oneCityName);
void getDepartureCityInfo(string& oneLine, string& depCityName);
int main()
{
    int V, E;        //number of vertices and edges

    cout << "Enter number of vertices and edges: " << endl;
    cin >> V >> E;
    cin.ignore(20, '\n');

    //a City array used to store all vertices (Cities) of the graph
    City* cityArray = new City[V];

    //an array used to store all edges of the graph
    Edge* edgeArray = new Edge[E];

    int i =0, j=0; //index for cityArray and edgeArray

    //local variables
    City* city1;
    City* city2;
    Edge* aNewEdge;
    string depCityName;
    string arrCityName;
    double price;

    string oneLine;

    //cout << "Enter one departure and its arrival city info." << endl;
    getline(cin, oneLine);

    while(oneLine.compare("End") != 0)
    {
        //get one line of the input, extract the first token
        //create a City if it doesn't exist in cityArray,
        //insert it inside the cityArray. This will be first point
        //for aNewEdge
        getDepartureCityInfo(oneLine, depCityName);

        if (searchCity(cityArray, V, depCityName) == -1){
            city1 = new City(depCityName);
            cityArray[i] = *city1;
            i++;
        }
        else{
            city1->cityName = depCityName;
            city1->parent = nullptr;
            city1->rank = 0;
        }

        //extract the arrival city info. check whether it exists in
        //cityArray or not, if not, create a new City, add it inside.
        //This city will be the second point for aNewEdge
        while (oneLine.empty() != true && (oneLine != ",")) {
            getArrCityInfo(oneLine, arrCityName, price);
            if (searchCity(cityArray, V, arrCityName) == -1) {
                city2 = new City(arrCityName);
                cityArray[i] = *city2;
                i++;
            }else{
                city2->cityName = arrCityName;
                city2->parent = nullptr;
                city2->rank = 0;
            }
            //by using the two cities we got above, create a new edge, add
            //it inside edgeArray
            aNewEdge = new Edge(city1, city2, price);
            edgeArray[j] = *aNewEdge;
            j++;
        }

        //get next line
        //cout << "Enter one departure and its arrival city info." << endl;
        getline(cin, oneLine);
    } //repeat until the 'End'

    //Create a Graph object by using cityArray and edgeArray
    //----
    Graph* graph = new Graph(V,E,cityArray,edgeArray);

    //Run Kruskal MST algorithm on above graph
    //----
    graph->MST_Kruskal();
}

//****************************************************************
//By giving a string, for example 'Dallas(456.5)', this function
//extract the arrival city name 'Dallas' and air ticket price '456.5'
//Note: the delimeter is left or right parenthesis
//****************************************************************
void getArrCityInfo(string& oneArrCityInfo, string& arrCityName, double& price)
{
    string delimiter1 = "(", delimiter2 = ")";
    int pos=oneArrCityInfo.find(delimiter1);
    string token = oneArrCityInfo.substr(0,pos);
    arrCityName = token;

    oneArrCityInfo.erase(0, pos+delimiter1.length());

    pos = oneArrCityInfo.find(delimiter2);
    token = oneArrCityInfo.substr(0,pos);
    price = stod(token);
    oneArrCityInfo.erase(0, pos+delimiter2.length()+1);
}

//*********************************************************************
//Given a city name, this function searches cityArray and it return the
//index of the City if it already exists, otherwise it returns -1
//****************************************************************
int searchCity(City* oneCityArray, int arraySize, string oneCityName)
{
    for (int i = 0; i < arraySize; i++) {
        if (oneCityArray[i].cityName == oneCityName){
            return i;
        }
    }
    return -1;
}

// Get the first token from the line which is the departure city
void getDepartureCityInfo(string& oneLine, string& depCityName){
    string delimiter = ",";
    int pos=oneLine.find(delimiter);
    string token = oneLine.substr(0, pos);
    depCityName = token;

    oneLine.erase(0,pos+1);
}
