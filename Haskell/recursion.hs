-- sum尾递归 --
sum' :: (Num a) => [a] -> a
sum' [] = error "empty list"
sum' [x] = x
sum' (x:xs) = x + sum xs

-- 实现 (x+y) --
add' :: Int -> Int -> Int
add' x y 
  | x == 0 = y
  | x > 0 = add' (x-1) (y+1)

-- 求三个数的Max --
max' :: (Ord a) => [a] -> a 
max' [] = error "empty list" 
max' [x] = x 
max' (x:xs) = max x (max' xs)