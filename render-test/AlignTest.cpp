
#include <cstdint>
#include <type_traits>
#include <typeinfo>

#include <stdio.h>

template <typename T1, typename T2>
inline typename std::conditional<sizeof(T1) >= sizeof(T2), T1, T2>::type AlignUp(T1 val, T2 alignment)
{
    //static_assert(std::is_unsigned<T1>::value == std::is_unsigned<T2>::value, "both types must be signed or unsigned");
    //static_assert(!std::is_pointer<T1>::value && !std::is_pointer<T2>::value, "types must not be pointers");
    //VERIFY(IsPowerOfTwo(alignment), "Alignment (", alignment, ") must be a power of 2");

    using T = typename std::conditional<sizeof(T1) >= sizeof(T2), T1, T2>::type;
    return (static_cast<T>(val) + static_cast<T>(alignment - 1)) & ~static_cast<T>(alignment - 1);
}

template <typename PtrType, typename AlignType>
inline PtrType* AlignUp(PtrType* val, AlignType alignment)
{
    return reinterpret_cast<PtrType*>(AlignUp(reinterpret_cast<uintptr_t>(val), static_cast<uintptr_t>(alignment)));
}


template <typename T1, typename T2>
inline typename std::conditional<sizeof(T1) >= sizeof(T2), T1, T2>::type AlignDown(T1 val, T2 alignment)
{
    // static_assert(std::is_unsigned<T1>::value == std::is_unsigned<T2>::value, "both types must be signed or unsigned");
    // static_assert(!std::is_pointer<T1>::value && !std::is_pointer<T2>::value, "types must not be pointers");
    // VERIFY(IsPowerOfTwo(alignment), "Alignment (", alignment, ") must be a power of 2");

    using T = typename std::conditional<sizeof(T1) >= sizeof(T2), T1, T2>::type;
    return static_cast<T>(val) & ~static_cast<T>(alignment - 1);
}

template <typename PtrType, typename AlignType>
inline PtrType* AlignDown(PtrType* val, AlignType alignment)
{
    return reinterpret_cast<PtrType*>(AlignDown(reinterpret_cast<uintptr_t>(val), static_cast<uintptr_t>(alignment)));
}


int main()
{
    auto sizeup = AlignUp(sizeof(void*)+1000, 16);
    auto sizedw = AlignDown(sizeof(void*), 16);
    printf("---%ld, %ld, %ld\n", sizeup, sizedw, static_cast<uintptr_t>(16) & ~static_cast<uintptr_t>(15));

    return 0;
}
