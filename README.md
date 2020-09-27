# Catalan-Sequence
        Write a multi-threaded program that computes the Catalan number sequence
        (http://mathworld.wolfram.com/CatalanNumber.html) and writes thosenumbers in fixed
        point format to a file called “catalan.dat”. Your program should take two command
        line arguments: the first specifies the number of Catalan numbers to generate and 
        the second specifies the number of threads to use to compute the Catalan number 
        sequence; you can assume a maximum of fourthreads.Create a way to balance the
        load among the threads.You mustuse the “long double” type to get the largest range
        possible; the Catalan numbers grow very quickly.Output must be in ascending order
        (fixed point format) in the file “catalan.dat”
