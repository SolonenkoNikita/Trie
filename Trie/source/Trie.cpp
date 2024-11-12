#include "Trie/Trie.hpp"

bool Node::has_child(char partial_key) const
{
	return children_[partial_key] != nullptr;
}

void Node::add_child(char partial_key)
{
	children_[partial_key] = new Node(this, partial_key);
	++count_of_descendant_;
}

Node* Node::get_child(char partial_key) const
{
	return children_[partial_key];
}

void Node::remove_child(char partial_key)
{
	if (children_[partial_key])
	{
		delete children_[partial_key];
		children_[partial_key] = nullptr;
		--count_of_descendant_;
	}
}

void Trie::insert(const std::string& key)
{
	Node* node = root_;
	for (char s : key)
	{
		if (!node->has_child(s))
			node->add_child(s);
		node = node->get_child(s);
	}
	node->key_end_flag_ = true;
}

bool Trie::count(const std::string& key) const
{
	Node* node = root_;
	for (char s : key)
	{
		if (!node->has_child(s))
			return false;
		node = node->get_child(s);
	}
	return node->key_end_flag_;
}

Node* Trie::find(const std::string& key) const
{
	Node* node = root_;
	for (char s : key)
	{
		if (!node->has_child(s))
			return nullptr;
		node = node->get_child(s);
	}
	if (!node->key_end_flag_)
		return nullptr;
	return node;
}

bool Trie::remove(const std::string& key)
{
	Node* node = find(key);
	if (!node)
		return false;
	node->key_end_flag_ = false;

	while (node != root_ && node->count_of_descendant_ == 0 && !node->key_end_flag_)
	{
		Node* parent = node->parent_;
		parent->remove_child(node->partial_key_);
		node = parent;
	}
	return true;
}

void Trie::traverse() const
{
	std::vector<char> prefix;
	traverse_recursive(root_, prefix);
}

void Trie::traverse_recursive(Node* node, std::vector<char>& prefix) const
{
	if (!node)
		return;
	if (node->partial_key_ != '\0')
	{
		prefix.emplace_back(node->partial_key_);
	}
	if (node->key_end_flag_)
	{
		for (char c : prefix)
		{
			std::cout << c;
		}
		std::cout << std::endl;
	}
	for (size_t i = 0; i < node->children_.size(); ++i)
	{
		if (node->children_[i])
		{
			traverse_recursive(node->children_[i], prefix);
		}
	}
	if (!prefix.empty())
	{
		prefix.pop_back();
	}
}

void Trie::clear(Node* node)
{
	if (!node) 
		return;
	for (Node* child : node->children_) 
	{
		clear(child);
	}
	delete node;
}

Trie::~Trie()
{
	clear(root_);
}
