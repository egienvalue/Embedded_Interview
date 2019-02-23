
# 

## 721. Accounts Merge

### Description

Given a list accounts, each element accounts[i] is a list of strings, where the first element accounts[i][0] is a name, and the rest of the elements are emails representing emails of the account.

Now, we would like to merge these accounts. Two accounts definitely belong to the same person if there is some email that is common to both accounts. Note that even if two accounts have the same name, they may belong to different people as people could have the same name. A person can have any number of accounts initially, but all of their accounts definitely have the same name.

After merging the accounts, return the accounts in the following format: the first element of each account is the name, and the rest of the elements are emails in sorted order. The accounts themselves can be returned in any order.

Example 1:
```
Input: 
accounts = [["John", "johnsmith@mail.com", "john00@mail.com"], ["John", "johnnybravo@mail.com"], ["John", "johnsmith@mail.com", "john_newyork@mail.com"], ["Mary", "mary@mail.com"]]
Output: [["John", 'john00@mail.com', 'john_newyork@mail.com', 'johnsmith@mail.com'],  ["John", "johnnybravo@mail.com"], ["Mary", "mary@mail.com"]]

Explanation: 
The first and third John's are the same person as they have the common email "johnsmith@mail.com".
The second John and Mary are different people as none of their email addresses are used by other accounts.
We could return these lists in any order, for example the answer [['Mary', 'mary@mail.com'], ['John', 'johnnybravo@mail.com'], 
['John', 'john00@mail.com', 'john_newyork@mail.com', 'johnsmith@mail.com']] would still be accepted.

Note:
The length of accounts will be in the range [1, 1000].
The length of accounts[i] will be in the range [1, 10].
The length of accounts[i][j] will be in the range [1, 30].
```

### Solution-1
```c++
class Solution {
public:
    
    vector<int> represents_map;
    
    
    int find(int ele){
        if(represents_map[ele] == ele){
            return ele;
        }    
        return represents_map[ele] = find(represents_map[ele]);
    }
    
    void self_union(int ele1, int ele2){
        represents_map[find(ele1)] = find(ele2);
    }
    
    
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        vector<vector<string>> ret;
        represents_map = vector<int>(accounts.size(),0);
        unordered_map<int, vector<string>> result;
        unordered_map<string, int> emailToID;
        for(int i=0;i<accounts.size();i++){
            represents_map[i]=i;
            set<string> temp(accounts[i].begin(), accounts[i].end());
            accounts[i] = vector<string>(temp.begin(), temp.end());
            for(int j=1;j<accounts[i].size();j++){
                if(emailToID.find(accounts[i][j]) != emailToID.end()){
                    self_union(i,emailToID[accounts[i][j]]);
                } else {
                    emailToID[accounts[i][j]] = i; 
                }
            }
        }
        for(auto &x : emailToID){
            int root = find(x.second);
            result[root].push_back(x.first);
        }
        for(auto &x : result){
            sort(x.second.begin(),x.second.end());
        }
        for(auto &x : result){
            vector<string> temp = x.second;
            temp.insert(temp.begin(), accounts[x.first][0]);
            ret.push_back(temp);
        }
        
        return ret;
    }
};

```