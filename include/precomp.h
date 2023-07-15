//
// Created by Noy on 2023/7/10.
//

#ifndef FLATCRAFT_PRECOMP_H
#define FLATCRAFT_PRECOMP_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <unordered_map>
#include <queue>
#include <memory>
#include <cmath>
#include <utility>
#include <functional>
#include <optional>
#include <thread>
#include <future>
#include <mutex>
#include <shared_mutex>
#include <random>

template<class A, class B>
std::unique_ptr<A> dynamic_unique_cast(std::unique_ptr<B>&& p){
    static_assert(std::is_convertible<A*, B*>::value, "A must be convertible to B");
    B* b = p.release();
    A* a = dynamic_cast<A*>(b);
    if(a == nullptr){
        delete b;
        return nullptr;
    }
    return std::unique_ptr<A>(a);
}

template<class K, class V>
V getOrDefault(const std::unordered_map<K,V>& map, const K& key, const V& def){
    auto it = map.find(key);
    if(it == map.end())
        return def;
    return it->second;
}

#endif //FLATCRAFT_PRECOMP_H
