//////////////////////////////////////
//           Author : Hasan         //
//              CSE,BUET            //
//////////////////////////////////////
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/detail/standard_policies.hpp>
#include<unordered_map>

using namespace std;

using namespace __gnu_pbds;

#define ll long long
#define N 300005
#define M 1000005
#define pb push_back
#define rep(i,n,m) for(int i = n; i < m; i++)
#define reps(i,n,m) for(int i = n;i >= m; i--)
#define sc scanf
#define pc printf

typedef tree<
int,
null_type,
less<int>,
rb_tree_tag,
tree_order_statistics_node_update>
ordered_set;

int n,m;
ll val[N],btree[N],divisors[M];
set<int>st;

void init(){
    rep(i,1,M){
        for(int j = i; j < M; j += i){
            divisors[j]++;
        }
    }
}

void update(int idx, ll x)
{
       while(idx<=n)
       {
             btree[idx]+=x;
             idx += idx & (-idx);
       }
}

ll query(int idx){
       ll sum=0;
       while(idx>0){
             sum+=btree[idx];
             idx -= idx & (-idx);
       }
       return sum;
}

int main()
{
    init();

    sc("%d%d",&n,&m);

    rep(i,1,n+1) sc("%lld",&val[i]),st.insert(i),update(i,val[i]);

    while(m--){
        int t,l,r;
        sc("%d%d%d",&t,&l,&r);
        if(t == 1){
            set<int>::iterator it = st.lower_bound(l);
            while(it != st.end() && *it <= r){
                update(*it,-val[*it]);
                val[*it] = divisors[val[*it]];
                update(*it,val[*it]);
                //because if it is 2 the number of divisors of that number
                //is always same
                //so no need to traverse this index
                //thus reducing time complexity
                if(val[*it] <= 2) it = st.erase(it);
                else it++;
            }
        }
        else{
            pc("%lld\n",query(r)-query(l-1));
        }
    }




    return 0;
}



