# GstSimpleSrc
this is a simple video test src for gstreamer, you can use it as a template.

## Build

```
meson build 

ninja -C build
```


## Build(Cross Compile)

```
PKG_CONFIG=pkg-config meson build --cross-file cross_file.txt

ninja -C build
```


## Runing

```
gst-launch-1.0 simplesrc ! pngenc ! filesink location=foo.png

```