#include <iostream>

template<typename Key, typename Value>
class hashmap {
private:
    static const size_t MAX_SIZE = 1000007;
    Value *map;

    [[nodiscard]] size_t hash(const Key& key) const {
        return std::hash<Key>{}(key) % MAX_SIZE;
    }

public:
    hashmap() {
        map = new Value[MAX_SIZE];
    }

    void insert(const Key& key, const Value& value) {
        size_t idx = hash(key);
        map[idx] = value;
    }

    Value get(const Key& key) {
        return map[hash(key)];
    }

    void remove(const Key& key) {
        map[hash(key)] = Value(0);
    }
};


int main() {
    hashmap<std::string, int> hashmap{};

    hashmap.insert("one", 1);
    hashmap.insert("two", 2);

    std::cout << hashmap.get("one") << "+" << hashmap.get("two") << "=" << hashmap.get("one") + hashmap.get("two");






    return 0;
}