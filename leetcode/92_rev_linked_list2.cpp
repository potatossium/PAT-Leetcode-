/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* reverseBetween(ListNode* head, int m, int n){
        // Corner Condition
        int change_len = n-m+1;
        if(change_len<=1){
            return head;
        }
        ListNode *result = head;
        ListNode *pre_head = NULL;
        ListNode *end = NULL;

        int m_step = m;
        while (--m_step){
            pre_head = head;
            head = head->next;
        }
        end = head;

        ListNode *new_head = NULL;
        while(head && change_len--){
            ListNode *temp = head->next;
            head->next = new_head;
            new_head = head;
            head = temp;
        }
        end->next = head;
        if(pre_head){ 
            pre_head->next = new_head;
        }else{
            //pre_head==NULL，m=1
            result = new_head;
        }
        return result;
    }
        

};
