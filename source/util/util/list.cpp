#include "../util.hpp"

#include <cstdlib>

template <typename Type> class util::List {
private:
    int length = 0;
    Type *data = nullptr;

public:
    Type &operator[](const unsigned int index) {
        return data[index];
    }

    void add(const Type value) {
        data = (Type*)std::realloc(data, sizeof(Type) * ++length);
        data[length - 1] = value;
    }

    void remove(unsigned int index) {
        if (index != length - 1) {
            for (int i = index + 1; i < length; i++) {
                data[i - 1] = data[i];
            }
        }
        data = (Type*)std::realloc(data, sizeof(Type) * --length);
    }

    int getLength() {
        return length;
    }

    int indexOf(const Type value) {
        for (int i = 0; i < length; i++) {
            if (data[i] == value) {
                return i;
            }
        }
        return -1;
    }

    ~List() {
        std::free(data);
    }
};