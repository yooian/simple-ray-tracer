#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"
#include <memory>
#include <vector>

// using std::make_shared;
// using std::shared_ptr;

class hittable_list : public hittable
{
public:
    // wouldnt be able to store hittable or hittable* since it's abstract
    std::vector<std::shared_ptr<hittable>> objects;

    hittable_list() {}
    hittable_list(std::shared_ptr<hittable> object) { add(object); }

    void clear() {}

    void add() {}

    bool hit() const override {}
};

#endif
