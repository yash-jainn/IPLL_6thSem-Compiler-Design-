// Test file for microC parser
// Testing comments

/* This is a multi-line
   comment to test */

// Testing function declaration
integer add(integer a, integer b) 
begin
    return a + b;
end

// Testing void function with pointer
integer add(integer a, integer b) 
begin
    return a + b;
end


// Testing main function with compound statements
integer main() 
begin
    // Variable declarations
    integer i;
    float result = 0.0;
    
    // Testing assignment
    i = 0;
    
    // Testing for loop
    for(i = 0; i < 10; i = i + 1)
    begin
        result = result + i;
    end

    
    // Testing while loop

    while(i > 0)
    begin
        i = i - 1;
    end
    
    // Testing do-while loop
    do
    begin
        result = result + 1.0;
    end while(result < 20.0);
    
    // Testing if-else
    if(result > 15.0)
    begin
        result = 15.0;
    end
    else
    begin
        result = 10.0;
    end
    
    // Testing conditional expression
    result = (i > 5) ? 10.0 : 5.0;
    
    // Testing function call
    i = add(5, 3);
    
    // Testing array access
    arr[0] = 42;
    
    // Testing pointer operations
    char* ptr;
    ptr->i = 10;
    
    // Testing various expressions
    result = 5 + 3 * 2;
    result = (5 + 3) * 2;
    i = 10 && 5;
    i = 10 || 5;
    i = 10 && 5;
    i = 10 || 0;
    i = !0;
    
    
    return 0;
end



