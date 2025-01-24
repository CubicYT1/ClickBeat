#include "../util.hpp"

#include <iostream>
#include <vector>

template <typename Key, typename Val> class util::Dictionary {
private:
    std::vector<Key> keys;
    std::vector<Val> vals;

public:
    Val &operator[](const Key key) {
        for (int i = 0; i < keys.size(); i++) {
            if (keys[i] == key) {
                return vals[i];
            }
        }
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