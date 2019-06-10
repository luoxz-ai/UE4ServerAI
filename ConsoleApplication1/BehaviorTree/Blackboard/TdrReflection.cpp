#include "TdrReflection.h"
#include "string.h"
#include<map>
#include<set>

#ifdef _MSC_VER
#else
#include "TdrReflectionErr.h"
#endif

#ifdef _MSC_VER
enum TdrReflectionErr
{
    Err_BB_OK = 0, /*û�д���*/
    Err_BB_Name_Null = -1, /*�ڰ���Ϊ��*/
    Err_BB_Name_Exist = -2, /*�ڰ����Ѿ����ڣ������ظ������*/
    Err_ActorID_Invalid = -3, /*ActorID �Ƿ�*/
    Err_BB_Name_NotExist = -4, /*û�д����ͺڰ�*/
    Err_BB_Name_Already_Regist = -5, /*��Actor�Ѿ�ע����ڰ壬����ע�������ظ�ע��*/
    Err_BB_Meta_Name_Null = -6, /*XML�л�ȡĳ���ڰ�����ʧ��*/
    Err_BB_Meta_Invalid = -7, /*XML�л�ȡĳ���ڰ�ʧ��*/
    Err_BB_No_Meta = -8, /*XML��û�ж���ڰ�*/
    Err_BB_No_MetaLib = -9, /*MetaLib ��ʼ��ʧ��*/
    Err_BB_MetaLib_Invalid = -10, /*MetaLib �Ƿ�*/
    Err_BB_Field_Name_Null = -11, /*�ֶ���Ϊ��*/
    Err_BB_Meta_Entry_Invalid = -12, /*MetaEntry �Ƿ�*/
    Err_BB_Entry_Offset_Invalid = -13, /*��ȡ��entryƫ�ƷǷ�*/
    Err_BB_TDR_Type_Invalid = -14, /*�ֶ����ͷǷ�*/
    Err_BB_Invalid_Str_Size = -15, /*�ڰ��ַ���Size̫С*/
    Err_BB_ArrayIndex_Invalid = -16, /*�����±�Ƿ�*/
    Err_BB_Array_Count_Invalid = -17, /*��������Ƿ�*/
    Err_BB_InputArray_Empty = -18, /*���������û��Ԫ��*/
    Err_BB_Not_Found = -19, /*û���ҵ����*/

    Err_Invalid = -10000 /*�����ϲ�Ӧ�ó���*/
};
#endif

typedef enum
{
    ArrayIndex_NotArray = -2,
    ArrayIndex_GetArray = -1,
} eArrayIndexType;


typedef std::map<std::string, int64_t> BBDataTable; /*��¼����ڰ����ݵ���ʼ��ַ����������ƫ�����ö�ȡ�ֶε�ֵ*/

static std::map<int, BBDataTable>g_mActorBBTable; /*��¼���� Actor ��ʹ�õĺڰ�����*/

static std::set<std::string>g_sBBNameList; /*��¼���кڰ����͵�����*/

static LPTDRMETALIB g_pstLib = NULL;
static LPTDRMETA g_pstMeta = NULL;
static LPTDRMETAENTRY g_pstEntry = NULL;

/**
 * [RegistBBName ע��ڰ�����]
 * @param  szBBName [�ڰ���]
 * @return          [�ο�TdrReflectionErr]
 */
static int RegistBBName(std::string szBBName);

/**
 * [GetEntryOffset ��ȡ�ڰ��ֶ�����ںڰ����ݵ�ƫ��]
 * @param  iRetCode    [���ش�����]
 * @param  szBBName    [�ڰ���]
 * @param  szFieldName [�ڰ��ֶ�]
 * @param  iArrayIndex [�����±꣬�������-2��ȡ���鱾���-1��>=0 ȡ�����±��Ӧ��ֵ]
 * @return             [�ο�TdrReflectionErr]
 */
static int GetEntryOffset(int& iRetCode, std::string szBBName, std::string szFieldName, int iArrayIndex = ArrayIndex_NotArray);

