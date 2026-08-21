cmake_minimum_required(VERSION 3.10)
project(EnglishAutocorrect CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(autocorrect
    main.cpp
    Dictionary.cpp
    Levenshtein.cpp
    Autocorrect.cpp
)