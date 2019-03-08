

## DFS

- Using recursive
  - LC 200 Number of Islands
  - reduce the code size

```c++
class Solution {
public:
    
    int total=0;
    void dfs(vector<vector<int>> & visited, vector<vector<char>>& grid, int start_i, int start_j){
        int m = grid.size();
        int n = grid[0].size();
        // boarder check is the stop recurse condition
        if(start_i <0 || start_j < 0 || start_i >= m || start_j >= n)
            return;
        if(visited[start_i][start_j]==1 || grid[start_i][start_j]=='0')
            return ;
        visited[start_i][start_j]=1;
        dfs(visited, grid, start_i +1, start_j +0);
        dfs(visited, grid, start_i -1, start_j + 0);
        dfs(visited, grid, start_i + 0, start_j + 1);
        dfs(visited, grid, start_i + 0 , start_j -1);
    }
    
    int numIslands(vector<vector<char>>& grid) {
        if(grid.empty())
            return 0;
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<int>> visited(m, vector<int>(n,0));
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if(grid[i][j]=='1' && visited[i][j]==0){
                    total++;
                    dfs(visited, grid, i, j);
                }
            }
        }
        return total;
    }
};

```

- Using traditional Stack
    LC 200 Number of Island

```c++
class Solution {
public:
    
    int total=0;
    vector<int> dir_i = {0,-1,1,0};
    vector<int> dir_j = {1,0,0,-1};
     
    void dfs(vector<vector<int>> & visited, vector<vector<char>>& grid, int start_i, int start_j){
        int m = grid.size();
        int n = grid[0].size();
        if(visited[start_i][start_j]==1)
            return;
        total++;
        stack<pair<int,int>> my_stack;
        my_stack.push(make_pair(start_i, start_j));
        visited[start_i][start_j] = 1;
        while(!my_stack.empty()){
            pair<int,int> cur = my_stack.top();
            my_stack.pop();
            for(int k=0;k<4;k++){
                int new_i = cur.first + dir_i[k];
                int new_j = cur.second + dir_j[k];
                if(new_i>=0 && new_j >=0 && new_i < m && new_j < n && visited[new_i][new_j] == 0 && grid[new_i][new_j]=='1'){
                    visited[new_i][new_j] = 1;
                    my_stack.push(make_pair(new_i, new_j));
                }
                
            }
        }
    }
    
    int numIslands(vector<vector<char>>& grid) {
        if(grid.empty())
            return 0;
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<int>> visited(m, vector<int>(n,0));
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if(grid[i][j]=='1'){
                    dfs(visited, grid, i, j);
                }
            }
        }
        return total;
    }
};
```







## BFS

- Using Traditional Queue
    LC 200 Number of Island

```c++
class Solution {
public:
    
    int total=0;
    vector<int> dir_i = {0,-1,1,0};
    vector<int> dir_j = {1,0,0,-1};
     
    void bfs(vector<vector<int>> & visited, vector<vector<char>>& grid, int start_i, int start_j){
        int m = grid.size();
        int n = grid[0].size();
        if(visited[start_i][start_j]==1)
            return;
        total++;
        deque<pair<int,int>> dq;
        dq.emplace_back(start_i,start_j);
        visited[start_i][start_j] = 1;
        while(!dq.empty()){
            pair<int,int> cur = dq.front();
            dq.pop_front();
            for(int k=0;k<dir_i.size();k++){
                int new_i=cur.first + dir_i[k];
                int new_j=cur.second + dir_j[k];
                if(new_i>=0 && new_j>=0 && new_i < m && new_j < n && visited[new_i][new_j]==0 && grid[new_i][new_j]=='1'){
                    dq.emplace_back(new_i, new_j);
                    visited[new_i][new_j]=1;
                }
                
            }
        }
        
    }
    
    int numIslands(vector<vector<char>>& grid) {
        if(grid.empty())
            return 0;
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<int>> visited(m, vector<int>(n,0));
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if(grid[i][j]=='1'){
                    bfs(visited, grid, i, j);
                }
            }
        }
        return total;
    }
};

```


## Uniont Find

- Union find with path compression
    LC 200 Number of Islands
