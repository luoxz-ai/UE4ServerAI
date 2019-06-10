/**
*
* @file     tdr_net_tlv.h
* @brief    TDRԪ����tlv��ʽ���罻����Ϣ�����ģ��
*
* @author avatarhuang
* @version 1.0
* @date 2015-09-10
*
*
* Copyright (c)  2015, ��Ѷ�Ƽ����޹�˾���������з���
* All rights reserved.
*
*/

#ifndef TDR_NET_TLV_H
#define TDR_NET_TLV_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
    *����tlv����ԭ�����Ԫ�������������ش洢����ת�������罻����Ϣ
    *@param[in] a_pstMeta Ԫ����������ָ�룬ͨ��tdr_get_meta_by_name��tdr_get_meta_by_id���Դ�Ԫ���ݿ��л�ȡ����ָ��
    *@param[in,out] a_pstNet �洢������Ϣ�ṹ��ָ��
    *   - ����    a_pstNet.pszBuff ָ������������Ϣ�Ļ�������ʼ��ַ
    *   - ����  a_pstNet.iBuff    ָ���������Ĵ�С
    *   - ���  a_pstNet.iBuff  ʵ�ʱ���������Ϣ���ܳ���
    *@param[in,out] a_pstHost �洢���ؽṹ��Ϣ�Ľṹ��ָ��
    *   - ����    a_pstHost.pszBuff ָ�����汾�ؽṹ��Ϣ�Ļ�������ʼ��ַ
    *   - ����  a_pstHost.iBuff   ָ���������Ĵ�С
    *   - ���  a_pstHost.iBuff  �������ĳ��ȴ��ڽṹ�峤�ȣ��޸�Ϊ�ṹ�峤�ȣ�
                                 ���С�ڽṹ��ĳ��ȣ��򲻻��޸ĸ�ֵ
    *@param[in] a_iFlag  ָ��tlv�������ͣ�Ϊ0��ʾ��novarint���룬Ϊ1��ʾ��varint����
    *
    *@note �������ʧ�ܣ���ȡ������Ϣ�ķ���:
    *   - 1.���ݷ���ֵ������tdr_error_string()���Ի�ȡ������Ϣ
    *   - 2.����a_pstHost.iBuff�õ���ʵ�ʱ������Ϣ���ܳ��ȣ�ͨ��a_pstHost�м�¼����Ϣ�����Ե���
    *       tdr_fprintf/tdr_sprintf ��ӡ���Ѿ��ɹ�����Ľṹ��Ϣ��ͨ�����tdr_hton_tlv����ʧ�ܣ�ͨ��
    *       ���ֶο��Զ�λ�������ľ���λ�á�
    *
    * @pre \e a_pstMeta ����Ϊ NULL�����ұ����Ӧ xml �����ļ��� struct Ԫ�ء�
    * @pre \e a_pstNet ����Ϊ NULL
    * @pre \e a_pstNet.pszBuff ����Ϊ NULL
    * @pre \e a_pstNet.iBuff �������0
    * @pre \e a_pstHost ����Ϊ NULL
    * @pre \e a_pstHost.pszBuff ����Ϊ NULL
    * @pre \e a_pstHost.iBuff �������0
    * @pre \e
    *
    *@retval 0   ����ɹ�
    *@retval >0  ����ɹ���������ĳЩ�������
    *@retval <0  ����ʧ�ܣ����ر�ʾ������Ϣ�Ĵ�����룺
    *       - TDR_ERR_NET_NO_NETBUFF_SPACE ����������Ϣ�Ļ�����ʣ��ռ䲻��
    *       - TDR_ERROR_NO_HOSTBUFF_SPACE ���ش洢������ʣ��ռ䲻��
    *       - TDR_ERROR_INVALID_REFER_VALUE     ��Ԫ�ص�refer����ֵ����ȷ����ֵ����Ϊ�����ұ����count����ֵС
    *       - TDR_ERROR_TOO_COMPLIEX_META Ԫ��������������������Ƕ�ײ�γ���32��
    *       - TDR_ERROR_NET_UNSUPPORTED_TYPE    ��֧�ֵ�Ԫ��������
    *       - TDR_ERROR_NET_INVALID_STRING_LEN string���͵�Ԫ�����ַ������ȳ�����Ԥ����󳤶�
    *
    * @note ����ýӿڷ���ʧ�ܣ����Ե��� tdr_get_error_detail ȡ����ϸ�Ĵ�����Ϣ
    *
    * @see  tdr_get_meta_by_name
    * @see  tdr_get_meta_by_id
    * @see  tdr_error_string
    * @see  tdr_get_error_detail
    */
