class R r where
  sum' :: Integer -> r

instance R Integer where
  sum' x = x

instance (Integral a, R r) => R (a -> r) where
  sum' x y = sum' (x + toInteger y)

main = print (sum' 6 7::Integer)