```c++
class Solution {
public:
    
    int total;

    int find(vector<int>& rep, int index){
        if(rep[index]!=index){
            // assign is the key with path compression;
            rep[index]=find(rep,rep[index]);
        }
        return  rep[index];
    }
    
    void self_union(vector<int> & rep, int index1, int index2){
        int root1 = find(rep, index1);
        int root2 = find(rep, index2);
        if(root1==root2)
            return;
        rep[root2] = root1;
        // union one time means the total number of islands decrement 1
        total--;
    }
    
    vector<int> dir_x = {1,0};
    vector<int> dir_y = {0,1};
    
    int numIslands(vector<vector<char>>& grid) {
        if(grid.empty()){
            return 0;
        }
        int m = grid.size();
        int n = grid[0].size();

        vector<int> rep_map(m*n,0);
        total = m*n;
        iota(rep_map.begin(), rep_map.end(), 0);
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if(grid[i][j]=='0'){
                    total--;
                    continue;
                }
                for(int k=0;k<dir_x.size();k++){
                    int new_x = dir_x[k] + i;
                    int new_y = dir_y[k] + j;
                    if(new_x >=0 && new_y >=0 && new_x < m && new_y < n && grid[new_x][new_y]=='1'){
                        self_union(rep_map, i*n+j, new_x*n+new_y);
                    }
                }
            }
        }
        
        return total;
    }
};

```

## Heap 实现



## Hash Map 实现
hash function 映射Key到address
![](./IMG/hash_func.png)

- Integer
```c++

```


```c++
class MyHashMap {
public:
    
    vector<list<pair<int,int>>> my_map;
    int max_size = 10000;
    
    /** Initialize your data structure here. */
    MyHashMap() {
        my_map.resize(max_size);
    }
    // hash function 在这里有很多种
    // for integer, we just mod it with the bucket size 
    int hash_func(int key){
        return key % max_size;
    }
    
    /** value will always be non-negative. */
    void put(int key, int value) {
        int hash_index = hash_func(key);
        list<pair<int,int>>::iterator iter;
        list<pair<int,int>> & link_list=my_map[hash_index];
        for(iter = link_list.begin();iter!=link_list.end();iter++){
            if((*iter).first==key){
                (*iter).second = value;
                return;
            }
        }
        link_list.emplace_back(key, value);
    }
    
    /** Returns the value to which the specified key is mapped, or -1 if this map contains no mapping for the key */
    int get(int key) {
        int hash_index = hash_func(key);
        list<pair<int,int>>::iterator iter;
        list<pair<int,int>> & link_list = my_map[hash_index];
        for(iter = link_list.begin();iter!=link_list.end();iter++){
            if((*iter).first==key){
                return (*iter).second;
            }
        }
        return -1;
    }
    
    /** Removes the mapping of the specified value key if this map contains a mapping for the key */
    void remove(int key) {
        int hash_index = hash_func(key);
        list<pair<int,int>>::iterator iter;
        list<pair<int,int>> & link_list = my_map[hash_index];
        for(iter = link_list.begin();iter!=link_list.end();iter++){
            if((*iter).first==key){
                link_list.erase(iter);
                return;
            }
        }
    }
};
```


## Quick sort

- Quick sort 实现
  - partition and sort
  - find the using a element as pivot to find it correct position in this array

```c++
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        int left = 0, right = nums.size() - 1, kth;
        while (true) {
            int idx = partition(nums, left, right);
            if (idx == k - 1) {
                kth = nums[idx];
                break;
            }
            if (idx < k - 1) {
                left = idx + 1;
            } else {
                right = idx - 1;
            }
        }
        return kth;
    }
private:
    int partition(vector<int>& nums, int left, int right) {
        int pivot = nums[left], l = left + 1, r = right;
        while (l <= r) {
            if (nums[l] < pivot && nums[r] > pivot) {
                swap(nums[l++], nums[r--]);
            }
            if (nums[l] >= pivot) {
                l++;
            }
            if (nums[r] <= pivot) {
                r--;
            }
        }
        swap(nums[left], nums[r]);
        return r;
    }
};
```

## Merge sort