/**
 * [GetActorEntryOffset ��ȡָ��Actor�ĺڰ��ֶ�����ںڰ����ݵ�ƫ��]
 * @param  iRetCode    [���ش�����]
 * @param  iActorID    [ActorΨһ��ʶ]
 * @param  szBBName    [�ڰ���]
 * @param  szFieldName [�ڰ��ֶ�]
 * @param  iArrayIndex [�����±꣬�������-2��ȡ���鱾���-1��>=0 ȡ�����±��Ӧ��ֵ]
 * @return             [description]
 */
static int64_t GetActorEntryOffset(int& iRetCode, int iActorID, std::string szBBName, std::string szFieldName, int iArrayIndex);

int InitBB(std::string szBBXmlFilePath)
{
    int iRet = tdr_create_lib_file(&g_pstLib, szBBXmlFilePath.c_str(), 1, NULL); //�ȴ���Ԫ���ݿ�
    if (iRet != 0)
    {
        return iRet;
    }

    if (g_pstLib == NULL)
    {
        return Err_BB_No_MetaLib;
    }

    if (tdr_get_meta_num(g_pstLib) <= 0)
    {
        return Err_BB_No_Meta;
    }

    for (int i = 0; i < tdr_get_meta_num(g_pstLib); i++)
    {
        g_pstMeta = tdr_get_meta_by_id(g_pstLib, i + 1);

        if (g_pstMeta == NULL)
        {
            printf("meta idx%d\n", i + 1);
            return Err_BB_Meta_Invalid;
        }
        const char *pszMetaName = tdr_get_meta_name(g_pstMeta);
        if (pszMetaName == NULL)
        {
            return Err_BB_Meta_Name_Null;
        }

        iRet = RegistBBName(pszMetaName);
        if (iRet != Err_BB_OK)
        {
            return iRet;
        }
    }

    return Err_BB_OK;
}

int GetBBID(std::string szBBName)
{
    if (g_pstLib == NULL)
    {
        return Err_BB_No_MetaLib;
    }

    if (tdr_get_meta_num(g_pstLib) <= 0)
    {
        return Err_BB_No_Meta;
    }

    for (int i = 0; i < tdr_get_meta_num(g_pstLib); i++)
    {
        g_pstMeta = tdr_get_meta_by_id(g_pstLib, i + 1);

        if (g_pstMeta == NULL)
        {
            printf("meta idx%d\n", i + 1);
            return Err_BB_Meta_Invalid;
        }
        const char *pszMetaName = tdr_get_meta_name(g_pstMeta);
        if (pszMetaName == NULL || szBBName != pszMetaName)
        {
            continue;
        }

        return i + 1;
    }

    return Err_BB_Not_Found;
}

static int RegistBBName(std::string szBBName)
{
    if (szBBName == "")
    {
        return Err_BB_Name_Null;
    }

    if (g_sBBNameList.find(szBBName) == g_sBBNameList.end())
    {
        g_sBBNameList.insert(szBBName);

        return Err_BB_OK;
    }
    else
    {
        return Err_BB_Name_Exist;
    }

    return Err_Invalid;
}

int RegistActorDataToBB(int iActorID, std::string szBBName, void* pstBBData)
{
    if (szBBName == "")
    {
        return Err_BB_Name_Null;
    }

    if (iActorID <= 0)
    {
        return Err_ActorID_Invalid;
    }

    if (g_sBBNameList.find(szBBName) == g_sBBNameList.end())
    {
        return Err_BB_Name_NotExist;
    }

    if (g_mActorBBTable.find(iActorID) == g_mActorBBTable.end())
    {
        BBDataTable stBBDataTable;
        stBBDataTable[szBBName] = (int64_t)pstBBData;
        g_mActorBBTable[iActorID] = stBBDataTable;

        return Err_BB_OK;
    }
    else
    {
        return Err_BB_Name_Already_Regist;
    }

    return Err_Invalid;
}

