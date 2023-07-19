#include "inter_finder.hpp"
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstdlib>

using namespace ghostfragment::fragmenting;

using frag_type   = std::vector<std::size_t>;
using system_type = std::vector<frag_type>;

using group_type = std::vector<std::size_t>;

using log_type = std::map<std::pair<std::size_t, std::size_t>, inter_type>;

void find_group_intersections(
  const system_type& fragments, inter_type inter, std::size_t recent_add,
  res_type& m, log_type& log, group_type& group) {
    if(group.size() > 2) {
        for(std::size_t i = 0; i < group.size() - 1; ++i) {
            if(log.count(std::make_pair(group[i], recent_add)) == 0) return;
        }
        inter_type::iterator it = set_intersection(
          inter.begin(), inter.end(), fragments[recent_add].begin(),
          fragments[recent_add].end(), inter.begin());
        inter.resize(it - inter.begin());
    } else if(group.size() == 2)
        inter = log[std::make_pair(group[0], group[1])];

    if(!(inter.empty())) {
        if(m.count(inter) > 0)
            m[inter] += (group.size() % 2 == 0) ? -1 : 1;
        else if(group.size() > 1)
            m[inter] = (group.size() % 2 == 0) ? -1 : 1;

        for(std::size_t new_frag = recent_add + 1; new_frag < fragments.size();
            ++new_frag) {
            group_type new_group(group);
            new_group.push_back(new_frag);
            find_group_intersections(fragments, inter, new_frag, m, log,
                                     new_group);
        }
    }
}

const log_type find_pair_intersections(
  const system_type& fragments) {
    log_type log;
    inter_type::iterator it;
    for(std::size_t i = 0; i < fragments.size(); ++i) {
        for(std::size_t j = i + 1; j < fragments.size(); ++j) {
            std::size_t smaller = (fragments[i].size() < fragments[j].size()) ? fragments[i].size() : fragments[j].size();
            inter_type inter(smaller);
            it = set_intersection(fragments[i].begin(), fragments[i].end(),
                                  fragments[j].begin(), fragments[j].end(),
                                  inter.begin());
            inter.resize(it - inter.begin());

            if(!(inter.empty()))
                log.insert(std::make_pair(std::make_pair(i, j), inter));
        }
    }
    return log;
}


void create_system(const mol_type& mol, system_type& fragments) {
    const nuke_type f_nuclei = mol.fragmented_nuclei();
    for(std::size_t i = 0; i < f_nuclei.size(); ++i) {
        auto nukes = f_nuclei[i];
        frag_type fragment;
        for(const auto atom_i : nukes) { fragment.push_back(atom_i); }
        fragments.push_back(fragment);
    }
}

res_type ghostfragment::fragmenting::intersections(const mol_type& mol) {
    res_type m;
    system_type fragments;
    create_system(mol, fragments);
    log_type log = find_pair_intersections(fragments);
    for(std::size_t i = 0; i < fragments.size(); ++i) {
        inter_type inter(fragments[i]);
        group_type group({i});
        find_group_intersections(fragments, inter, i, m, log, group);
    }
    return m;
}