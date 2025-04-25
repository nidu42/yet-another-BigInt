# yet-another-BigInt
Just a BigInt class, potentially a library in future. A lot of things need to be added

## Attention!
C++23 required!

### Things I want to add and change:
1) Constructors: BigInt(const std::string&)
2) Operators: /, %, /=, %=, ++, --, >> and << for output
3) Support for std::format(), std::print
4) Functions: pow(), sqrt() (it will call root() function), root(), is_prime(), find_random_prime(), gcd(), phi(), divisors()
5) Modular arithmetic functions: pow_mod() (it also should work with negatives number if modulo and abs(number) are mutually prime), inv_mod()
6) Implement fast multiplication (maybe Karatsuba Algorithm) and try to make division faster
7) Reduce the amount of copying, use more move semantics if possible
8) Think further if reserve optimizations are really needed
9) Ask for code review in the end  
