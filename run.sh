#!/bin/bash

usage () {
  echo "Usage :  $0 [options] [--] [Program Arguments]


  Options:
  -h|help       Display this message
  -d|dir        Run all sample codes in the specified directory"
}

while getopts "hd:" opt
do
  case $opt in
    d|dir)
      test -d "$OPTARG" && cd "$OPTARG"
      ;;
    *)
      usage
      exit 0
      ;;
  esac
done
shift $(($OPTIND-1))

run_in_folder() {
    local TYPE=$1
    shift 1
    if [[ -d "$TYPE" ]]; then
        cd "$TYPE"
        if [[ -f CMakeLists.txt ]]; then
            mkdir build && cd build && cmake .. && make
            tput setaf 1
            echo "--- Run $TYPE code: ./$TYPE.out $@ ---"
            ./$TYPE.out "$@"
            cd .. && rm -rf build
        elif [[ -f makefile || -f Makefile ]]; then
            make
            tput setaf 1
            echo "--- Run $TYPE code: ./$TYPE.out $@ ---"
            ./$TYPE.out "$@"
        fi
    fi
}

# c
if [[ -f sample.c ]]; then
    tput setaf 1
    gcc --std=c11 -Wall -Wextra sample.c -o c.out
    echo "--- Run C code: ./c.out $@ ---"
    ./c.out "$@"
    rm ./c.out
fi

(run_in_folder c)

# c++
if [[ -f sample.cpp ]]; then
    tput setaf 2
    g++ --std=c++11 -Wall -Wextra sample.cpp -o cpp.out
    echo "--- Run C++ code: ./cpp.out $@ ---"
    ./cpp.out "$@"
    rm ./cpp.out
fi

(run_in_folder cpp)

# go
if [[ -f sample.go ]]; then
    tput setaf 3
    go build -o go.out sample.go
    echo "--- Run Go code: ./go.out $@  ---"
    ./go.out "$@"
    rm ./go.out
fi

# Clear color
tput sgr0
