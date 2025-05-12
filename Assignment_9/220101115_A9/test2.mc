// Test basic arithmetic, assignment, and type conversion
void main()
 begin
    integer a = 10;
    integer b = 5;
    float c = 2.5;
    
    integer result1 = a + b * 2;
    float result2 = result1 / c;
    
    a = a + 1;
    b = b - 1;
    
    integer d = a * b + (a - b);
    float e = d / 2.0;
end