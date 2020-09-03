
startTime=$(date +%s%N)

make -j2

endTime=$(date +%s%N)

costTime=$(($(($endTime-$startTime))/1000000))

echo -e "\033[32m\033[1m"takes $costTime ms"\033[0m"
