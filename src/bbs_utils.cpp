#include "bbs_utils.hpp"
#include <cmath>

namespace bbs_utils {
    std::pair<unsigned long, unsigned long> naiveFactor(unsigned long n)
    {
       unsigned long limit = static_cast<unsigned long>(std::sqrt((long double)n));
       for (unsigned long i = 2; i < limit; i++)
       {
           if (n % i == 0)
           {
               return std::make_pair(i, n / i);
           }
       } return{0, 0};
    }
} // namespace bbs_utils