int UnregistActorDataToBB(int iActorID, std::string szBBName)
{
	if (szBBName == "")
	{
		return Err_BB_Name_Null;
	}

	if (iActorID <= 0)
	{
		return Err_ActorID_Invalid;
	}

	if (g_sBBNameList.find(szBBName) == g_sBBNameList.end())
	{
		return Err_BB_Name_NotExist;
	}

	std::map<int, BBDataTable>::iterator key = g_mActorBBTable.find(iActorID);
	if (key != g_mActorBBTable.end())
	{
		g_mActorBBTable.erase(key);

		return Err_BB_OK;
	}

	return Err_Invalid;
}

TdrDataTypes GetDataType(int iActorID, std::string szBBName, std::string szFieldName)
{
    g_pstMeta = tdr_get_meta_by_name(g_pstLib, szBBName.c_str());

    if (g_pstMeta == NULL)
    {
        return TdrDataTypes_None;
    }

    g_pstEntry = tdr_get_entry_by_path(g_pstMeta, szFieldName.c_str());
    if (g_pstEntry == NULL)
    {
        return TdrDataTypes_None;
    }

    int iType = tdr_get_entry_type(g_pstEntry);

    switch (iType)
    {
    case TDR_TYPE_CHAR:
    case TDR_TYPE_UCHAR:
    case TDR_TYPE_BYTE:
    case TDR_TYPE_SMALLINT:
    case TDR_TYPE_SMALLUINT:
    case TDR_TYPE_INT:
    case TDR_TYPE_UINT:
    case TDR_TYPE_LONG:
    case TDR_TYPE_ULONG:
    case TDR_TYPE_LONGLONG:
    case TDR_TYPE_ULONGLONG:
    {
        return TdrDataTypes_Int;
    }
    case TDR_TYPE_FLOAT:
    case TDR_TYPE_DOUBLE:
    {
        return TdrDataTypes_Float;
    }
    case TDR_TYPE_STRING:
    {
        return TdrDataTypes_String;
    }
    default:
    {
        return TdrDataTypes_None;
    }
    }
}


static int GetEntryOffset(int& iRetCode, std::string szBBName, std::string szFieldName, int iArrayIndex)
{
    iRetCode = Err_BB_OK;
    if (g_pstLib == NULL)
    {
        iRetCode = Err_BB_MetaLib_Invalid;
        return 0;
    }

    if (szBBName == "")
    {
        iRetCode = Err_BB_Name_Null;
        return 0;
    }

    if (szFieldName == "")
    {
        iRetCode = Err_BB_Field_Name_Null;
        return 0;
    }

    g_pstMeta = tdr_get_meta_by_name(g_pstLib, szBBName.c_str());

    if (g_pstMeta == NULL)
    {
        iRetCode = Err_BB_Meta_Invalid;
        return 0;
    }

    g_pstEntry = tdr_get_entry_by_path(g_pstMeta, szFieldName.c_str());
    if (g_pstEntry == NULL)
    {
        iRetCode = Err_BB_Meta_Entry_Invalid;
        return 0;
    }

    TDROFF iOffSetEntry;
    int iRet = tdr_entry_path_to_off(g_pstMeta, &g_pstEntry, &iOffSetEntry, szFieldName.c_str());
    if (iRet != 0)
    {
        iRetCode = iRet;
        return 0;
    }

    if (iArrayIndex == ArrayIndex_NotArray ||
            iArrayIndex == ArrayIndex_GetArray)
    {
        return iOffSetEntry;
    }
    else if (iArrayIndex >= 0)
    {
        int iArrayCount = tdr_get_entry_count(g_pstEntry);
        if (iArrayCount >= 1)
        {
            if (iArrayIndex > iArrayCount - 1)
            {
                iRetCode = Err_BB_ArrayIndex_Invalid;
                return 0;
            }

            int iSize = tdr_get_entry_unitsize(g_pstEntry);

            return iOffSetEntry + iSize * iArrayIndex;
        }
        else
        {
            iRetCode = Err_BB_Array_Count_Invalid;
            return 0;
        }
    }
    else
    {
        iRetCode = Err_BB_ArrayIndex_Invalid;
        return 0;
    }

    return iOffSetEntry;
}

