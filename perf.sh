#i/bin/bash

perf stat ./file_extension_reading
perf record -g -e branches,branch-misses ./file_extension_reading
