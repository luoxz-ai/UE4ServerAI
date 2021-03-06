/* This file is generated by tdr. */
/* No manual modification is permitted. */

/* creation time: Tue Jun  4 14:17:59 2019 */
/* tdr version: 2.7.26, build at 20171102 */

#include "TdrError.h"

namespace tsf4g_tdr
{


const char* TdrError::getErrorString(ErrorType errorCode)
{
    static const char* errorTab[] =
    {
        /* 0*/"no error",
        /* 1*/"available free space in buffer is not enough",
        /* 2*/"available data in buffer is not enough",
        /* 3*/"string length surpass defined size",
        /* 4*/"string length smaller than min string length",
        /* 5*/"string sizeinfo inconsistent with real length",
        /* 6*/"reffer value can not be minus",
        /* 7*/"reffer value bigger than count or size",
        /* 8*/"pointer-type argument is NULL",
        /* 9*/"cut-version is smaller than base-version",
        /*10*/"cut-version not covers entry refered by versionindicator",
        /*11*/"inet_ntoa failed when parse tdr_ip_t",
        /*12*/"value variable of tdr_ip_t is invalid",
        /*13*/"value variable of tdr_time_t is invalid",
        /*14*/"value variable of tdr_date_t is invalid",
        /*15*/"value variable of tdr_datetime_t is invalid",
        /*16*/"function 'localtime' or 'localtime_r' failed",
        /*17*/"invalid hex-string length, must be an even number",
        /*18*/"invalid hex-string format, each character must be a hex-digit",
        /*19*/"NULL pointer as parameter",
        /*20*/"cutVer from net-msg not in [BASEVERSION, CURRVERSION]",
        /*21*/"string-formated value underflow or overflow",
        /*22*/"failed to open file with read-mode",
        /*23*/"failed to open file with write-mode",
        /*24*/"failed to read data from file",
        /*25*/"failed to write data into file",
        /*26*/"failed to allocate heap memory",
        /*27*/"failed to parse XML-formated data",
        /*28*/"XML root-node is NOT what expected",
        /*29*/"failed to parse integer or float from string",
        /*30*/"specified macro name has NOT been defined",
        /*31*/"function has NOT been implemented",
        /*32*/"bad tlv encode magic",
        /*33*/"invalid selector",
        /*34*/"unmatched length",
        /*35*/"unknown type id",
        /*36*/"at least 1 required field been lost",
        /*37*/"null array shouldn't be packed",
        /*38*/"the field name is not existed",
        /*39*/"it is not support now.",
        /*40*/"unknown field id.",
        /*41*/"unmatch tag id.",
        /*42*/"unmatch type id.",
        /*43*/"not find.",
    };

    static const char* serviceErrTab[] =
    {
        /*TDR_ERR_SERVICE_MIN_ERRNO    */"null rpc client",
        /*TDR_ERR_SERVICE_MIN_ERRNO + 1*/"rpc method not been implemented yet",
        /*TDR_ERR_SERVICE_MIN_ERRNO + 2*/"null closure in servant",
        /*TDR_ERR_SERVICE_MIN_ERRNO + 3*/"unknown rpc method ",
    };

    int errorIndex = -1 * (int)errorCode;
    if (errorIndex < 0)
    {
        return errorTab[0];
    } else if (errorIndex < (int)(sizeof(errorTab)/sizeof(errorTab[0])))
    {
        return errorTab[errorIndex];
    } else if (errorIndex >= TDR_ERR_SERVICE_MIN_ERRNO &&
            errorIndex < TDR_ERR_SERVICE_MIN_ERRNO +
            (int)(sizeof(serviceErrTab)/sizeof(serviceErrTab[0])))
    {
        return serviceErrTab[errorIndex - TDR_ERR_SERVICE_MIN_ERRNO];
    } else
    {
        return "unknown error";
    }
}

}