static int64_t GetActorEntryOffset(int& iRetCode, int iActorID, std::string szBBName, std::string szFieldName, int iArrayIndex)
{
    iRetCode = Err_BB_OK;
    TDROFF iOffSetEntry = GetEntryOffset(iRetCode, szBBName, szFieldName, iArrayIndex);

    if (iRetCode != Err_BB_OK)
    {
        return 0;
    }

    if (iOffSetEntry < 0)
    {
        iRetCode = Err_BB_Entry_Offset_Invalid;
        return 0;
    }

    if (g_mActorBBTable.find(iActorID) != g_mActorBBTable.end())
    {
        if (g_mActorBBTable[iActorID].find(szBBName) != g_mActorBBTable[iActorID].end())
        {
            return g_mActorBBTable[iActorID][szBBName] + iOffSetEntry;
        }

        iRetCode = Err_BB_Name_NotExist;
        return 0;
    }

    iRetCode = Err_ActorID_Invalid;
    return 0;
}

int GetIntBBValue(int64_t& iValue, int iActorID, std::string szBBName, std::string szFieldName, int iArrayIndex)
{
    int iRetCode = Err_BB_OK;
    int64_t pData = GetActorEntryOffset(iRetCode, iActorID, szBBName, szFieldName, iArrayIndex);

    int iType = tdr_get_entry_type(g_pstEntry);

    switch (iType)
    {
    case TDR_TYPE_CHAR:
    case TDR_TYPE_UCHAR:
    case TDR_TYPE_BYTE:
    {
        iValue = *((int8_t *)pData);
        return iRetCode;
    }
    case TDR_TYPE_SMALLINT:
    case TDR_TYPE_SMALLUINT:
    {
        iValue = *((int16_t *)pData);
        return iRetCode;
    }
    case TDR_TYPE_INT:
    case TDR_TYPE_UINT:
    case TDR_TYPE_LONG:
    case TDR_TYPE_ULONG:
    {
        iValue = *((int32_t *)pData);
        return iRetCode;
    }
    case TDR_TYPE_LONGLONG:
    case TDR_TYPE_ULONGLONG:
    {
        iValue = *((int64_t *)pData);
        return iRetCode;
    }
    default:
    {
        return Err_BB_TDR_Type_Invalid;
    }
    }

    return iRetCode;
}

int GetFloatBBValue(double& fValue, int iActorID, std::string szBBName, std::string szFieldName, int iArrayIndex)
{
    int iRetCode = Err_BB_OK;
    int64_t pData = GetActorEntryOffset(iRetCode, iActorID, szBBName, szFieldName, iArrayIndex);

    int iType = tdr_get_entry_type(g_pstEntry);

    switch (iType)
    {
    case TDR_TYPE_FLOAT:
    {
        fValue = *((float *)pData);
        return iRetCode;
    }
    case TDR_TYPE_DOUBLE:
    {
        fValue = *((double *)pData);
        return iRetCode;
    }
    default:
    {
        return Err_BB_TDR_Type_Invalid;
    }
    }

    return iRetCode;
}

int GetStrBBValue(std::string& strValue, int iActorID, std::string szBBName, std::string szFieldName, int iArrayIndex)
{
    int iRetCode = Err_BB_OK;
    int64_t pData = GetActorEntryOffset(iRetCode, iActorID, szBBName, szFieldName, iArrayIndex);

    int iType = tdr_get_entry_type(g_pstEntry);

    switch (iType)
    {
    case TDR_TYPE_STRING:
    {
        strValue = (char *)pData;
        return iRetCode;
    }
    default:
    {
        return Err_BB_TDR_Type_Invalid;
    }
    }
    return iRetCode;
}

