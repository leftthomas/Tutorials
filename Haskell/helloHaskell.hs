doubleMe x = x + x

doubleUs x y = x*2 + y*2

doubleUs2 x y = doubleMe x +doubleMe y

doubleSmallNumber x = if x > 100 then x else x*2

doubleSmallNumber' x = (if x > 100 then x else x*2)+1

ren'Hao = "It's me, Ren Hao!"

lucky :: (Integral a) => a -> String
lucky 7 = "LUCKY NUMBER SEVEN!"
lucky x = "Sorry, you're out of luck, pal!"

head' :: [a] -> a
head' [] = error "Can't call head on an empty list, dummy!" 
head' (x:_) = x

tell :: (Show a) => [a] -> String
tell [] = "The list is empty"
tell (x:[]) = "The list has one element: " ++ show x
tell (x:y:[]) = "The list has two elements: " ++ show x ++ " and " ++ show y
tell (x:y:_) = "This list is long. The first two elements are: " ++ show x ++ " and " ++ show y

length' :: (Num b) => [a] -> b 
length' [] = 0
length' (_:xs) = 1 + length' xs

sum' :: (Num a) => [a] -> a 
sum' [] = 0
sum' (x:xs) = x + sum' xs

capital :: String -> String
capital "" = "Empty string, whoops!"
capital all@(x:xs) = "The first letter of " ++ all ++ " is " ++ [x]

bmiTell :: (RealFloat a) => a -> String 
bmiTell bmi
  | bmi <= 18.5 = "You're underweight, you emo, you!"
  | bmi <= 25.0 = "You're supposedly normal. Pffft, I bet you're ugly!"
  | bmi <= 30.0 = "You're fat! Lose some weight, fatty!"
  | otherwise = "You're a whale, congratulations!"

bmiTell' :: (RealFloat a) => a -> a -> String
bmiTell' weight height
  | weight/height ^ 2 <= 18.5 = "You're underweight, you emo, you!"
  | weight/height ^ 2 <= 25.0 = "You're supposedly normal. Pffft, I bet you're ugly!"
  | weight/height ^ 2 <= 30.0 = "You're fat! Lose some weight, fatty!"
  | otherwise = "You're a whale, congratulations!"

max' :: (Ord a) => a -> a -> a 
max' a b
  | a>b = a 
  | otherwise = b

myCompare :: (Ord a) => a -> a -> Ordering 
a `myCompare` b
  | a>b = GT 
  | a==b = EQ 
  | otherwise = LT

bmiTell_ :: (RealFloat a) => a -> a -> String 
bmiTell_ weight height
  | bmi <= 18.5 = "You're underweight, you emo, you!"
  | bmi <= 25.0 = "You're supposedly normal. Pffft, I bet you're ugly!"
  | bmi <= 30.0 = "You're fat! Lose some weight, fatty!"
  | otherwise = "You're a whale, congratulations!"
  where bmi = weight / height ^ 2

initials :: String -> String -> String
initials firstname lastname = [f] ++ ". " ++ [l] ++ "."
    where (f:_) = firstname
          (l:_) = lastname

calcBmis :: (RealFloat a) => [(a, a)] -> [a] 
calcBmis xs = [bmi w h | (w, h) <- xs]
    where bmi weight height = weight / height ^ 2

cylinder :: (RealFloat a) => a -> a -> a 
cylinder r h =
    let sideArea = 2 * pi * r * h 
        topArea = pi * r ^2
    in sideArea + 2 * topArea

calcBmis' :: (RealFloat a) => [(a, a)] -> [a]
calcBmis' xs = [bmi | (w, h) <- xs, let bmi = w / h ^ 2]

calcBmis_ :: (RealFloat a) => [(a, a)] -> [a]
calcBmis_ xs = [bmi | (w, h) <- xs, let bmi = w / h ^ 2, bmi >= 25.0]

describeList :: [a] -> String
describeList xs = "The list is " ++ case xs of [] -> "empty."
                                               [x] -> "a singleton list." 
                                               xs -> "a longer list."

maximum' :: (Ord a) => [a] -> a
maximum' [] = error "maximum of empty list" 
maximum' [x] = x
maximum' (x:xs)
    | x > maxTail = x
    | otherwise = maxTail 
    where maxTail = maximum' xs

maximum_ :: (Ord a) => [a] -> a
maximum_ [] = error "maximum of empty list" 
maximum_ [x] = x
maximum_ (x:xs) = max x (maximum' xs)

replicate' :: (Num i, Ord i) => i -> a -> [a] 
replicate' n x
    | n<=0 =[]
    | otherwise = x:replicate' (n-1) x

take' :: (Num i, Ord i) => i -> [a] -> [a] 
take' n _
    | n<=0 =[]
take' _ [] = []
take' n (x:xs) = x : take' (n-1) xs

reverse' :: [a] -> [a]
reverse' [] = []
reverse' (x:xs) = reverse' xs ++ [x]

repeat' :: a -> [a] 
repeat' x = x:repeat' x

zip' :: [a] -> [b] -> [(a,b)]
zip' _ [] = []
zip' [] _ = []
zip' (x:xs) (y:ys) = (x,y):zip' xs ys

elem' :: (Eq a) => a -> [a] -> Bool 
elem' a [] = False
elem' a (x:xs)
    | a == x = True
    | otherwise = a `elem'` xs

quicksort :: (Ord a) => [a] -> [a] 
quicksort [] = []
quicksort (x:xs) =
  let smallerSorted = quicksort [a | a <- xs, a <= x] 
      biggerSorted = quicksort [a | a <- xs, a > x]
  in smallerSorted ++ [x] ++ biggerSorted