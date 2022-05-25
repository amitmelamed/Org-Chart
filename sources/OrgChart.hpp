//
// Created by Amit on 13/05/2022.
//

#ifndef ORG_CHART_ORGCHART_HPP
#define ORG_CHART_ORGCHART_HPP
#include <iostream>
#include <vector>

#include "Iterator.hpp"
using namespace std;
namespace ariel{


    /**
     * OrgChart class represent hierarchy in a work place.
     * The OrgChart is a Generic Tree that the higher the level of the tree,
     * the higher the level of the worker.
     */
    class OrgChart{
        //-----Variables-----
        Node* boss;
        Node* endNode;

    public:
        //-----Constructors-----
        OrgChart();
        OrgChart(const OrgChart&);


        OrgChart(OrgChart& org) = default;
        OrgChart(OrgChart&& org) = default;
        OrgChart& operator=(OrgChart&&) = default;
        OrgChart& operator=(const OrgChart& org) = default;
        //-----Destructor-----
        ~OrgChart();
        //-----Functions-----
        OrgChart& add_root(string);
        OrgChart& add_sub(string const &,string const &);
        void BFS_print();
        //-----Iterators_Functions-----
        Iterator begin() const;
        Iterator end() const;
        Iterator begin_level_order() const;
        Iterator end_level_order() const;
        Iterator begin_reverse_order() const;
        Iterator reverse_order() const;
        Iterator begin_preorder() const;
        Iterator end_preorder() const;
        //operator overloading
        friend std::ostream &operator<<(std::ostream &o, OrgChart const &c);

    };
}
#endif //ORG_CHART_ORGCHART_HPP
