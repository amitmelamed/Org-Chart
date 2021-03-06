//
// Created by Amit on 18/05/2022.
//
/**
 * This Iterator file contains the implementation of the Iterator class
 */

#include <bits/stdc++.h>
#include "OrgChart.hpp"

using namespace std;

namespace ariel {
    /**
     * Constructor for the Iterator class
     */
    Iterator::Iterator() {
        index = 0;
    }

    /**
     * Returns the current node 'index' points on.
     * @return
     */
    Node *Iterator::getCurrent() {
        if (index >= nodes.size()) {
            throw runtime_error("Index out of range");
        }
        return nodes[index];
    }

    /**
     * returns True if the Iterator have next node to point on
     * @return
     */
    bool Iterator::hasNext() {
        bool ans= true;
        if (index >= nodes.size() - 1) {
            ans= false;
        }
        return ans;
    }

    /**
     * Add new node to the iterator by pushing him to the vector od nodes pointers
     * @param node
     */
    void Iterator::addNode(Node *node) {
        nodes.push_back(node);
    }

    /**
     * Operator overriding:
     * -> return Node pointer
     * * return the name of current Node
     * ++ increase to current node
     * == , != compression operators
     * @return
     */
    const Node *Iterator::operator->() const {
        return this->nodes[index];
    }

    string Iterator::operator*() {
        return this->nodes[index]->getName();
    }

    Iterator Iterator::operator++() {
        if (index < nodes.size()) {
            index++;
            return *this;
        }


        throw runtime_error("Index out of range");


    }

    bool operator==(const Iterator &A, const Iterator &B) {
        if (A.nodes.empty() || B.nodes.empty()) {
            throw runtime_error("Iterators are empty");
        }
        bool ans = false;
        if (A.nodes[A.index]->getName() == B.nodes[B.index]->getName()) {
            ans = true;
        }
        return ans;
    }

    bool operator!=(const Iterator &A, const Iterator &B) {
        return !(A == B);
    }

    /**
     * Insert into iterator new values from root,
     * using Depth-first search algorithm
     * @param iterator
     * @param root
     */
    void Iterator::DFS(Iterator *iterator, Node *root) {
        if (root == nullptr) {
            return;
        }
        iterator->addNode(root);
        for (size_t i = 0; i < root->getEmployees().size(); ++i) {
            DFS(iterator, root->getEmployees()[i]);
        }
    }
}