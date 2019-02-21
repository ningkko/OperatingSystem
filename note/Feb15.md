### Free-Space Management

- The problem: when managing free space using variable-based units:
￼0-10:FREE|10-20:USED|20-30:FREE

- void \*malloc(size t size) takes a single pa- rameter, size, which is the number of bytes requested by the applica- tion; it hands back a pointer (of no particular type, or a void pointer in C lingo) to a region of that size (or greater) \
\
Struct Blocks{\
  size_t size;\
  Struct Blocks_s* next;\
  uint64_t magic_number;\
  int8_t data[0];\
}

- To make sure that the memory distributed is the user’s memory