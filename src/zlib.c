#include <mruby.h>
#include <zlib.h>

static mrb_value
mrb_zlib_deflate(mrb_state *mrb, mrb_value self)
{
  return mrb_nil_value();
}

static mrb_value
mrb_zlib_inflate(mrb_state *mrb, mrb_value self)
{
  return mrb_nil_value();
}

void
mrb_mruby_zlib_gem_init(mrb_state* mrb) {
  struct RClass *zlib_module;

  zlib_module = mrb_define_module(mrb, "Zlib");
  mrb_define_module_function(mrb, zlib_module, "deflate", mrb_zlib_deflate, ARGS_REQ(1));
  mrb_define_module_function(mrb, zlib_module, "inflate", mrb_zlib_inflate, ARGS_REQ(1));
}

void
mrb_mruby_zlib_gem_final(mrb_state* mrb) {
}
