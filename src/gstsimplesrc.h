#ifndef __GST_simple_SRC_H__
#define __GST_simple_SRC_H__

#include <gst/gst.h>
#include <gst/base/gstpushsrc.h>

#include <gst/video/gstvideometa.h>
#include <gst/video/gstvideopool.h>

G_BEGIN_DECLS

#define GST_TYPE_simple_SRC \
  (gst_simple_src_get_type())
#define GST_simple_SRC(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj),GST_TYPE_simple_SRC,GSTSIMPLESRC))
#define GST_simple_SRC_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_CAST((klass),GST_TYPE_simple_SRC,GSTSIMPLESRCClass))
#define GST_IS_simple_SRC(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj),GST_TYPE_simple_SRC))
#define GST_IS_simple_SRC_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_TYPE((klass),GST_TYPE_simple_SRC))

/**
 * GSTSIMPLESRCPattern:
 * @GST_simple_SRC_SMPTE: A standard SMPTE test pattern
 * @GST_simple_SRC_SNOW: Random noise
 * @GST_simple_SRC_BLACK: A black image
 * @GST_simple_SRC_WHITE: A white image
 * @GST_simple_SRC_RED: A red image
 * @GST_simple_SRC_GREEN: A green image
 * @GST_simple_SRC_BLUE: A blue image
 * @GST_simple_SRC_CHECKERS1: Checkers pattern (1px)
 * @GST_simple_SRC_CHECKERS2: Checkers pattern (2px)
 * @GST_simple_SRC_CHECKERS4: Checkers pattern (4px)
 * @GST_simple_SRC_CHECKERS8: Checkers pattern (8px)
 * @GST_simple_SRC_CIRCULAR: Circular pattern
 * @GST_simple_SRC_BLINK: Alternate between black and white
 * @GST_simple_SRC_SMPTE75: SMPTE test pattern (75% color bars)
 * @GST_simple_SRC_ZONE_PLATE: Zone plate
 * @GST_simple_SRC_GAMUT: Gamut checking pattern
 * @GST_simple_SRC_CHROMA_ZONE_PLATE: Chroma zone plate
 * @GST_simple_SRC_BALL: Moving ball
 * @GST_simple_SRC_SMPTE100: SMPTE test pattern (100% color bars)
 * @GST_simple_SRC_SOLID: A solid color, defined by the
 * #GSTSIMPLESRC:foreground-color property
 * @GST_simple_SRC_BAR: Bar with foreground color
 * @GST_simple_SRC_PINWHEEL: Pinwheel
 * @GST_simple_SRC_SPOKES: Spokes
 * @GST_simple_SRC_GRADIENT: Gradient
 * @GST_simple_SRC_COLORS: All colors
 *
 * The test pattern to produce.
 *
 * The Gamut pattern creates a checkerboard pattern of colors at the
 * edge of the YCbCr gamut and nearby colors that are out of gamut.
 * The pattern is divided into 4 regions: black, white, red, and blue.
 * After conversion to RGB, the out-of-gamut colors should be converted
 * to the same value as their in-gamut neighbors.  If the checkerboard
 * pattern is still visible after conversion, this indicates a faulty
 * conversion.  Image manipulation, such as adjusting contrast or
 * brightness, can also cause the pattern to be visible.
 *
 * The Zone Plate pattern is based on BBC R&D Report 1978/23, and can
 * be used to test spatial frequency response of a system.  This
 * pattern generator is controlled by the xoffset and yoffset parameters
 * and also by all the parameters starting with 'k'.  The default
 * parameters produce a grey pattern.  Try 'simplesrc
 * pattern=zone-plate kx2=20 ky2=20 kt=1' to produce something
 * interesting.
 */
typedef enum {
  GST_simple_SRC_SMPTE,
  GST_simple_SRC_SNOW,
  GST_simple_SRC_BLACK,
  GST_simple_SRC_WHITE,
  GST_simple_SRC_RED,
  GST_simple_SRC_GREEN,
  GST_simple_SRC_BLUE,
  GST_simple_SRC_CHECKERS1,
  GST_simple_SRC_CHECKERS2,
  GST_simple_SRC_CHECKERS4,
  GST_simple_SRC_CHECKERS8,
  GST_simple_SRC_CIRCULAR,
  GST_simple_SRC_BLINK,
  GST_simple_SRC_SMPTE75,
  GST_simple_SRC_ZONE_PLATE,
  GST_simple_SRC_GAMUT,
  GST_simple_SRC_CHROMA_ZONE_PLATE,
  GST_simple_SRC_SOLID,
  GST_simple_SRC_BALL,
  GST_simple_SRC_SMPTE100,
  GST_simple_SRC_BAR,
  GST_simple_SRC_PINWHEEL,
  GST_simple_SRC_SPOKES,
  GST_simple_SRC_GRADIENT,
  GST_simple_SRC_COLORS
} GSTSIMPLESRCPattern;

typedef enum {
  GST_simple_SRC_FRAMES,
  GST_simple_SRC_WALL_TIME,
  GST_simple_SRC_RUNNING_TIME
} GSTSIMPLESRCAnimationMode;


typedef enum {
  GST_simple_SRC_WAVY,
  GST_simple_SRC_SWEEP,
  GST_simple_SRC_HSWEEP
} GSTSIMPLESRCMotionType;

typedef struct _GSTSIMPLESRC GSTSIMPLESRC;
typedef struct _GSTSIMPLESRCClass GSTSIMPLESRCClass;

/**
 * GSTSIMPLESRC:
 *
 * Opaque data structure.
 */
struct _GSTSIMPLESRC {
  GstPushSrc element;

  /*< private >*/

  /* type of output */
  GSTSIMPLESRCPattern pattern_type;

  /* video state */
  GstVideoInfo info; /* protected by the object or stream lock */
  GstVideoChromaResample *subsample;
  gboolean bayer;
  gint x_invert;
  gint y_invert;

  /* private */
  /* FIXME 2.0: Change type to GstClockTime */
  gint64 timestamp_offset;              /* base offset */

  /* running time and frames for current caps */
  GstClockTime running_time;            /* total running time */
  gint64 n_frames;                      /* total frames sent */
  gboolean reverse;

  /* previous caps running time and frames */
  GstClockTime accum_rtime;              /* accumulated running_time */
  gint64 accum_frames;                  /* accumulated frames */

  /* zoneplate */
  gint k0;
  gint kx;
  gint ky;
  gint kt;
  gint kxt;
  gint kyt;
  gint kxy;
  gint kx2;
  gint ky2;
  gint kt2;
  gint xoffset;
  gint yoffset;

  /* solid color */
  guint foreground_color;
  guint background_color;

  /* moving color bars */
  gint horizontal_offset;
  gint horizontal_speed;

  /* smpte & snow */
  guint random_state;

  /* Ball motion */
  GSTSIMPLESRCAnimationMode animation_mode;
  GSTSIMPLESRCMotionType motion_type;
  gboolean flip;

  void (*make_image) (GSTSIMPLESRC *v, GstClockTime pts, GstVideoFrame *frame);

  /* temporary AYUV/ARGB scanline */
  guint8 *tmpline_u8;
  guint8 *tmpline;
  guint8 *tmpline2;
  guint16 *tmpline_u16;

  guint n_lines;
  gint offset;
  gpointer *lines;
};

struct _GSTSIMPLESRCClass {
  GstPushSrcClass parent_class;
};

GType gst_simple_src_get_type (void);

G_END_DECLS

#endif /* __GST_simple_SRC_H__ */
