#include <Trie/Trie.hpp>
#include <Random/Random.hpp>

#include <absl/container/btree_set.h>

#include <set>
#include <unordered_set>
#include <chrono>

const int dictionary_size = 100000;

const int search_keys_count = 100000;

const int word_length = 15;

int main()
{

    std::vector<std::string> words;
    for (int i = 0; i < dictionary_size; ++i)
    {
        words.emplace_back(generate_random_word(word_length));
    }


    Trie trie;
    std::set<std::string> set;
    std::multiset<std::string> multi_set;
    std::unordered_set<std::string> un_set;
    absl::btree_set<std::string> btree;

  
    for (const auto& word : words)
    {
        trie.insert(word);
        set.insert(word);
        un_set.insert(word);
        multi_set.insert(word);
        btree.insert(word);
    }

    std::vector<std::string> search_keys;
    for (int i = 0; i < search_keys_count; ++i)
    {
        search_keys.emplace_back(generate_random_word(word_length));
    }

    auto start_trie = std::chrono::high_resolution_clock::now();
    for (const auto& key : search_keys)
    {
        trie.find(key);
    }
    auto end_trie = std::chrono::high_resolution_clock::now();
    auto duration_trie = std::chrono::duration_cast<std::chrono::microseconds>(end_trie - start_trie);


    auto start_set = std::chrono::high_resolution_clock::now();
    for (const auto& key : search_keys)
    {
        set.find(key);
    }
    auto end_set = std::chrono::high_resolution_clock::now();
    auto duration_set = std::chrono::duration_cast<std::chrono::microseconds>(end_set - start_set);

    auto start_un_set = std::chrono::high_resolution_clock::now();
    for (const auto& key : search_keys)
    {
        un_set.find(key);
    }
    auto end_un_set = std::chrono::high_resolution_clock::now();
    auto duration_un_set = std::chrono::duration_cast<std::chrono::microseconds>(end_un_set - start_un_set);

    auto start_mset = std::chrono::high_resolution_clock::now();
    for (const auto& key : search_keys)
    {
        trie.find(key);
    }
    auto end_mset = std::chrono::high_resolution_clock::now();
    auto duration_mset = std::chrono::duration_cast<std::chrono::microseconds>(end_mset - start_mset);

    auto start_btree = std::chrono::high_resolution_clock::now();
    for (const auto& key : search_keys)
    {
        trie.find(key);
    }
    auto end_btree = std::chrono::high_resolution_clock::now();
    auto duration_btree = std::chrono::duration_cast<std::chrono::microseconds>(end_btree - start_btree);

    std::cout << "Time in prefix " << duration_trie.count() << std::endl;
    std::cout << "Time in RB-balance-tree with not dublicate " << duration_set.count() << std::endl;
    std::cout << "Tine in RB-balance-tree " << duration_mset.count() << std::endl;
    std::cout << "Time in hash " << duration_un_set.count() << std::endl;
    std::cout << "Time in B-tree " << duration_btree.count() << std::endl;

    return 0;
}