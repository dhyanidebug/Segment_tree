#include<iostream>
#include<vector>
using namespace std;
typedef pair<int,int> node_type;
node_type merge(node_type l, node_type r){
       int min_el = min(l.first,r.first);
       int max_el = max(l.second,r.second);
       return {min_el,max_el};
    }
node_type query(int start,int end, int node, int left, int right,vector<node_type>&tree){
        if(left==start && right==end) return tree[node];
        if(left>right) return {INT_MAX,INT_MIN};
        int mid = start + (end-start)/2;
        node_type l= query(start,mid,2*node,left,min(right,mid),tree) ;
        node_type r=query(mid+1,end,2*node+1,max(mid+1,left),right, tree);
        return merge(l,r);
    }
void build_tree(vector<int>&nums,int start, int end, int node,vector<node_type>&tree){
        if(start==end){
            tree[node] = {nums[start],nums[start]};
            return;
        }
        int mid = start + (end-start)/2;
        build_tree(nums,start,mid,2*node,tree);
        build_tree(nums,mid+1,end,2*node+1,tree);
        tree[node]= merge(tree[2*node], tree[2*node+1]);
    }
void update_tree(int start, int end, int node, int idx, int val,vector<node_type>&tree){
        if(start == idx && end == idx){
            tree[node] ={val,val};
            return;
        }
        int mid = start + (end-start)/2;
        if(idx <=mid) update_tree(start,mid,2*node,idx,val,tree);
        else update_tree(mid+1,end,2*node+1,idx,val,tree);
        tree[node]= merge(tree[2*node], tree[2*node+1]);

    }
int main(){
    vector<int> nums;
    nums.push_back(1);
    nums.push_back(3);
    nums.push_back(4);
    nums.push_back(2);
    nums.push_back(5);
    nums.push_back(6);
    // [1,3,4,2,5,6]
    int n= nums.size();
    vector<node_type>tree(4*n);
    build_tree(nums, 0, n-1, 1,tree);
    while(1){
        cout<<"Press 1 for update and 2 for query and any other key for exit:  ";
        int type;
        cin>>type;
        cout<<"\n";
        if(type==1){
            int ind,val;
            cout<<"index to be updated: ";
            cin>> ind;
            cout<<"\n value to be updated: ";
            cin>>val;
            update_tree( 0, n-1, 1, ind, val,tree);
            nums[ind]=val;
            cout<<"updated nums is\n";
            for(int x : nums){
                cout<<x<<" ";
            }
            cout<<"\n";
        }
        else if(type==2){
            int left,right;
            cout<<" Left value: ";
            cin>> left;
            cout<<"\n Right value ";
            cin>> right;
            node_type result = query(0,n-1,1,left,right,tree);
            cout << "Query result: " << result.first<<" "<<result.second << "\n";
        }
        else break;

    }
    return 0;
}

