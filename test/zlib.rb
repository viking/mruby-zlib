assert('Zlib.deflate') do
  Zlib.respond_to? :deflate
end

assert('Zlib.inflate') do
  Zlib.respond_to? :inflate
end
