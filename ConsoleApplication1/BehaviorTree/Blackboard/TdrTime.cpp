/* This file is generated by tdr. */
/* No manual modification is permitted. */

/* creation time: Tue Jun  4 14:17:59 2019 */
/* tdr version: 2.7.26, build at 20171102 */

#if defined(_WIN32) || defined(_WIN64)
#pragma warning(disable:4996)
#endif

#include "TdrTime.h"

namespace tsf4g_tdr
{


bool TdrDate::isValid() const
{
    if ((-9999 > nYear) || (nYear > 9999))
    {
        return false;
    }

    if (12 < bMon)
    {
        return false;
    }

    if (31 < bDay)
    {
        return false;
    }
    switch(bMon)
    {
        case 2:
            {
                if ((nYear % 4) == 0 && ((nYear % 100) != 0 || (nYear % 400) == 0))
                {
                    if (29 < bDay)
                    {
                        return false;
                    }
                } else
                {
                    if (28 < bDay)
                    {
                        return false;
                    }
                }
                break;
            }
        case 4:
        case 6:
        case 9:
        case 11:
            {
                if (30 < bDay)
                {
                    return false;
                }
                break;
            }
        default:
            break;
    }

    return true;
}

}