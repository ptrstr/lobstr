#define CONCAT(a, b) a##b

#define ARG(N, ...) ARG_##N(__VA_ARGS__)

#define ARG_1(_1, ...) _1
#define ARG_2(_1, _2, ...) _2
#define ARG_3(_1, _2, _3, ...) _3
#define ARG_4(_1, _2, _3, _4, ...) _4
#define ARG_5(_1, _2, _3, _4, _5, ...) _5
#define ARG_6(_1, _2, _3, _4, _5, _6, ...) _6
#define ARG_7(_1, _2, _3, _4, _5, _6, _7, ...) _7
#define ARG_8(_1, _2, _3, _4, _5, _6, _7, _8, ...) _8
#define ARG_9(_1, _2, _3, _4, _5, _6, _7, _8, _9, ...) _9
#define ARG_10(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, ...) _10
#define ARG_11(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, ...) _11
#define ARG_12(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, ...) _12
#define ARG_13(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, ...) _13
#define ARG_14(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, ...) _14
#define ARG_15(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, ...) _15
#define ARG_16(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, ...) _16
#define ARG_17(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, ...) _17
#define ARG_18(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, ...) _18
#define ARG_19(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, ...) _19
#define ARG_20(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, ...) _20

#define COUNT_N(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, N, ...) N
#define COUNT(...) COUNT_N(__VA_ARGS__, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1)

#define STRUCT_ITEMS(...) STRUCT_ITEMS_N(COUNT(__VA_ARGS__), __VA_ARGS__)
#define STRUCT_ITEMS_N(N, ...) CONCAT(STRUCT_ITEMS_, N)(__VA_ARGS__)
#define STRUCT_ITEMS_1(...) ;
#define STRUCT_ITEMS_2(...) ARG(1, __VA_ARGS__) ARG(2, __VA_ARGS__);
#define STRUCT_ITEMS_4(...) ARG(1, __VA_ARGS__) ARG(2, __VA_ARGS__); ARG(3, __VA_ARGS__) ARG(4, __VA_ARGS__);
#define STRUCT_ITEMS_6(...) ARG(1, __VA_ARGS__) ARG(2, __VA_ARGS__); ARG(3, __VA_ARGS__) ARG(4, __VA_ARGS__); ARG(5, __VA_ARGS__) ARG(6, __VA_ARGS__);
#define STRUCT_ITEMS_8(...) ARG(1, __VA_ARGS__) ARG(2, __VA_ARGS__); ARG(3, __VA_ARGS__) ARG(4, __VA_ARGS__); ARG(5, __VA_ARGS__) ARG(6, __VA_ARGS__); ARG(7, __VA_ARGS__) ARG(8, __VA_ARGS__);
#define STRUCT_ITEMS_10(...) ARG(1, __VA_ARGS__) ARG(2, __VA_ARGS__); ARG(3, __VA_ARGS__) ARG(4, __VA_ARGS__); ARG(5, __VA_ARGS__) ARG(6, __VA_ARGS__); ARG(7, __VA_ARGS__) ARG(8, __VA_ARGS__); ARG(9, __VA_ARGS__) ARG(10, __VA_ARGS__);
#define STRUCT_ITEMS_12(...) ARG(1, __VA_ARGS__) ARG(2, __VA_ARGS__); ARG(3, __VA_ARGS__) ARG(4, __VA_ARGS__); ARG(5, __VA_ARGS__) ARG(6, __VA_ARGS__); ARG(7, __VA_ARGS__) ARG(8, __VA_ARGS__); ARG(9, __VA_ARGS__) ARG(10, __VA_ARGS__); ARG(11, __VA_ARGS__) ARG(12, __VA_ARGS__);
#define STRUCT_ITEMS_14(...) ARG(1, __VA_ARGS__) ARG(2, __VA_ARGS__); ARG(3, __VA_ARGS__) ARG(4, __VA_ARGS__); ARG(5, __VA_ARGS__) ARG(6, __VA_ARGS__); ARG(7, __VA_ARGS__) ARG(8, __VA_ARGS__); ARG(9, __VA_ARGS__) ARG(10, __VA_ARGS__); ARG(11, __VA_ARGS__) ARG(12, __VA_ARGS__); ARG(13, __VA_ARGS__) ARG(14, __VA_ARGS__);
#define STRUCT_ITEMS_16(...) ARG(1, __VA_ARGS__) ARG(2, __VA_ARGS__); ARG(3, __VA_ARGS__) ARG(4, __VA_ARGS__); ARG(5, __VA_ARGS__) ARG(6, __VA_ARGS__); ARG(7, __VA_ARGS__) ARG(8, __VA_ARGS__); ARG(9, __VA_ARGS__) ARG(10, __VA_ARGS__); ARG(11, __VA_ARGS__) ARG(12, __VA_ARGS__); ARG(13, __VA_ARGS__) ARG(14, __VA_ARGS__); ARG(15, __VA_ARGS__) ARG(16, __VA_ARGS__);
#define STRUCT_ITEMS_18(...) ARG(1, __VA_ARGS__) ARG(2, __VA_ARGS__); ARG(3, __VA_ARGS__) ARG(4, __VA_ARGS__); ARG(5, __VA_ARGS__) ARG(6, __VA_ARGS__); ARG(7, __VA_ARGS__) ARG(8, __VA_ARGS__); ARG(9, __VA_ARGS__) ARG(10, __VA_ARGS__); ARG(11, __VA_ARGS__) ARG(12, __VA_ARGS__); ARG(13, __VA_ARGS__) ARG(14, __VA_ARGS__); ARG(15, __VA_ARGS__) ARG(16, __VA_ARGS__); ARG(17, __VA_ARGS__) ARG(18, __VA_ARGS__);
#define STRUCT_ITEMS_20(...) ARG(1, __VA_ARGS__) ARG(2, __VA_ARGS__); ARG(3, __VA_ARGS__) ARG(4, __VA_ARGS__); ARG(5, __VA_ARGS__) ARG(6, __VA_ARGS__); ARG(7, __VA_ARGS__) ARG(8, __VA_ARGS__); ARG(9, __VA_ARGS__) ARG(10, __VA_ARGS__); ARG(11, __VA_ARGS__) ARG(12, __VA_ARGS__); ARG(13, __VA_ARGS__) ARG(14, __VA_ARGS__); ARG(15, __VA_ARGS__) ARG(16, __VA_ARGS__); ARG(17, __VA_ARGS__) ARG(18, __VA_ARGS__); ARG(19, __VA_ARGS__) ARG(20, __VA_ARGS__);


