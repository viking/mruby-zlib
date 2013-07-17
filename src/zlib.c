#include <mruby.h>
#include <mruby/value.h>
#include <mruby/string.h>
#include <stdlib.h>
#include <stdio.h>
#include <zlib.h>

static voidpf
zlib_alloc(voidpf opaque, uInt n, uInt size)
{
  return calloc((size_t) n, (size_t) size);
}

static void
zlib_free(voidpf opaque, voidpf p)
{
  free((void *) p);
}

static mrb_value
mrb_zlib_raise(mrb_state *mrb, z_streamp strm, int err)
{
  char msg[256];
  snprintf(msg, 256, "zlib error (%d): %s", err, strm->msg);
  mrb_raise(mrb, E_RUNTIME_ERROR, msg);
}

static mrb_value
mrb_zlib_deflate(mrb_state *mrb, mrb_value self)
{
  struct RString *result;
  mrb_value value_data, value_result = mrb_nil_value();
  z_stream strm;
  int res;

  mrb_get_args(mrb, "S", &value_data);

  strm.zalloc = zlib_alloc;
  strm.zfree = zlib_free;
  strm.opaque = NULL;

  res = deflateInit(&strm, Z_DEFAULT_COMPRESSION);
  if (res != Z_OK) {
    mrb_zlib_raise(mrb, &strm, res);
  }

  value_result = mrb_str_buf_new(mrb,
      deflateBound(&strm, RSTRING_LEN(value_data)));
  result = mrb_str_ptr(value_result);

  strm.next_in = RSTRING_PTR(value_data);
  strm.avail_in = RSTRING_LEN(value_data);
  strm.next_out = RSTRING_PTR(value_result);
  strm.avail_out = RSTRING_CAPA(value_result);

  while (1) {
    res = deflate(&strm, Z_FINISH);
    if (res == Z_OK) {
      value_result = mrb_str_resize(mrb, value_result,
          RSTRING_CAPA(value_result) * 2);
      strm.next_out = RSTRING_PTR(value_result) + strm.total_out;
      strm.avail_out = RSTRING_CAPA(value_result) - strm.total_out;
    }
    else if (res == Z_STREAM_END) {
      result->len = strm.total_out;
      *(result->ptr + result->len) = '\0';

      res = deflateEnd(&strm);
      if (res != Z_OK) {
        mrb_zlib_raise(mrb, &strm, res);
      }
      break;
    }
    else {
      mrb_zlib_raise(mrb, &strm, res);
    }
  }

  return value_result;
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
