assert('Zlib.deflate') do
  Zlib.respond_to? :deflate
end

assert('Zlib.gzip') do
  Zlib.respond_to? :gzip
end

assert('Zlib.inflate') do
  Zlib.respond_to? :inflate
end

assert('Zlib.deflate A*10') do
  Zlib.inflate(Zlib.deflate('A' * 10)) == 'A' * 10
end

assert('Zlib.gzip A*10') do
  Zlib.inflate(Zlib.gzip('A' * 10)) == 'A' * 10
end
