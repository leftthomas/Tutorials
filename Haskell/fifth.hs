module Main where
-- 迭代法计算
import Debug.Trace

debug = flip trace

main::IO()
main = do
    print(mysqrt 2.0)
    print(mysqrt2 2.0)

mysqrt::Double->Double
mysqrt x = iter x 1.0
    where iter x0 y
              | abs(x0-y*y)<0.0000001 = y `debug` ("y=" ++ show y)
              | otherwise = iter x0 (improve y)
              where improve y = (y+x/y)/2.0

-- 不动点定理计算
fixpoint::(Double->Double)->Double->Double
fixpoint f start=iter start (f start) 0.001
    where iter old new epsilon
              | abs(old new)<epsilon = old
              | otherwise = iter new (f new) epsilon

mysqrt2 x = fixpoint (\y->(x/y+y)/2.0) 1

-- 牛顿法计算
newton::(Double->Double)->Double->Double
newton f = fixpoint (\y->(y-f y/df y))
    where
    	df = (f (x+dx) - f x) /dx
    	dx = 0.001

mysqrt3 x = newton (\y->(x-y*y)) 1