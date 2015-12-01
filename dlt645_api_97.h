/****************************************************
    File           dlt645_api_97.h
    Brief         dlt645 规约 1997版 解析代码头文件
    Detail        实现对dlt645 1997版规约类型定义
                提供帧数据的封装及解析相关api    
    Author         liming
    Date           2012/10/20
    Version        1.0
    Functions
    CopyRight    国网电力科学院通信与用电技术分公司
    History    

****************************************************/
#ifndef _DLT645_API_1997_H_
#define _DLT645_API_1997_H_

#ifndef _TYPE_DEF_LM_
#define _TYPE_DEF_LM_
#ifndef __RTL_H__
#define __RTL_H__
typedef char    BOOL;
#endif
#define TRUE    (1)
#define FALSE   (0)
typedef unsigned char UCHAR;
typedef char    CHAR;
typedef unsigned short USHORT;
typedef short   SHORT;

typedef unsigned long ULONG;
typedef long    LONG;

#ifndef _TYPE_DEF_
#define _TYPE_DEF_
typedef char            INT8;       //c
typedef short           INT16;      //s
typedef int             INT32;      //l
typedef unsigned char   UINT8;      //uc
typedef unsigned short  UINT16;     //us
typedef unsigned int    UINT32;     //ul

#ifdef MACHINE_64_BITS
typedef long             INT64;
typedef unsigned   long  UINT64;
#else
typedef long  long           INT64;
typedef unsigned long  long  UINT64;
#endif

typedef char*           STRING;     //str
typedef char            ISBOOL;     //b
typedef unsigned int    IPADDR;     //ip
typedef double          DOUBLE;
typedef void*  FRWK_HANDLE;

#endif
#endif



//#define D97_DEBUG_ON

#ifdef D97_DEBUG_ON
#define OUT_BUF_LEN 1024
#define D97_ON  0
#define D97_OFF 1

extern int g_d97_need_pack;
extern char g_d97_out_data[OUT_BUF_LEN];
void debug_switch_d97(int show);
#endif


/* 常量定义 */
#define UNKNOWN_LEN        0xFFFFFFFF              /* 未知整数 */
#define D97_DATA_MAX_NR    8                       /* dlt645 1997 最大数据域字节数算规约ID */
#define D97_DATA_MAX       (D97_DATA_MAX_NR + 2)   /* dlt645 1997 最大数据域字节数 */
#define D97_ADDR_LEN       12                      /* 地址长 */
#define D97_FRAME_LEN_MIN  12                        /* DLT645 97 最小帧字节数 */    

/* 电表常数最大值 */
#define YEAR_P_MAX            0xF
#define INTERVAL_M_MAX     10
#define DAY_Q_MAX          8
#define RATE_K_MAX         14           /* */
#define HOLIDAY_N_MAX      100          /* 公共假日数 N最大值 */
#define D97_NAME_LEN       64           /* 最大名字长度 (字节数)*/

/* 控制码C域 功能码 */
#define CTRL_CODE_RESERVE                    0x00   /*保留*/
#define CTRL_CODE_READ_DATA                  0x01   /*读取数据*/
#define CTRL_CODE_READ_AFTERDATA            0x02   /*读取后续数据*/
#define CTRL_CODE_READ_DATA_RE              0x03   /*重读数据*/
#define CTRL_CODE_WRITE_DATA                0x04   /*写数据*/
#define CTRL_CODE_SYNC_TIME                 0x08   /*广播校时*/
#define CTRL_CODE_WRITE_ADDR                0x0A   /*写设备地址*/
#define CTRL_CODE_MODIFY_BAUD                0x0C   /*更改通信速率*/
#define CTRL_CODE_MODIFY_PASSWORD           0x0F   /*更改密码*/
#define CTRL_CODE_MAXDEMAND_CLEAR           0x10   /*最大需求量清 0*/


/* 全局变量 */
extern unsigned char g_year_p;      /* 年时区数 P(1~F)*/
extern unsigned char g_interval_m;  /*日时段(每日切换数)m (1~10)*/
extern unsigned char g_day_q;       /*日时段表数 q (1~8)*/
extern unsigned char g_rate_k;      /* 费率数 k (1~14)*/
extern unsigned char g_holiday_n;   /* 公共假日数 n*/


/* 类型定义 */

/* 帧数据转换标志 决定 接口结构数据与帧数据转换方向 */
typedef enum
{
    E_D97_TRANS_U2F,    /* 封包过程 user -> frame 将用户接口数据转换 到 帧数据*/
    E_D97_TRANS_F2U,    /* 解包过程 frame-> user  */    
}E_D97_TRANS_FLAG;


typedef struct
{
    BOOL bRateErr;  // 费率数超
    BOOL bDayErr;   // 日时段数超
    BOOL bYearErr;  // 年时区数超
    BOOL bPwdErr;   // 密码错或未授权
    BOOL bErrID;    // 数据标识错
    BOOL bErrData;  // 非法数据
}S_D97_ERR;


