#include "function.h"
#include <algorithm>
#include <iostream>
using namespace std;
oj::Vector::Vector() {
    begin_ = end_ = last_ = NULL;
}

oj::Vector::size_type oj::Vector::capacity() const {
    if(begin_ == NULL)
        return 0;
    else
        return end_ - begin_;
}

oj::Vector::size_type oj::Vector::size() const {
    if(begin_ == NULL)
        return 0;
    else
        return last_ - begin_;
}

void oj::Vector::pop_back() {
    if(size()) {
        last_ = last_ - 1;
    }
}
void oj::Vector::push_back(value_type val) {
    oj::Vector::size_type cp = capacity(), sz = size();
    if(sz == cp) { // reallocate the memory
        oj::Vector::pointer new_begin = new value_type[max(cp+1, cp*3)];
        for(int i = 0; i < sz; i++) {
            new_begin[i] = begin_[i];
        }
        new_begin[sz] = val;

        delete[] begin_;
        begin_ = new_begin;
        end_ = new_begin + max(cp+1, cp*3);
        last_ = new_begin + sz + 1;
    }
    else { // push to the end of the array
        begin_[sz] = val;
        last_ = last_ + 1;
    }
}
void oj::Vector::insert(size_type pos,size_type count,value_type val) {
    oj::Vector::size_type cp = capacity(), sz = size(), new_capacity;
    if(sz + count > cp)
        new_capacity = max(cp + cp/2, cp + count);
    else
        new_capacity = cp;
    oj::Vector::pointer new_begin = new value_type[new_capacity];

    if(pos > sz)
        pos = sz;
    for(int i = 0; i < pos; i++) {
        new_begin[i] = begin_[i];
    }
    for(int i = 0; i < count; i++) {
        new_begin[pos+i] = val;
    }
    for(int i = pos+count; i < sz+count; i++) {
        new_begin[i] = begin_[i-count];
    }

    delete[] begin_;
    begin_ = new_begin;
    end_ = new_begin + new_capacity;
    last_ = new_begin + sz + count;
}

void oj::Vector::reserve(size_type new_capacity) {
    if(new_capacity > capacity()) {
        oj::Vector::size_type sz = size();
        oj::Vector::pointer new_begin = new value_type[new_capacity];
        for(int i = 0; i < sz; i++) {
            new_begin[i] = begin_[i];
        }
        delete[] begin_;
        begin_ = new_begin;
        end_ = new_begin + new_capacity;
        last_ = new_begin + sz;
    }
}

void oj::Vector::resize(size_type new_size) {
    oj::Vector::size_type sz = size();
    if(new_size > capacity()) {
        reserve(new_size);
    }
    last_ = begin_ + new_size;

    for(int i = sz; i < new_size; i++)
        begin_[i] = 0;
}

oj::Vector::~Vector() { // free the space
    delete[] begin_;
}
