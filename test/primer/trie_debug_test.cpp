#include <fmt/format.h>
#include <bitset>
#include <functional>
#include <numeric>
#include <optional>
#include <random>
#include <thread>  // NOLINT

#include "common/exception.h"
#include "gtest/gtest.h"
#include "primer/trie.h"
#include "primer/trie_answer.h"
#include "trie_debug_answer.h"  // NOLINT

namespace bustub {

TEST(TrieDebugger, TestCase) {
  std::mt19937_64 gen(2333);
  std::uniform_int_distribution<uint32_t> dis(0, 100);

  auto trie = Trie();
  for (uint32_t i = 0; i < 10; i++) {
    std::string key = fmt::format("{}", dis(gen));
    auto value = dis(gen);
    trie = trie.Put<uint32_t>(key, value);
  }

  // Put a breakpoint here.
  std::cout << "root size: " << trie.Root_size() << std::endl;
  auto m = trie.Root_children();
//  std::map<char, std::shared_ptr<const TrieNode>>::iterator it;
  for (auto & it : m) {
    std::cout << "key: " << it.first << std::endl;
  }
  // (1) How many children nodes are there on the root?
  // Replace `CASE_1_YOUR_ANSWER` in `trie_answer.h` with the correct answer.
//  if (CASE_1_YOUR_ANSWER != Case1CorrectAnswer()) {
//    ASSERT_TRUE(false);
//  }
  std::cout << "passed question 1 " << std::endl;

  // (2) How many children nodes are there on the node of prefix `9`?
  // Replace `CASE_2_YOUR_ANSWER` in `trie_answer.h` with the correct answer.
  std::cout << "size of prefix '9' node: " << m.at('9')->children_.size() << std::endl;
//  if (CASE_2_YOUR_ANSWER != Case2CorrectAnswer()) {
//    ASSERT_TRUE(false);
//  }
  std::cout << "passed question 2 " << std::endl;
  // (3) What's the value for `93`?
  auto node1 = m.at('9');
  auto node2 = node1->children_.at('3');
  auto ret = dynamic_cast<const TrieNodeWithValue<uint32_t>*>(node2.get());
  if (ret != nullptr) {
    std::cout << "value at '93': " << *ret->value_ << std::endl;
  }
  // Replace `CASE_3_YOUR_ANSWER` in `trie_answer.h` with the correct answer.
//  if (CASE_3_YOUR_ANSWER != Case3CorrectAnswer()) {
//    ASSERT_TRUE(false);
//  }
}

}  // namespace bustub
