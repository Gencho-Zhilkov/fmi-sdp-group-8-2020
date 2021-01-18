// Compile and run with: g++ -g --std=c++2a 01_hashmap.cpp && ./a.out
// Need the c++2a to use the traits
#include <cassert>
#include <functional>
#include <vector>
#include <list>
#include <stdexcept>
#include <iostream>


struct HashMapTraits {
    size_t initialNumberOfBuckets = 16;
    double expandThreshold = 0.67;
    int expandFactor = 2;
    double shrinkThreshold = 0.33;
    int shrinkFactor = 2;
};


template<
    typename Key,
    typename Value,
    typename Hash = std::hash<Key>,
    typename KeyEqual = std::equal_to<Key>,
    const HashMapTraits traits = HashMapTraits()>
class HashMap  {
private:
    using Bucket = std::list<std::pair<Key, Value>>;

    std::vector<Bucket> buckets;
    size_t numElements;

    void rehash() {
        const auto shouldExpand = numElements > (size_t)(buckets.size() * traits.expandThreshold);
        const auto shouldShrink = numElements < (size_t)(buckets.size() * traits.shrinkThreshold);

        if (!shouldShrink && !shouldExpand) {
            return;
        }

        const size_t newSize = shouldExpand ? buckets.size() * traits.expandFactor : buckets.size() / traits.shrinkFactor;

        std::vector<Bucket> newBuckets(newSize);
        for(const auto bucket: buckets) {
            for(const auto pair: bucket) {
                const auto h = Hash()(pair.first) % newSize;
                newBuckets[h].push_back(pair);
            }
        }

        buckets = newBuckets;
    }

    std::pair<Bucket&, typename Bucket::iterator> locate(const Key& key) {
        const auto hashedKey = Hash()(key) % this->buckets.size();
        Bucket& bucket = buckets[hashedKey];
        for(auto it = bucket.begin(); it != bucket.end(); ++it) {
            if(KeyEqual()(it->first, key)) {
                return {bucket, it};
            }
        }
        return {bucket, bucket.end()};
    }

public:
    HashMap() : buckets(traits.initialNumberOfBuckets), numElements(0) {}

    void insert(const Key& key, const Value& value) {
        auto [bucket, it] = locate(key);
        if (it != bucket.end()) {
            throw std::invalid_argument("Key already inserted!");
        } else {
            bucket.push_back({key, value});
            numElements ++;
            rehash();
        }
    }

    void insertOrUpdate(const Key& key, const Value& value) {
        auto [bucket, it] = locate(key);
        if (it != bucket.end()) {
            it->second = value;
        } else {
            bucket.push_back({key, value});
            numElements ++;
            rehash();
        }
    }

    void erase(const Key& key) {
        auto [bucket, it] = locate(key);
        if (it != bucket.end()) {
            bucket.erase(it);
            numElements --;
            rehash();
        } else {
          throw std::out_of_range("Key not found!");
        }
    }

    Value& at(const Key& key) {
        auto [bucket, it] = locate(key);
        if (it != bucket.end()) {
          return it->second;
        } else {
          throw std::out_of_range("Key not found!");
        }
    }

    Value& get(const Key& key, const Value& missing) {
        auto [bucket, it] = locate(key);
        return it != bucket.end() ? it->second : missing;
    }
};


int main() {
    using namespace std;

    HashMap<string, int> h;
    h.insert("foo", 1);
    h.insert("bar", 2);
    h.insert("baz", 3);

    try {
        h.insert("foo", 4);
    } catch (const invalid_argument& err) {
        cerr << err.what() << endl;
    }

    for(auto key : {"foo", "bar", "baz", "boom"}) {
        try {
            cout << key << " -> " << h.at(key) << endl;
        } catch (const out_of_range& err) {
            cerr << err.what() << endl;
        }
    }

    try {
        h.erase("boom!");
    } catch (const out_of_range& err) {
        cerr << err.what() << endl;
    }

    h.erase("foo");
    try {
        cout << h.at("foo") << endl;
    } catch (const out_of_range& err) {
        cerr << err.what() << endl;
    }
}
