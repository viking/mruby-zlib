
use https://github.com/iij/mruby-zlib

mruby-zlib
==========

Provides zlib compression for mruby.

Example:

    x = "foo"
    y = Zlib.deflate(x)
    z = Zlib.inflate(y)

## License

MIT
