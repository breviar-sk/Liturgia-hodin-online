#include "vstudio.h"

#ifndef __CGIUTILS_CPP_
#define __CGIUTILS_CPP_

#include "cgiutils.h"


/* cgiutils.c
 *
 * (c) 1995-1996 William E. Weinman
 *
 * 1.1 -- splitword() now skips leading spaces
 * mierne upravil duurko (Juraj Vidéky), 29/10/99a.D.
 *
 */


/* splitword(char *out, char *in, char stop)
 *
 * moves all the characters up to the first 
 * occurance of stop from in to out, then
 * terminates out. then copies in, begining 
 * with the first character after stop, to 
 * the begining of in (effectively shifting 
 * it to the begining).
 */
void splitword(char *out, char *in, char stop)
{
	int i, j;

	while (*in == ' ') in++; /* skip past any spaces */

	for (i = 0; in[i] && (in[i] != stop); i++)
		out[i] = in[i];

	out[i] = '\0'; /* terminate it */
	if (in[i]) ++i; /* position past the stop */

	while (in[i] == ' ') i++; /* skip past any spaces */

	for (j = 0; in[j];)  /* shift the rest of the in */
		in[j++] = in[i++];
}

char x2c(char *x)
{
	register char c;

	/* note: (x & 0xdf) makes x upper case */
	c = (char)(x[0] >= 'A' ? ((x[0] & 0xdf) - 'A') + 10 : (x[0] - '0'));
	c *= 16;
	c += (char)(x[1] >= 'A' ? ((x[1] & 0xdf) - 'A') + 10 : (x[1] - '0'));
	return(c);
}

/* this function goes through the URL char-by-char 
   and converts all the "escaped" (hex-encoded) 
   sequences to characters 

   this version also converts pluses to spaces. I've 
   seen this done in a separate step, but it seems 
   to me more efficient to do it this way. 
*/

void unescape_url(char *url)
{
	register int i, j;

	for (i = 0, j = 0; url[j]; ++i, ++j)
	{
		if ((url[i] = url[j]) == '%')
		{
			url[i] = x2c(&url[j + 1]);
			j += 2;
		}
		else if (url[i] == '+')
			url[i] = ' ';
	}
	url[i] = '\0';  /* terminate it at the new length */
}

#endif /* __CGIUTILS_CPP_ */