int tdr_hton_tlv(IN LPTDRMETA a_pstMeta, INOUT LPTDRDATA a_pstNet, INOUT LPTDRDATA a_pstHost, IN int a_iFlag);

/**
*����tlv����ԭ�����Ԫ�������������罻����Ϣת���ɱ��ش洢����
*@param[in] a_pstMeta Ԫ����������ָ�룬ͨ��tdr_get_meta_by_name��tdr_get_meta_by_id���Դ�Ԫ���ݿ��л�ȡ����ָ��
*@param[in,out] a_pstHost �洢���ؽṹ��Ϣ�Ľṹ��ָ��
*   - ����    a_pstHost.pszBuff ָ�����汾�ؽṹ��Ϣ�Ļ�������ʼ��ַ
*   - ����  a_pstHost.iBuff   ָ���������Ĵ�С
*   - ���  a_pstHost.iBuff   �������ĳ��ȴ��ڽṹ�峤�ȣ��޸�Ϊ�ṹ�峤�ȣ�
                              ���С�ڽṹ��ĳ��ȣ��򲻻��޸ĸ�ֵ
*@param[in,out] a_pstNet �洢������Ϣ�ṹ��ָ��
*   - ����    a_pstNet.pszBuff ָ������������Ϣ�Ļ�������ʼ��ַ
*   - ����  a_pstNet.iBuff    ָ���������Ĵ�С
*   - ���  a_pstNet.iBuff  ʵ�ʽ���������Ϣ���ܳ���
*
*@param[in] a_iFlag  ����������Ϊ0
*@note Ԫ����������ӵ��������Ϣ������δ������ֶ�ʱ����defaultvalueֵ��δ�ڽ��ʱ����
*@note �������ʧ�ܣ���ȡ������Ϣ�ķ���:
    *   - ���ݷ���ֵ������tdr_error_string()���Ի�ȡ������Ϣ
    *   - ����a_pstHost.iBuff�õ���ʵ�ʽ������Ϣ���ܳ��ȣ����������Ϊƫ��ֵ������tdr_entry_off_to_path���Ի�ȡ
    *       ����ʱ��Ա��·����Ϣ���Ӷ���λ����������ĸ�λ�ó���
    *   - ����tdr_fprintf/tdr_sprintf���Դ�ӡ���Ѿ����������
*
* @pre \e a_pstMeta ����Ϊ NULL�����ұ����Ӧ xml �����ļ��� struct Ԫ�ء�
* @pre \e a_pstNet ����Ϊ NULL
* @pre \e a_pstNet.pszBuff ����Ϊ NULL
* @pre \e a_pstNet.iBuff �������0
* @pre \e a_pstHost ����ΪNULL
* @pre \e a_pstHost.pszBuff ����Ϊ NULL
* @pre \e a_pstHost.iBuff �������0
*
*@retval 0   ����ɹ�
*@retval >0  ����ɹ���������ĳЩ�������
*@retval <0  ����ʧ�ܣ����ر�ʾ������Ϣ�Ĵ�����룺
*       - TDR_ERR_NET_NO_NETBUFF_SPACE ����������Ϣ�Ļ�����ʣ��ռ䲻��
*       - TDR_ERROR_NO_HOSTBUFF_SPACE ���ش洢������ʣ��ռ䲻��
*       - TDR_ERROR_INVALID_REFER_VALUE     ��Ԫ�ص�refer����ֵ����ȷ����ֵ����Ϊ�����ұ����count����ֵС
*       - TDR_ERROR_TOO_COMPLIEX_META Ԫ��������������������Ƕ�ײ�γ���32��
*       - TDR_ERROR_NET_UNSUPPORTED_TYPE    ��֧�ֵ�Ԫ��������
*       - TDR_ERROR_NET_INVALID_STRING_LEN string���͵�Ԫ�����ַ������ȳ�����Ԥ����󳤶�
*
* @note ����ýӿڷ���ʧ�ܣ����Ե��� tdr_get_error_detail ȡ����ϸ�Ĵ�����Ϣ
*
* @see  tdr_get_meta_by_name
* @see  tdr_get_meta_by_id
* @see  tdr_error_string
* @see  tdr_fprintf
* @see  tdr_get_error_detail
*/
int tdr_ntoh_tlv(IN LPTDRMETA a_pstMeta, INOUT LPTDRDATA a_pstHost, INOUT LPTDRDATA a_pstNet, IN int a_iFlag);

#ifdef __cplusplus
}
#endif

#endif
