
# Sum 

## 1. Two Sum 

### Description
Given an array of integers, return indices of the two numbers such that they add up to a specific target.

You may assume that each input would have exactly one solution, and you may not use the same element twice.

Example:

```
Given nums = [2, 7, 11, 15], target = 9,

Because nums[0] + nums[1] = 2 + 7 = 9,
return [0, 1].
```

### Solution-1 O(n)-O(n)

We can use the hash table to search the target - current_val. {Key, Value} = {Value, Index+1}. When there is no Key existing, the value equals to zero.

```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        //sort(nums.begin(), nums.end());
        int left=0;
        int right=nums.size()-1;
        map<int,int> hash_table;
        for(int i=0;i<nums.size();i++){
            // 不等于0代表元素存在在hash table中，直接return
            if(hash_table[target - nums[i]] != 0){
                return {hash_table[target - nums[i]]-1, i};
            }
            // 使用 0 判断hash_tabl 中是否存在相应的key，因为第一个元素的index 为0 所以这里使用 i+1 去避免 
            hash_table[nums[i]] = i+1;
        }
        //这句话无所谓
        return {0,0};
    }
};
```

## 15. 3Sum

### Description

Given an array nums of n integers, are there elements a, b, c in nums such that a + b + c = 0? Find all unique triplets in the array which gives the sum of zero.

Note:

The solution set must not contain duplicate triplets.

Example:

```
Given array nums = [-1, 0, 1, 2, -1, -4],

A solution set is:
[
  [-1, 0, 1],
  [-1, -1, 2]
]
```

### Solution-1 O(N^2) - O(1)
Here we degrade the 3sum question to 2sum, we fix one of the value, and search the other two with two pointer in the sorted array. ***But using this way, we have to store each result we found in a set to avoid the duplicate triplet.***

```c++
class Solution {
public:

    vector<vector<int>> threeSum(vector<int>& nums) {
        if(nums.size() <=2){
            return {};
        }
        set<vector<int>> ret;
        sort(nums.begin(), nums.end());
        for(int i=0;i<nums.size()-2;i++){
            int target = 0;
            int left = i+1;
            int right = nums.size()-1;
            while(left < right){
                int sum = nums[left] + nums[right] + nums[i];
                // 如果大于 说明太大，唯一减小sum的方式就是right--;
                if(sum > target){
                    right--;
                } else if(sum == target){
                    ret.insert({nums[i], nums[left], nums[right]});
                    right--;
                    left++;
                // 如果小于 说明太小，唯一增大的方式就是left++;
                } else {
                    left++;
                }
                //cout << left << " " << right << endl;
            }
        }
        return vector<vector<int>>(ret.begin(), ret.end());
        
    }
};

```

### Solution-2 O(N^2) - O(1)

Solution2 will try to not use the set to void duplicate. The intuition is the same like solution1.

```c++
class Solution {
public:

    vector<vector<int>> threeSum(vector<int>& nums) {
        if(nums.size() <=2){
            return {};
        }
        vector<vector<int>> ret;
        sort(nums.begin(), nums.end());
        for(int i=0;i<nums.size()-2;i++){
            // 不能使用while循环找最后一个数，这样就会缺少{-1,-1,2}类似的triplet, 所以这里从duplicates number中的第一个开始访问
            if(i>0 && nums[i]==nums[i-1])
                continue;
            int target = 0;
            int left = i+1;
            int right = nums.size()-1;
            
            while(left < right){
                int sum = nums[left] + nums[right] + nums[i];
                // 如果大于 只有right--
                if(sum > target){
                    right--;

                // 如果等于 先添加数组到result中 然后跳过相同的元素
                } else if(sum == target){
                    ret.push_back({nums[i], nums[left], nums[right]});
                    // 找出一个之后通过while循环避免继续添加相同的元素。
                    while(nums[left]==nums[left+1]) left++;
                    while(nums[right]==nums[right-1]) right--;
                    right--;
                    left++;
                // 如果小于 只有left++
                } else {
                    left++;
                }
                //cout << left << " " << right << endl;
            }
        }
        return vector<vector<int>>(ret.begin(), ret.end());
        
    }
};

```

## 18. 4Sum

### Description

Given an array nums of n integers and an integer target, are there elements a, b, c, and d in nums such that a + b + c + d = target? Find all unique quadruplets in the array which gives the sum of target.

Note:

