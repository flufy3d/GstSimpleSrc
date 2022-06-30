
project('gst-simple-src', 'c', version : '1.0.1', license : 'MIT')


cc = meson.get_compiler('c')


gst_dep = dependency('gstreamer-1.0',
  method : 'auto',
  required : true, fallback : ['gstreamer', 'gst_dep'])

gst_base_dep = dependency('gstreamer-base-1.0',
  method : 'pkg-config',
  fallback : ['gstreamer', 'gst_base_dep'])

video_dep = dependency('gstreamer-video-1.0',
  method : 'pkg-config',
  fallback: ['gst-plugins-base', 'video_dep'])


simplesrc_deps = [video_dep, gst_dep, gst_base_dep]


sources = [
  'src/gstsimplesrc.c',
  'src/simplesrc.c',
  'src/orc-dist.c'
]


gstsimplesrc = library('gstsimplesrc',
  sources,
  c_args : [],
  include_directories: ['.', './src'],
  dependencies : simplesrc_deps
)
