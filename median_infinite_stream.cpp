/*
Given that integers are being read from a data stream.
 Find the median of all the elements read so far starting from the first integer till the last integer.
 This is also called the Median of Running Integers.
 The data stream can be any source of data, for example, a file, an array of integers, input stream etc.


 Approach: The idea is to use max heap and min heap to store the elements of higher half and lower half.
 Max heap and min heap can be implemented using priority_queue in C++ STL. Below is the step by step algorithm to solve this problem.
Algorithm:


Create two heaps. One max heap to maintain elements of lower half and one min heap to maintain elements of higher half at any point of time..
Take initial value of median as 0.
For every newly read element, insert it into either max heap or min-heap and calculate the median based on the following conditions:
If the size of max heap is greater than the size of min-heap and the element is less than
the previous median then pop the top element from max heap and insert into min-heap and
 insert the new element to max heap else insert the new element to min-heap.
 Calculate the new median as the average of top of elements of both max and min heap.
If the size of max heap is less than the size of min-heap and the element is greater than
 the previous median then pop the top element from min-heap and
 insert into the max heap and insert the new element to min heap
 else insert the new element to the max heap.
 Calculate the new median as the average of top of elements of both max and min heap.
If the size of both heaps is the same.
Then check if the current is less than the previous median or not.
 the current element is less than the previous median then insert it to the max heap and
  a new median will be equal to the top element of max heap.
  If the current element is greater than the previous median then insert it to min-heap and
  new median will be equal to the top element of min heap.
Below is the implementation of above approach.

*/
// C++ program to find med in
// stream of running integers
#include <bits/stdc++.h>
using namespace std;

// function to calculate med of stream
void printMedians(double arr[], int n)
{
    // max heap to store the smaller half elements
    priority_queue<double> s;

    // min heap to store the greater half elements
    priority_queue<double, vector<double>, greater<double>> g;

    double med = arr[0];
    s.push(arr[0]);

    cout << med << endl;

    // reading elements of stream one by one
    /* At any time we try to make heaps balanced and
        their sizes differ by at-most 1. If heaps are
        balanced,then we declare median as average of
        min_heap_right.top() and max_heap_left.top()
        If heaps are unbalanced,then median is defined
        as the top element of heap of larger size */
    for (int i = 1; i < n; i++)
    {
        double x = arr[i];

        // case1(left side heap has more elements)
        if (s.size() > g.size())
        {
            if (x < med)
            {
                g.push(s.top());
                s.pop();
                s.push(x);
            }
            else
                g.push(x);

            med = (s.top() + g.top()) / 2.0;
        }

        // case2(both heaps are balanced)
        else if (s.size() == g.size())
        {
            if (x < med)
            {
                s.push(x);
                med = (double)s.top();
            }
            else
            {
                g.push(x);
                med = (double)g.top();
            }
        }

        // case3(right side heap has more elements)
        else
        {
            if (x > med)
            {
                s.push(g.top());
                g.pop();
                g.push(x);
            }
            else
                s.push(x);

            med = (s.top() + g.top()) / 2.0;
        }

        cout << med << endl;
    }
}

// Driver program to test above functions
int main()
{
    // stream of integers
    double arr[] = {5, 15, 10, 20, 3};
    int n = sizeof(arr) / sizeof(arr[0]);
    printMedians(arr, n);
    return 0;
}
/*
Time Complexity: O(n Log n). 
Time Complexity to insert element in min heap is log n. So to insert n element is O( n log n).
Auxiliary Space : O(n). 
The Space required to store the elements in Heap is O(n).
*/