The solution set must not contain duplicate quadruplets.

Example:

```
Given array nums = [1, 0, -1, 0, -2, 2], and target = 0.

A solution set is:
[
  [-1,  0, 0, 1],
  [-2, -1, 1, 2],
  [-2,  0, 0, 2]
]
```

### Solution-1 O(N^3)

Actually, the 4Sum can also be degrade to the 2 sum question. Here we firstly fix the first two elements that the 4sum needs. Then we use the same mechanism of 2sum to search another 2 element.

```c++
class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int>> ret;
        if(nums.size()<4)
            return ret;
        sort(nums.begin(), nums.end());
        for(int first=0;first<nums.size()-3;first++){
            if(first > 0 && nums[first] == nums[first-1])
                continue;
            for(int second=first+1;second < nums.size()-2;second++){
                if(second > first+1 && nums[second] == nums[second-1])
                    continue;
                int left = second+1;
                int right = nums.size()-1;
                int my_target = target - nums[first] - nums[second];
                while(left < right){
                    int sum = nums[left] + nums[right];
                    if(sum == my_target){
                        ret.push_back({nums[first], nums[second], nums[left], nums[right]});
                        while(nums[left]==nums[left+1]) left++;
                        while(nums[right]==nums[right-1]) right--;
                        left++;
                        right--;
                    } else if(sum < my_target){
                        left++;
                    } else {
                        right--;
                    }
                }
            }
        }
        return ret;
    }
};
```

## 974. Subarray Sums Divisible by K

### Description
Given an array A of integers, return the number of (contiguous, non-empty) subarrays that have a sum divisible by K.

 

Example 1:
```
Input: A = [4,5,0,-2,-3,1], K = 5
Output: 7
Explanation: There are 7 subarrays with a sum divisible by K = 5:
[4, 5, 0, -2, -3, 1], [5], [5, 0], [5, 0, -2, -3], [0], [0, -2, -3], [-2, -3]
```

### Solution-1 

```c++
class Solution {
public:
    int subarraysDivByK(vector<int>& A, int K) {
        int m = A.size();
        vector<int> count(K,0);
        int cu_sum=0;
        for(int i=0;i<m;i++){
            cu_sum += A[i];
            count[(cu_sum%K + K)%K] ++;
        }
        int ret=0;
        for(auto &x: count){
            if(x>1)
                ret += x *(x-1)/2;
        }
        return ret + count[0];
    }
};
```

## 523. Continuous Subarray Sum


### Solution-1
```c++
class Solution {
public:
    bool checkSubarraySum(vector<int>& nums, int k) {
        int sum=0;
        unordered_map<int,int> my_map;
        my_map[0]=-1;
        for(int i=0;i<nums.size();i++){
            sum += nums[i];
            if(k!=0)
                sum = sum % k;
            if(my_map.find(sum) != my_map.end()){
                if(i-my_map[sum] > 1){
                    return true;
                }
            } else {
                my_map[sum] = i;
            }
        }
        return false;
    }
};

```


# Parenthesis related

## 678. Valid Parenthesis String

### Description 

Given a string containing only three types of characters: '(', ')' and '*', write a function to check whether this string is valid. We define the validity of a string by these rules:

Any left parenthesis '(' must have a corresponding right parenthesis ')'.
Any right parenthesis ')' must have a corresponding left parenthesis '('.
Left parenthesis '(' must go before the corresponding right parenthesis ')'.
'*' could be treated as a single right parenthesis ')' or a single left parenthesis '(' or an empty string.
An empty string is also valid.

Example 1:
```
Input: "()"
Output: True
```
Example 2:
```
Input: "(*)"
Output: True
```
Example 3:
```
Input: "(*))"
Output: True
```

### Solution-1
This solution is not so efficient, it use the DFS with Backtracking to check the validity.

```c++
// 第一种写法 比较好
class Solution {
public:
    
    bool result=false;
    bool helper(int index, string s, int pair){
        if(pair < 0)
            return false;
        if(index==s.length()){
            if(pair==0)
                return true;    
            return false;
        }
        if(s[index]=='('){
            return helper(index+1, s, pair+1);
        } else if(s[index]==')') {            
            return helper(index+1, s, pair-1);
        } else if(s[index]=='*'){
            return helper(index+1, s, pair+1) || helper(index+1, s, pair-1) || helper(index+1, s, pair);
        }
        return false;
        
    }
    
    bool checkValidString(string s) {
        return helper(0, s, 0);
    }
};
```

