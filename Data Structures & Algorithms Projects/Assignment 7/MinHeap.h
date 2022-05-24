//********************************************************
// Name of Author: Eduardo Teodosio Campuzano
// Description: represents a minheap data structure
//********************************************************

#ifndef CSE310ASSIGNMENT07_MINHEAP_H
#define CSE310ASSIGNMENT07_MINHEAP_H

#endif //CSE310ASSIGNMENT07_MINHEAP_H

#include "LinkedList.h"

using namespace std;

//represent each node of the graph which is a departure City
struct City
{
    string cityName;
    int d;
    struct City* parent;
    LinkedList* arrCityList;
};

//class Heap represents a Min-heap that contains City objects. Underline data structure is
//a one dimensional array of City objects.
class MinHeap
{
private:
    struct City* cityArr;	//an array of departure cities City
    int capacity, size;

public:
    MinHeap(int capacity);
    ~MinHeap();

    City* getCityArr();
    City getCityObject(int index);
    int getSize();
    int getCapacity();
    int isFound(string cityName);
    bool decreaseKey(int index, City oneCitywithNewD);
    bool insert(City oneCity);
    void heapify(int index);
    City getHeapMin();
    City extractHeapMin();
    int leftChild(int parentIndex);
    int rightChild(int parentIndex);
    int parent(int childIndex);
    void printHeap();
    void swapCity(City c);

    void build_min_heap();      //***newly added function
};

//Constructor to dynamically allocate memory for a heap with the specified capacity
MinHeap::MinHeap(int capacity)
{
    cityArr = new City[capacity];
    this->capacity = capacity;
    size = 0;
}

City MinHeap::getCityObject(int index) {
    return cityArr[index];
}

MinHeap::~MinHeap() {
    delete[] cityArr;
}

City* MinHeap::getCityArr() { return cityArr; }

int MinHeap::getSize() { return size; }

int MinHeap::getCapacity() { return capacity; }

//search for a city in the minheap
int MinHeap::isFound(string cityName) {
    for (int i = 0; i < size; i++) {
        if (cityArr[i].cityName == cityName){
            return i;
        }
    }
    return -1;
}

// takes the node and swaps it with its smallest child
bool MinHeap::decreaseKey(int index, City oneCitywithNewD) {
    City current;
    City replacement;

    if (isFound(oneCitywithNewD.cityName) == -1){
        return false;
    }

    if (oneCitywithNewD.d > cityArr[index].d){
        return false;
    }

    if (index < capacity){
        cityArr[index].d = oneCitywithNewD.d;

        while (index >= 1 && cityArr[parent(index)].d > cityArr[index].d){
            current = cityArr[index];
            replacement = cityArr[parent(index)];
            cityArr[parent(index)] = current;
            cityArr[index] = replacement;
            index = parent(index);
        }
        return true;
    }
    else {
        return false;
    }
}

//Inserts a city into the minheap and then we make sure it is in the right place
bool MinHeap::insert(City oneCity) {
    City* temp;
    bool success = false;
    int newCap;

    if (size == capacity){
        newCap = 2*capacity;
        capacity = newCap;
        temp = new City[capacity];
        for (int i = 0; i < size; i++) {
            temp[i] = cityArr[i];
        }
        delete [] cityArr;
        cityArr = temp;
        cout << "Reach the capacity limit. Double the capacity" << endl;
        cout << "\nThe new capacity now is " << newCap << endl << endl;
    }
    if (size < capacity){
        cityArr[size] = oneCity;
        decreaseKey(size, oneCity);
        size++;
        success = true;
    }
    return success;

}

// float a node up or down the list
void MinHeap::heapify(int index) {
    int left = leftChild(index);
    int right = rightChild(index);
    int smallestIndex;
    City replacement;
    City current;

    if (left <= size && cityArr[left].d < cityArr[index].d) {
        smallestIndex = left;
    }
    else{
        smallestIndex = index;
    }

    if (right <= size && cityArr[right].d < cityArr[smallestIndex].d) {
        smallestIndex = right;
    }

    if (smallestIndex != index){
        current = cityArr[index];
        replacement = cityArr[smallestIndex];
        cityArr[index] = replacement;
        cityArr[smallestIndex] = current;
        heapify(smallestIndex);
    }
}

City MinHeap::getHeapMin() {
    return cityArr[0];
}

//****************************************************************
//**Changed a little bit. Once extractedHeapMin, the procedure will
//put the last element at index 0 and re-heapify the array. We will
//keep the extracted City object
City MinHeap::extractHeapMin()
{
    City lastNode = cityArr[size-1];
    City* temp = cityArr;
    City returnCity;
    if (getSize() < 1)
    {
        cout << "\nError: empty heap, cannot extract min" << endl;
    }
    else{
        returnCity = getHeapMin();
        cityArr[0] = lastNode;
        size = size-1;
        for (int i = 1; i < size  ; i++) {
            cityArr[i] = temp[i];
        }

    }
    heapify(0);
    return returnCity;
}

// These return the parent and children
int MinHeap::leftChild(int parentIndex) { return (2*parentIndex) + 1; }

int MinHeap::rightChild(int parentIndex) { return (2*parentIndex) + 2; }

int MinHeap::parent(int childIndex) { return (childIndex-1)/2; }

//*********************************************************
void MinHeap::printHeap()
{
    if (cityArr == NULL || size == 0)
        cout << "\nEmpty heap, no elements" << endl;
    else
    {
        cout << "\nHeap size = " << getSize() << "\n" << endl;

        cout << left;
        cout << setw(15) << "City Name"
             << setw(12) << "d Value"
             << setw(15) << "PI"
             << "Arrival City List" << endl;

        for (int i = 0; i < getSize(); i++)
        {
            cout << left;
            cout << setw(15) << cityArr[i].cityName
                 << setw(12) << cityArr[i].d;
            if(cityArr[i].parent != NULL)
                cout << setw(15) << cityArr[i].parent->cityName;
            else
                cout << setw(15) << "No Parent";
            cityArr[i].arrCityList->printArrCityList();
        }
    }
}

void MinHeap::build_min_heap() {
    for (int i = size/2; i>=1  ; i--) {
        heapify(i);
    }
}

//swaps a city object with one in the minheap
void MinHeap::swapCity(City c) {
    this->cityArr[isFound(c.cityName)] = c;
    decreaseKey(isFound(c.cityName),cityArr[isFound(c.cityName)]);
}
