cmake_minimum_required(VERSION 3.10)
project(bbs_lib CXX)

set(CMAKE_CXX_STANDARD 17)

# Toy BBS Library

add_library(bbs_toy STATIC src/bbs_toy.cpp)
target_include_directories(bbs_toy PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(toy_demo examples/toy_demo.cpp)
target_link_libraries(toy_demo PRIVATE bbs_toy)

# Production BBS Library (Uses GMP)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GMP REQUIRED gmp)

set(GMP_LIBRARY_DIRS "/opt/homebrew/Cellar/gmp/6.3.0/lib")

add_library(bbs_production STATIC src/bbs_production.cpp)
target_include_directories(bbs_production
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
           ${GMP_INCLUDE_DIRS}
)

target_link_directories(bbs_production PUBLIC ${GMP_LIBRARY_DIRS})

target_link_libraries(bbs_production PUBLIC gmp gmpxx)

add_executable(production_demo examples/production_demo.cpp)
target_link_libraries(production_demo PRIVATE bbs_production)

add_executable(encryption_demo examples/encryption_demo.cpp)
target_link_libraries(encryption_demo PRIVATE bbs_production)


# Utils Library (for cryptanalysis)

add_library(bbs_utils STATIC 
    src/bbs_utils.cpp
)
target_include_directories(bbs_utils 
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(factor_demo examples/factor_demo.cpp)
target_link_libraries(factor_demo PRIVATE bbs_toy bbs_utils)


add_executable(partial_seed_demo examples/partial_seed_demo.cpp)
target_link_libraries(partial_seed_demo PRIVATE bbs_toy)


# Side-Channel Library & Demo


add_library(bbs_sidechannel STATIC 
    src/bbs_sidechannel.cpp
)

target_include_directories(bbs_sidechannel 
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(sidechannel_demo examples/sidechannel_demo.cpp)
target_link_libraries(sidechannel_demo PRIVATE bbs_toy bbs_sidechannel)

# Experiments

add_executable(exp_factor_time_vs_n experiments/exp_factor_time_vs_n.cpp)
target_link_libraries(exp_factor_time_vs_n PRIVATE bbs_toy bbs_utils)

add_executable(exp_factor_time_vs_partial_seed experiments/exp_factor_time_vs_partial_seed.cpp)
target_link_libraries(exp_factor_time_vs_partial_seed PRIVATE bbs_toy bbs_utils)

add_executable(exp_factor_time_vs_known_pq experiments/exp_factor_time_vs_known_pq.cpp)
target_link_libraries(exp_factor_time_vs_known_pq PRIVATE bbs_toy bbs_utils)
