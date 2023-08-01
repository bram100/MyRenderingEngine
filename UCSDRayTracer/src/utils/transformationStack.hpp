//
//  transformationStack.hpp
//  UCSDRayTracer
//
//  Created by Brendan Mulcahey on 3/27/23.
//

#ifndef transformationStack_hpp
#define transformationStack_hpp

#include <stdio.h>
#include <iostream>
//#include "vector.hpp"
//#include "matrix.hpp"
//#include "transform.hpp"

//using namespace std;
/*
#define MAX 10

class stack {
    int top;

public:
    transformation a[MAX]; // Maximum size of Stack

    stack() { top = -1; }
    bool push(transformation x);
    transformation pop();
    transformation peek();
    bool isEmpty();
};

bool stack::push(transformation x)
{
    if (top >= (MAX - 1)) {
        std::cout << "Stack Overflow";
        return false;
    }
    else {
        a[++top] = x;
        std::cout << "Matrix pushed into stack\n";
        return true;
    }
}

transformation stack::pop()
{
    if (top < 0) {
        std::cout << "Stack Underflow";
        return transformation();
    }
    else {
        transformation x = a[top--];
        return x;
    }
}

transformation stack::peek()
{
    if (top < 0) {
        std::cout << "Stack is Empty";
        return transformation();
    }
    else {
        transformation x = a[top];
        return x;
    }
}

bool stack::isEmpty()
{
    return (top < 0);
}

/*
// Driver program to test above functions
int main()
{
    class Stack s;
    s.push({{1, 2}, {3, 4}});
    s.push({{5, 6}, {7, 8}});
    s.push({{9, 10}, {11, 12}});
    
    transformation m = s.pop();
    
    cout << "Popped matrix from stack: \n";
    
    for (int i = 0; i < m.size(); i++) {
        for (int j = 0; j < m[i].size(); j++) {
            cout << m[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
*/

#endif /* transformationStack_hpp */
