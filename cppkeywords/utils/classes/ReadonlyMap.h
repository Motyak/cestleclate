#ifndef UTILS_CLASSES_READONLY_MAP_H
#define UTILS_CLASSES_READONLY_MAP_H

template <typename K, typename V>
class ReadonlyMap {
    std::map<K,V> map;
  public:
    ReadonlyMap(std::initializer_list<std::pair<K,V>> keyValuePairs) {
        for (auto pair : keyValuePairs) {
            this->map[pair.first] = pair.second;
        }
    }
    
    V operator[](K key) const {
        return this->map.at(key);
    }
};

#endif
