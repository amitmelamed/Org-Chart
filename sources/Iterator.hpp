//
// Created by lucas on 17/05/2022.
//

#ifndef ORG_CHART_ITERATOR_HPP
#define ORG_CHART_ITERATOR_HPP
#include "Node.hpp"
using namespace std;

namespace ariel{
    /**
     *Iterator for the Org Chart class
     * The iterator have a vector of nodes pointers,
     * and an index of the current Node.
     */
    class Iterator{
        vector<Node*> nodes;
        size_t index;
    public:
        //-----Constructors-----
        Iterator();

        //-----Getters-----
        Node* getCurrent();
        int size();
        //-----Functions-----
        void addNode(Node*);
        bool hasNext();
        void DFS(Iterator* iterator,Node* root);

        //-----Operator_Overloading-----
        Iterator operator++(); //++prefix
        string operator*(); //*prefix
        friend bool operator==(const Iterator &A,const Iterator  &B);
        friend bool operator!=(const Iterator &A,const Iterator  &B);
        Node const * operator->() const;

    };
}
#endif //ORG_CHART_ITERATOR_HPP
