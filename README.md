# CRYPTO

# Dependencies: 
  cs50 library
  
  # Install instructions: (For Linux and Mac)
   Download the latest release from https://github.com/cs50/libcs50/releases
   Extract libcs50-*.*
   cd libcs50-*
   sudo make install
    
# Troubleshooting
  If when compiling your program, you see:

  ```/usr/bin/ld: cannot find -lcs50```:
  Add ```export LIBRARY_PATH=/usr/local/lib``` to your ~/.bashrc.
  
  ```fatal error: 'cs50.h' file not found```:
  Add ```export C_INCLUDE_PATH=/usr/local/include``` to your ~/.bashrc.
  
  ```cannot open shared object file: No such file or directory```:
  Add ```export LD_LIBRARY_PATH=/usr/local/lib``` to your ~/.bashrc.

# Build: (Build using your preferred compiler)
  ```
  $ clang vigenere.c -o vigenere -lcs50
  ```
  
  or,
  
  Add these at the bottom or your ~/.bashrc file
  ```
    export CC="clang"
    export CFLAGS="-fsanitize=signed-integer-overflow -fsanitize=undefined -ggdb3 -O0 -std=c11 -Wall -Werror -Wextra -Wno-sign-compare -Wno-unused-parameter -Wno-unused-variable -Wshadow"
    export LDLIBS="-lcrypt -lcs50 -lm"
  ```
  and then build using:
  ```
    $ make vigenere
  ```
  
  
Detailed instructions can be found at:
https://cs50.readthedocs.io/library/c/
