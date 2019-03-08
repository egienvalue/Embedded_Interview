
#include <vector>
#include <map>
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