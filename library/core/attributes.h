#ifndef LIB_CORE_ATTRIBUTES_H
#define LIB_CORE_ATTRIBUTES_H

#define PACKED         __attribute__((packed))
#define SECTION(NAME)  __attribute__((section(NAME)))
#define OPTIMIZE(NAME) __attribute__((optimize(NAME)))
#define ALIGN(N)       __attribute__((aligned(N)))

#endif
