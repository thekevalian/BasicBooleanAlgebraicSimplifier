# Algorithm of Boolean Logic Simplifier

I tried to implement the [Quine McCluskey Algorithm](http://www.cs.columbia.edu/~cs4823/handouts/quine-mccluskey-handout.pdf). \
Input:  minterms\
Output: simplified boolean expression\
I based my implementation from the paper above and a modification of the [Kernighan's Algorithm](https://iq.opengenus.org/brian-kernighan-algorithm/). 
# Methodology
1. Represent each bit of each minterm as two bits. We will allow them to be the following values and they will mean
- 0 -> 00
- 1 -> 01
- X -> 10 (Don't Care)
- \- -> 11 (Useful when determining prime implicants)
    - For example:
      - 5 -> (3 bytes of 0s) 0 0 0 0 0 1 0 1 => (6 bytes of 0s) 00 00 00 00 00 00 01 00 01
    - Input size will be constrained to 32 inputs since maximum minterm will be $(2^{32}-1) = 4294967295$ which requires 32 bits to represent
    - For simplicity, I will also let the output be limited to 32 bits
1. For each minterm, 


# Todo:
1. Create the class that implements Methodology Step 1