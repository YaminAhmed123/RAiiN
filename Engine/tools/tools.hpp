#ifndef TOOLS_H
#define TOOLS_H

/*
* This header defines a set of functions that can be used for easy development
* Copyright (c) 2025 CortexR7
*/

namespace tools{
    // Generics

    // P = preAllocation Size
    // S = size
    // T = type
    // K = increment size if currentCapacity is reached
    template<int K,int P,int S,typename T>
    class GenericArray
    {
        private:
        int size = 0;
        int currentCapacity;
        public:
        T* array;

        GenericArray() : currentCapacity(S+P)
        {
            size = S;
            array = new T[size+P];    // WARNING: allocations must be freed later
        }

        ~GenericArray()
        {
            delete[] array;         // memory getting freed
        }

        T* getPointer()
        {
            return array;
        }

    
        int getSize()
        {
            return size;
        }

        void addElement(T element)
        {
            if(size < currentCapacity){
                ++size;
                array[size-1] = element;
            }   else{
                T* newArray = new T[currentCapacity + K];
                for(int i = 0; i < size; ++i){
                    newArray[i] = array[i];
                }
                newArray[size] = element;
                ++size;
                currentCapacity += K;
                delete[] array;
                array = newArray;
            }
        }
    };
}

// Generics

// P = preAllocation Size
// S = size
// T = type
// K = increment size if currentCapacity is reached
template<int K,int P,int S,typename T>
class GenericArray
{
    private:
    int size = 0;
    int currentCapacity;
    public:
    T* array;

    GenericArray() : currentCapacity(S+P)
    {
        size = S;
        array = new T[size+P];    // WARNING: allocations must be freed later
    }

    ~GenericArray()
    {
        delete[] array;         // memory getting freed
    }

    T* getPointer()
    {
        return array;
    }

    
    int getSize()
    {
        return size;
    }

    void addElement(T element)
    {
        if(size < currentCapacity){
            ++size;
            array[size-1] = element;
        } else{
            T* newArray = new T[currentCapacity + K];
            for(int i = 0; i < size; ++i){
                newArray[i] = array[i];
            }
            newArray[size] = element;
            ++size;
            currentCapacity += K;
            delete[] array;
            array = newArray;
        }
    }
};

#endif