int GetIntArrayBBValue(std::vector<int64_t>& intArray, int iActorID, std::string szBBName, std::string szFieldName)
{
    int iRetCode = Err_BB_OK;
    intArray.clear();

    int64_t pData = GetActorEntryOffset(iRetCode, iActorID, szBBName, szFieldName, ArrayIndex_GetArray);

    int iArrayCount = tdr_get_entry_count(g_pstEntry);
    if (iArrayCount < 1)
    {
        return Err_BB_Array_Count_Invalid;
    }

    int iType = tdr_get_entry_type(g_pstEntry);

    switch (iType)
    {
    case TDR_TYPE_CHAR:
    case TDR_TYPE_UCHAR:
    case TDR_TYPE_BYTE:
    {
        for (int i = 0; i < iArrayCount; ++i)
        {
            intArray.push_back(*((int8_t *)(pData + i * 1)));
        }
        return iRetCode;
    }
    case TDR_TYPE_SMALLINT:
    case TDR_TYPE_SMALLUINT:
    {
        for (int i = 0; i < iArrayCount; ++i)
        {
            intArray.push_back(*((int16_t *)(pData + i * 2)));
        }
        return iRetCode;
    }
    case TDR_TYPE_INT:
    case TDR_TYPE_UINT:
    case TDR_TYPE_LONG:
    case TDR_TYPE_ULONG:
    {
        for (int i = 0; i < iArrayCount; ++i)
        {
            intArray.push_back(*((int32_t *)(pData + i * 4)));
        }
        return iRetCode;
    }
    case TDR_TYPE_LONGLONG:
    case TDR_TYPE_ULONGLONG:
    {
        for (int i = 0; i < iArrayCount; ++i)
        {
            intArray.push_back(*((int64_t *)(pData + i * 8)));
        }
        return iRetCode;
    }
    default:
    {
        return Err_BB_TDR_Type_Invalid;
    }
    }

    return iRetCode;
}

int GetFloatArrayBBValue(std::vector<double>& floatArray, int iActorID, std::string szBBName, std::string szFieldName)
{
    int iRetCode = Err_BB_OK;
    floatArray.clear();

    int64_t pData = GetActorEntryOffset(iRetCode, iActorID, szBBName, szFieldName, ArrayIndex_GetArray);

    int iArrayCount = tdr_get_entry_count(g_pstEntry);
    if (iArrayCount < 1)
    {
        return Err_BB_Array_Count_Invalid;
    }

    int iType = tdr_get_entry_type(g_pstEntry);

    switch (iType)
    {
    case TDR_TYPE_FLOAT:
    {
        for (int i = 0; i < iArrayCount; ++i)
        {
            floatArray.push_back(*((float *)(pData + i * 4)));
        }
        return iRetCode;
    }
    case TDR_TYPE_DOUBLE:
    {
        for (int i = 0; i < iArrayCount; ++i)
        {
            floatArray.push_back(*((double *)(pData + i * 8)));
        }
        return iRetCode;
    }
    default:
    {
        return Err_BB_TDR_Type_Invalid;
    }
    }

    return iRetCode;
}

int GetStrArrayBBValue(std::vector<std::string>& strArray, int iActorID, std::string szBBName, std::string szFieldName)
{
    int iRetCode = Err_BB_OK;
    strArray.clear();

    int64_t pData = GetActorEntryOffset(iRetCode, iActorID, szBBName, szFieldName, ArrayIndex_GetArray);

    int iArrayCount = tdr_get_entry_count(g_pstEntry);
    if (iArrayCount < 1)
    {
        return Err_BB_Array_Count_Invalid;
    }

    int iType = tdr_get_entry_type(g_pstEntry);

    switch (iType)
    {
    case TDR_TYPE_STRING:
    {
        int iSize = tdr_get_entry_unitsize(g_pstEntry);
        for (int i = 0; i < iArrayCount; ++i)
        {
            strArray.push_back((char *)(pData + i * iSize));
        }
        return iRetCode;
    }
    default:
    {
        return Err_BB_TDR_Type_Invalid;
    }
    }

    return iRetCode;
}

