
#include "library.h"
#include <stdio.h>

namespace cam
{
 inline namespace v1{
    void A::show()
    {
        printf("A::v1\n");
    }
}

//  namespace v2{
//     void A::show()
//     {
//         printf("A::v2\n");
//     }
// }
}