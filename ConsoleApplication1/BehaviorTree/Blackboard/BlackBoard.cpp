/* This file is generated by tdr. */
/* No manual modification is permitted. */

/* metalib version: 10 */
/* metalib md5sum: 6f5632e4a08068fb87f5e36963885eb8 */

/* creation time: Tue Jun  4 14:17:59 2019 */
/* tdr version: 2.7.26, build at 20171102 */

#if defined(_WIN32) || defined(_WIN64)
#pragma warning(disable:4996 4244)
#endif

#include "BlackBoard.h"
#include "TdrTypeUtil.h"

namespace BlackBoard
{

using tsf4g_tdr::TdrBufUtil;
using tsf4g_tdr::TdrTypeUtil;



TdrError::ErrorType
BB_ServerTest::construct()
{
    TdrError::ErrorType ret = TdrError::TDR_NO_ERROR;

    this->iTestKeyNum = 0;

    this->iTestKey1 = 0;

    this->iTestKey2 = 0;

    this->iTestKey3 = 0;

    return ret;
}

TdrError::ErrorType
BB_ServerTest::pack(char* buffer, size_t size, size_t* usedSize, unsigned cutVer) const
{
    if (NULL == buffer)
    {
        TSF4G_TDR_DEBUG_TRACE();
        return TdrError::TDR_ERR_NULL_POINTER_PARAMETER;
    }

    TdrWriteBuf destBuf(buffer, size);
    TdrError::ErrorType ret = pack(destBuf, cutVer);
    if (NULL != usedSize)
    {
        *usedSize = destBuf.getUsedSize();
    }

    return ret;
}

TdrError::ErrorType
BB_ServerTest::pack(TdrWriteBuf& destBuf, unsigned cutVer) const
{
    TdrError::ErrorType ret = TdrError::TDR_NO_ERROR;

    /* adjust cutversion */
    if (0 == cutVer || BB_ServerTest::CURRVERSION < cutVer)
    {
        cutVer = BB_ServerTest::CURRVERSION;
    }

    /* check cutversion */
    if (BB_ServerTest::BASEVERSION > cutVer)
    {
        TSF4G_TDR_DEBUG_TRACE();
        return TdrError::TDR_ERR_CUTVER_TOO_SMALL;
    }

    /* pack member: this->iTestKeyNum */
    {
        ret = destBuf.writeInt32(this->iTestKeyNum);
        if (TdrError::TDR_NO_ERROR != ret)
        {
            TSF4G_TDR_DEBUG_TRACE();
            return ret;
        }
    }

    /* pack member: this->iTestKey1 */
    {
        ret = destBuf.writeInt32(this->iTestKey1);
        if (TdrError::TDR_NO_ERROR != ret)
        {
            TSF4G_TDR_DEBUG_TRACE();
            return ret;
        }
    }

    /* pack member: this->iTestKey2 */
    {
        ret = destBuf.writeInt32(this->iTestKey2);
        if (TdrError::TDR_NO_ERROR != ret)
        {
            TSF4G_TDR_DEBUG_TRACE();
            return ret;
        }
    }

    /* pack member: this->iTestKey3 */
    {
        ret = destBuf.writeInt32(this->iTestKey3);
        if (TdrError::TDR_NO_ERROR != ret)
        {
            TSF4G_TDR_DEBUG_TRACE();
            return ret;
        }
    }

    return ret;
}

TdrError::ErrorType
BB_ServerTest::unpack(const char* buffer, size_t size, size_t* usedSize, unsigned cutVer)
{
    if (NULL == buffer)
    {
        TSF4G_TDR_DEBUG_TRACE();
        return TdrError::TDR_ERR_NULL_POINTER_PARAMETER;
    }

    TdrReadBuf srcBuf(buffer, size);
    TdrError::ErrorType ret = unpack(srcBuf, cutVer);
    if (NULL != usedSize)
    {
        *usedSize = srcBuf.getUsedSize();
    }

    return ret;
}

TdrError::ErrorType
BB_ServerTest::unpack(TdrReadBuf& srcBuf, unsigned cutVer)
{
    TdrError::ErrorType ret = TdrError::TDR_NO_ERROR;

    /* adjust cutversion */
    if (0 == cutVer || BB_ServerTest::CURRVERSION < cutVer)
    {
        cutVer = BB_ServerTest::CURRVERSION;
    }

    /* check cutversion */
    if (BB_ServerTest::BASEVERSION > cutVer)
    {
        TSF4G_TDR_DEBUG_TRACE();
        return TdrError::TDR_ERR_CUTVER_TOO_SMALL;
    }

    /* unpack member: this->iTestKeyNum */
    {
        ret = srcBuf.readInt32(this->iTestKeyNum);
        if (TdrError::TDR_NO_ERROR != ret)
        {
            TSF4G_TDR_DEBUG_TRACE();
            return ret;
        }
    }

    /* unpack member: this->iTestKey1 */
    {
        ret = srcBuf.readInt32(this->iTestKey1);
        if (TdrError::TDR_NO_ERROR != ret)
        {
            TSF4G_TDR_DEBUG_TRACE();
            return ret;
        }
    }

    /* unpack member: this->iTestKey2 */
    {
        ret = srcBuf.readInt32(this->iTestKey2);
        if (TdrError::TDR_NO_ERROR != ret)
        {
            TSF4G_TDR_DEBUG_TRACE();
            return ret;
        }
    }

    /* unpack member: this->iTestKey3 */
    {
        ret = srcBuf.readInt32(this->iTestKey3);
        if (TdrError::TDR_NO_ERROR != ret)
        {
            TSF4G_TDR_DEBUG_TRACE();
            return ret;
        }
    }

    return ret;
}

TdrError::ErrorType
BB_ServerTest::visualize(char* buffer, size_t size, size_t* usedSize, int indent, char separator) const
{
    if (NULL == buffer)
    {
        TSF4G_TDR_DEBUG_TRACE();
        return TdrError::TDR_ERR_NULL_POINTER_PARAMETER;
    }

    TdrWriteBuf destBuf(buffer, size);
    TdrError::ErrorType ret = visualize(destBuf, indent, separator);
    if (NULL != usedSize)
    {
        *usedSize = destBuf.getUsedSize();
    }

    return ret;
}

TdrError::ErrorType
BB_ServerTest::visualize(TdrWriteBuf& destBuf, int indent, char separator) const
{
    TdrError::ErrorType ret = TdrError::TDR_NO_ERROR;

    /* visualize member: this->iTestKeyNum */
    ret = TdrBufUtil::printVariable(destBuf, indent, separator, "[iTestKeyNum]", "%d", this->iTestKeyNum);
    if (TdrError::TDR_NO_ERROR != ret)
    {
        TSF4G_TDR_DEBUG_TRACE();
        return ret;
    }

    /* visualize member: this->iTestKey1 */
    ret = TdrBufUtil::printVariable(destBuf, indent, separator, "[iTestKey1]", "%d", this->iTestKey1);
    if (TdrError::TDR_NO_ERROR != ret)
    {
        TSF4G_TDR_DEBUG_TRACE();
        return ret;
    }

    /* visualize member: this->iTestKey2 */
    ret = TdrBufUtil::printVariable(destBuf, indent, separator, "[iTestKey2]", "%d", this->iTestKey2);
    if (TdrError::TDR_NO_ERROR != ret)
    {
        TSF4G_TDR_DEBUG_TRACE();
        return ret;
    }

    /* visualize member: this->iTestKey3 */
    ret = TdrBufUtil::printVariable(destBuf, indent, separator, "[iTestKey3]", "%d", this->iTestKey3);
    if (TdrError::TDR_NO_ERROR != ret)
    {
        TSF4G_TDR_DEBUG_TRACE();
        return ret;
    }

    return ret;
}

const char*
BB_ServerTest::visualize_ex(char* buffer, size_t size, size_t* usedSize, int indent, char separator) const
{
    if (NULL == buffer || 0 == size)
    {
        return "";
    }

    TdrWriteBuf destBuf(buffer, size);
    visualize(destBuf, indent, separator);

    size_t targetPos = destBuf.getUsedSize();
    const size_t totalSize = size;
    if (totalSize <= targetPos)
    {
        targetPos = totalSize - 1;
    }
    buffer[targetPos] = '\0';

    if (NULL != usedSize)
    {
        *usedSize = destBuf.getUsedSize();
    }

    return destBuf.getBeginPtr();
}

const char*
BB_ServerTest::visualize_ex(TdrWriteBuf& destBuf, int indent, char separator) const
{
    if (NULL == destBuf.getBeginPtr() || 0 == destBuf.getTotalSize())
    {
        return "";
    }

    visualize(destBuf, indent, separator);

    size_t targetPos = destBuf.getUsedSize();
    const size_t totalSize = destBuf.getTotalSize();
    if (totalSize <= targetPos)
    {
        targetPos = totalSize - 1;
    }
    destBuf.writeChar('\0', targetPos);

    return destBuf.getBeginPtr();
}



TdrError::ErrorType
BT_Monster_Normal::construct()
{
    TdrError::ErrorType ret = TdrError::TDR_NO_ERROR;

    this->iTargetActor = 0;

    this->chNeedGoHome = 0;

    memset(&this->returnPos, 0, 3 * sizeof(float));

    memset(&this->patrolPos, 0, 3 * sizeof(float));

    this->fStandTime = 0;

    this->iPatrolType = 0;

    this->chNeedFlee = 0;

    return ret;
}

TdrError::ErrorType
BT_Monster_Normal::pack(char* buffer, size_t size, size_t* usedSize, unsigned cutVer) const
{
    if (NULL == buffer)
    {
        TSF4G_TDR_DEBUG_TRACE();
        return TdrError::TDR_ERR_NULL_POINTER_PARAMETER;
    }

    TdrWriteBuf destBuf(buffer, size);
    TdrError::ErrorType ret = pack(destBuf, cutVer);
    if (NULL != usedSize)
    {
        *usedSize = destBuf.getUsedSize();
    }

    return ret;
}

TdrError::ErrorType
BT_Monster_Normal::pack(TdrWriteBuf& destBuf, unsigned cutVer) const
{
    TdrError::ErrorType ret = TdrError::TDR_NO_ERROR;

    /* adjust cutversion */
    if (0 == cutVer || BT_Monster_Normal::CURRVERSION < cutVer)
    {
        cutVer = BT_Monster_Normal::CURRVERSION;
    }

    /* check cutversion */
    if (BT_Monster_Normal::BASEVERSION > cutVer)
    {
        TSF4G_TDR_DEBUG_TRACE();
        return TdrError::TDR_ERR_CUTVER_TOO_SMALL;
    }

    /* pack member: this->iTargetActor */
    {
        ret = destBuf.writeInt32(this->iTargetActor);
        if (TdrError::TDR_NO_ERROR != ret)
        {
            TSF4G_TDR_DEBUG_TRACE();
            return ret;
        }
    }

    /* pack member: this->chNeedGoHome */
    {
        ret = destBuf.writeInt8(this->chNeedGoHome);
        if (TdrError::TDR_NO_ERROR != ret)
        {
            TSF4G_TDR_DEBUG_TRACE();
            return ret;
        }
    }

    /* pack member: this->returnPos */
    {
        for (unsigned returnPos_i = 0; returnPos_i < 3; returnPos_i++)
        {
            ret = destBuf.writeFloat(this->returnPos[returnPos_i]);
            if (TdrError::TDR_NO_ERROR != ret)
            {
                TSF4G_TDR_DEBUG_TRACE();
                return ret;
            }
        }
    }

    /* pack member: this->patrolPos */
    {
        for (unsigned patrolPos_i = 0; patrolPos_i < 3; patrolPos_i++)
        {
            ret = destBuf.writeFloat(this->patrolPos[patrolPos_i]);
            if (TdrError::TDR_NO_ERROR != ret)
            {
                TSF4G_TDR_DEBUG_TRACE();
                return ret;
            }
        }
    }

    /* pack member: this->fStandTime */
    {
        ret = destBuf.writeFloat(this->fStandTime);
        if (TdrError::TDR_NO_ERROR != ret)
        {
            TSF4G_TDR_DEBUG_TRACE();
            return ret;
        }
    }

    /* pack member: this->iPatrolType */
    {
        ret = destBuf.writeInt32(this->iPatrolType);
        if (TdrError::TDR_NO_ERROR != ret)
        {
            TSF4G_TDR_DEBUG_TRACE();
            return ret;
        }
    }

    /* pack member: this->chNeedFlee */
    {
        ret = destBuf.writeInt8(this->chNeedFlee);
        if (TdrError::TDR_NO_ERROR != ret)
        {
            TSF4G_TDR_DEBUG_TRACE();
            return ret;
        }
    }

    return ret;
}

TdrError::ErrorType
BT_Monster_Normal::unpack(const char* buffer, size_t size, size_t* usedSize, unsigned cutVer)
{
    if (NULL == buffer)
    {
        TSF4G_TDR_DEBUG_TRACE();
        return TdrError::TDR_ERR_NULL_POINTER_PARAMETER;
    }

    TdrReadBuf srcBuf(buffer, size);
    TdrError::ErrorType ret = unpack(srcBuf, cutVer);
    if (NULL != usedSize)
    {
        *usedSize = srcBuf.getUsedSize();
    }

    return ret;
}

TdrError::ErrorType
BT_Monster_Normal::unpack(TdrReadBuf& srcBuf, unsigned cutVer)
{
    TdrError::ErrorType ret = TdrError::TDR_NO_ERROR;

    /* adjust cutversion */
    if (0 == cutVer || BT_Monster_Normal::CURRVERSION < cutVer)
    {
        cutVer = BT_Monster_Normal::CURRVERSION;
    }

    /* check cutversion */
    if (BT_Monster_Normal::BASEVERSION > cutVer)
    {
        TSF4G_TDR_DEBUG_TRACE();
        return TdrError::TDR_ERR_CUTVER_TOO_SMALL;
    }

    /* unpack member: this->iTargetActor */
    {
        ret = srcBuf.readInt32(this->iTargetActor);
        if (TdrError::TDR_NO_ERROR != ret)
        {
            TSF4G_TDR_DEBUG_TRACE();
            return ret;
        }
    }

    /* unpack member: this->chNeedGoHome */
    {
        ret = srcBuf.readInt8(this->chNeedGoHome);
        if (TdrError::TDR_NO_ERROR != ret)
        {
            TSF4G_TDR_DEBUG_TRACE();
            return ret;
        }
    }

    /* unpack member: this->returnPos */
    {
        for (unsigned returnPos_i = 0; returnPos_i < 3; returnPos_i++)
        {
            ret = srcBuf.readFloat(this->returnPos[returnPos_i]);
            if (TdrError::TDR_NO_ERROR != ret)
            {
                TSF4G_TDR_DEBUG_TRACE();
                return ret;
            }
        }
    }

    /* unpack member: this->patrolPos */
    {
        for (unsigned patrolPos_i = 0; patrolPos_i < 3; patrolPos_i++)
        {
            ret = srcBuf.readFloat(this->patrolPos[patrolPos_i]);
            if (TdrError::TDR_NO_ERROR != ret)
            {
                TSF4G_TDR_DEBUG_TRACE();
                return ret;
            }
        }
    }

    /* unpack member: this->fStandTime */
    {
        ret = srcBuf.readFloat(this->fStandTime);
        if (TdrError::TDR_NO_ERROR != ret)
        {
            TSF4G_TDR_DEBUG_TRACE();
            return ret;
        }
    }

    /* unpack member: this->iPatrolType */
    {
        ret = srcBuf.readInt32(this->iPatrolType);
        if (TdrError::TDR_NO_ERROR != ret)
        {
            TSF4G_TDR_DEBUG_TRACE();
            return ret;
        }
    }

    /* unpack member: this->chNeedFlee */
    {
        ret = srcBuf.readInt8(this->chNeedFlee);
        if (TdrError::TDR_NO_ERROR != ret)
        {
            TSF4G_TDR_DEBUG_TRACE();
            return ret;
        }
    }

    return ret;
}

TdrError::ErrorType
BT_Monster_Normal::visualize(char* buffer, size_t size, size_t* usedSize, int indent, char separator) const
{
    if (NULL == buffer)
    {
        TSF4G_TDR_DEBUG_TRACE();
        return TdrError::TDR_ERR_NULL_POINTER_PARAMETER;
    }

    TdrWriteBuf destBuf(buffer, size);
    TdrError::ErrorType ret = visualize(destBuf, indent, separator);
    if (NULL != usedSize)
    {
        *usedSize = destBuf.getUsedSize();
    }

    return ret;
}

TdrError::ErrorType
BT_Monster_Normal::visualize(TdrWriteBuf& destBuf, int indent, char separator) const
{
    TdrError::ErrorType ret = TdrError::TDR_NO_ERROR;

    /* visualize member: this->iTargetActor */
    ret = TdrBufUtil::printVariable(destBuf, indent, separator, "[iTargetActor]", "%d", this->iTargetActor);
    if (TdrError::TDR_NO_ERROR != ret)
    {
        TSF4G_TDR_DEBUG_TRACE();
        return ret;
    }

    /* visualize member: this->chNeedGoHome */
    ret = TdrBufUtil::printVariable(destBuf, indent, separator, "[chNeedGoHome]", "0x%02x", this->chNeedGoHome);
    if (TdrError::TDR_NO_ERROR != ret)
    {
        TSF4G_TDR_DEBUG_TRACE();
        return ret;
    }

    /* visualize member: this->returnPos */
    ret = TdrBufUtil::printArray(destBuf, indent, separator, "[returnPos]", 3);
    if (TdrError::TDR_NO_ERROR != ret)
    {
        TSF4G_TDR_DEBUG_TRACE();
        return ret;
    }

    for (unsigned returnPos_i = 0; returnPos_i < 3; returnPos_i++)
    {
        ret = destBuf.textize(" " "%f", this->returnPos[returnPos_i]);
        if (TdrError::TDR_NO_ERROR != ret)
        {
            TSF4G_TDR_DEBUG_TRACE();
            return ret;
        }
    }
    ret = destBuf.writeCharWithNull(separator);
    if (TdrError::TDR_NO_ERROR != ret)
    {
        TSF4G_TDR_DEBUG_TRACE();
        return ret;
    }

    /* visualize member: this->patrolPos */
    ret = TdrBufUtil::printArray(destBuf, indent, separator, "[patrolPos]", 3);
    if (TdrError::TDR_NO_ERROR != ret)
    {
        TSF4G_TDR_DEBUG_TRACE();
        return ret;
    }

    for (unsigned patrolPos_i = 0; patrolPos_i < 3; patrolPos_i++)
    {
        ret = destBuf.textize(" " "%f", this->patrolPos[patrolPos_i]);
        if (TdrError::TDR_NO_ERROR != ret)
        {
            TSF4G_TDR_DEBUG_TRACE();
            return ret;
        }
    }
    ret = destBuf.writeCharWithNull(separator);
    if (TdrError::TDR_NO_ERROR != ret)
    {
        TSF4G_TDR_DEBUG_TRACE();
        return ret;
    }

    /* visualize member: this->fStandTime */
    ret = TdrBufUtil::printVariable(destBuf, indent, separator, "[fStandTime]", "%f", this->fStandTime);
    if (TdrError::TDR_NO_ERROR != ret)
    {
        TSF4G_TDR_DEBUG_TRACE();
        return ret;
    }

    /* visualize member: this->iPatrolType */
    ret = TdrBufUtil::printVariable(destBuf, indent, separator, "[iPatrolType]", "%d", this->iPatrolType);
    if (TdrError::TDR_NO_ERROR != ret)
    {
        TSF4G_TDR_DEBUG_TRACE();
        return ret;
    }

    /* visualize member: this->chNeedFlee */
    ret = TdrBufUtil::printVariable(destBuf, indent, separator, "[chNeedFlee]", "0x%02x", this->chNeedFlee);
    if (TdrError::TDR_NO_ERROR != ret)
    {
        TSF4G_TDR_DEBUG_TRACE();
        return ret;
    }

    return ret;
}

const char*
BT_Monster_Normal::visualize_ex(char* buffer, size_t size, size_t* usedSize, int indent, char separator) const
{
    if (NULL == buffer || 0 == size)
    {
        return "";
    }

    TdrWriteBuf destBuf(buffer, size);
    visualize(destBuf, indent, separator);

    size_t targetPos = destBuf.getUsedSize();
    const size_t totalSize = size;
    if (totalSize <= targetPos)
    {
        targetPos = totalSize - 1;
    }
    buffer[targetPos] = '\0';

    if (NULL != usedSize)
    {
        *usedSize = destBuf.getUsedSize();
    }

    return destBuf.getBeginPtr();
}

const char*
BT_Monster_Normal::visualize_ex(TdrWriteBuf& destBuf, int indent, char separator) const
{
    if (NULL == destBuf.getBeginPtr() || 0 == destBuf.getTotalSize())
    {
        return "";
    }

    visualize(destBuf, indent, separator);

    size_t targetPos = destBuf.getUsedSize();
    const size_t totalSize = destBuf.getTotalSize();
    if (totalSize <= targetPos)
    {
        targetPos = totalSize - 1;
    }
    destBuf.writeChar('\0', targetPos);

    return destBuf.getBeginPtr();
}


}