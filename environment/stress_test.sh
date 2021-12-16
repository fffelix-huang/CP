# $1 : gen
# $2 : brute
# $3 : sol
g++ -std=c++17 -I . -O2 $1.cpp -o $1
g++ -std=c++17 -I . -O2 $2.cpp -o $2
g++ -std=c++17 -I . -O2 $3.cpp -o $3
for((i = 1; ; ++i)); do
	./$1 $i > debug_in
	./$3 < debug_in > my_out
	./$2 < debug_in > ans_out
	diff -Z my_out ans_out || break
	echo -e "\033[1;32mPassed test: " $i "\033[m"
done
echo -e "\033[1;45mWA on the following test\033[m"
echo -e "\033[0;46mInput\033[m"
cat debug_in
echo ""
echo -e "\033[1;41mYour answer\033[m"
cat my_out
echo ""
echo -e "\033[1;42mCorrect answer\033[m"
cat ans_out
