#include "util_util_test.h"

void __Test__Util()
{
    MCError e;
    if ((e = TestSameAsSet()) != mcet::NoErr)
    {
        std::cout << e.DisplayError() << std::endl;
    }
}

MCError TestSameAsSet()
{
    int *a, *b;

    // true

    a = new int[5]{1, 2, 3, 4, 5};
    b = new int[5]{1, 2, 3, 4, 5};
    if (!SameAsSet(a, b, 5))
        return mcet::genTestErr("SameAsSet is wrong in true case 1");

    a = new int[5]{1, 2, 3, 4, 5};
    b = new int[5]{1, 2, 3, 5, 4};
    if (!SameAsSet(a, b, 5))
        return mcet::genTestErr("SameAsSet is wrong in true case 2");

    a = new int[5]{1, 2, 3, 4, 5};
    b = new int[5]{3, 5, 1, 4, 2};
    if (!SameAsSet(a, b, 5))
        return mcet::genTestErr("SameAsSet is wrong in true case 3");

    // false test

    a = new int[5]{1, 2, 3, 4, 5};
    b = new int[5]{1, 2, 3, 4, 6};
    if (SameAsSet(a, b, 5))
        return mcet::genTestErr("SameAsSet is wrong in false case 1");

    a = new int[5]{1, 2, 3, 4, 5};
    b = new int[5]{5, 4, 3, 2, 3};
    if (SameAsSet(a, b, 5))
        return mcet::genTestErr("SameAsSet is wrong in false case 2");

    a = new int[5]{1, 2, 3, 4, 5};
    b = new int[5]{1, 2, 3, 4, 4};
    if (SameAsSet(a, b, 5))
        return mcet::genTestErr("SameAsSet is wrong in false case 3");

    return mcet::NoErr;
}