/*  规约类型 */
typedef enum
{
    E_D97_RULER_UNKNOWN,                     // 未知规约类型    
    E_D97_RULER_STANDARD_MIN,               /* dlt645 97 标准规约类型最小值 */
    /* 电能 */
    E_D97_RULER_STANDARD_POWER_MIN = E_D97_RULER_STANDARD_MIN,         /* 标签规约表电能量最大值对应表A.1*/
    E_D97_RULER_FORTH_HAVE_POWER_TOTAL = E_D97_RULER_STANDARD_MIN,   /* 正向有功总电能 */
    E_D97_RULER_FORTH_HAVE_POWER_RATE,    /* 正向有功费率电能*/
    E_D97_RULER_FORTH_HAVE_POWER_BLOCK,      /* 正向有功电能数据块 */

    E_D97_RULER_BACK_HAVE_POWER_TOTAL,   /* 反向有功总电能 */
    E_D97_RULER_BACK_HAVE_POWER_RATE,    /* 反向有功费率电能*/
    E_D97_RULER_BACK_HAVE_POWER_BLOCK,   /* 反向有功电能数据块 */

    E_D97_RULER_FORTH_NONE_POWER_TOTAL,   /* 正向无功总电能 */
    E_D97_RULER_FORTH_NONE_POWER_RATE,    /* 正向无功费率电能*/
    E_D97_RULER_FORTH_NONE_POWER_BLOCK,      /* 正向无功电能数据块 */

    E_D97_RULER_BACK_NONE_POWER_TOTAL,   /* 反向无功总电能 */
    E_D97_RULER_BACK_NONE_POWER_RATE,    /* 反向无功费率电能*/
    E_D97_RULER_BACK_NONE_POWER_BLOCK,   /* 反向无功电能数据块 */

    E_D97_RULER_QUAD_1_NONE_POWER_TOTAL,   /* 1 象限无功总电能 */
    E_D97_RULER_QUAD_1_NONE_POWER_RATE,    /* 1 象限无功费率电能*/
    E_D97_RULER_QUAD_1_NONE_POWER_BLOCK,   /* 1 象限无功电能数据块 */
    
    E_D97_RULER_QUAD_4_NONE_POWER_TOTAL,   /* 4 象限无功总电能 */
    E_D97_RULER_QUAD_4_NONE_POWER_RATE,    /* 4 象限无功费率电能*/
    E_D97_RULER_QUAD_4_NONE_POWER_BLOCK,   /* 4 象限无功电能数据块 */

    E_D97_RULER_QUAD_2_NONE_POWER_TOTAL,   /* 2 象限无功总电能 */
    E_D97_RULER_QUAD_2_NONE_POWER_RATE,    /* 2 象限无功费率电能*/
    E_D97_RULER_QUAD_2_NONE_POWER_BLOCK,   /* 2 象限无功电能数据块 */

    E_D97_RULER_QUAD_3_NONE_POWER_TOTAL,   /* 3 象限无功总电能 */
    E_D97_RULER_QUAD_3_NONE_POWER_RATE,    /* 3 象限无功费率电能*/
    E_D97_RULER_QUAD_3_NONE_POWER_BLOCK,   /* 3 象限无功电能数据块 */

    /* 标签规约表电能量最大值对应表A.1*/
    E_D97_RULER_STANDARD_POWER_MAX = E_D97_RULER_QUAD_3_NONE_POWER_BLOCK, 

    /* 最大需量 */
    /* 标签规约表最大需量量最小值对应表A.2*/
    E_D97_RULER_STANDARD_DEMAND_MIN = E_D97_RULER_STANDARD_POWER_MAX + 1, 
     /* 正向有功总最大需量 */
    E_D97_RULER_FORTH_HAVE_DEMAND_TOTAL = E_D97_RULER_STANDARD_DEMAND_MIN,  
    E_D97_RULER_FORTH_HAVE_DEMAND_RATE,    /* 正向有功费率最大需量*/
    E_D97_RULER_FORTH_HAVE_DEMAND_BLOCK,   /* 正向有功最大需量数据块 */

    E_D97_RULER_BACK_HAVE_DEMAND_TOTAL,   /* 反向有功总最大需量 */
    E_D97_RULER_BACK_HAVE_DEMAND_RATE,    /* 反向有功费率最大需量*/
    E_D97_RULER_BACK_HAVE_DEMAND_BLOCK,   /* 反向有功最大需量数据块 */

    E_D97_RULER_FORTH_NONE_DEMAND_TOTAL,   /* 正向无功总最大需量 */
    E_D97_RULER_FORTH_NONE_DEMAND_RATE,    /* 正向无功费率最大需量*/
    E_D97_RULER_FORTH_NONE_DEMAND_BLOCK,      /* 正向无功最大需量数据块 */

    E_D97_RULER_BACK_NONE_DEMAND_TOTAL,   /* 反向无功总最大需量 */
    E_D97_RULER_BACK_NONE_DEMAND_RATE,    /* 反向无功费率最大需量*/
    E_D97_RULER_BACK_NONE_DEMAND_BLOCK,   /* 反向无功最大需量数据块 */

    E_D97_RULER_QUAD_1_NONE_DEMAND_TOTAL,   /* 1 象限无功总最大需量 */
    E_D97_RULER_QUAD_1_NONE_DEMAND_RATE,    /* 1 象限无功费率最大需量*/
    E_D97_RULER_QUAD_1_NONE_DEMAND_BLOCK,   /* 1 象限无功最大需量数据块 */
    
    E_D97_RULER_QUAD_4_NONE_DEMAND_TOTAL,   /* 4 象限无功总最大需量 */
    E_D97_RULER_QUAD_4_NONE_DEMAND_RATE,    /* 4 象限无功费率最大需量*/
    E_D97_RULER_QUAD_4_NONE_DEMAND_BLOCK,   /* 4 象限无功最大需量数据块 */

    E_D97_RULER_QUAD_2_NONE_DEMAND_TOTAL,   /* 2 象限无功总最大需量 */
    E_D97_RULER_QUAD_2_NONE_DEMAND_RATE,    /* 2 象限无功费率最大需量*/
    E_D97_RULER_QUAD_2_NONE_DEMAND_BLOCK,   /* 2 象限无功最大需量数据块 */

    E_D97_RULER_QUAD_3_NONE_DEMAND_TOTAL,   /* 3 象限无功总最大需量 */
    E_D97_RULER_QUAD_3_NONE_DEMAND_RATE,    /* 3 象限无功费率最大需量*/
    E_D97_RULER_QUAD_3_NONE_DEMAND_BLOCK,   /* 3 象限无功最大需量数据块 */

    /* 标签规约表最大需量量最大值对应表A.2*/
    E_D97_RULER_STANDARD_DEMAND_MAX = E_D97_RULER_QUAD_3_NONE_DEMAND_BLOCK, 

    /* 最大需量发生时间 */
    E_D97_RULER_FORTH_HAVE_DEMAND_TIME_TOTAL,   /* 正向有功总最大需量发生时间 */
    E_D97_RULER_FORTH_HAVE_DEMAND_TIME_RATE,    /* 正向有功费率最大需量发生时间*/
    E_D97_RULER_FORTH_HAVE_DEMAND_TIME_BLOCK,    /* 正向有功最大需量发生时间数据块 */

    E_D97_RULER_BACK_HAVE_DEMAND_TIME_TOTAL,   /* 反向有功总最大需量发生时间 */
    E_D97_RULER_BACK_HAVE_DEMAND_TIME_RATE,    /* 反向有功费率最大需量发生时间*/
    E_D97_RULER_BACK_HAVE_DEMAND_TIME_BLOCK,   /* 反向有功最大需量发生时间数据块 */

    E_D97_RULER_FORTH_NONE_DEMAND_TIME_TOTAL,   /* 正向无功总最大需量发生时间 */
    E_D97_RULER_FORTH_NONE_DEMAND_TIME_RATE,    /* 正向无功费率最大需量发生时间*/
    E_D97_RULER_FORTH_NONE_DEMAND_TIME_BLOCK,    /* 正向无功最大需量发生时间数据块 */

    E_D97_RULER_BACK_NONE_DEMAND_TIME_TOTAL,       /* 反向无功总最大需量发生时间 */
    E_D97_RULER_BACK_NONE_DEMAND_TIME_RATE,        /* 反向无功费率最大需量发生时间*/
    E_D97_RULER_BACK_NONE_DEMAND_TIME_BLOCK,       /* 反向无功最大需量发生时间数据块 */

    E_D97_RULER_QUAD_1_NONE_DEMAND_TIME_TOTAL,   /* 1 象限无功总最大需量发生时间 */
    E_D97_RULER_QUAD_1_NONE_DEMAND_TIME_RATE,    /* 1 象限无功费率最大需量发生时间*/
    E_D97_RULER_QUAD_1_NONE_DEMAND_TIME_BLOCK,   /* 1 象限无功最大需量发生时间数据块 */

    E_D97_RULER_QUAD_4_NONE_DEMAND_TIME_TOTAL,   /* 4 象限无功总最大需量发生时间 */
    E_D97_RULER_QUAD_4_NONE_DEMAND_TIME_RATE,    /* 4 象限无功费率最大需量发生时间*/
    E_D97_RULER_QUAD_4_NONE_DEMAND_TIME_BLOCK,   /* 4 象限无功最大需量发生时间数据块 */

    E_D97_RULER_QUAD_2_NONE_DEMAND_TIME_TOTAL,   /* 2 象限无功总最大需量发生时间 */
    E_D97_RULER_QUAD_2_NONE_DEMAND_TIME_RATE,    /* 2 象限无功费率最大需量发生时间*/
    E_D97_RULER_QUAD_2_NONE_DEMAND_TIME_BLOCK,   /* 2 象限无功最大需量发生时间数据块 */

    E_D97_RULER_QUAD_3_NONE_DEMAND_TIME_TOTAL,   /* 3 象限无功总最大需量发生时间 */
    E_D97_RULER_QUAD_3_NONE_DEMAND_TIME_RATE,    /* 3 象限无功费率最大需量发生时间*/
    E_D97_RULER_QUAD_3_NONE_DEMAND_TIME_BLOCK,   /* 3 象限无功最大需量发生时间数据块 */

    /* 标签规约表最大需量发生时间最大值对应表A.2*/
    E_D97_RULER_STANDARD_DEMAND_TIME_MAX = E_D97_RULER_QUAD_3_NONE_DEMAND_TIME_BLOCK, 

    /* 标签规约类型固定类最大值 对应表A1-A3*/
    E_D97_RULER_STANDARD_CONSTANT_MAX = E_D97_RULER_STANDARD_DEMAND_TIME_MAX, 

    /* 变量数据 */
    
    /*变量数据最小值 */
    E_D97_RULER_STANDARD_VAR_MIN = E_D97_RULER_STANDARD_CONSTANT_MAX + 1, 
    
    /* 最近一次编程时间 */
    E_D97_RULER_RECENT_PROGRAME_TIME = E_D97_RULER_STANDARD_VAR_MIN,      
    E_D97_RULER_RECENT_CLEAR_DEMAND_TIME,        /* 最近一次最大需量清0时间 */
    E_D97_RULER_PROGRAME_TIMES,                     /* 编程次数 */
    E_D97_RULER_CLEAR_DEMAND_TIMES,                 /* 最大需量清0次数 */
    E_D97_RULER_CELL_WORK_TIMES,                 /* 电池工作时间 */
    E_D97_RULER_PHASE_LOSS_TOTAL_TIMES,             /* 总断相次数 */
    E_D97_RULER_PHASE_A_LOSS_TIMES,                 /* A相断相次数 */
    E_D97_RULER_PHASE_B_LOSS_TIMES,              /* B相断相次数 */
    E_D97_RULER_PHASE_C_LOSS_TIMES,                 /* C相断相次数 */
    E_D97_RULER_PHASE_LOSS_SPEND,                   /* 总断相时间累积值 */
    E_D97_RULER_PHASE_A_LOSS_SPEND,               /* A相断相时间累积值 */
    E_D97_RULER_PHASE_B_LOSS_SPEND,               /* B相断相时间累积值 */
    E_D97_RULER_PHASE_C_LOSS_SPEND,               /* C相断相时间累积值 */

    E_D97_RULER_RECENT_PHASE_LOSS_START_TIME,      /* 最近一次断相起始时刻 */
    E_D97_RULER_RECENT_PHASE_A_LOSS_START_TIME,     /* A相最近一次断相起始时刻 */
    E_D97_RULER_RECENT_PHASE_B_LOSS_START_TIME,  /* B相最近一次断相起始时刻 */
    E_D97_RULER_RECENT_PHASE_C_LOSS_START_TIME,     /* C相最近一次断相起始时刻 */

    E_D97_RULER_RECENT_PHASE_LOSS_END_TIME,          /* 最近一次断相结束时刻 */
    E_D97_RULER_RECENT_PHASE_A_LOSS_END_TIME,       /* A相最近一次断相结束时刻 */
    E_D97_RULER_RECENT_PHASE_B_LOSS_END_TIME,    /* B相最近一次断相结束时刻 */
    E_D97_RULER_RECENT_PHASE_C_LOSS_END_TIME,    /* C相最近一次断相结束时刻 */
    E_D97_RULER_PHASE_A_VOLT,                     /* A相电压 */
    E_D97_RULER_PHASE_B_VOLT,                     /* B相电压 */
    E_D97_RULER_PHASE_C_VOLT,                     /* C相电压 */
    E_D97_RULER_PHASE_A_ELEC,                     /* A相电流 */
    E_D97_RULER_PHASE_B_ELEC,                     /* B相电流 */
    E_D97_RULER_PHASE_C_ELEC,                     /* C相电流 */

    E_D97_RULER_INSTANT_HAVE_POWER_RATE,         /* 瞬时有功功率 */
    E_D97_RULER_PHASE_A_HAVE_POWER_RATE,         /* A相有功功率  */
    E_D97_RULER_PHASE_B_HAVE_POWER_RATE,         /* B相有功功率  */
    E_D97_RULER_PHASE_C_HAVE_POWER_RATE,         /* C相有功功率  */

    E_D97_RULER_FORTH_HAVE_POWER_RATE_LIMIT,     /* 正向有功功率上限 */
    E_D97_RULER_BACK_HAVE_POWER_RATE_LIMIT,         /* 反向有功功率上限 */

    E_D97_RULER_INSTANT_NONE_POWER_RATE,         /* 瞬时无功功率 */
    E_D97_RULER_PHASE_A_NONE_POWER_RATE,         /* A相无功功率  */
    E_D97_RULER_PHASE_B_NONE_POWER_RATE,         /* B相无功功率  */
    E_D97_RULER_PHASE_C_NONE_POWER_RATE,         /* C相无功功率  */


    E_D97_RULER_TOTAL_POWER_RATE_FACTOR,         /* 总功率因数 */
    E_D97_RULER_PHASE_A_POWER_RATE_FACTOR,         /* A相功率因数 */
    E_D97_RULER_PHASE_B_POWER_RATE_FACTOR,         /* B相功率因数 */
    E_D97_RULER_PHASE_C_POWER_RATE_FACTOR,         /* C相功率因数 */

    /* 对应表A5 参变量数据标识编码表 */
    E_D97_RULER_DATE_AND_WEEK_NUMBER,             /* 日期和周数 */
    E_D97_RULER_TIME,                             /* 时间 */
    E_D97_RULER_STWD_METER_RUN,                      /* 电能运行状态字 */
    E_D97_RULER_STWD_NETWIRE_RUN,                  /* 电网运行状态字 */
    E_D97_RULER_STWD_WEEK_DAY,                       /* 周休日运行状态字 */

    E_D97_RULER_METER_HAVA_CONSTANT,              /* 电表常数(有功) */
    E_D97_RULER_METER_NONE_CONSTANT,              /* 电表常数(无功) */

    E_D97_RULER_METER_ID,                         /* 表号 */
    E_D97_RULER_USER_ID,                          /* 用户号 */
    E_D97_RULER_DEV_CODE,                          /* 设备码 */
    E_D97_RULER_DEMAND_PERIOD,                      /* 最大需要量周期 */
    E_D97_RULER_SLIP_TIME,                          /* 滑差时间 */
    E_D97_RULER_DISPLAY_INTURN_TIME,              /* 循显时间 */
    E_D97_RULER_DISPLAY_HOLD_TIME,                   /* 停显时间 */
    E_D97_RULER_DISPLAY_POWER_DECIMAL_DIGITS,      /* 显示电能小数位数 */
    E_D97_RULER_DISPLAY_DEMAND_DECIMAL_DIGITS,      /* 显示功率(最大需量)小数位数 */
    E_D97_RULER_AUTO_READ_METER_DATE,              /* 自动抄表日期 */
    E_D97_RULER_LOAD_DELEGATE_DATE,               /* 负荷代表日 */
    E_D97_RULER_HAVE_POWER_START_DATA,            /* 有功电能起始读取 */
    E_D97_RULER_NONE_POWER_START_DATA,            /* 无功电能起始读取 */
    E_D97_RULER_OUTPUT_PULSE_WIDTH,                  /* 输出脉冲宽度 */
    E_D97_RULER_PASSWORD,                         /* 密码权限及密码 */
    E_D97_RULER_YEAR_ZONE_P,                      /* 年时区数 P */
    E_D97_RULER_DAY_ZONE_Q,                          /* 日时段表数 q */
    E_D97_RULER_DAY_ZONE_M,                          /* 日时段(每日切换数)m <=10*/
    E_D97_RULER_RATE_K,                                /* 费率数 K<= 14 */
    E_D97_RULER_HOLIDAY_NUMBER_N,                  /* 公共假日数 n */
    E_D97_RULER_START_DATE_DAY_ZONE_P,              /* P时区起始日期及日时段表号(P = 1~F) */
    E_D97_RULER_START_TIME_RATE_TH_Q_ZONE_M,      /* 第(q)日时段第(m)时段起始时间及费率号 (q=1~8)(m=1-m_max<=10)*/
    E_D97_RULER_DATE_DAY_ZONE_HOLIDAY_N,          /* 第(n)公共假日日期及日时段表号 */
    E_D97_RULER_WEEKS_DAY_ZONE,                        /* 周休日采用的时时段表号 */
    E_D97_RULER_LOAD_RECORD_START_TIME,           /* 负荷记录起始时间 */
    E_D97_RULER_LOAD_RECORD_PERIOD_TIME,          /* 负荷记录间隔时间 */    

    /* 对应表A6负荷记录数据标识编码表 */
   
    E_D97_RULER_CURRENT_POWER_LOAD_BLOCK,          /* 当前正向有功总电能负荷记录数据块 */
    E_D97_RULER_CURRENT_DEMAND_LOAD_BLOCK,           /* 当前正向最大需量负荷记录数据块 */

    E_D97_RULER_STANDARD_VAR_MAX = E_D97_RULER_CURRENT_DEMAND_LOAD_BLOCK, /* 变量数据规约类型 最大值 */
    E_D97_RULER_STANDARD_MAX = E_D97_RULER_CURRENT_DEMAND_LOAD_BLOCK, /* dlt645 97 标准规约类型最大值 */
    
    /* 用户扩展 */
    E_D97_RULER_USER_EXTEND_MIN,                 /*  用户扩展规约类型起始位置 */

    //.....这里添加用户的规约类型

    E_D97_RULER_USER_EXTEND_MAX,                   /* 用户自定义规约最大值 */


    /* 这之上添加用户扩展规约 */
    E_D97_RULER_MAX
    
}E_D97_RULER_TYPE;