#define DISTRIBUTED_CALL(FN, ...) DISTRIBUTED_CALL_N(FN, COUNT(__VA_ARGS__), __VA_ARGS__)
#define DISTRIBUTED_CALL_N(FN, N, ...) CONCAT(DISTRIBUTED_CALL_, N)(FN, __VA_ARGS__)
#define DISTRIBUTED_CALL_1(FN, ...) 
#define DISTRIBUTED_CALL_2(FN, ...) FN(ARG(2, __VA_ARGS__))
#define DISTRIBUTED_CALL_4(FN, ...) FN(ARG(2, __VA_ARGS__)) FN(ARG(4, __VA_ARGS__))
#define DISTRIBUTED_CALL_6(FN, ...) FN(ARG(2, __VA_ARGS__)) FN(ARG(4, __VA_ARGS__)) FN(ARG(6, __VA_ARGS__))
#define DISTRIBUTED_CALL_8(FN, ...) FN(ARG(2, __VA_ARGS__)) FN(ARG(4, __VA_ARGS__)) FN(ARG(6, __VA_ARGS__)) FN(ARG(8, __VA_ARGS__))
#define DISTRIBUTED_CALL_10(FN, ...) FN(ARG(2, __VA_ARGS__)) FN(ARG(4, __VA_ARGS__)) FN(ARG(6, __VA_ARGS__)) FN(ARG(8, __VA_ARGS__)) FN(ARG(10, __VA_ARGS__))
#define DISTRIBUTED_CALL_12(FN, ...) FN(ARG(2, __VA_ARGS__)) FN(ARG(4, __VA_ARGS__)) FN(ARG(6, __VA_ARGS__)) FN(ARG(8, __VA_ARGS__)) FN(ARG(10, __VA_ARGS__)) FN(ARG(12, __VA_ARGS__))
#define DISTRIBUTED_CALL_14(FN, ...) FN(ARG(2, __VA_ARGS__)) FN(ARG(4, __VA_ARGS__)) FN(ARG(6, __VA_ARGS__)) FN(ARG(8, __VA_ARGS__)) FN(ARG(10, __VA_ARGS__)) FN(ARG(12, __VA_ARGS__)) FN(ARG(14, __VA_ARGS__))
#define DISTRIBUTED_CALL_16(FN, ...) FN(ARG(2, __VA_ARGS__)) FN(ARG(4, __VA_ARGS__)) FN(ARG(6, __VA_ARGS__)) FN(ARG(8, __VA_ARGS__)) FN(ARG(10, __VA_ARGS__)) FN(ARG(12, __VA_ARGS__)) FN(ARG(14, __VA_ARGS__)) FN(ARG(16, __VA_ARGS__))
#define DISTRIBUTED_CALL_18(FN, ...) FN(ARG(2, __VA_ARGS__)) FN(ARG(4, __VA_ARGS__)) FN(ARG(6, __VA_ARGS__)) FN(ARG(8, __VA_ARGS__)) FN(ARG(10, __VA_ARGS__)) FN(ARG(12, __VA_ARGS__)) FN(ARG(14, __VA_ARGS__)) FN(ARG(16, __VA_ARGS__)) FN(ARG(18, __VA_ARGS__))
#define DISTRIBUTED_CALL_20(FN, ...) FN(ARG(2, __VA_ARGS__)) FN(ARG(4, __VA_ARGS__)) FN(ARG(6, __VA_ARGS__)) FN(ARG(8, __VA_ARGS__)) FN(ARG(10, __VA_ARGS__)) FN(ARG(12, __VA_ARGS__)) FN(ARG(14, __VA_ARGS__)) FN(ARG(16, __VA_ARGS__)) FN(ARG(18, __VA_ARGS__)) FN(ARG(20, __VA_ARGS__))

#define USE_REGS(...) \
static struct {STRUCT_ITEMS(__VA_ARGS__)} registers; \
void registers_get() {DISTRIBUTED_CALL(LOAD_REG, __VA_ARGS__)} \
void registers_set() {DISTRIBUTED_CALL(SAVE_REG, __VA_ARGS__)}
#define SAVE_REG(to_expand)  _SAVE_REG(to_expand)
#define _SAVE_REG(reg) asm("mov %0, %%" #reg ";" : : "m" (registers.reg));
#define LOAD_REG(to_expand) _LOAD_REG(to_expand)
#define _LOAD_REG(reg) asm("mov %%" #reg ", %0;" : "=m" (registers.reg));
