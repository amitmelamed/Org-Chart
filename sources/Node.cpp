//
// Created by Amit on 18/05/2022.
//
#include <bits/stdc++.h>
#include "OrgChart.hpp"

/**
* This Node file contains the implementation of the Node class
*/

using namespace std;
namespace ariel {
    /**
     * Constructor for the Node class
     * @param name
     */

    Node::Node(string name, int level) {
        this->name=std::move(name);
        this->level=level;
    }
    /**
     * Getters for the Node Class
     */
    string Node::getName() const{
        return name;
    }

    int Node::getLevel() const {
        return level;
    }

    vector<Node *> Node::getEmployees() const{
        return employees;
    }
    int Node::size() const{
        return this->name.length();
    }

    /**
     * Operator overriding
     * << returns the Node's name
     * @param o
     * @param node
     * @return
     */
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

}
