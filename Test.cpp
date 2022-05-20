


#include <iostream>
#include <vector>
#include "../doctest.h"
#include "OrgChart.hpp"

using namespace ariel;
TEST_CASE("Basic Chart"){
    OrgChart organization;
    organization.add_root("CEO")
    .add_sub("CEO", "CTO")         // Now the CTO is subordinate to the CEO
    .add_sub("CEO", "CFO")         // Now the CFO is subordinate to the CEO
    .add_sub("CEO", "COO")         // Now the COO is subordinate to the CEO
    .add_sub("CTO", "VP_SW") // Now the VP Software is subordinate to the CTO
    .add_sub("COO", "VP_BI");
    vector<string> names_level_order={"CEO", "CTO", "CFO", "COO", "VP_SW", "VP_BI"};
    vector<string> names_pre_order={"CEO", "CTO", "VP_SW", "CFO", "COO" ,"VP_BI"};
    vector<string> names_reverse_order={"VP_SW", "VP_BI", "CTO", "CFO", "COO", "CEO"};
    vector<int> size_level_order={3,3,3,3,5,5};
    vector<int> size_pre_order={3,3,5,3,3,5};
    vector<int> size_reverse_order={5,5,3,3,3,3};
    size_t i=0;
    for (auto it = organization.begin_level_order(); it != organization.end_level_order(); ++it)
    {
       CHECK_EQ(names_level_order[i],(*it));
       CHECK_EQ(size_level_order[i],it->size());
       i++;
    }
    i=0;
    for (auto it=organization.begin_preorder(); it!=organization.end_preorder(); ++it) {
        CHECK_EQ(names_pre_order[i],(*it));
        CHECK_EQ(size_pre_order[i],it->size());
        i++;
    }
    i=0;
    for (auto it = organization.begin_reverse_order(); it != organization.reverse_order(); ++it)
    {
        CHECK_EQ(names_reverse_order[i],(*it));
        CHECK_EQ(size_reverse_order[i],it->size());
        i++;
    } // prints: VP_SW VP_BI CTO CFO COO CEO
}

TEST_CASE("Add root and sub input"){
    OrgChart organization;
    organization.add_root("CEO");
    CHECK_THROWS(organization.add_sub("Not_CEO","Amit"));//only CEO in the tree
    CHECK_THROWS(organization.add_sub("Amit","Amit"));//Amit not in the tree
    CHECK_THROWS(organization.add_sub("Melamed","CFO"));
    CHECK_NOTHROW(organization.add_sub("CEO","Amit"));
    CHECK_NOTHROW(organization.add_sub("Amit","TUF"));
    CHECK_NOTHROW(organization.add_sub("CEO","Melamed"));


    vector<string> names_level_order={"CEO",  "Amit" , "Melamed",  "TUF"};
    vector<string> names_pre_order={"CEO","Amit","TUF","Melamed"};
    vector<string> names_reverse_order={"TUF", "Amit", "Melamed", "CEO"};


size_t i=0;
    for (auto it = organization.begin_level_order(); it != organization.end_level_order(); ++it)
    {
        CHECK_EQ(names_level_order[i],(*it));
        i++;
    }

    i=0;
    for (auto it=organization.begin_preorder(); it!=organization.end_preorder(); ++it) {
        CHECK_EQ(names_pre_order[i],(*it));
        i++;
    }
    i=0;

    for (auto it = organization.begin_reverse_order(); it != organization.reverse_order(); ++it)
    {
        CHECK_EQ(names_reverse_order[i],(*it));
        i++;
    }
}

TEST_CASE("Comparing two iterators"){
    OrgChart organization;
    organization.add_root("CEO");
    CHECK_THROWS(organization.add_sub("Not_CEO","Amit"));//only CEO in the tree
    CHECK_THROWS(organization.add_sub("Amit","Amit"));//Amit not in the tree
    CHECK_THROWS(organization.add_sub("Melamed","CFO"));
    CHECK_NOTHROW(organization.add_sub("CEO","Amit"));
    CHECK_NOTHROW(organization.add_sub("Amit","TUF"));
    CHECK_NOTHROW(organization.add_sub("CEO","Melamed"));

    Iterator pre_order=organization.begin_preorder();
    for (auto it=organization.begin_preorder(); it!=organization.end_preorder(); ++it) {
        CHECK_EQ(it,pre_order);
        ++pre_order;
    }

    Iterator level_order=organization.begin_level_order();
    for (auto it = organization.begin_level_order(); it != organization.end_level_order(); ++it){
        CHECK_EQ(it,level_order);
        ++level_order;
    }

    Iterator reverse_order=organization.begin_reverse_order();
    for (auto it = organization.begin_reverse_order(); it != organization.reverse_order(); ++it){
        CHECK_EQ(it,reverse_order);
        ++reverse_order;
    }
}