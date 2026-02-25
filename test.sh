#i/bin/bash

cmake --build build 
valgrind -s --track-origins=yes ./file_extension_reading
