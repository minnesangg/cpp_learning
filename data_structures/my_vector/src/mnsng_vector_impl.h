#ifndef MINNESANG_VECTOR_IMPL_H
#define MINNESANG_VECTOR_IMPL_H

namespace minnesang {

    template <typename T>
    Vector<T>::Vector() : size(0), capacity(10) {
        arr = new T[capacity];
    }

    template <typename T>
    Vector<T>::~Vector() {
        delete[] arr;
    }


    template <typename T>
    void Vector<T>::resize(size_t new_capacity) {
        T* new_arr = new T[new_capacity];

        for (size_t i = 0; i < size; i++) {
            new_arr[i] = arr[i];
        }

        delete[] arr;
        arr = new_arr;
        capacity = new_capacity;
    }


    template <typename T>
    void Vector<T>::push_back(const T& value) {
        if (size == capacity) {
            resize(2 * capacity);
        }
        arr[size++] = value;
    }

    template <typename T>
    void Vector<T>::pop_back() {
        if (size == 0) {
            throw std::runtime_error("Cannot pop from an empty vector");
        }
        size--;
    }

    template <typename T>
    T& Vector<T>::operator[](size_t index) {
        if (index >= size) {
            throw std::runtime_error("Index out of bounds");
        }
        return arr[index];
    }

    template <typename T>
    const T& Vector<T>::operator[](size_t index) const {
        if (index >= size) {
            throw std::runtime_error("Index out of bounds");
        }
        return arr[index];
    }

    template <typename T>
    size_t Vector<T>::get_size() const {
        return size;
    }

    template <typename T>
    size_t Vector<T>::get_capacity() const {
        return capacity;
    }

    template <typename T>
    size_t Vector<T>::index_of(const T& value) const {
        if(contains(value)){
            for(size_t i = 0; i < size; i++){
                if(arr[i] == value){
                    return i;
                }
            }
        } else {
            return -1;
        }
        return -1;
    }

    template <typename T>
    void Vector<T>::clear() {
        size = 0;
    }


    template <typename T>
    void Vector<T>::shrink_to_fit() {
        if (capacity > size) {
            resize(size);
        }
    }


    template <typename T>
    void Vector<T>::insert(size_t index, const T& value) {
        if (index > size) {
            throw std::runtime_error("Index out of bounds");
        }
        if (size == capacity) {
            resize(2 * capacity);
        }

        for (size_t i = size; i > index; i--) {
            arr[i] = arr[i - 1];
        }
        arr[index] = value;
        size++;
    }

    template <typename T>
    void Vector<T>::erase(size_t index) {
        if (index >= size) {
            throw std::runtime_error("Index out of bounds");
        }

        for (size_t i = index; i < size - 1; i++) {
            arr[i] = arr[i + 1];
        }
        size--;
    }


    template <typename T>
    const T& Vector<T>::front() {
        if(size == 0){
            throw std::runtime_error("Vector is empty");
        } else{
            return arr[0];
        }
    }

    template <typename T>
    const T& Vector<T>::back() {
        if(size == 0){
            throw std::runtime_error("Vector is empty");
        } else {
            return arr[size-1];
        }
    }


    template <typename T>
    bool Vector<T>::is_empty() const {
        return size == 0;
    }

    template <typename T>
    bool Vector<T>::is_sorted() const {
        return is_sorted_increasly() || is_sorted_decreasly();
    }    

    template <typename T>
    bool Vector<T>::is_sorted_increasly() const {
        for (size_t i = 1; i < size; ++i) {
            if (arr[i - 1] > arr[i]) {
                return false; 
            }
        }
        return true;
    }
    
    template <typename T>
    bool Vector<T>::is_sorted_decreasly() const {
        for (size_t i = 1; i < size; ++i) {
            if (arr[i - 1] < arr[i]) {
                return false; 
            }
        }
        return true;
    }    

    template <typename T>
    bool Vector<T>::contains(const T& value) const {
        for (size_t i = 0; i < size; i++) {
            if (arr[i] == value) {
                return true;
            }
        }
        return false;  
    }
    

    template <typename T>
    int Vector<T>::binary_search(const T& value) {
        if (!is_sorted_increasly() && !is_sorted_decreasly()) {
            throw std::runtime_error("Vector is not sorted");
            }

        size_t left = 0;
        size_t right = size - 1;
        size_t mid;

        bool is_increasing = is_sorted_increasly();

        while (left <= right) {
            mid = left + (right - left) / 2;

            if (arr[mid] == value) {
                return mid;
            }

            if (is_increasing) {
                if (arr[mid] < value) {
                left = mid + 1;
                } else {
                    right = mid - 1;
                }
            } else {
                if (arr[mid] > value) {
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            }
        }

        return -1;  
    }

    template <typename T>
    void Vector<T>::quickSort(size_t left, size_t right) {
        if (left >= right) {
            return;  
        }

        int pivotIndex = left + (right - left) / 2;  
        T pivot = arr[pivotIndex];

        size_t i = left;
        size_t j = right;

        while (i <= j) {
            while (arr[i] < pivot) {
                i++;
            }
            while (arr[j] > pivot) {
                j--;
            }

            if (i <= j) {
                std::swap(arr[i], arr[j]);  
                i++;
                j--;
            }
        }

        if (left < j) {
            quickSort(left, j);
        }
        if (i < right) {
            quickSort(i, right);
        }
    }
    
} 

#endif