```c++
// 这种写法为 第一次的写法
class Solution {
public:
    
    bool result=false;
    void helper(int index, string s, int pair){

        // 需要匹配的括号数量为0 并且 index到达最长 说明valid
        if(index==s.length()){
            if(pair==0)
                result = true;
            return;
        }
        if(result == true){
            return;
        }
        // 发现前括号 pair数量+1
        if(s[index]=='('){
            helper(index+1, s, pair+1);
        } else if(s[index]==')') {

            // 如果有没有未匹配的 括号 直接return
            if(pair < 1){
                return;

            // 如果有匹配的括号 pair数量-1 继续搜索
            } else {
                helper(index+1, s, pair-1);
            }
        } else if(s[index]=='*'){
            
            // 依次检查3种情况
            helper(index+1, s,pair+1);
            
            if(pair>0){
                helper(index+1, s, pair-1);
            }
            
            helper(index+1, s, pair);
        } 
    }
    bool checkValidString(string s) {
        helper(0, s, 0);
        return result;
    }
};

```

### Solution-2
Using Dynamic Programming, we need to find the induction equation. 




# Product

## 238. Product of Array Except Self

### Description
Given an array nums of n integers where n > 1,  return an array output such that output[i] is equal to the product of all the elements of nums except nums[i].

Example:
```
Input:  [1,2,3,4]
Output: [24,12,8,6]
```
Note: Please solve it without division and in O(n).

Follow up:
Could you solve it with constant space complexity? (The output array does not count as extra space for the purpose of space complexity analysis.)

### Solution-1 O(N)-O(N)

Because we can't use the division here, so we need to calculate the cmulative product from left to right, and from right to left. Then stor them into two vectors. result[i] = prod_left[i-1] * prod_right[i+1]

```c++
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        vector<int> prod_left = nums;
        vector<int> prod_right = nums;
        vector<int> ret(nums.size(),0);
        for(int i=1;i<nums.size();i++){
            prod_left[i] = prod_left[i-1] * prod_left[i];
            prod_right[nums.size()-i-1] = prod_right[nums.size()-i] * prod_right[nums.size()-i-1];
        }
        for(int i=0;i<ret.size();i++){
            int left= i-1 < 0 ? 1 : prod_left[i-1];
            int right = i+1 > ret.size()-1 ? 1 : prod_right[i+1];
            ret[i] = left*right;
        }
        return ret;
    }
};
```

### Solution-2 O(N)-O(1)
In here, we do a very simple change. We don't need the vector to store the pre-computed value of the product of all elements in the left of our target position.

```c++
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int prod_left=1;
        int prod_right=1;
        vector<int> ret(nums.size(), 1);
        for(int i=0;i<nums.size();i++){
            ret[i] *= prod_left;
            prod_left *= nums[i];            
            ret[nums.size()-i-1] *= prod_right;
            prod_right *= nums[nums.size()-i-1];
        }
        return ret;
    }
};
```
# Longest Common Series

## 5. Longest Palindromic Substring

### Description
Given a string s, find the longest palindromic substring in s. You may assume that the maximum length of s is 1000.

Example 1:
```
Input: "babad"
Output: "bab"
Note: "aba" is also a valid answer.
```
Example 2:
```
Input: "cbbd"
Output: "bb"
```

### Solution-1 O(N^2)- O(N^2) DP 
This problem can be regarded as find longest common substring problem for string S and its reverse string S'. We use the DP to calculate. DP[i][j] mean the longest length of common suffix of two substrings, one ends in index i, one ends at index j. We use this mechanism to find the longest common substring.
We could see that the longest common substring method fails when there exists a reversed copy of a non-palindromic substring in some other part of S. To rectify this, each time we find a longest common substring candidate, we check if the substring’s indices are the same as the reversed substring’s original indices. If it is, then we attempt to update the longest palindrome found so far; if not, we skip this and find the next candidate.

