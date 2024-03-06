#include <iostream>


template<typename T, typename Compare = std::less<T>>
class heap {
public:
    size_t max_size = INT_MAX;
    size_t size;
    T *arr;
    Compare compare;
public:
    heap() : size(0), compare() { arr = new T[max_size]; };

    heap(std::initializer_list<T> list) : size(list.size()), compare() {
        arr = new T[max_size];

        size_t i = 0;
        for(T elem : list) arr[i++] = elem;


        for (int j = (size >> 1) - 1; j >= 0; j--) heapify_down(j);
    };

    size_t left_child(size_t parent) { return (parent << 1) + 1; }

    size_t right_child(size_t parent) { return (parent << 1) + 2; }

    void heapify_down(size_t idx) {
        size_t l = left_child(idx);
        size_t r = right_child(idx);
        size_t lowest;

        if(l < size && (compare(arr[l], arr[r]) || r >= size)) lowest = l;
        else lowest = idx;

        if(r < size && (compare(arr[r], arr[lowest]) || l >= size)) lowest = r;

        if(lowest != idx) {
            std::swap(arr[idx], arr[lowest]);
            heapify_down(lowest);
        }
    }

    T delete_min() {
        if (size > 0) {
            T result = arr[0];
            arr[0] = arr[size - 1];
            size--;

            heapify_down(0);

            return result;
        } else {
            throw std::logic_error("empty heap!");
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const heap<T, Compare>& heap) {
        for(int i = 0; i < heap.size; i++) os << heap.arr[i] << " ";
        return os;
    }
};


int main() {
    heap<int, std::greater<>> heapmax = {4, 3, 2, 1, 8, 14, -1};

    std::cout << heapmax << std::endl;

    heapmax.delete_min();

    std::cout << heapmax;


    return 0;
}