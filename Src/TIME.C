/********************************** (C) COPYRIGHT *******************************
* File Name          : TIME.C
* Author             : WCH
* Version            : V1.0
* Date               : 2015/05/20
* Description        : CH559 TIME Interface
                     (1)、串口0输出打印信息，波特率可调;              				   
*******************************************************************************/

#include "TIME.h"

/*******************************************************************************
* Function Name  : CfgFsys( )
* Description    : CH559时钟选择和配置函数,默认使用内部晶振12MHz，如果定义了FREQ_SYS可以
                   根据PLL_CFG和CLOCK_CFG配置得到，公式如下：
                   Fsys = (Fosc * ( PLL_CFG & MASK_PLL_MULT ))/(CLOCK_CFG & MASK_SYS_CK_DIV);
                   具体时钟需要自己配置
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/ 
//void	CfgFsys( )  
//{
//    SAFE_MOD = 0x55;                                                           //开启安全模式
//    SAFE_MOD = 0xAA;                                                 
//    CLOCK_CFG |= bOSC_EN_XT;                                                   //使能外部晶振                                         
//    CLOCK_CFG &= ~bOSC_EN_INT;                                                
////	PLL_CFG = 0x18;                                                            //配置系统时钟
////	CLOCK_CFG = 0x0c;
//    SAFE_MOD = 0xFF;                                                           //关闭安全模式  
//}

/*******************************************************************************
* Function Name  : mDelayus(UNIT16 n)
* Description    : us延时函数
* Input          : UNIT16 n
* Output         : None
* Return         : None
*******************************************************************************/ 
void	mDelayuS( UINT16 n )  // 以uS为单位延时
{
	while ( n ) {  // total = 12~13 Fsys cycles, 1uS @Fsys=12MHz
		++ SAFE_MOD;  // 2 Fsys cycles, for higher Fsys, add operation here
#ifdef	FREQ_SYS
#if		FREQ_SYS >= 14000000
		++ SAFE_MOD;
#endif
#if		FREQ_SYS >= 16000000
		++ SAFE_MOD;
#endif
#if		FREQ_SYS >= 18000000
		++ SAFE_MOD;
#endif
#if		FREQ_SYS >= 20000000
		++ SAFE_MOD;
#endif
#if		FREQ_SYS >= 22000000
		++ SAFE_MOD;
#endif
#if		FREQ_SYS >= 24000000
		++ SAFE_MOD;
#endif
#if		FREQ_SYS >= 26000000
		++ SAFE_MOD;
#endif
#if		FREQ_SYS >= 28000000
		++ SAFE_MOD;
#endif
#if		FREQ_SYS >= 30000000
		++ SAFE_MOD;
#endif
#if		FREQ_SYS >= 32000000
		++ SAFE_MOD;
#endif
#if		FREQ_SYS >= 34000000
		++ SAFE_MOD;
#endif
#if		FREQ_SYS >= 36000000
		++ SAFE_MOD;
#endif
#if		FREQ_SYS >= 38000000
		++ SAFE_MOD;
#endif
#if		FREQ_SYS >= 40000000
		++ SAFE_MOD;
#endif
#endif
		-- n;
	}
}

/*******************************************************************************
* Function Name  : mDelayms(UNIT16 n)
* Description    : ms延时函数
* Input          : UNIT16 n
* Output         : None
* Return         : None
*******************************************************************************/
void	mDelaymS( UINT16 n )                                                  // 以mS为单位延时
{
	while ( n ) 
	{
		mDelayuS( 1000 );
		-- n;
	}
}                                         
