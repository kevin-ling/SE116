//
//  WriteCode.cpp
//
//  Created by 孙炜程 on 11/18/15.
//  Copyright © 2015 孙炜程. All rights reserved.
//
#include "WriteCode.h"
#include <iostream>
#include <queue>
#include <algorithm>

TreeNode* getNode(const string &s)
{
	if (s == "#")
		return nullptr;
	return new TreeNode(stoi(s));
}
TreeNode* WriteCode::RecoverTree(vector<string> str){
	TreeNode* root = getNode(str[0]);
	if (root == nullptr)
		return nullptr;
	TreeNode* current = root;
	queue<TreeNode*> toRecover;
	toRecover.push(root);
	auto begin = str.begin();
	++begin;
	auto end = str.end();
	while (!toRecover.empty() && begin != end)     // use queue to implement the process
	{
		TreeNode* current = toRecover.front();
		toRecover.pop();
		if ((current->left = getNode(*begin))!= nullptr)
			toRecover.push(current->left);
		++begin;
		if (begin == end)
			break;
		if ((current->right = getNode(*begin)) != nullptr)
			toRecover.push(current->right);
		++begin;
	}
    return root;
}
int cal_sum(TreeNode* root, int &maxSum)
{
	if (root == nullptr)
		return 0;
	int left = cal_sum(root->left, maxSum);
	int right = cal_sum(root->right, maxSum);
	int sum = left + right + root->val;
	if (sum > maxSum)
		maxSum = sum;
	int thismax = std::max(left,right);
	return std::max(thismax + root->val, root->val);
}
int WriteCode::FindMaxPathSum(TreeNode* root){
	int maxSum = root->val;
	cal_sum(root, maxSum);
	return maxSum;
}
int cal_height(TreeNode* root, int &longest)
{
	if (root == nullptr)
		return -1;
	int left = cal_height(root->left, longest);
	int right = cal_height(root->right, longest);
	int path = left + right + 2;
	if (path > longest)
		longest = path;
	return 1 + std::max(left, right);
}
int WriteCode::TreeDiameter(TreeNode* root){
	int maxPath = 0;
	cal_height(root, maxPath);
    return maxPath+1;
}
