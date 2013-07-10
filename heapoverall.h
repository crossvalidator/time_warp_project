
#include <iostream>
#include <vector>
#include <iterator>
using namespace std;

class Heap {


public:
    vector<float> heap;
	int left(int parent);
    int right(int parent);
    int parent(int child);
    void heapifyup(int index);
    void heapifydown(int index);


    Heap();
    ~Heap();
    void insert(float element);
    float deletemin();
    void print();
    int size(); 


};

