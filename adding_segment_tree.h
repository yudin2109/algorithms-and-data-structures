#include <vector>

using namespace std;

class AddingSegmentTree {
  private:
    struct Node {
        long long value;
        int leftBorder, rightBorder;

        Node(long long _value = 0, int _left = -1, int _right= -1) {
            value = _value;
            leftBorder = _left;
            rightBorder = _right;
        }
    };

    vector<Node> data;

    void build(const vector<long long>& arr, int v, int left, int right) {
        if (left == right)
            data[v] = Node{arr[left], left, left};
        else {
            int middle = (right + left) / 2;
            build(arr, 2 * v + 1, left, middle);
            build(arr, 2 * v + 2, middle + 1, right);
            data[v] = Node{0, data[2 * v + 1].leftBorder, data[2 * v + 2].rightBorder};
        }
    }

  public:
    AddingSegmentTree(const vector<long long>& arr) : data(4 * arr.size()) {
        build(arr, 0, 0, arr.size() - 1);
    }

    void RangeAdd(int left, int right, long long add, int v = 0) {
        if (right < data[v].leftBorder || left > data[v].rightBorder || right < left)
            return;
        if (left == data[v].leftBorder && right == data[v].rightBorder)
            data[v].value += add;
        else {
            RangeAdd(left, min(data[2 * v + 1].rightBorder, right), add, 2 * v + 1);
            RangeAdd(max(left, data[2 * v + 2].leftBorder), right, add, 2 * v + 2);
        }
    }

    long long getValue(int position, long long add = 0, int v = 0) {
        if (position == data[v].leftBorder && position == data[v].rightBorder)
            return data[v].value + add;
        if (position <= data[2 * v + 1].rightBorder)
            return getValue(position, add + data[v].value, 2 * v + 1);
        else
            return getValue(position, add + data[v].value, 2 * v + 2);
    }
};