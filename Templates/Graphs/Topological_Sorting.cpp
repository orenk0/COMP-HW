int flag, v[..];
int od[..], p; // the final order
void dfs(int a) {
    if(v[a]==1) flag = 1;
    if(v[a]) return;
    v[a] = 1; // gray
    for each neighbor a -> i dfs(i);
    v[a] = 2; // black
    od[p] = a; p--;
}
// ...

for(i=0; i<n; i++) v[i]=0; //white
flag=0; p=n-1;
for(i=0; i<n; i++) if(!v[i])
dfs(i);
if(flag) // say there is a cycle;
