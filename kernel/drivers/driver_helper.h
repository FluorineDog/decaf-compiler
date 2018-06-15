#pragma once
#include <algorithm>
#include <string>
#include <vector>
using std::find_if;
using std::string;
using std::vector;
// template <typename Key, typename Value>
using Key = std::string;
using Value = double;

class MapSeq {
 private:
  vector<std::pair<Key, Value>> record;
  using EntryType = std::pair<Key, Value>;

 public:
  // nullable
  const Value* find(const Key& key) const {
    auto iter = find_if(record.begin(), record.end(),
                        [=](EntryType&& entry) { return entry.first == key; });
    if (iter != record.end()) {
      return &iter->second;
    } else {
      return nullptr;
    }
  }
  Value* find(const Key& key) {
    auto ans = std::as_const(*this).find(key);
    return const_cast<Value*>(ans);
  }

  void append(Key&& key, Value&& value) {
    record.emplace_back(std::make_pair(  //
        std::forward<Key>(key),          //
        std::forward<Value>(value)));
  }
  auto begin() const { return record.begin(); }
  auto begin() { return record.begin(); }
  auto end() const { return record.end(); }
  auto end() { return record.end(); }
};