/* 错误类型定义 */
typedef enum
{
    E_D97_OK = 0,  /* 0 返回正确 */

    /* 参数错误 */
    E_D97_ERROR_PARA_OUT_RANGE,      /* 参数越界 */
    E_D97_ERROR_PARA_POINTER_NULL,   /* 参数指针为空 */
    E_D97_ERROR_PARA_NONE,            /* 不存在 */
    E_D97_ERROR_ID_UNKNOWN,          /* 未知的规约 ID 规约ID 没有定义 */

    //check frame
    E_D97_ERROR_FRAME_UNCOMP,        /* 不完整的帧数据 */
    E_D97_ERROR_FRAME_0x68,          /* 测试帧帧起始符 0x68 的位置不对 */
    E_D97_ERROR_FRAME_CHECK_SUM,     /* 测试帧检验和不对 */
    E_D97_ERROR_FRAME_END_0x16,      /* 测试帧结束符 0x16 不对 */

}eD97Err;

/* DLT645 1997 版规约解析函数指针类型 */    
typedef eD97Err(*F_D97_RULER_TRANS)(E_D97_TRANS_FLAG, void*, void*);


/* 查看数据的时间点 */
typedef enum
{
    E_D97_CHECK_POINT_CURRENT,             /* 当前 */
    E_D97_CHECK_POINT_LAST_MONTH,          /* 上月 */
    E_D97_CHECK_POINT_LAST_LAST_MONTH,   /* 上上月 */
    
}E_D97_CHECK_POINT;


