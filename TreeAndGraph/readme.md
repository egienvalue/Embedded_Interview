# Tree

## 95. Unique Binary Search Trees II

### Description
Given an integer n, generate all structurally unique BST's (binary search trees) that store values 1 ... n.

Example:
```
Input: 3
Output:
[
  [1,null,3,2],
  [3,2,null,1],
  [3,1,null,null,2],
  [2,1,3],
  [1,null,2,null,3]
]
Explanation:
The above output corresponds to the 5 unique BST's shown below:

   1         3     3      2      1
    \       /     /      / \      \
     3     2     1      1   3      2
    /     /       \                 \
   2     1         2                 3
```

### Solution-1
```c++
class Solution {
public:
    
    vector<TreeNode*> helper(int min, int max){
        vector<TreeNode*> ret;
        if(min > max)
            return {nullptr};
        for(int i=min;i<=max;i++){
            vector<TreeNode*> left_tree = helper(min, i-1);
            vector<TreeNode*> right_tree = helper(i+1, max);
            for(auto &left_subtree:left_tree){
                for(auto & right_subtree: right_tree){
                    TreeNode* root = new TreeNode(i);
                    root->left = left_subtree;
                    root->right = right_subtree;
                    ret.push_back(root);
                }
            }
        }
        return ret;
        
    }
    
    vector<TreeNode*> generateTrees(int n) {
        if(n==0)
            return {};
        return helper(1,n);
    }
};
```