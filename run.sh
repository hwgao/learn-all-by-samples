#!/bin/bash
set -x

export GOPATH="$(dirname $(realpath $0))/go"
INPUT="${PWD}"

declare -A languages=(
    [c]='gcc --std=c11 -Wall -Wextra ${INPUT} -o ${OUTPUT}'
    [cpp]='g++ --std=c++11 -Wall -Wextra ${INPUT} -o ${OUTPUT}'
    [go]='go build -o ${OUTPUT} ${INPUT}'
    [py]='python ${INPUT}'
    [js]='node ${INPUT}'
)

usage () {
  echo "Usage :  $0 [options] [--] [Program Arguments]


  Options:
  -h|help       Display this message
  -s|source     File or directory to run"
}

run_output() {
    if [[ -e "$OUTPUT" ]]; then
        tput setaf 1
        ./"$OUTPUT" "$@"
        rm "$OUTPUT"
        tput sgr0
    fi
}

while getopts "s:" opt
do
  case $opt in
    s|source)
      INPUT="$OPTARG"
      ;;
    *)
      usage
      exit 0
      ;;
  esac
done
shift $(($OPTIND-1))

if [[ -f "$INPUT" ]]; then
    cd "$(dirname $INPUT)"
    INPUT="$(basename $INPUT)"
    OUTPUT="${INPUT%.*}"
    eval ${languages[${INPUT##*.}]}
elif [[ -d "$INPUT" ]]; then
    cd "$INPUT"
    INPUT="$(basename $INPUT)"
    OUTPUT="${INPUT%.*}"
    if [[ -f CMakeLists.txt ]]; then
        mkdir build && cd build && cmake .. && make
    elif [[ -f makefile || -f Makefile ]]; then
        make
    else
        count=$(ls -1 *.go 2>/dev/null | wc -l)
        if [[ $count != 0  ]]; then
            go build
        fi
    fi
fi

run_output "$@"