/* 帧包中含有的数据类型 组合结构

 说明:    
 (1)XXXXXX.XX 代表测量值的整数值和小数位
 (2)NNNN 为计算值和设定值
 (3)YYMMDDWW 为年、月、日、周次
 (4)hhmmss 为时、分、秒

  每种类型对应一种结构体类型来解析或封装转换数据
*/
typedef enum
{
    E_D97_FORMAT_UNKOWN,
    /* 时间 */
    E_D97_FORMAT_MMDDHHmm,
    E_D97_FORMAT_YYMMDDWW,
    E_D97_FORMAT_hhmmss,
    E_D97_FORMAT_DDhh,

    /* 组合 */
    E_D97_FORMAT_MMDDNN,
    E_D97_FORMAT_MMDDhhmm,
    E_D97_FORMAT_hhmmNN,
    
    
    /* NN */
    E_D97_FORMAT_NN,
    E_D97_FORMAT_NN_1 = E_D97_FORMAT_NN,
    
    E_D97_FORMAT_NNNN,
    E_D97_FORMAT_NN_2 = E_D97_FORMAT_NNNN,
    
    E_D97_FORMAT_NNNNNN,
    E_D97_FORMAT_NN_3 = E_D97_FORMAT_NNNNNN,
    
    E_D97_FORMAT_NNNNNNNN,    
    E_D97_FORMAT_NN_4 = E_D97_FORMAT_NNNNNNNN,

    E_D97_FORMAT_NNNNNNNNNN,    
    E_D97_FORMAT_NN_5 = E_D97_FORMAT_NNNNNNNNNN,
    
    E_D97_FORMAT_NN_6,
    E_D97_FORMAT_NN_7,
    E_D97_FORMAT_NN_8,
    E_D97_FORMAT_NN_9,
    
    E_D97_FORMAT_NNNNNNN_N,  /* NNNNNN.N */
    
    /* XX.XX */
    E_D97_FORMAT_X,          /* X */
    E_D97_FORMAT_XX,          /* X */
    E_D97_FORMAT_XXX,        /* XXX */
    E_D97_FORMAT_X_XXX,      /* X.XXX */
    E_D97_FORMAT_XX_XX,      /* XX.XX */
    E_D97_FORMAT_XX_XXXX,    /* XX.XXXX */
    E_D97_FORMAT_XXXXXX_XX,  /* XXXXXX.XX */

    /* STATE WORD */
    E_D97_FORMAT_STWD_METER_RUN,       /* 电表运行状态字 */
    E_D97_FORMAT_STWD_NETWIRE_RUN,     /* 电网状态字 */
    E_D97_FORMAT_STWD_WEEK_DAY,        /* 周休日状态字 */
    E_D97_FORMAT_MAX,

}E_D97_DATA_FORMAT;

