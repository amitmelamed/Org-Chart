//
// Created by Amit on 13/05/2022.
//
#include <bits/stdc++.h>
#include "OrgChart.hpp"

using namespace std;
namespace ariel {
    /**
     * Constructor for the Node class
     * @param name
     */

    Node::Node(string name, int level) {
        this->name=name;
        this->level=level;
    }

    /**
     * Getters for the Node Class
     */
    string Node::getName() {
        return name;
    }

    int Node::getLevel() {
        return level;
    }

    vector<Node *> Node::getEmployees() {
        return employees;
    }

    std::ostream &operator<<(std::ostream &o, Node const &node){
        o<<node.name;
        return o;
    }

    /**
     * Functions for the Node Class
     */
    void Node::addEmployee(Node *newNode) {
        employees.push_back(newNode);
    }

    /**
     * Constructor for the OrgChart class
     */
    OrgChart::OrgChart() {
        boss = new Node("none",0);
        endNode=new Node("END",-1);
    }
    /**
     * Functions for the org chart class
     * add root-adding a new root to the tree
     */
    OrgChart OrgChart::add_root(string name) {
        Node *newBoss;
        newBoss = new Node(name,0);
        boss = newBoss;
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
    OrgChart OrgChart::add_sub(string father, string child) {
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
     * Constructor for the Iterator class
     */
    Iterator::Iterator() {
        index=0;
    }

    Node *Iterator::getCurrent() {
        if(index>=nodes.size()){
            throw runtime_error("Index out of range");
        }
        return nodes[index];
    }

    bool Iterator::hasNext() {
        if(index>=nodes.size()-1){
            return false;
        }
        return true;
    }

    void Iterator::addNode(Node * node) {
        nodes.push_back(node);
    }


    const Node *Iterator::operator->() const {
        return this->nodes[index];
    }


    string Iterator::operator*() {
        return nodes[index]->getName();
    }

    Iterator Iterator::operator++() {
        if(index<nodes.size()){
            index++;
            return *this;
        }
        else
        {
            throw runtime_error("Index out of range");
        }

    }
    bool operator==(const Iterator &A,const Iterator  &B){
        if(A.nodes.size()==0||B.nodes.size()==0){
            throw runtime_error("Iterators are empty");
        }
        if(A.nodes[A.index]->getName()==B.nodes[B.index]->getName())
            return true;
        return false;
    }
    bool operator!=(const Iterator &A,const Iterator  &B){
        return !(A==B);
    }

    void Iterator::DFS(Iterator* iterator,Node* root) {
        if(root== nullptr){
            return;
        }
        iterator->addNode(new Node(root->getName(),root->getLevel()));
        for (size_t i = 0; i < root->getEmployees().size(); ++i) {
            DFS(iterator,root->getEmployees()[i]);
        }
    }
    Iterator OrgChart::begin_preorder() {
        Iterator iterator;
        iterator.DFS(&iterator,boss);
        iterator.addNode(endNode);
        return iterator;

    }

    Iterator OrgChart::end_preorder() {
        Iterator iterator;
        iterator.DFS(&iterator,boss);

        iterator.addNode(endNode);
        while (iterator.hasNext()){
            ++iterator;
        }
        return iterator;

    }

    Iterator OrgChart::begin_level_order() {
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

    Iterator OrgChart::end_level_order() {
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

    Iterator OrgChart::begin_reverse_order() {
        Iterator iterator;
        iterator= this->begin_level_order();
        return iterator;
    }

    Iterator OrgChart::reverse_order() {
        Iterator reverseIterator=begin_reverse_order();

        while (reverseIterator.hasNext()){
            ++reverseIterator;
        }
        return reverseIterator;
    }

    int Node::size() const{
        return this->name.length();
    }

    Iterator OrgChart::begin() {
        return begin_level_order();
    }

    Iterator OrgChart::end() {
        return end_level_order();
    }
    OrgChart::~OrgChart() {
        for (auto it = begin_reverse_order(); it != reverse_order(); ++it)
        {
            //cout<<"gay";
            //delete (it.getCurrent());
        }
    }
}
