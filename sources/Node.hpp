//
// Created by lucas on 17/05/2022.
//
#include <iostream>
#include <vector>
#ifndef ORG_CHART_NODE_HPP
#define ORG_CHART_NODE_HPP
using namespace std;
namespace ariel{
    /**
     * The Node class represent a Worker in the work place.
     * each worker have a name.
     * each worker have a vector of employees that works under him.
     */
    class Node{
        //-----Variables-----
        string name;
        vector<Node*> employees;
        int level;
    public:
        //-----Constructors-----
        Node(string,int);
        //-----Getters-----
        string getName();
        vector<Node*> getEmployees();
        int getLevel();

        //-----Functions-----
        void addEmployee(Node*);
        int size() const;
        //-----Operator_overloading-----
        friend std::ostream &operator<<(std::ostream &o, Node const &c);

    };
}
#endif //ORG_CHART_NODE_HPP