/* 规约的读写权限 */
typedef enum
{
    E_D97_RDWR_READ_ONLY,   /* 只读属性 */
    E_D97_RDWR_WRITE_ONLY,  /* 只写属性 */
    E_D97_RDWR_READ_WRITE,  /* 可读可写 */

}E_D97_RULER_READ_WRITE;


/* 帧数据的单位类型 */
typedef enum
{
    E_D97_UNIT_COUNT,             /* 个数 */
    E_D97_UNIT_TIME,              /* 次数 */
    E_D97_UNIT_FACTOR,            /* 因数 */
    E_D97_UNIT_NUMBER,            /* 常数 */
    E_D97_UNIT_MMDDHHmm,          /* 月_日_小时_分钟 */
    E_D97_UNIT_MMDDhhmm,          /* 月_日_小时_分钟 */
    E_D97_UNIT_YYMMDDWW,          /* 年月日周 */
    E_D97_UNIT_DD,
    E_D97_UNIT_hhmmss,            /* 小时 分 秒 */
    E_D97_UNIT_hh,                /* 小时 */
    E_D97_UNIT_mm,                /* 分钟 */
    E_D97_UNIT_ss,                /* 秒 */
    E_D97_UNIT_ms,                /* 毫秒 */
    E_D97_UNIT_DDhh,              /* 日 小时 */
    E_D97_UNIT_A,                 /* 电流 安 */
    E_D97_UNIT_V,                 /* 电压 伏 */
    E_D97_UNIT_KW,                  /* 功 千瓦特 */
    E_D97_UNIT_KWH,                  /* 功 千瓦特时 */
    E_D97_UNIT_KVARH,                 
    E_D97_UNIT_X,                  /* XX 不带小数点 */
    E_D97_UNIT_X_DOT,              /* 似类 XX.XX 带小数点 */
    E_D97_UNIT_stwd,              /* 状态字 */
    E_D97_UNIT_ID,                /* 表号，用户号，设备号 */

    
    
}E_D97_DATA_UNIT;

