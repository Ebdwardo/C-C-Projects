//********************************************************************
// Name of Author: Eduardo Teodosio Campuzano
// Description: This is the header file that defines an undirected graph
//              with an array of vertices and edges
//********************************************************************

#include "Edge.h"

using namespace std;

class Graph
{
   private:
      int V, E;         //number of vertices and edges in the graph
      City* cityArr;    //an array of City objects
      Edge* edgeArr;    //an array of Edge objects
      Edge* A;

   public:
      Graph(int numOfCities, int numOfEdges, City* cityArray, Edge* edgeArray);
      void destructor();
      void make_set(City* aCity);
      City* find_set(City* aCity);
      void link(City* aCity, City* bCity);
      void Union(City* aCity, City* bCity);
      void printEdgeArray();
      void MergeSortEdges();
      void mergeSort(Edge* edgeArray, int start, int end);
      void merge(Edge* edgeArray, int start, int mid, int end);

      void MST_Kruskal();
};

//*******************************************************************
//Constructor
Graph::Graph(int numOfCities, int numOfEdges, City* cityArray, Edge* edgeArray)
{
	V = numOfCities;
	E = numOfEdges;
	cityArr = cityArray;
	edgeArr = edgeArray;
}

//*******************************************************************
//Destructor
void Graph::destructor()
{
    delete[] cityArr;
    delete[] edgeArr;
}

//*******************************************************************
//Given a City, this function creates a new set whose only member is
//the City.
void Graph::make_set(City* aCity)
{
	aCity->parent = aCity;
	aCity->rank = 0;
}

//*******************************************************************
//Given a City, this function returns a pointer to the representative
//of the (unique) set containing 'aCity'
City* Graph::find_set(City* aCity)
{
	if (aCity != aCity->parent){
	    aCity->parent = find_set(aCity->parent);
	}
    return aCity->parent;
}

//*******************************************************************
//Given two cities, this function checks the dynamic sets that contain
//'aCity' and 'bCity' and update their rank and parent info. accordingly
void Graph::link(City* aCity, City* bCity)
{
	if (aCity->rank > bCity->rank){
	    bCity->parent = aCity;
	}
	else{
	    aCity->parent = bCity;
	    if (aCity->rank == bCity->rank){
	        bCity->rank++;
	    }
	}
}

//*******************************************************************
//Given two cities, this function unites the dynamic sets that contain
//'aCity' and 'bCity' into a new set that is the union of the two sets.
void Graph::Union(City* aCity, City* bCity)
{
	link(find_set(aCity), find_set(bCity));
}

//*******************************************************************
//This function print each of the edges of edge array. It can be
//used as an auxillary function to check the MergeSort result
void Graph::printEdgeArray()
{
    for (int i = 0; i < E; i++) {
        edgeArr[i].printEdge();
    }
}

//*******************************************************************
//This function performs the Merge Sort on the graph edges according
//to the weight. Sort all edges in non-decreasing order
void Graph::MergeSortEdges()
{
	mergeSort(edgeArr,0, E-1);
}

//*******************************************************************
//This function performs the Merge Sort on a sub edgeArray.
void Graph::mergeSort(Edge* edgeArray, int start, int end)
{
    if(start>=end){
        return;//returns recursively
    }
    int m = (start+end-1)/2;
    mergeSort(edgeArray,start,m);
    mergeSort(edgeArray,m+1,end);
    merge(edgeArray,start,m,end);
}

//*******************************************************************
//This function merges the two sorted sub edgeArray.
void Graph::merge(Edge* edgeArray, int start, int mid, int end)
{
    int n1 = mid-start+1;  //get the length of the first half subarray
    int n2 = end-mid;      //get the length of the second half subarray

     //Dynamically create two new arrays each stored the sorted half
     Edge* left = (Edge*)malloc(sizeof(Edge) * n1);
     Edge* right = (Edge*)malloc(sizeof(Edge) * n2);

    for (int i = 0; i < n1; i++)
        left[i] = edgeArray[start + i];
    for (int j = 0; j < n2; j++)
        right[j] = edgeArray[mid + 1 + j];

    // Merge the temp arrays back into arr[l..r]

    // Initial index of first subarray
    int i = 0;

    // Initial index of second subarray
    int j = 0;

    // Initial index of merged subarray
    int k = start;

    while (i < n1 && j < n2) {
        if (left[i].getPrice() <= right[j].getPrice()) {
            edgeArray[k] = left[i];
            i++;
        }
        else {
            edgeArray[k] = right[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of
    // L[], if there are any
    while (i < n1) {
        edgeArray[k] = left[i];
        i++;
        k++;
    }

    // Copy the remaining elements of
    // R[], if there are any
    while (j < n2) {
        edgeArray[k] = right[j];
        j++;
        k++;
    }

	   //at the end, release the memory left and right occupied
//      delete left;
//      delete right;
}


//*******************************************************************
//This function performs the Kruskal algorithm on the graph.
void Graph::MST_Kruskal()
{
   cout << "MST Kruskal Algorithm Result\n" << endl;
   double totalWeight = 0.0;

    for (int i = 0; i < V; i++) {

        make_set(&cityArr[i]);
    }
    MergeSortEdges();
    for (int i = 0; i < E; ++i) {
        if (find_set(edgeArr[i].getCity1()) != find_set(edgeArr[i].getCity2())){
            Union(find_set(edgeArr[i].getCity1()), find_set(edgeArr[i].getCity2()));
            totalWeight += edgeArr[i].getPrice();
            edgeArr[i].printEdge();
        }
    }

   cout << "=================================================" << endl;
   cout << "Total Price: " << totalWeight << endl;
}
