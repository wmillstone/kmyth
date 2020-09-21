/**
 * tpm2_kmyth_misc.c:
 *
 * C library containing miscellaneous utilities supporting Kmyth applications
 * using TPM 2.0
 */

#include "tpm2_kmyth_misc.h"

#include <stdlib.h>
#include <stdarg.h>

//############################################################################
// kmyth_clear()
//############################################################################
void kmyth_clear(void *v, size_t size)
{
  if (v == NULL)
    return;

  volatile unsigned char *p = v;

  while (size--)
    *p++ = '\0';
}

//############################################################################
// kmyth_clear_and_free()
//############################################################################
void kmyth_clear_and_free(void *v, size_t size)
{
  if (v == NULL)
    return;
  kmyth_clear(v, size);
  free(v);
}

//############################################################################
// kmyth_clean()
//############################################################################
// Clear and free the first clearCount void pointers passed in, and free the remaining pointers. Count
// is the total number of void pointers passed in.
void kmyth_clean(int count, int clearCount, ...)
{
  va_list valist;
  va_start(valist, clearCount);
  for (j = 0; j < count; j++) 
  {
    data = va_arg(valist, void*);
    if (j < clearCount)
      kmyth_clear_and_free(data, strlen(data));
    else
      free(data);      
  }
  
  va_end(valist);
}

//############################################################################
// secure_memset()
//############################################################################
void *secure_memset(void *v, int c, size_t n)
{
  volatile unsigned char *p = v;

  while (n--)
    *p++ = c;

  return v;
}
