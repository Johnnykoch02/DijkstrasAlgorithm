all:
        g++ PP4Test.cpp .\src\Graph.cpp -g --std=c++17 -o a.exe
        ./a
compile:
        g++ PP4Test.cpp .\src\Graph.cpp -g --std=c++17 -o a.exe
run:
        ./a