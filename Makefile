include_dirs = hearders src

build:
	arm-none-eabi-gcc -c -I $(include_dirs) -O3  src/main.c