/* 控制码域 C 帧传送方向 */
typedef enum
{
    E_D97_CTRL_DIR_M2S, // 主站到从站
    E_D97_CTRL_DIR_S2M, // 从站到主站
    
}E_D97_CTRL_DIR;

/* 从站异常标志 */
typedef enum
{
    E_D97_CTRL_SR_OK, // 从站正常应答
    E_D97_CTRL_SR_NO, // 从站异常应答
    
}E_D97_CTRL_SR;

/* 有无后续帧标志 */
typedef enum
{
    E_D97_CTRL_FLW_NONE, //无后续
    E_D97_CTRL_FLW_HAVE, //有后续
    
}E_D97_CTRL_FLW;

/* 控制域C 功能码 */
typedef enum
{
    E_D97_CTRL_FNC_RESERVE                    = 0x00,   /*保留*/
    E_D97_CTRL_FNC_READ_DATA                  = 0x01,   /*读取数据*/
    E_D97_CTRL_FNC_READ_AFTERDATA            = 0x02,   /*读取后续数据*/
    E_D97_CTRL_FNC_READ_DATA_RE              = 0x03,   /*重读数据*/
    E_D97_CTRL_FNC_WRITE_DATA                = 0x04,   /*写数据*/
    E_D97_CTRL_FNC_SYNC_TIME                 = 0x08,   /*广播校时*/
    E_D97_CTRL_FNC_WRITE_ADDR                = 0x0A,   /*写设备地址*/
    E_D97_CTRL_FNC_MODIFY_BAUD                = 0x0C,   /*更改通信速率*/
    E_D97_CTRL_FNC_MODIFY_PASSWORD           = 0x0F,   /*更改密码*/
    E_D97_CTRL_FNC_MAXDEMAND_CLEAR           = 0x10,   /*最大需求量清 0*/
    
}E_D97_CTRL_FNC;

/*  解析包数据域的结果标志 */
typedef enum
{
    E_D97_UNPD_FLG_OK,          /* 解析正确 数据可用 且数据是正常的答复 */
    E_D97_UNPD_FLG_ERROR_OK,    /* 解析正确 数据可用 且数据是异常的答复 */
    E_D97_UNPD_FLG_NONE_DATA,   /* 没有对应除规约 数据 */
    E_D97_UNPD_FLG_FUNC_NULL,   /* 没有解析函数 */
    E_D97_UNPD_FLG_FUNC_ERROR,  /* 有解析函数，但解析过程出错 */
    E_D97_UNPD_FLG_NONE_STRUCT, /* 没有解析该类型的用户侧数据结构 */

}E_D97_UNPD_FLG;

typedef enum
{
    E_D97_ST_OK, //表示正常
    E_D97_ST_NO, //表示不正常，错误，超过
    
}E_D97_ST_OK_NO;

/* 结构 */
/* DLT645 1997 规约类型额外参数 */
typedef struct
{
    E_D97_CHECK_POINT checkPoint;       /* 检查时间点 */

    unsigned char      rate_k;           /* 费率类型 值k(1 ~ 14)*/
    unsigned char    year_p;           /* 年时区数 p(1~F) */
    unsigned char    holiday_n;       /*公共假日数n(n < 255)*/
    unsigned char      day_q;              /*日时段表数q (1 ~ 8)*/
    unsigned char    interval_m;     /*日时段(每日切换数)m (1~10)*/
        
}S_D97_RULER_TYPE_PARA;





/* 规约的详细信息 */
typedef struct
{
    E_D97_RULER_TYPE         type;       /* 规约类型 */
    S_D97_RULER_TYPE_PARA    para;       /* 规约类型的额外数据 */      
    E_D97_DATA_FORMAT        format;     /* 帧中数据格式 */
    E_D97_DATA_UNIT          unit;       /* 单位类型 */
    E_D97_RULER_READ_WRITE   rdwr;       /* 读写属性 */
    
    int                      length;     /* 数据长度(字节数) */
    F_D97_RULER_TRANS        func;       /* 转换函数 */
    char name[D97_NAME_LEN];             /* 数据项名称 */

}S_D97_RULER_INFOR;

typedef struct
{
    unsigned short ruler_id;     /* 规约标签符 C0 C1  型如 0x40E3 */
    unsigned char  ctrl_code;    /* 控制码 */
    unsigned char  data_len;     /* 数据域字节数 包括规约和其它数据 */
    char* address;               /* 地址 */
    char* data;                  /* 数据 */

}S_D97_PACK_FRAME;