```c++
class Solution {
public:
    string longestPalindrome(string s) {
        int n=s.length();
        int max_len=0;
        int idx=0;
        string reverse_s(s.rbegin(), s.rend());
        vector<vector<int>>dp(n+1, vector<int>(n+1,0));
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                //找到相同的之后 使用最长后缀的递归公式来算 直接+1
                if(s[i-1]==reverse_s[j-1]){
                    dp[i][j] = dp[i-1][j-1]+1;
                    // 这里的check 是为了避免S'中出现逆转之后有一段非回文的字符串和原始字符串中的一部分相同 所以需要做index检查(candidate的每个字符的index在 原始字符串中和在逆转字符串中相加应该等于n-1)
                    if( (j-1)-dp[i][j]+1 == n-1 - (i-1) && dp[i][j]>max_len){
                        max_len = dp[i][j];
                        idx = i-1-max_len+1;
                    }
                }
            }
        }
        return s.substr(idx, max_len);
    }
};

```


## 583. Delete Operation for Two Strings

### Description
Given two words word1 and word2, find the minimum number of steps required to make word1 and word2 the same, where in each step you can delete one character in either string.

Example 1:
```
Input: "sea", "eat"
Output: 2
Explanation: You need one step to make "sea" to "ea" and another step to make "eat" to "ea".
```
Note:

The length of given words won't exceed 500.
Characters in given words can only be lower-case letters.

### Solution-1 DP
We can regard this question as find the longest length of common non-consecutive characters array.

```c++
class Solution {
public:
    int minDistance(string word1, string word2) {
        int m = word1.size();
        int n = word2.size();
        vector<vector<int>> dp(m+1, vector<int>(n+1,0));
        for(int i=1;i<=m;i++){
            for(int j=1;j<=n;j++){
                if(word1[i-1]==word2[j-1]){
                    dp[i][j]= dp[i-1][j-1] +1;
                // 这里可以理解为当此时字母不一样时 最长的公共非连续的子字母串的长度取决于 word1少一个字母 或者word2少一个字母时的最长非连续子字母串
                } else {
                    dp[i][j]=max(dp[i-1][j], dp[i][j-1]);
                }
            }
        }
        return m+n - 2* dp[m][n];
    }
};
```



# Edit distance

## 161. One Edit Distance


### Description
Given two strings s and t, determine if they are both one edit distance apart.

Note: 

There are 3 possiblities to satisify one edit distance apart:

Insert a character into s to get t
Delete a character from s to get t
Replace a character of s to get t
Example 1:
```
Input: s = "ab", t = "acb"
Output: true
Explanation: We can insert 'c' into s to get t.
```
Example 2:
```
Input: s = "cab", t = "ad"
Output: false
Explanation: We cannot get t from s by only one step.
```
Example 3:
```
Input: s = "1203", t = "1213"
Output: true
Explanation: We can replace '0' with '1' to get t.
```

### Solution-1
```c++
class Solution {
public:
    bool isOneEditDistance(string s, string t) {
        int m=s.length();
        int n=t.length();
        if(s==t) return false;
        if(abs(m-n) > 1) return false;
        for(int i=0;i<min(m,n);i++){
            if(s[i]!=t[i]){
                // insert
                if(s.substr(i+1)==t.substr(i)) return true;
                // delete 
                if(s.substr(i)==t.substr(i+1)) return true;
                // replace
                if(s.substr(i+1)==t.substr(i+1)) return true;
                return false;
            }
        }
        return true;
    }
};
```

## 72. Edit Distance



# Calculator Series

## 227. Basic Calculator II

### Description
Implement a basic calculator to evaluate a simple expression string.

The expression string contains only non-negative integers, +, -, *, / operators and empty spaces . The integer division should truncate toward zero.

Example 1:
```
Input: "3+2*2"
Output: 7
Example 2:

Input: " 3/2 "
Output: 1
Example 3:

Input: " 3+5 / 2 "
Output: 5
Note:
```
You may assume that the given expression is always valid.
Do not use the eval built-in library function.

### Solution-1
Using stack to track
```c++
class Solution {
public:
    int calculate(string s) {
        stack<int> my_stack;
        int cu_num =0;
        int temp_num =0;
        char last_oper = '+';
        for(int i=0;i<=s.length();i++){
            if(i<s.length() && s[i]==' ')
                continue;
            if(i < s.length() && isdigit(s[i])){
                cu_num = cu_num*10 + s[i]-'0';
            } else {
                switch(last_oper){
                    case '+':
                        my_stack.push(cu_num);
                        break;
                    case '-':
                        my_stack.push(-cu_num);
                        break;
                    case '*':
                        temp_num = my_stack.top();
                        my_stack.pop();
                        temp_num = temp_num * cu_num;
                        my_stack.push(temp_num);
                        break;
                    case '/':
                        temp_num = my_stack.top();
                        my_stack.pop();
                        temp_num = temp_num / cu_num;
                        my_stack.push(temp_num);
                        break;
                    default:
                        break;
                }
                cu_num=0;
                last_oper = s[i];
            }
        }
        
        int ret=0;
        while(!my_stack.empty()){
            ret += my_stack.top();
            cout << my_stack.top() << endl;
            my_stack.pop();
        }
        return ret;
        
    }
};
```

