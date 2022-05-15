//
// Created by Amit on 13/05/2022.
//

#ifndef ORG_CHART_ORGCHART_HPP
#define ORG_CHART_ORGCHART_HPP
#include <iostream>
#include <vector>
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
        //-----Constructor-----

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
    /**
     *Iterator for the Org Chart class
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
    /**
     * OrgChart class represent hierarchy in a work place.
     * The OrgChart is a Generic Tree that the higher the level of the tree,
     * the higher the level of the worker.
     */
    class OrgChart{
        //-----Variables-----
        Node* boss;

    public:
        //-----Constructors-----
        OrgChart();
        //-----Functions-----
        OrgChart add_root(string);
        OrgChart add_sub(string,string);
        void BFS_print();
        //-----Iterators_Functions-----
        Iterator begin();
        Iterator end();
        Iterator begin_level_order();
        Iterator end_level_order();
        Iterator begin_reverse_order();
        Iterator reverse_order();
        Iterator begin_preorder();
        Iterator end_preorder();
        //operator overloading
        friend std::ostream &operator<<(std::ostream &o, OrgChart const &c);
    };
}
#endif //ORG_CHART_ORGCHART_HPP
