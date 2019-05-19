#include <algorithm>
#include <vector>

using namespace std;

template <typename T>
class SparseTable {
  private:
    vector<vector<T>> data;

    size_t log(int x) {
        size_t result = 0;
        while ((1 << (result + 1)) <= x)
            ++result;
        return result;
    }

  public:
    SparseTable(const vector<T>& array) : data{log(array.size()) + 1} {
        for (size_t i = 0; i < data.size(); ++i) {
            int len = 1 << i;
            data[i].resize(array.size() - len + 1);
            
            for (size_t j = 0; j + len - 1 < array.size(); ++j) {
                if (len == 1)
                    data[i][j] = array[j];
                else
                    data[i][j] = min(data[i - 1][j], data[i - 1][j + len / 2]);
            }
        }
    }

    T getMin(int left, int right) {
        if (left > right)
            swap(left, right);
        int logLen = log(right - left + 1);
        return min(data[logLen][left], data[logLen][right - (1 << logLen) + 1]);
    }
};