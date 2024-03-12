/* DSU (Union Find) - (OPTIMIZED IMPLEMENTATION IS LAST ONE)

We are given several elements, each of which is a separate set.
A DSU will have an operation to combine any two sets, and it will be able to tell in which set a specific element is.

We will store the sets in the form of trees: each tree will correspond to one set.
The root of the tree will be the representative/leader of the set.

For the implementation this means that we will have to maintain an array parent that stores a reference to its immediate ancestor in the tree.

*/

struct dsu {    
  vector<int> parent;
  vector<int> size_;

  dsu(int n) {
    parent.resize(n);
    iota(parent.begin(), parent.end(), 0);
    size_.resize(n, 1);
  }

  int find_(int x) {
    return x == parent[x] ? x : parent[x] = find_(parent[x]);
  }

};

bool union_(int x,int y) {
  int X = find_(x), Y = find_(y);
  if (X == Y) {
    return false;
  }
  if (size_[X] < size_[Y]) {
    swap(X, Y);
  }
  parent[Y] = X;
  size_[X] += size_[Y];
  return true;
}

// Naive Implementation: It is easy to construct an example, so that the trees degenerate into long chains.
// In that case each call find_set(v) can take O(n) time. 


void make_set(int v) {
    parent[v] = v;
}

int find_set(int v) {
    if (v == parent[v])
        return v;
    return find_set(parent[v]);
}

void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b)
        parent[b] = a;
}

struct UnionFind {
   vector<int> C;
   UnionFind(int n) : C(n) { for (int i = 0; i < n; i++) C[i] = i; }
   int find(int x) { return (C[x] == x) ? x : C[x] = find(C[x]); }
   void merge(int x, int y) { C[find(x)] = find(y); }
};


// OPTIMIZED IMPLEMENTATION: path compression with union by size / rank

//DSU
struct dsu
{
    vector<int> parent;
    vector<int> sz;
    
    dsu(int n)
    {
        parent=vector<int>(n);
        for(int i=0;i<n;i++)parent[i]=i;
        sz=vector<int>(n,1);
    }
    
    int find_(int x)
    {
        int root=x;
        while(root!=parent[root])
            root=parent[root];
        
        //Path compression
        while(parent[x]!=root)
        {
            int p=parent[x];
            parent[x]=root;
            x=p;
        }
        return root;
    }
    bool union_(int x,int y)
    {
        int X=find_(x);
        int Y=find_(y);
        // x and y are already in the same set
        if(X==Y)
            return false;
        // x and y are not in same set, so we merge them
        if(sz[X]<sz[Y])
            swap(X, Y);
        // merge yRoot into xRoot
        parent[Y]=X;
        sz[X]+=sz[Y];
        return true;
    }
};