/* 控制域C 结构定义 */
typedef struct
{
    E_D97_CTRL_DIR direct;    // 帧传送方向 
    E_D97_CTRL_SR  reply;      // 从站应答异常标志
    E_D97_CTRL_FLW follow;      // 有无后续帧
    E_D97_CTRL_FNC funcode;      // 功能码
    
}S_D97_CTRL_CODE;


/* 错误信息状态字 */
typedef struct
{
    E_D97_ST_OK_NO  rate_k;      // E_D97_ST_NO 表示费率k数超
    E_D97_ST_OK_NO    day_q;      // E_D97_ST_NO 日时段数超
    E_D97_ST_OK_NO  year_p;     // E_D97_ST_NO 年时区数超
    E_D97_ST_OK_NO    password;    // E_D97_ST_NO 密码错
    E_D97_ST_OK_NO  rule_id;    // E_D97_ST_NO 数据标识错
    E_D97_ST_OK_NO    data;        // E_D97_ST_NO 非法数据
    
}S_D97_STWD_ERR;

/* 电表状态字 用户侧结构 */
typedef struct
{
    E_D97_ST_OK_NO dir_none;   // 无功电能方向         正向(E_D97_ST_OK) 反向(E_D97_ST_NO)
    E_D97_ST_OK_NO dir_have;   // 有功电能方向         正向(E_D97_ST_OK) 反向(E_D97_ST_NO)
    E_D97_ST_OK_NO cell;       // 电池电压          正常(E_D97_ST_OK) 欠压(E_D97_ST_NO)
    E_D97_ST_OK_NO demand;        // 最大需量计算方式  滑差(E_D97_ST_OK) 区间(E_D97_ST_NO)
    E_D97_ST_OK_NO read;       // 抄表方式             自动(E_D97_ST_OK) 手动(E_D97_ST_NO)
    
}S_D97_STWD_METER;

/*电网运行状态字 用户侧结构 */
typedef struct
{
    E_D97_ST_OK_NO volt_A;      // A相过压  正常(E_D97_ST_OK) 过压(E_D97_ST_NO)
    E_D97_ST_OK_NO volt_B;      // B相过压  正常(E_D97_ST_OK) 过压(E_D97_ST_NO) 
    E_D97_ST_OK_NO volt_C;        // C相过压  正常(E_D97_ST_OK) 过压(E_D97_ST_NO)
    E_D97_ST_OK_NO out_A;       // A相断电  正常(E_D97_ST_OK) 断电(E_D97_ST_NO)
    E_D97_ST_OK_NO out_B;        // B相断电  正常(E_D97_ST_OK) 断电(E_D97_ST_NO)
    E_D97_ST_OK_NO out_C;        // C相断电  正常(E_D97_ST_OK) 断电(E_D97_ST_NO)
    
}S_D97_STWD_NET_WIRE;

// 周休日状态字 用户侧结构
typedef struct
{
    E_D97_ST_OK_NO day_1;      /* 周1   工作(E_D97_ST_OK) 休息(E_D97_ST_NO)*/
    E_D97_ST_OK_NO day_2;      /* 周2   工作(E_D97_ST_OK) 休息(E_D97_ST_NO)*/
    E_D97_ST_OK_NO day_3;      /* 周3   工作(E_D97_ST_OK) 休息(E_D97_ST_NO)*/
    E_D97_ST_OK_NO day_4;      /* 周4   工作(E_D97_ST_OK) 休息(E_D97_ST_NO)*/
    E_D97_ST_OK_NO day_5;      /* 周5   工作(E_D97_ST_OK) 休息(E_D97_ST_NO)*/
    E_D97_ST_OK_NO day_6;      /* 周6   工作(E_D97_ST_OK) 休息(E_D97_ST_NO)*/
    E_D97_ST_OK_NO day_7;      /* 周日  工作(E_D97_ST_OK) 休息(E_D97_ST_NO)*/

}S_D97_STWD_WEEK_DAY;


typedef struct
{
    unsigned char MM;
    unsigned char DD;
    unsigned char HH;
    unsigned char mm;
    
}S_D97_FMT_MMDDHHmm;



typedef struct
{
    unsigned char YY;
    unsigned char MM;
    unsigned char DD;
    unsigned char WW;
    
}S_D97_FMT_YYMMDDWW;

typedef struct
{
    unsigned char DD;
    unsigned char hh;
    
}S_D97_FMT_DDhh;

typedef struct
{
    unsigned char MM;
    unsigned char DD;
    unsigned char NN;
}S_D97_FMT_MMDDNN;

typedef struct
{
    unsigned char hh;
    unsigned char mm;
    unsigned char ss;    
    
}S_D97_FMT_hhmmss;

/* 用户接口侧数据结构 */
typedef union
{



    /* 状态字 */
    S_D97_STWD_ERR      stwd_err; // 错误信息状态字
    S_D97_STWD_WEEK_DAY weed_day; // 周休日状态字
    S_D97_STWD_NET_WIRE net_wire; // 电网运行状态字
    S_D97_STWD_METER     meter;    // 电表运行状态字


}U_D97_DATA_UNPACK;


/* 解析帧信息数据结构 */
typedef struct
{
    unsigned char          ctrl_c;           /* 控制码 字节型 */
    unsigned char          lead_num;         /* 前导字符 0xFE的个数 */
    unsigned short         ruler_id;         /* 规约ID */
    unsigned short           data_len;         /* 数据域长 */
    unsigned short         frame_len;         
    
    E_D97_RULER_TYPE       type;             /* 规约类型 */
    E_D97_DATA_FORMAT      format;           /* 帧中数据格式 */
    E_D97_DATA_UNIT        unit;             /* 单位类型 */
    E_D97_UNPD_FLG         flag;             /* 解析数据到用户侧数据的标志，说明解析状态 决定data_unpack 是否可用 */
    S_D97_CTRL_CODE        ctrl_s;           /* 控制码结构 */
    S_D97_RULER_TYPE_PARA  para;             /* 规约类型的额外数据 */ 
    
    U_D97_DATA_UNPACK      data_unpack;      /* 转换为用户侧的数据 */ 
    unsigned char          data_pack[D97_DATA_MAX_NR];   /* 数据域 不包括规约ID的部分 没有做转换 */
    unsigned  char         address[D97_ADDR_LEN+1]; //12位地址域数据         
}S_D97_UNPACK;



