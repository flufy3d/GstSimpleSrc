
project('gst-simple-src', 'c', version : '1.0.1', license : 'MIT')

plugin_c_args = ['-DHAVE_CONFIG_H', '-DDISABLE_ORC']

cdata = configuration_data()
cdata.set_quoted('VERSION', meson.project_version())
cdata.set_quoted('PACKAGE', 'gst-simplesrc-plugin')
cdata.set_quoted('GST_LICENSE', 'MIT')
cdata.set_quoted('GST_PACKAGE_NAME', 'GStreamer Simple Test Source Plug-in')
cdata.set_quoted('GST_PACKAGE_ORIGIN', 'https://360.world')
configure_file(output : 'config.h', configuration : cdata)



cc = meson.get_compiler('c')

libm = cc.find_library('m', required : false)

gst_dep = dependency('gstreamer-1.0',
  required : true, fallback : ['gstreamer', 'gst_dep'])

gst_base_dep = dependency('gstreamer-base-1.0',
  fallback : ['gstreamer', 'gst_base_dep'])

video_dep = dependency('gstreamer-video-1.0',
  fallback: ['gst-plugins-base', 'video_dep'])


simplesrc_deps = [video_dep, gst_dep, gst_base_dep, libm]


sources = [
  'src/gstsimplesrc.c',
  'src/simplesrc.c',
  'src/orc-dist.c'
]


gstsimplesrc = library('gstsimplesrc',
  sources,
  c_args : plugin_c_args,
  include_directories: ['.', './src'],
  dependencies : simplesrc_deps
)
