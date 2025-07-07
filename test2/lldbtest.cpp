
#include <stdio.h>
#include <cstdlib>
#include <sanitizer/coverage_interface.h>

//clang++ -std=c++17 -fsanitize-coverage=trace-pc-guard  lldbtest.cpp -o test

__attribute__((constructor)) static void fun1()
{
    printf("before main\n");
}

__attribute__((destructor)) static void fun2()
{
    printf("after main exit \n");
}


void atexit_fun()
{
    printf("at exit\n");
}

extern "C" void __sanitizer_cov_trace_pc_guard_init(uint32_t *start, uint32_t *stop)
{
    printf("__sanitizer_cov_trace_pc_guard_init\n");

}

extern "C" void __sanitizer_cov_trace_pc_guard(uint32_t *guard)
{
    // printf("guard: %d\n", *guard);
    // if(!*guard)
    //     return;

    void *PC = __builtin_return_address(0);
    char PCDes[1024] = {0};

    __sanitizer_symbolize_pc(PC, "%p %F %L", PCDes, sizeof(PCDes));

    printf("__sanitizer_cov_trace_guard : %s\n", PCDes);
}

int main()
{
    atexit(atexit_fun);

    printf("%d\n", (10 + 15) & (~15));

    printf("heel\n");
}