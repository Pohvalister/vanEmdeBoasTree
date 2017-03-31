#ifndef VANEMDEBOASTREE_MY_MATH_H
#define VANEMDEBOASTREE_MY_MATH_H
#define UI unsigned long long int

inline constexpr UI my_2_log(UI value) {
    UI pattern = 1;
    UI count = 0;
    while (pattern < value) {
        pattern *= 2;
        count++;
    }
    return count;
}

inline constexpr UI my_2_pow(UI value) {
    if (value == 0)
        return 1;
    if (value % 2 == 1)
        return my_2_pow(value - 1) * 2;
    UI tmp = my_2_pow(value / 2);
    return tmp * tmp;
}
//нужно большая половина байтов тк при 1 байте будет 0 что плохо тк массив из 0 элементов
inline constexpr UI high(UI byteVal, UI value) {
    return (value >> ((byteVal / 2)));
}

inline constexpr UI low(UI byteVal, UI value) {
    return value - (high(byteVal, value) << ((byteVal / 2)));
}

#endif //VANEMDEBOASTREE_MY_MATH_H
