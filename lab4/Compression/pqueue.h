/*
 *  The Priority Queue class.
 *
 *
 *
 *
 */

#ifndef PQUEUE_H
#define PQUEUE_H
#include <iostream>
#include <vector>
using namespace std;

template<typename ValueType>
class PriorityQueue
{
    public:
        PriorityQueue()
        {
            heapSize = 0;
        }
        ~PriorityQueue()
        {
            heapSize = 0;
            heap.clear();
        }

        void clear()
        {
            heap.clear();
        }

        void push(const ValueType & value, int priority)
        {
            if (heapSize == heap.size())
                heap.push_back(heapEntry());
            int index = heapSize++;
            heap[index].value = value;
            heap[index].priority = priority;
            
            while (index > 0)
            {
                int parent = (index-1)/2;
                if (prior(parent, index))
                    break;
                swapEntries(parent, index);
                index = parent;
            }
        }

        ValueType pop()
        {
            if (heapSize == 0)
                throw;
            --heapSize;
            ValueType value = heap[0].value;

            swapEntries(0, heapSize);
            int index = 0;
            while (true)
            {
                int left = 2*index+1;
                int right = 2*index+2;
                if (left >= heapSize)
                    break;
                int child = left;
                if (right < heapSize && prior(right, left))
                    child = right;
                if (prior(index, child))
                    break;
                swapEntries(index, child);

                index = child;
            }

            return value;
        }



    private:
        struct heapEntry
        {
            ValueType value;
            int       priority;
        };
        vector<heapEntry> heap;
        int               heapSize;

        bool prior(int lhs, int rhs)
        {
            return heap[lhs].priority < heap[rhs].priority;
        }
        
        void swapEntries(int lhs, int rhs)
        {
            heapEntry tmp = heap[lhs];
            heap[lhs] = heap[rhs];
            heap[rhs] = tmp;
        }
};



#endif
