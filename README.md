# Bytesort
*Linear Time Byte Sorter*

Bytesort is a scalable and heavily performance optimized sorting program. It uses histogram sort, variation of bucket sort to sort all bytes from STDIN with a worst-case runtime of O(N). This program is primarly meant as a demonstration of the sorting 

## Usage
```
Usage: cat [FILE] | ./bytesort [OPTION]...

Sorts all the bytes from STDIN and writes them to STDOUT.

  -h, --help       Shows this message.
  -c, --compact    Prints each character only once followed by the
                   number of times it appears. (aaaaa --> a:5)
  -x, --hex        Replaces each byte with it hex code in compact mode.
  -p, --printable  Ignored all bytes outside the range of printable
                   ASCII characters [0x21; 0x7E].
  -n, --newline    Adds a newline to the end of the output.

WARNING: This program may exit with an error when attemting
         to sort more than 18447 Petabytes of data.
```