int SetIntBBValue(int iActorID, std::string szBBName, std::string szFieldName, int64_t llValue, int iArrayIndex)
{
    int iRetCode = Err_BB_OK;
    int64_t pData = GetActorEntryOffset(iRetCode, iActorID, szBBName, szFieldName, iArrayIndex);
    if (iRetCode != Err_BB_OK)
    {
        return iRetCode;
    }

    int iType = tdr_get_entry_type(g_pstEntry);

    switch (iType)
    {
    case TDR_TYPE_CHAR:
    case TDR_TYPE_UCHAR:
    case TDR_TYPE_BYTE:
    {
        *((int8_t *)pData) = (int8_t)llValue;
        break;
    }
    case TDR_TYPE_SMALLINT:
    case TDR_TYPE_SMALLUINT:
    {
        *((int16_t *)pData) = (int16_t)llValue;
        break;
    }
    case TDR_TYPE_INT:
    case TDR_TYPE_UINT:
    case TDR_TYPE_LONG:
    case TDR_TYPE_ULONG:
    {
        *((int32_t *)pData) = (int32_t)llValue;
        break;
    }
    case TDR_TYPE_LONGLONG:
    case TDR_TYPE_ULONGLONG:
    {
        *((int64_t *)pData) = (int64_t)llValue;
        break;
    }
    default:
    {
        return Err_BB_TDR_Type_Invalid;
    }
    }

    return Err_BB_OK;
}

int SetFloatBBValue(int iActorID, std::string szBBName, std::string szFieldName, double fValue, int iArrayIndex)
{
    int iRetCode = Err_BB_OK;
    int64_t pData = GetActorEntryOffset(iRetCode, iActorID, szBBName, szFieldName, iArrayIndex);
    if (iRetCode != Err_BB_OK)
    {
        return iRetCode;
    }

    int iType = tdr_get_entry_type(g_pstEntry);

    switch (iType)
    {
    case TDR_TYPE_FLOAT:
    {
        *((float *)pData) = (float)fValue;
        break;
    }
    case TDR_TYPE_DOUBLE:
    {
        *((double *)pData) = (double)fValue;
        break;
    }
    default:
    {
        return Err_BB_TDR_Type_Invalid;
    }
    }

    return Err_BB_OK;
}

int SetStrBBValue(int iActorID, std::string szBBName, std::string szFieldName, std::string szStr, int iArrayIndex)
{
    int iRetCode = Err_BB_OK;
    int64_t pData = GetActorEntryOffset(iRetCode, iActorID, szBBName, szFieldName, iArrayIndex);
    if (iRetCode != Err_BB_OK)
    {
        return iRetCode;
    }

    int iType = tdr_get_entry_type(g_pstEntry);

    switch (iType)
    {
    case TDR_TYPE_STRING:
    {
        int iSize = tdr_get_entry_unitsize(g_pstEntry);
        if (iSize >= 2 && iSize > (int)szStr.size())
        {
            strncpy((char *)pData, szStr.c_str(), iSize);
        }
        else
        {
            return Err_BB_Invalid_Str_Size;
        }

        break;
    }
    default:
    {
        return Err_BB_TDR_Type_Invalid;
    }
    }

    return Err_BB_OK;
}

int SetIntArrayBBValue(int iActorID, std::string szBBName, std::string szFieldName, std::vector<int64_t>& aIntArray)
{
    int iRetCode = Err_BB_OK;
    if (aIntArray.size() <= 0)
    {
        return Err_BB_InputArray_Empty;
    }
    int64_t pData = GetActorEntryOffset(iRetCode, iActorID, szBBName, szFieldName, ArrayIndex_GetArray);
    if (iRetCode != Err_BB_OK)
    {
        return iRetCode;
    }

    int iArrayCount = tdr_get_entry_count(g_pstEntry);
    if (iArrayCount < 1)
    {
        return Err_BB_Array_Count_Invalid;
    }

    if ((int)aIntArray.size() < iArrayCount)
    {
        iArrayCount = aIntArray.size();
    }

    int iType = tdr_get_entry_type(g_pstEntry);

    switch (iType)
    {
    case TDR_TYPE_CHAR:
    case TDR_TYPE_UCHAR:
    case TDR_TYPE_BYTE:
    {
        for (int i = 0; i < iArrayCount; ++i)
        {
            *((int8_t *)(pData + i)) = (int8_t)aIntArray[i];
        }
        break;
    }
    case TDR_TYPE_SMALLINT:
    case TDR_TYPE_SMALLUINT:
    {
        for (int i = 0; i < iArrayCount; ++i)
        {
            *((int16_t *)(pData + i * 2)) = (int16_t)aIntArray[i];
        }
        break;
    }
    case TDR_TYPE_INT:
    case TDR_TYPE_UINT:
    case TDR_TYPE_LONG:
    case TDR_TYPE_ULONG:
    {
        for (int i = 0; i < iArrayCount; ++i)
        {
            *((int32_t *)(pData + i * 4)) = (int32_t)aIntArray[i];
        }
        break;
    }
    case TDR_TYPE_LONGLONG:
    case TDR_TYPE_ULONGLONG:
    {
        for (int i = 0; i < iArrayCount; ++i)
        {
            *((int64_t *)(pData + i * 8)) = (int64_t)aIntArray[i];
        }
        break;
    }
    default:
    {
        return Err_BB_TDR_Type_Invalid;
    }
    }

    return Err_BB_OK;
}

