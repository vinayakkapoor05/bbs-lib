#ifndef BBS_UTILS_HPP
#define BBS_UTILS_HPP

#include <utility>

namespace bbs_utils
{
    // Naively factor n using trial division
    std::pair<unsigned long, unsigned long> naiveFactor (unsigned long n);  

} // namespace bbs_utils

#endif // BBS_UTILS_HPP