function make() {
	echo -e '\033[1;42m[No flag]\033[m Compiling' $1'.cpp with c++17.'
	'g++' '-std=c++17' '-I' '.' $1'.cpp' '-o' $1
}

function fast() {
	echo -e '\033[1;45m[-O2 flag]\033[m Compiling' $1'.cpp with c++17.'
	'g++' '-std=c++17' '-I' '.' '-O2' $1'.cpp' '-o' $1
}

function debug() {
	echo -e '\033[1;41m[DEBUG MODE]\033[m Compiling' $1'.cpp with c++17.'
	'g++' '-std=c++17' '-I' '.' '-DLOCAL' $1'.cpp' '-o' $1
}

function submit() {
	echo 'Expanding' $1'.cpp'
	'python3' 'expander.py' $1'.cpp'
	clip.exe < combined.cpp
}

function open() {
	echo 'Opening' $1
	'cmd.exe' '/C' 'start' $1
}
