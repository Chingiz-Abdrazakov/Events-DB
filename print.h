#pragma once
#include "date.h"
#include <sstream>
#include <exception>
#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>

using namespace std;

template<typename T>
ostream& operator << (ostream& os, const vector<T>& v) {
    bool first = true;
    for (const T& item : v) {
        if (!first) {
            os << " ";
        }
        os << item;
    }
    return os;
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
    bool first = true;
    for (const auto& x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os;
}

/*
template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
    bool first = true;
    for (const auto& kv : m) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << kv.first << ": " << kv.second;
    }
}
*/