int SetFloatArrayBBValue(int iActorID, std::string szBBName, std::string szFieldName, std::vector<double>& aFloatArray)
{
    int iRetCode = Err_BB_OK;

    if (aFloatArray.size() <= 0)
    {
        return Err_BB_InputArray_Empty;
    }
    int64_t pData = GetActorEntryOffset(iRetCode, iActorID, szBBName, szFieldName, ArrayIndex_GetArray);
    if (iRetCode != Err_BB_OK)
    {
        return iRetCode;
    }

    int iArrayCount = tdr_get_entry_count(g_pstEntry);
    if (iArrayCount < 1)
    {
        return Err_BB_Array_Count_Invalid;
    }

    if ((int)aFloatArray.size() < iArrayCount)
    {
        iArrayCount = aFloatArray.size();
    }

    int iType = tdr_get_entry_type(g_pstEntry);

    switch (iType)
    {
    case TDR_TYPE_FLOAT:
    {
        for (int i = 0; i < iArrayCount; ++i)
        {
            *((float *)(pData + i * 4)) = (float)aFloatArray[i];
        }
        break;
    }
    case TDR_TYPE_DOUBLE:
    {
        for (int i = 0; i < iArrayCount; ++i)
        {
            *((double *)(pData + i * 8)) = (double)aFloatArray[i];
        }
        break;
    }
    default:
    {
        return Err_BB_TDR_Type_Invalid;
    }
    }

    return Err_BB_OK;
}

int SetStrArrayBBValue(int iActorID, std::string szBBName, std::string szFieldName, std::vector<std::string>& aStrArray)
{
    int iRetCode = Err_BB_OK;

    if (aStrArray.size() <= 0)
    {
        return Err_BB_InputArray_Empty;
    }
    int64_t pData = GetActorEntryOffset(iRetCode, iActorID, szBBName, szFieldName, ArrayIndex_GetArray);
    if (iRetCode != Err_BB_OK)
    {
        return iRetCode;
    }

    int iArrayCount = tdr_get_entry_count(g_pstEntry);
    if (iArrayCount < 1)
    {
        return Err_BB_Array_Count_Invalid;
    }

    if ((int)aStrArray.size() < iArrayCount)
    {
        iArrayCount = aStrArray.size();
    }

    int iType = tdr_get_entry_type(g_pstEntry);

    switch (iType)
    {
    case TDR_TYPE_STRING:
    {
        for (int i = 0; i < iArrayCount; ++i)
        {
            int iSize = tdr_get_entry_unitsize(g_pstEntry);
            if (iSize >= 2 && iSize > (int)aStrArray[i].size())
            {
                strncpy((char *)(pData + i * iSize), aStrArray[i].c_str(), iSize);
            }
            else
            {
                return Err_BB_Invalid_Str_Size;
            }
        }

        break;
    }
    default:
    {
        return Err_BB_TDR_Type_Invalid;
    }
    }

    return Err_BB_OK;
}
