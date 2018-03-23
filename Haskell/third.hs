-- QuickCheck --
import Test.QuickCheck

mymax :: Int->Int->Int
mymax x y
  | x <= y = x
  | x > y = y


prop_Max :: Int->Int->Bool
prop_Max x y = (x <= mymax x y) && (y <= mymax x y)

main = quickCheck prop_Max





-- 八皇后问题 --
boardSize = 8

queens 0 = [[]]
queens n = [ x : y | y <- queens (n-1), x <- [1..boardSize], safe x y 1]
  where
    safe x [] n = True
    safe x (c:y) n = and [ x /= c , x /= c + n , x /= c - n , safe x y (n+1)]