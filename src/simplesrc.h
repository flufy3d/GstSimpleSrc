#ifndef __simple_SRC_H__
#define __simple_SRC_H__

#include <glib.h>

struct vts_color_struct {
  guint8 Y, U, V, A;
  guint8 R, G, B;
  guint16 gray;
};


typedef struct paintinfo_struct paintinfo;

struct paintinfo_struct
{
  const struct vts_color_struct *colors;
  const struct vts_color_struct *color;

  void (*paint_tmpline) (paintinfo * p, int x, int w);
  void (*convert_tmpline) (paintinfo * p, GstVideoFrame *frame, int y);
  void (*convert_hline) (paintinfo * p, GstVideoFrame *frame, int y);
  GstVideoChromaResample *subsample;
  int x_offset;

  int x_invert;
  int y_invert;

  guint8 *tmpline;
  guint8 *tmpline2;
  guint8 *tmpline_u8;
  guint16 *tmpline_u16;

  guint n_lines;
  gint offset;
  gpointer *lines;

  struct vts_color_struct foreground_color;
  struct vts_color_struct background_color;
};
#define PAINT_INFO_INIT {0, }

void    gst_simple_src_smpte        (GSTSIMPLESRC * v, GstClockTime pts, GstVideoFrame *frame);
void    gst_simple_src_smpte75      (GSTSIMPLESRC * v, GstClockTime pts, GstVideoFrame *frame);
void    gst_simple_src_snow         (GSTSIMPLESRC * v, GstClockTime pts, GstVideoFrame *frame);
void    gst_simple_src_black        (GSTSIMPLESRC * v, GstClockTime pts, GstVideoFrame *frame);
void    gst_simple_src_white        (GSTSIMPLESRC * v, GstClockTime pts, GstVideoFrame *frame);
void    gst_simple_src_red          (GSTSIMPLESRC * v, GstClockTime pts, GstVideoFrame *frame);
void    gst_simple_src_green        (GSTSIMPLESRC * v, GstClockTime pts, GstVideoFrame *frame);
void    gst_simple_src_blue         (GSTSIMPLESRC * v, GstClockTime pts, GstVideoFrame *frame);
void    gst_simple_src_solid        (GSTSIMPLESRC * v, GstClockTime pts, GstVideoFrame *frame);
void    gst_simple_src_blink        (GSTSIMPLESRC * v, GstClockTime pts, GstVideoFrame *frame);
void    gst_simple_src_checkers1    (GSTSIMPLESRC * v, GstClockTime pts, GstVideoFrame *frame);
void    gst_simple_src_checkers2    (GSTSIMPLESRC * v, GstClockTime pts, GstVideoFrame *frame);
void    gst_simple_src_checkers4    (GSTSIMPLESRC * v, GstClockTime pts, GstVideoFrame *frame);
void    gst_simple_src_checkers8    (GSTSIMPLESRC * v, GstClockTime pts, GstVideoFrame *frame);
void    gst_simple_src_circular     (GSTSIMPLESRC * v, GstClockTime pts, GstVideoFrame *frame);
void    gst_simple_src_zoneplate    (GSTSIMPLESRC * v, GstClockTime pts, GstVideoFrame *frame);
void    gst_simple_src_gamut        (GSTSIMPLESRC * v, GstClockTime pts, GstVideoFrame *frame);
void    gst_simple_src_chromazoneplate (GSTSIMPLESRC * v, GstClockTime pts, GstVideoFrame *frame);
void    gst_simple_src_ball         (GSTSIMPLESRC * v, GstClockTime pts, GstVideoFrame *frame);
void    gst_simple_src_smpte100     (GSTSIMPLESRC * v, GstClockTime pts, GstVideoFrame *frame);
void    gst_simple_src_bar          (GSTSIMPLESRC * v, GstClockTime pts, GstVideoFrame *frame);
void    gst_simple_src_pinwheel     (GSTSIMPLESRC * v, GstClockTime pts, GstVideoFrame * frame);
void    gst_simple_src_spokes       (GSTSIMPLESRC * v, GstClockTime pts, GstVideoFrame * frame);
void    gst_simple_src_gradient     (GSTSIMPLESRC * v, GstClockTime pts, GstVideoFrame * frame);
void    gst_simple_src_colors       (GSTSIMPLESRC * v, GstClockTime pts, GstVideoFrame * frame);

#endif
