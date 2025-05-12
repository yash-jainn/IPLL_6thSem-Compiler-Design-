// Test arrays, pointers and memory operations
void main() begin
    integer arr[10];
    integer i = 0;
    integer *p;
    
    // Initialize array
   for(i=0;i<10;i=i+1) begin
        arr[i] = i * i;
        i = i + 1;
    end
    
    // Use pointer operations
    p = &arr[5];
    integer val = *p;
    *p = val + 10;
    
    // Array indexing with expressions
    integer j = 3;
    integer k = arr[j + 1] - arr[j - 1];
end