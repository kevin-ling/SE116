//
//  WriteCode.h
//
//  Created by 孙炜程 on 11/18/15.
//  Copyright © 2015 孙炜程. All rights reserved.
//

#ifndef WriteCode_h
#define WriteCode_h
#include <string>
#include <vector>
#include <set>

using namespace std;

struct TreeNode{
    int val;
    TreeNode * left;
    TreeNode * right;
    TreeNode(int x): val(x),left(NULL),right(NULL){}
};

class WriteCode{
public:
    TreeNode* RecoverTree(vector<string> str);
    int FindMaxPathSum(TreeNode* root);
    int TreeDiameter(TreeNode* root);
};

#endif /* WriteCode_h */
