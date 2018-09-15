/**
	@filename TIME.h
	@brief    TIME configuring and time delay functions
	@author   tzaiyang
	Copyright (c) 2018 EPIC. All rights reserved.
*/
#ifndef SRC_TIME_H_
#define SRC_TIME_H_

#include <stdio.h>
#define NO_XSFR_DEFINE
#include "CH559.h"

// 定义函数返回值
#ifndef SUCCESS
#define SUCCESS 1
#endif

#ifndef FAIL
#define FAIL 0
#endif

#define FREQ_SYS 12000000            // 系统主频12MHz

void CfgFsys();                       // CH559时钟选择和配置
void mDelayuS(UINT16 n);              // 以uS为单位延时
void mDelaymS(UINT16 n);              // 以mS为单位延时

#endif  // SRC_TIME_H_
