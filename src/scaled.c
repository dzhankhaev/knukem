#include "engine.h"

void RESIZE(uint* src, uint* dest, uint ws, uint hs, uint wd, uint hd)
{
  uint xx, yy;
  uint x, y;
  uint ixx, iyy;
  uint ix, iy;
  uint cx, cy;
  uint cxy, cc;
  uint pin, pout, p;
  uint b, g, r, a;
  uint *ikx, *iky;
  uint *kx, *ky;

  cx = (ws - 1) / wd + 2;
  cy = (hs - 1) / hd + 2;
  x = cx * wd;
  y = cy * hd;

  ikx = (uint *)malloc(x * 4);
  iky = (uint *)malloc(y * 4);
  kx = (uint *)malloc(x * 4);
  ky = (uint *)malloc(y * 4);

  for (xx = 0; xx < x; xx++)
  {
    ikx[xx] = 0;
    kx[xx] = 0;
  }

  for (yy = 0; yy < y; yy++)
  {
    iky[yy] = 0;
    ky[yy] = 0;
  }

  if (ws >= wd)
  {
    cxy = ws;
    pin = 0; pout = 1; p = 0;
    for(;;)
    {
      cc = pout * ws - pin * wd;
      if (cc >= wd)
      {
        kx[p] = wd;
      }
      else
      {
        kx[p] = cc;
        ikx[p] = pin;
        p = pout * cx;
        pout += 1;
        kx[p] = wd - cc;
      }
      ikx[p] = pin;
      pin += 1;
      if (pin >= ws) break;
      p += 1;
    }
  }
  else
  {
    cxy = wd;
    for (x = 0; x < wd; x++)
    {
      p = x * 2;
      kx[p + 1] = x * (ws - 1) % (wd - 1);
      ikx[p] = x * (ws - 1) / (wd - 1);
      kx[p] = wd - kx[p + 1];
      ikx[p + 1] = (ikx[p] + 1) % ws;
    }
  }

  if (hs >= hd)
  {
    cxy *= hs;
    pin = 0; pout = 1; p = 0;
    for(;;)
    {
      cc = pout * hs - pin * hd;
      if (cc >= hd)
      {
        ky[p] = hd;
      }
      else
      {
        ky[p] = cc;
        iky[p] = pin;
        p = pout * cy;
        pout += 1;
        ky[p] = hd - cc;
      }
      iky[p] = pin;
      pin += 1;
      if (pin >= hs) break;
      p += 1;
    }
  }
  else
  {
    cxy *= hd;
    for (y = 0; y < hd; y++)
    {
      p = y * 2;
      ky[p + 1] = y * (hs - 1) % (hd - 1);
      iky[p] = y * (hs - 1) / (hd - 1);
      ky[p] = hd - ky[p + 1];
      iky[p + 1] = (iky[p] + 1) % hs;
    }
  }

  iyy = 0;
  for (yy = 0; yy < hd; yy++)
  {
    ixx = 0;
    for (xx = 0; xx < wd; xx++)
    {
      b = g = r = a = 0;
      iy = iyy;
      for (y = 1; y <= cy; y++)
      {
        ix = ixx;
        for (x = 1; x <= cx; x++)
        {
          cc = src[ikx[ix] + iky[iy] * ws];
          b += (cc & 0xff) * kx[ix] * ky[iy];
          g += ((cc & 0xff00) >> 8) * kx[ix] * ky[iy];
          r += ((cc & 0xff0000) >> 16) * kx[ix] * ky[iy];
          a += ((cc & 0xff000000) >> 24) * kx[ix] * ky[iy];
          ix += 1;
        }
        iy += 1;
      }
      dest[xx + yy * wd] = b / cxy
                        + (g / cxy << 8)
                        + (r / cxy << 16)
                        + (a / cxy << 24);
      ixx += cx;
    }
    iyy += cy;
  }
  return;
}