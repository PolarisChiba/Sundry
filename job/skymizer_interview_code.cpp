#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
template<int N>
class Vector {
    public:
        Vector():capacity_(N), size_(0), data_(NULL) {
            // data_ = new int[capacity_];
        }

        inline void push_back(const int& value) {
            if (capacity_ == N && size_ != N) {
                data2_[size_ ++] = value;
            } else if (size_ == N && capacity_ == N) {
                data_ = new int[2 * N];
                for (int i = 0; i < N; ++ i)
                    data_[i] = data2_[i];
                capacity_ = 2 * N;
                data_[size_ ++] = value;
            } else if (size_ == capacity_) {
                int *tempData = new int[capacity_ * 2];
                for (int i = 0; i < size_; ++ i) {
                    tempData[i] = data_[i];
                }
                delete [] data_;
                data_ = tempData;
                capacity_ *= 2;
            } else {
                data_[size_ ++] = value;
            }
        }

        void pop_back() {
            size_ -= 1;
        }

        int operator[](int i) const {
            return data_[i];
        }

        int getSize() const {
            return size_;
        }
    private:
        int capacity_;
        int size_;
        int* data_;
        int data2_[N];
};



/*
void f(const Vector &x){
    std::cout << x.getSize() << "\n";
    for (int i = 0; i < x.getSize(); ++ i) {
        std::cout << x[i] << " ";
    }
    std::cout << "\n";
}
*/

int main() {
    int n = 10000000;
    for (int i = 0; i < n; ++i) {
        Vector<32> x;
        int random_size = 1 + (std::rand() % 32);
        for (int j = 0; j < random_size; ++j) {
            x.push_back(std::rand());
        }
        // std::cout << random_size << "\n";
        // f(x);
    }
    n = 1000000;
    Vector<1152> *x = new Vector<1152>[n];
    for (int i = 0; i < n; ++i) {
        int random_max = 128 + (std::rand() % 1024);
        int random_size = 1 + (std::rand() % random_max);
        for (int j = 0; j < random_size; ++j) {
            x[i].push_back(std::rand());
        }
        // f(x);
    }
}