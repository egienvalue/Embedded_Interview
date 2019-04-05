
#include <vector>
#include <map>
#include <stack>

using namespace std;

struct TreeNode{
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
};


vector<int> result;
void pre_order(TreeNode* root){
    if(root == nullptr)
        return;
    result.push_back(root->val);
    pre_order(root->left);
    pre_order(root->right);
}

vector<int> in_order_iter(TreeNode* root){
    stack<TreeNode*> my_stack;
    vector<int> result;

    while(!root || !my_stack.empty()){
        while(root){
            my_stack.push(root);
            root = root->left;
        }
        result.push_back(my_stack.top()->val);
        my_stack.pop();
        root = root->right;
    }

    return result;
}

vector<int> pre_order_iter(TreeNode* root){
    stack<TreeNode*> my_stack;
    vector<int> result;
    my_stack.push(root);
    while(!my_stack.empty()){
        result.push_back(my_stack.top()->val);
        my_stack.pop();
        if(root->right)
            my_stack.push(root->right);
        if(root->left)
            my_stack.push(root->left);
    }
    return result;
}

vector<int> post_order_iter(TreeNode* root){
    stack<TreeNode*> my_stack;
    vector<int> result;
    

}

template<class Item>
void push(Item new_item){
    heap.push_back(new_item);
    _heap_size ++;
    fixUp(heap, heap_size);
}

template<class Item>
void pop(){
    heap.pop_back();
    _heap_size--;
    fixDown(heap, 1);

}


template<class Item>
void fixUp(vector<Item> heap, int k){
    while(k>1 && heap[k] > heap[k/2]){
        swap(heap[k], heap[k/2]);
        k /= 2;
    }

}

template<class Item>
void fixDown(vector<Item> heap, int k){
    while(k*2 < heap.size()){
        // find the left child index
        int j = k*2;
        // compare which child is larger
        if(heap[j] < heap[j+1]) j++;

        // check if need to swap with the parent and child
        if(heap[k] >= heap[j])
            break;
        swap(heap[j], heap[k]);
        k = j;
    }
}

int partition_quick(vector<int>nums, int left, int right){
    int pivot = nums[right];
    int l = left;
    int r = right-1;
    while(true){
        while(nums[l]>pivot)  l++;
        while(l < r && nums[r]<pivot)  r--;
        if(l >= r){
            break;
        }
        swap(nums[l], nums[r]);
    }
    // here we can only swap with the left because the nums[l] must be higher than the pivot
    swap(nums[right], nums[l]);
    return l;
}


int partition(vector<int> nums, int left, int right){
    int pivot = nums[left];
    int l = left +1;
    int r = right;
    while(l <= r){
        if(nums[l] < pivot && nums[r] > pivot){
            swap(nums[l], nums[r]);
            l++;
            r--;
        }
        if(nums[l] > pivot){
            l++;
        }
        if(nums[r] < pivot){
            r--;
        }
    }
    swap(nums[left], nums[r]);

}



int test1(vector<int> nums, int k){
    map<int, int> my_map;
    vector<int> cumu_product(nums.size()+1,1);
    my_map[1]=1;
    int cu_product=1;
    int result=0;
    for(int i=1;i<nums.size();i++){
        cumu_product[i] = nums[i-1] * cumu_product[i-1];
    }
    for(int i=0;i<cumu_product.size()-1;i++){
        for(int j=i+1;j<cumu_product.size();j++){
            if(cumu_product[j] / cumu_product[i] <=k){
                result++;
            }
        }
    }
    return result;
}

int numSubarrayProductLessThanK(vector<int>& nums, int k) {
    if (k <= 1) return 0;
    int n = nums.size(), prod = 1, ans = 0, left = 0;
    for (int i = 0; i < n; i++) {
        prod *= nums[i];
        while (prod >= k) prod /= nums[left++];
        ans += i - left + 1;
    }
    return ans;
}

static int GCD(int a, int b) {
    if(b==0) return a;
    else return GCD(b, a%b);
}

int calculateRotorConfiguration(int rotorCount, int minRotorValue, int maxRotorValue){

    for(int i=minRotorValue;i<=maxRotorValue;i++){
        int count =0;
        for(int j=minRotorValue;j<=maxRotorValue;j++){
            if(i!=j && GCD(i,j) == 1) 

        }

    }

}


void helper(TreeNode* root, int & sum){
    if(root==nullptr){
        return ;
    }
    helper(root->right);
    root->val = sum + root->val;
    helper(root->left);
}


struct Folder{
    string name;
    bool is_file;
    list<Folder*> sub_folder;
}

Folder* root;

// path = A -> B -> C;
vector<string> get_all_file(vector<string>path, Folder* root){
    Folder* cur = root;
    for(int i=0;i<path.length();i++){
        for(auto & x: cur->sub_folder){
            if(x->name = path[i]){
                cur = x;
                break;
            }
        }
    }
}


int node_dist_BST(TreeNode* root, TreeNode* p1, TreeNode* p2, int& dist1, int& dist2){


}

class Package{

public:

    string getID(){

    }


}

class Locker{

public:


    Locker(int row, int col){
        locker_matrix = vector<vector<string>>

    }

    bool store(Package pk1){


    }

    bool get(string Pkg_ID, string pass_word){



    }

    void{




    }

private:

    vector<vector<string>> locker_matrix;

}