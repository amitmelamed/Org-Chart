//
// Created by Amit on 17/05/2022.
//

#include "../doctest.h"
#include "OrgChart.hpp"

TEST_CASE("Basic Chart"){
ariel::OrgChart organization;
organization.add_root("CEO")
.add_sub("CEO", "CTO")         // Now the CTO is subordinate to the CEO
.add_sub("CEO", "CFO")         // Now the CFO is subordinate to the CEO
.add_sub("CEO", "COO")         // Now the COO is subordinate to the CEO
.add_sub("CTO", "VP_SW") // Now the VP Software is subordinate to the CTO
.add_sub("COO", "VP_BI");
vector<string> names_level_order={"CEO", "CTO", "CFO", "COO", "VP_SW", "VP_BI"};
vector<string> names_pre_order{"CEO", "CTO", "VP_SW", "CFO", "COO" ,"VP_BI"};
vector<int> size_level_order={3,3,3,3,5,5};
vector<int> size_pre_order={3,3,5,3,3,5};
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
}