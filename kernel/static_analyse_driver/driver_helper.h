#pragma once
#include <algorithm>
#include <string>
#include <vector>
#include <set>
using std::find_if;

using std::string;
using std::vector;
// using Key = std::string;
// using Value = double;
template <typename Key, typename Value>
class SeqMap {
 private:
  using Entry = std::pair<Key, Value>;
  vector<Entry> record;
  using EntryType = std::pair<Key, Value>;

 public:
  // nullable
  const Value* find(const Key& key) const {
    auto iter = find_if(record.rbegin(), record.rend(),
                        [=](auto&& entry) { return entry.first == key; });
    if (iter != record.rend()) {
      return &(iter->second);
    } else {
      return nullptr;
    }
  }
  Value* find(const Key& key) {
    auto ans = std::as_const(*this).find(key);
    return const_cast<Value*>(ans);
  }

  template <typename K, typename V>
  void append(K&& key, V&& value) {
    record.emplace_back(std::forward<Key>(key),  //
                        std::forward<Value>(value));
  }
  Entry& operator[](int i){
    return record[i];
  }
  const Entry& operator[](int i) const{
    return record[i];
  }
  auto begin() const { return record.begin(); }
  auto begin() { return record.begin(); }
  auto end() const { return record.end(); }
  auto end() { return record.end(); }
  size_t size() const { return record.size(); }
};

inline bool is_basic_type(string type){
  return std::set<std::string>({"int", "double", "bool", "string"}).count(type);
}