- Using two pointer to merge
```c++
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int index = m+n-1;
        int ptr1 = m-1;
        int ptr2 = n-1;
        while(ptr1 >=0 || ptr2 >=0){
            int int1 = ptr1 < 0 ? INT_MIN : nums1[ptr1];
            int int2 = ptr2 < 0 ? INT_MIN : nums2[ptr2];
            if(int1 > int2){
                nums1[index--] = int1;
                ptr1--;
            } else {
                nums1[index--] = int2;
                ptr2--;
            }
        }
    }
};
```

## Insert sort


## Bubble sort


## Selectiong sort


## topological sort


## Mono stack



## Mono queue




## Trie - Prefix Tree

```c++
// Typical Trie Node design

struct TrieNode {

    // using the is_end as a indicator of existence
    bool is_end;
    struct TrieNode* links[26];
    TrieNode() {
        is_end = false;
        for(int i=0;i<26;i++){
            links[i] = nullptr;
        }
    }
    bool containsKey(char x){
        return links[x-'a'] != nullptr;
    }
    void put(char x, TrieNode* node){
        links[x-'a'] = node;
    }

    TrieNode* get(char x){
        return links[x-'a'];
    }

    bool isEnd(){
        return is_end;
    }
    void setEnd(){
        is_end = true;
    }
};

class Trie {

public:

    TrieNode* root;

    /** Initialize your data structure here. */
    Trie() {
        root = new TrieNode();
    }
    
    /** Inserts a word into the trie. */
    void insert(string word) {
        TrieNode* node_ptr;
        node_ptr = root;
        for(int i=0;i<word.length();i++){
            if(!node_ptr->containsKey(word[i])){
                TrieNode* new_node = new TrieNode();
                node_ptr->put(word[i], new_node);
            }
            node_ptr = node_ptr->get(word[i]);
        }
        node_ptr->setEnd();
    }
    
    /** Returns if the word is in the trie. */
    bool search(string word) {
        TrieNode* node_ptr;
        node_ptr = root;
        for(int i=0;i<word.length();i++){
            if(!node_ptr->containsKey(word[i])){
                return false;
            }
            node_ptr = node_ptr->get(word[i]);
        }
        if(node_ptr->isEnd())
            return true;
        else
            return false;
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        TrieNode* node_ptr;
        node_ptr = root;
        for(int i=0;i<prefix.length();i++){
            if(!node_ptr->containsKey(prefix[i])){
                return false;
            }
            node_ptr = node_ptr->get(prefix[i]);
        }
        return true;
    }
};


```

## Tree Traverse

### Inorder

- Iterative
```c++
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        stack<TreeNode*> my_stack;
        vector<int> ret;
        while(root!=nullptr || !my_stack.empty()){
            while(root!=nullptr){
                my_stack.push(root);
                root = root->left;
            }
            root = my_stack.top();
            my_stack.pop();
            ret.push_back(root->val);
            root = root->right;
        }
        return ret;
    }
};
```
- recursive
```c++
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> nodes;
        inorder(root, nodes);
        return nodes;
    }
private:
    void inorder(TreeNode* root, vector<int>& nodes) {
        if (!root) {
            return;
        }
        inorder(root -> left, nodes);
        nodes.push_back(root -> val);
        inorder(root -> right, nodes);
    }
};
```


### Preorder

- Iterative
```c++
class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        stack<TreeNode*> my_stack;
        vector<int> ret;
        if(root==nullptr){
            return ret;
        }
        my_stack.push(root);
        while(!my_stack.empty()){
            TreeNode* top = my_stack.top();
            ret.push_back(top->val);
            my_stack.pop();
            if(top->right){
                my_stack.push(top->right);
            }
            if(top->left){
                my_stack.push(top->left);
            }
        }
        return ret;
    }
};
```


### Postorder

- Iterative
```c++
class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> ret;
        if(root==nullptr){
            return ret;
        }
        stack<TreeNode*> my_stack;
        my_stack.push(root);
        while(!my_stack.empty()){
            TreeNode* top = my_stack.top();
            ret.push_back(top->val);
            my_stack.pop();
            if(top->left){
                my_stack.push(top->left);
            }
            if(top->right){
                my_stack.push(top->right);
            }
        }
        return vector<int>(ret.rbegin(), ret.rend());
    }
};
```


## Boyer-Moore Voting Algorithm

- used to find the majority element

