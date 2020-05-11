#include <string>
#include <vector>

class Solution{
public:
    std::vector<std::string> generateParenthesis(int n){
        std::vector<std::string> result;
        generate("", n, n, result);
        return result;
    }
private:
    void generate(std::string item, int left, int right, 
                    std::vector<std::string> &result){
        if(left==0&&right==0){
            result.push_back(item);
            return;
        }
        if(left>0){
            generate(item+'(', left-1, right, result);
        }
        if(left<right){
            generate(item+')', left, right-1, result);
        }
        
    }
};
