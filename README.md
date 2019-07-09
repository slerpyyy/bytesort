# Bytesort
*Linear Time Byte Sorter*

Bytesort is a scalable and heavily performance optimized sorting program. It uses histogram sort, a variation of bucket sort to sort all bytes from STDIN with a worst-case runtime of O(N).

This program exists purely as a proof of concept. It is meant more as a demonstration of a linear time sorting algorithm than a genuine tool for applications, where sorting large quantities of 8-bit numbers would be necessary, as I don't expect there to be that many.

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

WARNING: This program may exit with an error when attempting
         to sort more than 18447 Petabytes of data.
```

## The Algorithm
This program is an implementation of the sorting algorithm, formally known **histogram sort**. The basic idea is that, if you generate the histogram from an array of integers and throw away the original array, the only piece of information you're losing about the numbers in the original array is their order.

### Step-by-Step Example
1. Start with a string of letters:
```
cdbacdda
```

2. Count how often each letter appears:
```
a:2 b:1 c:2 d:3
```

3. Make a new string using the information collected above:
```
aabccddd
```

### Runtime Complexity
Both the generation of the histogram and the generation of the final string scale linearly to the length of the original string. As both processes run in sequence, the runtime of the entire sorting algorithm is proportional to n + n = 2n, which means histogram sort takes O(n) time.

## Building
On Linux, you can build this program by running the following command:
```
gcc bytesort.c -o bytesort -Wall -Ofast -funroll-loops
```
I'm not planning on adding Windows support any time soon.
