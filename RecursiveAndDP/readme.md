

## 139. Word Break

### Description


### Solution-1 O(N^2)-O(N) DFS+Memorization

Here we can use the DFS (recursive) to search the right way to break the word. Every time when we encountered a word int the string belongs to the wordDict, we search the rest of string. (使用DFS时关键在于利用memorization进行 优化 去除不必要的搜索，这里关键在于观察递归函数的调用，就发现了可能会有冗余)

```c++
class Solution {
public:
    
    map<string,int> my_map;
    unordered_set<int> hash_set; // Space O(N)
    int max_len=0;
    
    bool helper(string s, int index){
        bool ret = false;
        if(index==s.length())
            return true;
        for(int i=index;i<s.length();i++){
            //如果没有搜过 那么尝试去搜索
            //这里的搜索 每当发现 有一个 word可以break出来之后就继续搜素这个word之后的剩余的string是否可以break出来 
            if(hash_set.find(i)==hash_set.end()){
                if(my_map[s.substr(index,i-index+1)]){
                    // 可以很容易看出这里有冗余的搜索，helper(s,i+1), 使用recursive的时候，其实传进去这里i的值 在很多call中都是一样的 所以这里我们用一个hash_set 来记录已经search过的index 
                    ret = ret || helper(s,i+1);
                    // 添加已经搜过的位置
                    hash_set.insert(i);
                }
            }
        }
        return ret;
    }
    
    bool wordBreak(string s, vector<string>& wordDict) {
        for(int i=0;i<wordDict.size();i++){
            my_map[wordDict[i]] = 1;
            max_len = max(max_len, (int)wordDict[i].length());
        }
        return helper(s,0);
    }
};

```
### Solution-2 O(N^2)-O(N) DP

We use a boolean vector dp[]. dp[i] is set to true if a valid word (word sequence) ends at index i. The optimization is to look from current position i back and only substring and do dictionary look up in case the preceding position j with dp[j] == true is found.

```c++
class Solution {
public:
    
    map<string,int> hash_table;
    bool wordBreak(string s, vector<string>& wordDict) {
        vector<bool> dp(s.length()+1, false);
        for(int i=0;i<wordDict.size();i++){
            hash_table[wordDict[i]]=1;
        }
        // ends at index 0 means "" is true in our case;
        dp[0]= true;
        for(int i=1;i<=s.length();i++){
            for(int j=0;j<i;j++){
                // get the sub_str from index j to index i-1, because we have already know if the string ends at index j can be broken from dp[j]
                string temp_string = s.substr(j,i-j);
                if(dp[j] && hash_table[temp_string]){
                    dp[i]=true;
                    break;
                }  
            }   
        }
        return dp[s.length()];
        
    }
};


```