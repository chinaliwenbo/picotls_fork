
#include "stdio.h"
#include "stdint.h"

/*
内存对齐涉及到两个部分:
1、计算一个对齐的值
2、根据对齐值分配空间

计算对齐值:
    基本类型的自身对齐值：基本类型自身所占的空间大小，即 sizeof() 值； 结构体或类的自身对齐值：其所有成员中的最大对齐值
    指定对齐值：使用 #pragma pack(n) 时指定的对齐值 n (1,2,4,8,16...)

    上面两种情况下, 再选取一个一个较小的值，作为最终有效的对齐值。

    用伪代码表示就是:
    if (typeof(变量) == 基本类型){
        对齐值 = sizeof(变量)
    } else if (typeof(变量) == 结构体){
        对齐值 = max(sizeof(结构体.成员变量1), sizeof(结构体.成员变量2), sizeof(结构体.成员变量3)...)
    }

    if (pragma pack n < 对齐值){
        对齐值 = n
    } 
    

基本类型的对齐:
    1、内存其实地址必须是有效对齐值的整数倍。

结构体的对齐:
    1、结构体变量的起始地址能够被其有效对齐值整除；
    2、每个成员相对于结构体首地址的偏移都能被有效对齐值整除，如不能则在前一个成员后填充字节；
    3、结构体的总大小为有效对齐值的整数倍，如不能则在最后面填充字节。
*/

/*
实战一: 默认gcc对齐
这个结构体的有效对齐值是4, 
所以A结构体的起始地址必须是4的倍数， 假设A结构体起始地址为 0x0
b相对于结构体的起始地址是偏移4个字节，是有效对齐值的整数倍，a后面不用置空字节, 所以b的地址为0x4
c的起始地址无法被4整除, 正常算出来是5, 因此要偏移到8的位置, 因此起始地址为0x8
总体长度是12个字节。
*/

struct A{
    int a;  // 4 bytes
    char b;  // 1bytes
    short c;  // 2 bytes
} a;


/**
实战二：默认gcc对齐
这个结构体的有效对齐值是4, 同样的道理
b处于0x0的位置。
a处于0x4的位置。
c处于0x8的位置。
总体长度仍然是12个字节
*/
struct B{
    char   b;
    int    a;
    short  c;
} b;

/*
实战三: 自定义对齐值2, 2 < sizeof(int), 所以有效对齐值为2
b处于0x0的位置。
a处于0x2的位置。占据4个字节
c处于0x6的位置。
整体是8个字节
*/
#pragma pack(2)  //指定按2字节对齐
struct C{
    char  b;
    int   a;
    short c;
} c;
#pragma pack()   //取消指定对齐，恢复缺省对齐

/*
实战四：变量的自定义对齐
*/
// __align(8) char buffer[128];
 typedef struct
 {
    uint8_t a;
    uint16_t b;
    uint32_t c;
    uint64_t d;
 } d;

/*
实战五： 无对齐， 总共15个字节
*/
#pragma pack(1)  //指定按2字节对齐
typedef struct
 {
    uint8_t a; 
    uint16_t b; 
    uint32_t c; 
    uint64_t d; 
 } e;
#pragma pack()   //取消指定对齐，恢复缺省对齐

/*
实战六：设置一个很大的对齐值, 这个值是无效的。
*/
#pragma pack(64)  //指定按2字节对齐
typedef struct
 {
    uint8_t a; 
    uint16_t b; 
    uint32_t c; 
    uint64_t d; 
 } f;
#pragma pack()   //取消指定对齐，恢复缺省对齐

int main(){
    printf("a sizeof info: %d\n", sizeof(a));
    printf("b sizeof info: %d\n", sizeof(b));
    printf("c sizeof info: %d\n", sizeof(c));
    printf("d sizeof info: %d\n", sizeof(d));
    printf("d sizeof info: %d\n", sizeof(e));
    printf("d sizeof info: %d\n", sizeof(f));
}