/* 公共函数 */
/* 通过规约ID获取规约其它详细信息 */
eD97Err get_d97_ruler_info(unsigned short rulerID, S_D97_RULER_INFOR *outRulerInfo);

/* 通过规约类型 和 一些额外的参数来获得规约 ID */
eD97Err get_d97_ruler_id(E_D97_RULER_TYPE rulerType,  S_D97_RULER_TYPE_PARA para, unsigned short *poutRulerID);

//eD97Err get_d97_ruler_type();

/* 通过地址 规约ID 数据域数据及长度 封帧 */
eD97Err pack_d97_frame_by_data(S_D97_PACK_FRAME *inPara, char *outBuffer, int *outLength);  

//解析 dlt645 97帧 
eD97Err unpack_d97_frame(void *inpBuffer, int inBufferLength, S_D97_UNPACK *outpFrame);

/* 根据数据格式类型转换帧数据 */
eD97Err trans_d97_frame_data(E_D97_DATA_FORMAT format,
                            E_D97_TRANS_FLAG flag,
                            void *pUser,
                            void *pFrame);

/* 第一个有效帧查找函数 */
int get_d97_first_valid_frame(void *inpBuffer,  // 输入buffer
                              int inBufferLen,  // 输入buffer字长
                              char** poutPos,   // 第一个有效帧的位置
                              int * poutLen);   // 第一个有效帧的长度
/* 判断一个帧是不是正确的dlt645 1997 */
int is_right_d97_frame(void *inpBuffer, int inBufferLen);

/* 具体的分解转换函数 */
eD97Err trans_d97_format_X(E_D97_TRANS_FLAG flag, void *user, void*frame);
eD97Err trans_d97_format_XX(E_D97_TRANS_FLAG flag, void *user, void*frame);
eD97Err trans_d97_format_XXX(E_D97_TRANS_FLAG flag, void *user, void*frame);
eD97Err trans_d97_format_X_XXX(E_D97_TRANS_FLAG flag, void *user, void*frame);
eD97Err trans_d97_format_XX_XX(E_D97_TRANS_FLAG flag, void *user, void*frame);
eD97Err trans_d97_format_XX_XXXX(E_D97_TRANS_FLAG flag, void *user, void*frame);
eD97Err trans_d97_format_XXXXXX_XX(E_D97_TRANS_FLAG flag, void *user, void*frame);

/*YYMMDDhhmmss*/
eD97Err trans_d97_format_MMDDHHmm(E_D97_TRANS_FLAG flag, void *user, void*frame);
eD97Err trans_d97_format_YYMMDDWW(E_D97_TRANS_FLAG flag, void *user, void*frame);
eD97Err trans_d97_format_hhmmss(E_D97_TRANS_FLAG flag, void *user, void*frame);
eD97Err trans_d97_format_DDhh(E_D97_TRANS_FLAG flag, void *user, void*frame);

/* state word transfer function */
eD97Err trans_d97_format_stwd_meter(E_D97_TRANS_FLAG flag, void *user, void*frame);
eD97Err trans_d97_format_stwd_netwire(E_D97_TRANS_FLAG flag, void *user, void*frame);
eD97Err trans_d97_format_stwd_weekday(E_D97_TRANS_FLAG flag, void *user, void*frame);
eD97Err trans_d97_format_stwd_error(E_D97_TRANS_FLAG flag, void *user, void*frame);

eD97Err trans_d97_format_MMDDNN(E_D97_TRANS_FLAG flag, void *user, void*frame);
eD97Err trans_d97_format_MMDDhhmm(E_D97_TRANS_FLAG flag, void *user, void*frame);
eD97Err trans_d97_format_hhmmNN(E_D97_TRANS_FLAG flag, void *user, void*frame);

eD97Err trans_d97_format_NN(E_D97_TRANS_FLAG flag, void *user, void*frame);
eD97Err trans_d97_format_NNNN(E_D97_TRANS_FLAG flag, void *user, void*frame);
eD97Err trans_d97_format_NNNNNN(E_D97_TRANS_FLAG flag, void *user, void*frame);
eD97Err trans_d97_format_NNNNNNNN(E_D97_TRANS_FLAG flag, void *user, void*frame);
eD97Err trans_d97_format_NN_6(E_D97_TRANS_FLAG flag, void *user, void*frame);
eD97Err trans_d97_format_NNNNNN_N(E_D97_TRANS_FLAG flag, void *user, void*frame);

// 错误状态字
eD97Err trans_d97_format_err_word(E_D97_TRANS_FLAG flag, void *user, void*frame);



/*内部函数*/
void d97_str2bcd(const char *pstr, unsigned char *pbcd, int len);
void bcd2str(const char* inBCD, char *outStr, int len);       /* BCD 转换为 字符串 */
double d97_bcd_to_decimal(unsigned char* pBcd, int len);
int  d97_remove_dot(int len, char*inArray, char *outArray);
void d97_bcd2str(const char* inBCD, char *outStr, int len);
double d97_bcd_to_double(unsigned char* pBcd, int len,int LeftDigit);
/* 解析控制码 */
eD97Err trans_d97ctrl_struct2char(unsigned char *outChar, S_D97_CTRL_CODE *inStruct); //将结构封装成字节
eD97Err trans_d97ctrl_char2struct(unsigned char inChar,  S_D97_CTRL_CODE *outStruct); //将字节封装成结构

#if 0




/* 封装与解封装 */

/* frame */
int pack_d97_frame_by_id(); /* */
int pack_d97_frame_by_type();

/* data */
int pack_d97_data_field();
int unpack_d97_data_field();






#endif 


#endif /* _DLT645_API_1997_H_ */


