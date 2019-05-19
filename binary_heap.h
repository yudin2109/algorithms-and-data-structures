#include <vector>

using namespace std;

template <typename T>
class BinaryHeap {
  private:
    vector<T> data;

    size_t getParent(size_t x) {
        if (x == 0)
            return 0;
        else
            return (x - 1) / 2;
    }

    size_t getLeftChild(size_t x) {
        return 2 * x + 1;
    }

    size_t getRightChild(size_t x) {
        return 2 * x + 2;
    }

    void HeapUp(size_t i) {
        size_t parent = getParent(i);
        while (i != parent && data[i] < data[parent]) {
            swap(data[i], data[parent]);
            i = parent;
            parent = getParent(parent);
        }
    }

    void HeapDown(size_t i) {
        size_t leftChild = getLeftChild(i);
        size_t rightChild = getRightChild(i);

        size_t minChild = i;
        if (leftChild < data.size() && data[leftChild] < data[i])
            minChild = leftChild;
        if (rightChild < data.size() && data[rightChild] < data[minChild])
            minChild = rightChild;
        if (minChild != i) {
            swap(data[i], data[minChild]);
            HeapDown(minChild);
        }
    }

  public:
    BinaryHeap(size_t capacity = 0) {
        data.reserve(capacity);
    }

    BinaryHeap(const vector<pair<int, int>>& _data) : data{_data} {
        for (size_t i = 0; i < data.size(); ++i) {
            HeapDown(data.size() - i - 1);
        }
    }

    bool isEmpty() {
        return data.empty();
    }

    void insert(const T& el) {
        data.push_back(el);
        HeapUp(data.size() - 1);
    }

    T getMin() {
        return data[0];
    }

    T extractMin() {
        T minValue = getMin();
        swap(data[0], data[data.size() - 1]);
        data.pop_back();
        HeapDown(0);

        return minValue;
    }  
};
