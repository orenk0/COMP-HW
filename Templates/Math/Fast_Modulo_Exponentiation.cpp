/*
Fast Modulo exponentiation, calculate 𝑎^𝑏  𝑚𝑜𝑑 𝑚 in 𝑂(log⁡𝑏).
It uses binary expansion of b, and is very straightforward.
*/

ll expo(ll a, ll b, ll m) {
  ll res = 1;
  while (b > 0) {
    if (b & 1) {
      res *= a;
      res %= m; 
    }    
    a *= a;
    a %= m; 
    b >>= 1; 
  } 
  return res;
}
