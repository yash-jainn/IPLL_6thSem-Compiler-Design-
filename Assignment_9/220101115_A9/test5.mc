// Simple function to calculate factorial
integer factorial(integer n)
 begin
    if (n <= 1) 
    begin
        return 1;
    end 
    else 
    begin
        return n * factorial(n - 1);
    end
end

// Function to check if a number is prime
integer isPrime(integer num) begin
    if (num <= 1)
     begin
        return 0;
    end
    
    integer i;
    for( i = 2 ;i*i<=num;i=i+1 ) 
    begin
        if (num % i == 0) 
        begin
            return 0;
        end
       
    end
    return 1;
end

// Main function with nested blocks and function calls
void main() begin
    integer n = 5;
    integer fact = factorial(n);
    
    begin
        integer i = 10;
        integer j = 20;
        integer k = i + j;
        
        if (isPrime(k)) begin
            fact = fact + k;
        end
        
        begin
            float x = 3.14;
            float y = x * k;
        end
    end
    
    integer result = fact;
end