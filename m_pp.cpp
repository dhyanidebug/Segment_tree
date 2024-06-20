#include<iostream>
#include<vector>
using namespace std;
#define ll long long

void merge(pair<ll,ll>&l, pair<ll,ll>&r,pair<ll,ll>&node )
{
    vector<ll>v;
    v.push_back(l.first);
    v.push_back(l.second);
    v.push_back(r.first);
    v.push_back(r.second);
    sort(v.begin(),v.end());
    node.first = v[3];
    node.second = v[2];
    return;
    
}
void build(vector<pair<ll,ll>>&tree,  vector<ll>&a, int s, int e, int node){
    if(s==e){
        tree[node] = {a[s],0};
        return;
    }
    ll mid = s + (e-s)/2;
    build(tree,a,s,mid,2*node);
    build(tree,a,mid+1,e,2*node+1);
    merge(tree[2*node], tree[2*node+1], tree[node]);
    return ;
}
pair<ll,ll> query(ll l, ll r,ll s, ll e,ll node,vector<pair<ll,ll>>&tree){
     if (r < s || l > e) {
            return {INT_MIN, INT_MIN};
        }
    if (l <= s && e <= r) {
            return tree[node];
        }
    ll mid = s + (e-s)/2;
    pair<ll,ll>left= query(l,r,s,mid,2*node,tree);
    pair<ll,ll>right= query(l,r,mid+1,e,2*node+1,tree);
    pair<ll,ll>val{0,0};
    merge(left,right,val);
    return val;
    
}
int main(){ 
    vector<ll>a{ 1, 3, 4, 2, 5,6 };
    ll n = a.size();
    // cout<<n<<"\n";
    vector<pair<ll,ll>>tree(4*n);
    build(tree, a, 0,n-1,1);
    ll l =2;
    ll r = 5;
    pair<ll,ll>t=query(l,r,0,n-1,1,tree);
    cout<<t.first * t.second<<"\n";
    return 0;

    // return 0;
}