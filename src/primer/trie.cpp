#include "primer/trie.h"
#include <string_view>
#include <stack>
#include "common/exception.h"

using namespace std;

namespace bustub {

template <class T>
auto Trie::Get(string_view key) const -> const T * {

  // You should walk through the trie to find the node corresponding to the key. If the node doesn't exist, return
  // nullptr. After you find the node, you should use `dynamic_cast` to cast it to `const TrieNodeWithValue<T> *`. If
  // dynamic_cast returns `nullptr`, it means the type of the value is mismatched, and you should return nullptr.
  // Otherwise, return the value.
  if (this->root_ == nullptr) {
    return nullptr;
  }
  shared_ptr<const TrieNode> cur = this->root_;
  for (char ch : key) {
    if (!cur->children_.count(ch)) {
      return nullptr;
    }
    cur = cur->children_.at(ch);

  }

  auto ret = dynamic_cast<const TrieNodeWithValue<T>*>(cur.get());
  if (ret == nullptr) {
    return nullptr;
  }
  return ret->value_.get();
}

template <class T>
auto Trie::Put(string_view key, T value) const -> Trie {
  // Note that `T` might be a non-copyable type. Always use `move` when creating `shared_ptr` on that value.
  // You should walk through the trie and create new nodes if necessary. If the node corresponding to the key already
  // exists, you should create a new `TrieNodeWithValue`.

  shared_ptr<TrieNode> root_ptr;
  if (this->root_ == nullptr) {
    root_ptr = make_shared<TrieNode>();
  } else {
    root_ptr = this->root_->Clone();
  }
  shared_ptr<TrieNode> child = root_ptr;
  shared_ptr<TrieNode> cur = nullptr;
  for (char ch : key) {
    cur = child;
    if (cur->children_.count(ch)) {
      auto original_child = cur->children_[ch];
      child = original_child->Clone();
    } else {
      child = make_shared<TrieNode>();
    }
    cur->children_[ch] = child;
  }
  child = make_shared<TrieNodeWithValue<T>>(
      child->children_, make_shared<T>(std::move(value)));
  if (cur == nullptr) {
    // empty string
    return Trie(child);
  }
  cur->children_[key.at(key.length() - 1)] = child;
  return Trie(root_ptr);
}

auto Trie::Remove(string_view key) const -> Trie {
  // You should walk through the trie and remove nodes if necessary. If the node doesn't contain a value any more,
  // you should convert it to `TrieNode`. If a node doesn't have children any more, you should remove it.
  if (this->root_ == nullptr) {
    return {};
  }
  stack<shared_ptr<TrieNode>> stk{};

  shared_ptr<TrieNode> root_ptr = this->root_->Clone();
  shared_ptr<TrieNode> child = root_ptr;
  shared_ptr<TrieNode> cur;
  for (char ch : key) {
    cur = child;
    stk.push(cur);
    auto original_child = cur->children_[ch];
    if (original_child == nullptr) {
      return *this;
    }
    child = original_child->Clone();
  }

  if (child->children_.empty()) {
    child = nullptr;
  } else {
    child = make_shared<TrieNode>(child->children_);
  }

  for (size_t i = key.length(); i != 0; i--) {
    char ch = key.at(i - 1);
    cur = stk.top();
    stk.pop();
    if (child == nullptr) {
      cur->children_.erase(ch);
    } else {
      cur->children_[ch] = child;
    }
    if (!cur->is_value_node_ && cur->children_.empty()) {
      child = nullptr;
    } else {
      child = cur;
    }
  }
  if (!root_ptr->is_value_node_ && root_ptr->children_.empty()) {
    return {};
  }
  return Trie(shared_ptr<const TrieNode>(root_ptr));
}

// Below are explicit instantiation of template functions.
//
// Generally people would write the implementation of template classes and functions in the header file. However, we
// separate the implementation into a .cpp file to make things clearer. In order to make the compiler know the
// implementation of the template functions, we need to explicitly instantiate them here, so that they can be picked up
// by the linker.

template auto Trie::Put(string_view key, uint32_t value) const -> Trie;
template auto Trie::Get(string_view key) const -> const uint32_t *;

template auto Trie::Put(string_view key, uint64_t value) const -> Trie;
template auto Trie::Get(string_view key) const -> const uint64_t *;

template auto Trie::Put(string_view key, string value) const -> Trie;
template auto Trie::Get(string_view key) const -> const string *;

// If your solution cannot compile for non-copy tests, you can remove the below lines to get partial score.

using Integer = unique_ptr<uint32_t>;

template auto Trie::Put(string_view key, Integer value) const -> Trie;
template auto Trie::Get(string_view key) const -> const Integer *;

template auto Trie::Put(string_view key, MoveBlocked value) const -> Trie;
template auto Trie::Get(string_view key) const -> const MoveBlocked *;

}  // namespace bustub