### Solution-2

```c++
class Solution {
public:
    int calculate(string s) { 
        char last_oper = '+';
        s = s + "+";
        int cur_num = 0;
        int ret=0;
        for(int i=0;i<s.length();i++){
            if(isdigit(s[i])){
                int temp=0;
                while(isdigit(s[i])) {
                    if(s[i]!=' ')
                        temp = temp * 10 + s[i]-'0';
                    i++;
                }
                switch(last_oper){
                    case '+':
                        cur_num += temp;
                        break;
                    case '-':
                        cur_num -= temp;
                        break;
                    case '*':
                        cur_num *= temp;
                        break;
                    case '/':
                        cur_num = cur_num/temp;
                        break;
                }
                i--;
                
            } else if(s[i]!=' '){
                if(s[i]=='-' || s[i]=='+'){
                    ret += cur_num;
                    cout << cur_num << endl;
                    cur_num=0;
                }
                last_oper = s[i];
                
            }
        }
        return ret;
    }
};
```

# String Process

## 43. Multiply Strings

### Description




### Solution-1;
This is the traditional way to simulate mannully compute the result;
```c++
class Solution {
public:
    
    string sum(string num1, string num2){
        int ptr1=num1.length()-1;
        int ptr2=num2.length()-1;
        int carry = 0;
        int remain =0;
        string result = "";
        
        while(ptr1>=0 || ptr2>=0){
            int digit1 = ptr1 >=0 ? num1[ptr1]-'0' : 0;
            int digit2 = ptr2 >=0 ? num2[ptr2]-'0' : 0;
            //cout << digit1 << " " << digit2 << endl;
            remain = (digit1 + digit2 + carry) % 10;
            carry = (digit1 + digit2 + carry) / 10;
            //remain = (digit1 + digit2 + carry) % 10;
            result = to_string(remain) + result;
            ptr1--;
            ptr2--;
        }
        if(carry > 0){
            result = to_string(carry) + result;
        }
        return result;
    }
    
    string multiply_char(string num1, char char1){
        int ptr1 = num1.length()-1;
        int carry = 0;
        int remain = 0;
        int digit2 = char1 -'0';
        string result = "";
        for(;ptr1 >=0;ptr1 --){
            int digit1 = num1[ptr1] -'0';
            remain = (carry + digit1 * digit2) % 10;
            carry = (digit2 * digit1 + carry) /10;
            result = to_string(remain) + result;
        }
        if(carry > 0)
            result = to_string(carry) + result;
        return result;
    }
    string multiply(string num1, string num2) {
        string result="0";
        int count=0;
        if(num1=="0" || num2 == "0")
            return "0";
        //return sum(num1,num2);
        for(int i=num1.length()-1;i>=0;i--){
            string zero(count++, '0');
            string temp = multiply_char(num2,num1[i]) + zero;
            //cout << temp << endl;
            result = sum(temp, result);
        }
        return result;
    }
};
```

### Soluiton-2

```c++
class Solution {
public:
    string multiply(string num1, string num2) {
        int m = num1.length();
        int n = num2.length();
        if(num1 == "0" || num2 =="0")
            return "0";
        reverse(num1.begin(), num1.end());
        reverse(num2.begin(), num2.end());
        vector<int> result(m+n, 0);
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                // num1[i] and num2[j] contribute to result[i+j]
                result[i+j] += (num1[i]-'0') * (num2[j]-'0');
                // result[i+j] contribute to result[i+j+1] if it is greater than 10;
                result[i+j+1] += result[i+j] /10;
                // take the resedual of result[i+j];
                result[i+j] %= 10;
            }
        }
        string ret="";
        int i=result.size()-1;
        while(result[i]==0) i--;
        for(;i>=0;i--){
            ret += to_string(result[i]) ;
        }
        return ret;
    }
};
```