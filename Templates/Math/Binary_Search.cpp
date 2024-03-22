int left = 0,
right = max(n, m) + 17,
ans = -1;
while (left <= right){ 
  int mid = left + (right - left)/2; //avoids overflow 
  if (works(mid)) {
    ans = mid;
    right = mid - 1;
  } 
  else { 
    left = mid + 1;
  }
}
cout << ans << endl;
