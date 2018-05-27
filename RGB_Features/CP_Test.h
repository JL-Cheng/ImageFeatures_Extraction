#pragma once
#ifndef CP_TEST_H
#define CP_TEST_H

struct Pixel;

extern void test();

//进行rgb值近似，如[0,63)->1，从而减小颜色维度
extern void approximateRGB(Pixel &p);

#endif // !CP_TEST_H
