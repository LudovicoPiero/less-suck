static void bstack(Monitor *m) {
  unsigned int i, n;
  int mx = 0, my = 0, mh = 0, mw = 0;
  int sx = 0, sy = 0, sh = 0, sw = 0;
  float mfacts, sfacts;
  int mrest, srest;
  Client *c;

#if VANITYGAPS_PATCH
  int oh, ov, ih, iv;
  getgaps(m, &oh, &ov, &ih, &iv, &n);
#else
  for (n = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), n++)
    ;
#endif // VANITYGAPS_PATCH

  if (n == 0)
    return;

#if VANITYGAPS_PATCH
  sx = mx = m->wx + ov;
  sy = my = m->wy + oh;
  sh = mh = m->wh - 2 * oh;
  mw = m->ww - 2 * ov - iv * (MIN(n, m->nmaster) - 1);
  sw = m->ww - 2 * ov - iv * (n - m->nmaster - 1);

  if (m->nmaster && n > m->nmaster) {
    sh = (mh - ih) * (1 - m->mfact);
    mh = (mh - ih) * m->mfact;
    sx = mx;
    sy = my + mh + ih;
  }
#else
  sx = mx = m->wx;
  sy = my = m->wy;
  sh = mh = m->wh;
  sw = mw = m->ww;

  if (m->nmaster && n > m->nmaster) {
    sh = mh * (1 - m->mfact);
    mh = mh * m->mfact;
    sy = my + mh;
  }
#endif // VANITYGAPS_PATCH

  getfacts(m, mw, sw, &mfacts, &sfacts, &mrest, &srest);

  for (i = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), i++) {
    if (i < m->nmaster) {
#if CFACTS_PATCH
      resize(c, mx, my,
             (mw / mfacts) * c->cfact + (i < mrest ? 1 : 0) - (2 * c->bw),
             mh - (2 * c->bw), 0);
#else
      resize(c, mx, my, (mw / mfacts) + (i < mrest ? 1 : 0) - (2 * c->bw),
             mh - (2 * c->bw), 0);
#endif // CFACTS_PATCH
#if VANITYGAPS_PATCH
      mx += WIDTH(c) + iv;
#else
      mx += WIDTH(c);
#endif
    } else {
#if CFACTS_PATCH
      resize(c, sx, sy,
             (sw / sfacts) * c->cfact + ((i - m->nmaster) < srest ? 1 : 0) -
                 (2 * c->bw),
             sh - (2 * c->bw), 0);
#else
      resize(c, sx, sy,
             (sw / sfacts) + ((i - m->nmaster) < srest ? 1 : 0) - (2 * c->bw),
             sh - (2 * c->bw), 0);
#endif // CFACTS_PATCH
#if VANITYGAPS_PATCH
      sx += WIDTH(c) + iv;
#else
      sx += WIDTH(c);
#endif
    }
  }
}
