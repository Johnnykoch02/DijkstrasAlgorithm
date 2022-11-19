all:
        g++ main.cpp Graph.cpp --std=c++17 -p a.exe
        ./a
compile:
        g++ main.cpp Graph.cpp -g --std=c++17 -o a.exe
run:
        ./a