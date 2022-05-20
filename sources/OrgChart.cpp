//
// Created by Amit on 13/05/2022.
//
#include <bits/stdc++.h>
#include "OrgChart.hpp"

/**
* This OrgChart file contains the implementation of the OrgChart class,
*/

using namespace std;
namespace ariel {
    /**
     * Constructor for the OrgChart class
     */
    OrgChart::OrgChart() {
        boss = nullptr;
        endNode=new Node("END",-1);
    }
    /**
     * Copy Constructor
     * @param chart
     */
    OrgChart::OrgChart(const OrgChart &chart) {
        boss=chart.boss;
        endNode=chart.endNode;
    }

    /**
     * Functions for the org chart class
     * add root-adding a new root to the tree
     */


    /**
    * Deconstructor using reverse BFS algorithm
    */
    OrgChart::~OrgChart() {

        vector<Node*> stack;
        list<Node*> queue;

        queue.push_back(boss);
        Node* curr = nullptr;
        while (queue.size()){
            curr=queue.front();
            queue.pop_front();
            stack.push_back(curr);
            for (size_t i = 0; i < curr->getEmployees().size(); i++) {
                queue.push_back(curr->getEmployees()[curr->getEmployees().size()-1-i]);
            }
        }
        for (size_t i = 0; i < stack.size(); ++i) {
            delete stack[stack.size()-i-1];
        }
        delete endNode;
    }
    OrgChart& OrgChart::add_root(string name) {
        boss = new Node(name,0);
        return *this;
    }
    /**
     * add sub function add employee to the chosen father.
     * the function search the father node with BFS algorithm.
     * In case the father is found, we will create a new node to the father employees vector.
     * @param father
     * @param child
     * @return
     */
    OrgChart& OrgChart::add_sub(string father, string child) {
        if (boss->getName() == father) {
            Node *childNode = new Node(child,1);
            boss->addEmployee(childNode);
            return *this;
        }
        queue < Node * > q;  // Create a queue
        q.push(boss); // Enqueue root
        while (!q.empty()) {
            int n = q.size();

            // If this node has children
            while (n > 0) {
                // Dequeue an item from queue and print it
                Node *p = q.front();
                q.pop();
                if (p->getName() == father) {
                    Node *childNode = new Node(child,p->getLevel()+1);
                    p->addEmployee(childNode);
                    return *this;
                }
                // Enqueue all children of the dequeued item
                for (size_t i = 0; i < p->getEmployees().size(); i++)
                    q.push(p->getEmployees()[i]);
                n--;
            }
        }
        throw std::runtime_error("Father not found");
    }

    /**
     * When overloading the << operator we will output the Org chart,
     * by preforming a BFS on the tree, starting from the Boss node.
     * @param o
     * @param chart
     * @return
     */
    std::ostream &operator<<(std::ostream &o, OrgChart const &chart) {
        if(chart.boss== nullptr){
            return o;
        }
        queue < Node * > q;  // Create a queue
        q.push(chart.boss);


        while (!q.empty()){
            int n = q.size();
            // If this node has children
            while (n > 0) {
                // Dequeue an item from queue and print it
                Node *p = q.front();
                q.pop();
                o << p->getName() << " ";

                // Enqueue all children of the dequeued item
                for (size_t i = 0; i < p->getEmployees().size(); i++)
                    q.push(p->getEmployees()[i]);
                n--;
            }
            o << endl;
        }
        return o;
    }

    /**
     * Iterators traversal:
     * Each Algorithm has begin and end Iterator Creator
     * The traversal used:
     * Pre-order - using Pre order algorithm
     * Level-order - using BFS algorithm
     * Reverse_order - using BFS with stack instead of queue,
     * and going from right leafs to left.
     * @return
     */
    Iterator OrgChart::begin_preorder() const {
        Iterator iterator;
        iterator.DFS(&iterator,boss);
        iterator.addNode(endNode);
        return iterator;

    }

    Iterator OrgChart::end_preorder() const{
        Iterator iterator;
        iterator.DFS(&iterator,boss);

        iterator.addNode(endNode);
        while (iterator.hasNext()){
            ++iterator;
        }
        return iterator;

    }

    Iterator OrgChart::begin_level_order() const{
        Iterator iterator;

        if(boss== nullptr){
            return iterator;
        }
        queue < Node * > q;  // Create a queue
        q.push(boss);


        while (!q.empty()){
            int n = q.size();
            // If this node has children
            while (n > 0) {
                // Dequeue an item from queue and print it
                Node *p = q.front();
                q.pop();
                iterator.addNode(p);

                // Enqueue all children of the dequeued item
                for (size_t i = 0; i < p->getEmployees().size(); i++)
                    q.push(p->getEmployees()[i]);
                n--;
            }
        }
        iterator.addNode(endNode);
        return iterator;
    }

    Iterator OrgChart::end_level_order() const{
        Iterator iterator;


        if(boss== nullptr){
            return iterator;
        }
        queue < Node * > q;  // Create a queue
        q.push(boss);


        while (!q.empty()){
            int n = q.size();
            // If this node has children
            while (n > 0) {
                // Dequeue an item from queue and print it
                Node *p = q.front();
                q.pop();
                iterator.addNode(p);

                // Enqueue all children of the dequeued item
                for (size_t i = 0; i < p->getEmployees().size(); i++)
                    q.push(p->getEmployees()[i]);
                n--;
            }
        }
        iterator.addNode(endNode);
        while (iterator.hasNext()){
            ++iterator;
        }
        return iterator;
    }

    Iterator OrgChart::begin_reverse_order() const{
        Iterator iterator;
        if(boss== nullptr){
            return iterator;
        }
        vector<Node*> stack;
        list<Node*> queue;

        queue.push_back(boss);
        Node* curr = nullptr;
        while (queue.size()){
            curr=queue.front();
            queue.pop_front();
            stack.push_back(curr);
            for (size_t i = 0; i < curr->getEmployees().size(); i++) {
                queue.push_back(curr->getEmployees()[curr->getEmployees().size()-1-i]);
            }
        }
        for (size_t i = 0; i < stack.size(); ++i) {
            iterator.addNode(stack[stack.size()-i-1]);
        }

        iterator.addNode(endNode);

        return iterator;
    }

    Iterator OrgChart::reverse_order() const{
        Iterator reverseIterator=begin_reverse_order();

        reverseIterator.addNode(endNode);
        while (reverseIterator.hasNext()){
            ++reverseIterator;
        }

        return reverseIterator;
    }



    /**
     * begin and end function to be able to iterate:
     * for (auto element : organization)
     * @return
     */
    Iterator OrgChart::begin() const{
        return begin_level_order();
    }

    Iterator OrgChart::end() const{
        return end_level_order();
    }

}
