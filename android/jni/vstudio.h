/***************************************************************/
/*                                                             */
/* vstudio.h                                                   */
/* (c)2007 | Juraj Vidéky | videky@breviar.sk                  */
/*                                                             */
/* description | necessary for Visual Studio (Express Edition) */
/*                                                             */
/***************************************************************/

#ifndef __VSTUDIO_H
#define __VSTUDIO_H

#if (_MSC_VER >= 1400)       // VC8+
#pragma warning(disable : 4996)
	#ifndef _CRT_SECURE_NO_DEPRECATE
	#define _CRT_SECURE_NO_DEPRECATE
	#endif /* _CRT_SECURE_NO_DEPRECATE */
	#ifndef _CRT_NONSTDC_NO_DEPRECATE
	#define _CRT_NONSTDC_NO_DEPRECATE
	#endif /* _CRT_NONSTDC_NO_DEPRECATE */
#endif   // VC8+

#endif // __VSTUDIO_H
