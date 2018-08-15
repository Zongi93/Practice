#include <iostream>

// ------------------ Start of myVector.h ------------------

#include <stdexcept>

#define MYVECTOR_MAX_SIZE 64

template <class T>
class myVector
{
protected:
    T data[MYVECTOR_MAX_SIZE];
    int size;

    void shift_left(int from);
    void shift_right(int from);
public:
    myVector();
    void push_back(const T& newData);
    void insert(const T& newData, int atIndex);
    const T pop_back();
    const T erase(int atIndex);
    T operator [](int atIndex) const;
    T & operator [](int atIndex);

    const int getSize();

    void sort();
};

// ------------------ End of myVector.h ------------------
// ------------------ Start of myVector.cpp ------------------

template <class T>
void myVector<T>::shift_left(int from){
    if(from > 0){
        for(int i=from; i<=size; ++i){
            data[i-1] = data[i];
        }
        size--;
    }
}

template <class T>
void myVector<T>::shift_right(int from){
    T temp = data[size-1];
    if(from < size){
        for(int i=size-1; i>from; --i){
            data[i] = data[i-1];
        }
    }
    push_back(temp);
}

template <class T>
myVector<T>::myVector()
{
    size = 0;
}

template <class T>
void myVector<T>::push_back(const T &newData){
    if(size < MYVECTOR_MAX_SIZE){
        data[size++] = newData;
    }
    else throw std::length_error("myVector max size reached!");
}

template <class T>
void myVector<T>::insert(const T &newData, int atIndex){
    if(atIndex <= size && size < MYVECTOR_MAX_SIZE){
        shift_right(atIndex);
        data[atIndex] = newData;
    }
    else throw std::out_of_range("unable to insert, myVector size is less then target index");
}

template <class T>
const T myVector<T>::pop_back(){
    if(size > 0){
        T removed = data[--size];
        return removed;
    }
    else throw std::out_of_range("unable to pop, myVector size is 0");
}

template <class T>
const T myVector<T>::erase(int atIndex){
    if(size >= atIndex && atIndex >= 0){
        T removed = data[atIndex];
        shift_left(atIndex + 1);
        return removed;
    }
    else throw std::out_of_range("unable to erase, myVector size is 0");
}

template <class T>
T myVector<T>::operator [](int atIndex) const{
    if(atIndex < size){
        return data[atIndex];
    }
    else throw std::out_of_range("myVector size is less then target index");
}

template <class T>
T & myVector<T>::operator [](int atIndex){
    if(atIndex < size){
        return data[atIndex];
    }
    else throw std::out_of_range("myVector size is less then target index");
}

template <class T>
const int myVector<T>::getSize(){
    return size;
}

template <class T>
void myVector<T>::sort(){

    // Shell sort algorithm via https://en.wikipedia.org/wiki/Shellsort

    int gaps[] = {701, 301, 132, 57, 23, 10, 4, 1};

    for(int i = 0; i<8; ++i){
        int gap = gaps[i];

        for(int j = gap; j < size; ++j){

            T temp = data[j];
            int k;
            for(k = j; k >= gap && data[k - gap] > temp; k-=gap){
                data[k] = data[k - gap];
            }

            data[k] = temp;

        }

    }

}

// ------------------ End of myVector.cpp ------------------

void Log(myVector<int> &v){
    for(int i = 0; i < v.getSize();++i)std::cout<<v[i]<<" ";
    std::cout<<std::endl<<std::endl;
}



// Fibonacci without recursion

int f(int n){
    int current = 1;
    int prev = 1;

    while(n-- > 1){
        current = current + prev;
        prev = current - prev;
    }

    return current;
}


int main()
{
    const int data[] = { 5, 20, 19, 1, 5, 13, 68, 14, 3};

    myVector<int> a;

    for(auto val : data){
        a.push_back(val);
    }
    std::cout<<"After initialization:"<<std::endl;
    Log(a);

    a.sort();

    std::cout<<"Sorted:"<<std::endl;
    Log(a);

    a[2] = 2;

    std::cout<<"Second element changed to \"2\" and popped: "<<a.pop_back()<<std::endl;

    Log(a);

    a.insert(1993,1);

    a.erase(0);

    std::cout<<"Inserted 1993 to 1st place, and erased the 0th element:"<<std::endl;
    Log(a);

    a.sort();

    std::cout<<"Sorted:"<<std::endl;
    Log(a);

    std::cout<<std::endl<<"Fibonacci sequence:"<<std::endl;
    for(int i = 0; i < 10; ++i)std::cout<<f(i)<<", ";

    std::cout<<std::endl;
    return 0;
}
