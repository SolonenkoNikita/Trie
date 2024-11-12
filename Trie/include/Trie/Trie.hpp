#pragma once

#include <string>
#include <iostream>
#include <array>
#include <vector>

struct Node
{
	Node* parent_;

	std::array<Node*, 256> children_;

	char partial_key_;

	size_t count_of_descendant_;

	bool key_end_flag_;

	Node(Node* parent = nullptr, char partial_key_ = '\0') : parent_(parent), partial_key_(partial_key_),
																count_of_descendant_(0), key_end_flag_(false)
	{
		children_.fill(nullptr);
	}

	bool has_child(char partial_key) const;

	void add_child(char partial_key);

	Node* get_child(char partial_key) const;

	void remove_child(char partial_key);
};

class Trie
{
private:

	Node* root_;
public:

	Trie() : root_(new Node()) {}

	void insert(const std::string&);

	bool count(const std::string&) const;

	Node* find(const std::string&) const;

	bool remove(const std::string&);

	void traverse() const;
	
	~Trie();
private:

	void traverse_recursive(Node* node, std::vector<char>&) const;

	void clear(Node*);

};


