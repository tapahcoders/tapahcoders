#!/bin/bash
set -e
for f in $(git diff --name-only HEAD^1)
do
  cd ${HOME}/build/${TRAVIS_REPO_SLUG}
  pwd
  echo $f
  EXT=$(echo $f| rev | cut -f 1 -d'.' | rev )
  echo "EXT => ${EXT}"
  if test "${EXT}" = "cpp"
  then
    DIRNAME=$(dirname $f)
    echo "DIRNAME => ${DIRNAME}"
    cd ${DIRNAME}
    BASENAME=$(basename $f .cpp)
    echo "BASENAME => ${BASENAME}"
    g++ -g -Wall ${BASENAME}.cpp -o ${BASENAME}
    ls -l ${BASENAME}.in.txt
    ./${BASENAME} < ${BASENAME}.in.txt > ${BASENAME}.result.txt
    echo "Result is"
    cat ${BASENAME}.result.txt
    ls -l ${BASENAME}.out.txt
    diff -Naur ${BASENAME}.result.txt ${BASENAME}.out.txt
  fi
done
