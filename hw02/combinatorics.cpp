#include "combinatorics.h"


uint64_t factorial(uint64_t val) {
    if (val==0)
        return 1;
    if (val < 3)
        return val;
    return val * factorial(val - 1);
}


uint64_t permutation(uint64_t val, uint64_t val2) {

    if(numbersCheck(val,val2))
        return factorial(val)/factorial(val - val2);
    return 0;
}

bool numbersCheck(uint64_t val, uint64_t val2)
{
    return val >= val2;
}

uint64_t combination(uint64_t val, uint64_t val2) {
    if(numbersCheck(val,val2))
        return factorial(val)/(factorial(val2) * factorial(val - val2));
    return 0;
}
