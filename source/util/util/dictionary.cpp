#include "../util.hpp"

template <typename Key, typename Val> class util::Dictionary {
private:
    List<Key> keys;
    List<Val> vals;

public:
    Val &operator[](const Key key) {
        return vals[keys.indexOf(key)];
    }

    void add(const Key key, const Val val) {
        keys.add(key);
        vals.add(val);
    }

    void remove(const unsigned int index) {
        keys.remove(index);
        vals.remove(index);
    }

    int getLength() {
        return keys.getLength();
    }

    Val &byindex(const unsigned int index) {
        return vals[index];
    }
};