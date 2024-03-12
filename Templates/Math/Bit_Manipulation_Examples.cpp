/* 
Let 𝑛,𝑥. Solve the following tasks.

Q: Set the 𝑥’th bit of 𝑛  to 1.
A: 𝑛=𝑛|(1≪𝑥)
  
Q: Set the 𝑥’th bit of 𝑛  to 0.
A: 𝑛=𝑛 & ~(1≪𝑥)

Q: Flip the 𝑥’th bit of 𝑛.
A: 𝑛=𝑛^(1≪𝑥)
  
Q: Check if the 𝑥’th bit of 𝑛 is 1.
A: bool=(𝑛≫𝑥)  & 1

Q: Given 𝑘, check if 2^𝑘 divides 𝑛.
A: bool=𝑛 & ((1≪𝑘)−1)==0
  
Q: Check if 𝑛 is a power of 2.
A: bool=𝑛 &&  !(𝑛 & (𝑛−1))

Q: Set the rightmost bit of 𝑛 to 0.
A: n=𝑛 & (𝑛−1)

  
Q: Count the number of 1’s in 𝑛
int countSetBits(int n){
  int count = 0;
  while (n){ 
    n = n & (n - 1); 
    count++;  
  }  
  return count;
}

*/

