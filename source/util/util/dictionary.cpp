#include "../util.hpp"

#include <iostream>
#include <vector>

template <typename Key, typename Val> class util::Dictionary {
private:
    std::vector<Key> keys;
    std::vector<Val> vals;

public:
    Val &operator[](const Key key) {
        return vals[std::find(keys.begin(), keys.end(), key)];
    }

    void add(const Key key, const Val val) {
        keys.push_back(key);
        vals.push_back(val);
    }

    void remove(const unsigned int index) {
        keys.erase(keys.begin() + index);
        vals.erase(vals.begin() + index);
    }

    int getLength() {
        return keys.size();
    }

    Val &byindex(const unsigned int index) {
        return vals[index];
    }
};