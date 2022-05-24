//********************************************************
// Your Name: Eduardo Teodosio Campuzano
// Description: This contains the struct Food and the class Heap and its function definitions, heap is a data structure containing food objects sorted in order of keys
// it is sorted as a max heap and the functions will keep that property
//********************************************************

#ifndef ASSIGNMENT3_HEAP_H
#define ASSIGNMENT3_HEAP_H


#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

//Food represents a food. Each food with a unique key
struct Food
{
    int key;
    string foodName;
    double price;
};

//class Heap represents a Max heap that contains Food objects. Underline data structure is
//a one dimensional array of Food objects.
class Heap
{
private:
    struct Food* foodArr;	//an array of Food
    int capacity , size ;

public:
    Heap(int capacity);
    ~Heap();
    Food* getFoodArr();
    int getSize();
    int getCapacity();
    int isFound(int foodKey);
    bool increaseKey(int index, Food oneFoodwithNewKey);
    bool insert(int key, string foodName, double foodPrice);
    void heapify(int index);
    Food getHeapMax();
    void extractHeapMax();
    int leftChild(int parentIndex);
    int rightChild(int parentIndex);
    int parent(int childIndex);
    void printHeap();
};

//Constructor to dynamically allocate memory for a heap with the specified capacity
Heap::Heap(int capacity)
{
    this->capacity = capacity;
    foodArr = new Food[this->capacity];
    this->size = 0;
}

//Destructor
//Before termination, the destructor is called to free the associated memory occupied by the heap.
//and prints the number of nodes deleted by it.
Heap::~Heap()
{
    int foodCount = 0;
    for (int i = 0;  i < size; i++) {
        foodCount++;
    }
    delete[] foodArr;

    cout << "\nThe number of deleted food items is: " << foodCount << endl;
}

// return the Food* array
Food* Heap::getFoodArr() {
    return foodArr;
}

// returns the size of the heap
int Heap::getSize() {
    return size;
}

// return the capacity of the heap
int Heap::getCapacity() {
    return capacity;
}

// searches the heap to see if the key is already there
int Heap::isFound(int foodKey) {
    for (int i = 0; i < capacity; i++) {
        if (foodArr[i].key == foodKey){
            return i;
        }
    }
    return -1;
}

// increases the key of a food item if it exists and it is greater than the old key
bool Heap::increaseKey(int index, Food oneFoodwithNewKey) {
    Food current;
    Food replacement;

    if (isFound(oneFoodwithNewKey.key) != -1){
        return false;
    }

    if (oneFoodwithNewKey.key < foodArr[index].key){
        return false;
    }

    if (index < capacity){
        foodArr[index].key = oneFoodwithNewKey.key;

        while (index >= 1 && foodArr[parent(index)].key < foodArr[index].key){
            current = foodArr[index];
            replacement = foodArr[parent(index)];
            foodArr[parent(index)] = current;
            foodArr[index] = replacement;
            index = parent(index);
        }
        return true;
    }
    else {
        return false;
    }
}

// inserts the food at the end with value of 0 and then
bool Heap::insert(int insertKey, string foodName, double foodPrice) {
    Food* temp;
    bool success = false;
    int newCap;

    if (size == capacity){
        newCap = 2*capacity;
        capacity = newCap;
        temp = new Food[capacity];
        for (int i = 0; i < size; i++) {
            temp[i] = foodArr[i];
        }
        delete [] foodArr;
        foodArr = temp;
        cout << "Reach the capacity limit. Double the capacity" << endl;
        cout << "\nThe new capacity now is " << newCap << endl << endl;
    }
    if (size < capacity){
        Food nodeInsert;
        nodeInsert.key = 0;
        nodeInsert.foodName = foodName;
        nodeInsert.price = foodPrice;

        Food nodeForIncreaseKey;
        nodeForIncreaseKey.key = insertKey;
        foodArr[size] = nodeInsert;
        increaseKey(size, nodeForIncreaseKey);
        size++;
        success = true;
    }
    return success;

}

// floats down a value in order to keep max heap properties
void Heap::heapify(int index) {
    int left = leftChild(index);
    int right = rightChild(index);
    int largestIndex;
    Food replacement;
    Food current;

    if (left <= size && foodArr[left].key > foodArr[index].key) {
        largestIndex = left;
    }
    else{
        largestIndex = index;
    }

    if (right <= size && foodArr[right].key > foodArr[largestIndex].key) {
        largestIndex = right;
    }

    if (largestIndex != index){
        current = foodArr[index];
        replacement = foodArr[largestIndex];
        foodArr[index] = replacement;
        foodArr[largestIndex] = current;
        heapify(largestIndex);
    }


}

// gets the root node
Food Heap::getHeapMax() {
    return foodArr[0];
}
//removes the root and then heapifies the new root
void Heap::extractHeapMax() {
    Food lastNode = foodArr[size-1];
    Food* temp = foodArr;

    if (size < 1){
        cout << "heap empty" << endl;
    }

    foodArr[0] = lastNode;
    size = size-1;
    for (int i = 1; i < size  ; i++) {
        foodArr[i] = temp[i];
    }
    heapify(0);
}

// returns the left child node for a parent
int Heap::leftChild(int parentIndex) {
    return (2*parentIndex) + 1;

}

// returns the right child node for a parent
int Heap::rightChild(int parentIndex) {
    return (2*parentIndex) + 2;
}

// returns the parent of the child
int Heap::parent(int childIndex) {
    return (childIndex-1)/2;
}

// prints the heap
void Heap::printHeap()
{
    if (size == 0){
        cout << "\nEmpty heap, no elements" << endl;
    }
    else{
        cout<< "\nHeap capacity = " << capacity << endl << endl;
        cout<< "Heap size = " << size;
        cout << endl;
        for (int i = 0; i < size; i++) {
            cout << left;
            cout << setw(5) << foodArr[i].key
                 << setw(8) << foodArr[i].foodName
                 << setw(8) << fixed << setprecision(2) << foodArr[i].price << endl;
        }
    }

}

#endif //ASSIGNMENT3_HEAP_H
