
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