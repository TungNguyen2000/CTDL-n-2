#pragma once
#include <iostream>
using namespace std;
class Node
{
public:
	Node* left;
	Node* right;
	int data;
	int freq;
	string code;
public:
	bool isEndNode() {
		if (left == nullptr && right == nullptr) { return true; }
		return false;
	}
public:
	void operator () (Node* node) {
		left = node->left;
		right = node->right;
		data = node->data;
		freq = node->freq;
		code = node->code;
	}
	Node() {
		//parent = nullptr;
		//this = nulltr;
		left = nullptr;
		right = nullptr;
		data = 0;
		freq = 0;
		code = string();
	}
	Node(Node& l, Node& r) {//:left(l),right(r) {
		data = l.data + r.data;
		freq = 0;
		code = string();// char(l.data) + char(r.data);
		left = &l;
		right = &r;
		//l->parent = this;
		//r->parent = this;
		//parent = nullptr;
	}

};