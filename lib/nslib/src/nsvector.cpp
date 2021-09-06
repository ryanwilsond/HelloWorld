#include "nsvector"

template <class T>
T vector<T>::elem(int i) {
    return this->vec[i];
}

template <class T>
T vector<T>::operator[](int i) {
    return this->elem(i);
}

template <class T>
void vector<T>::append(T elem) {
    if (this->count >= this->vec_alloc) this->increaseAlloc(10);
    this->vec[this->count++] = elem;
}

template <class T>
int vector<T>::getAlloc() {
    return this->vec_alloc;
}

template <class T>
T* vector<T>::toArray() {
    T* q = (T*)malloc(this->vec_alloc*sizeof(T));

    for (int j=0; j<this->vec_alloc; j++) {
        q[j] = this->vec[j];
    }

    return q;
}
