/* This file is generated by tdr. */
/* No manual modification is permitted. */

/* metalib version: 10 */
/* metalib md5sum: 6f5632e4a08068fb87f5e36963885eb8 */

/* creation time: Tue Jun  4 14:17:59 2019 */
/* tdr version: 2.7.26, build at 20171102 */

#ifndef BBData_h_
#define BBData_h_

#include "TdrBuf.h"
#include "TdrError.h"
#include "TdrBufUtil.h"

#include "BlackBoard.h"

namespace BlackBoard
{

using tsf4g_tdr::TdrError;
using tsf4g_tdr::TdrReadBuf;
using tsf4g_tdr::TdrWriteBuf;


#pragma pack(1)


class BBDataBodyUnion
{
    public: /* members */
        union
        {
            BB_ServerTest stServerTest; /**id:0*/
            BT_Monster_Normal stMonsterNormal; /**id:1*/
        };

    public: /* methods */
        TdrError::ErrorType construct(int64_t selector);

        TdrError::ErrorType construct();

        TdrError::ErrorType pack(int64_t selector, TdrWriteBuf& destBuf, unsigned cutVer = 0) const;
        TdrError::ErrorType pack(int64_t selector, char* buffer, size_t size,
                                 size_t* usedSize = NULL, unsigned cutVer = 0) const;

        TdrError::ErrorType unpack(int64_t selector, TdrReadBuf& srcBuf, unsigned cutVer = 0);
        TdrError::ErrorType unpack(int64_t selector, const char* buffer, size_t size,
                                   size_t* usedSize = NULL, unsigned cutVer = 0);

        TdrError::ErrorType visualize(int64_t selector, TdrWriteBuf& destBuf,
                                      int indent = 0, char separator = '\n') const;
        TdrError::ErrorType visualize(int64_t selector, char* buffer, size_t size,
                                      size_t* usedSize = NULL, int indent = 0, char separator = '\n') const;


    public:
        /* version infomation */
        enum
        {
            BASEVERSION = 1,
            CURRVERSION = 1,
        };
};

typedef       BBDataBodyUnion          tagBBDataBodyUnion;
typedef       BBDataBodyUnion             BBDATABODYUNION;
typedef       BBDataBodyUnion*          LPBBDATABODYUNION;
typedef const BBDataBodyUnion*         LCPBBDATABODYUNION;


class BBData // 登录系统上行包
{
    public: /* members */
        int32_t iType;
        BBDataBodyUnion stDataBody;

    public: /* methods */
        TdrError::ErrorType construct();

        TdrError::ErrorType pack(TdrWriteBuf& destBuf, unsigned cutVer = 0) const;
        TdrError::ErrorType pack(char* buffer, size_t size, size_t* usedSize = NULL, unsigned cutVer = 0) const;

        TdrError::ErrorType unpack(TdrReadBuf& srcBuf, unsigned cutVer = 0);
        TdrError::ErrorType unpack(const char* buffer, size_t size, size_t* usedSize = NULL, unsigned cutVer = 0);

        /* set indent = -1 to disable indent */
        TdrError::ErrorType visualize(TdrWriteBuf& destBuf, int indent = 0, char separator = '\n') const;
        TdrError::ErrorType visualize(char* buffer, size_t size, size_t* usedSize = NULL, int indent = 0, char separator = '\n') const;
        const char* visualize_ex(TdrWriteBuf& destBuf, int indent = 0, char separator = '\n') const;
        const char* visualize_ex(char* buffer, size_t size, size_t* usedSize = NULL, int indent = 0, char separator = '\n') const;


    public:
        /* version infomation */
        enum
        {
            BASEVERSION = 1,
            CURRVERSION = 1,
        };
};

typedef       BBData          tagBBData;
typedef       BBData             BBDATA;
typedef       BBData*          LPBBDATA;
typedef const BBData*         LCPBBDATA;


#pragma pack()

}
#endif
