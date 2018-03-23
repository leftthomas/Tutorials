type Stack = [Int]

pop :: Stack -> (Int, Stack)
pop (x:xs) = (x,xs)

push :: Int -> Stack -> ((), Stack)
push a xs = ((), a:xs)

stackManip =
  do
    push 3
    a <- pop
    pop

addNum :: Int -> Int -> State Int Int
addNum = opNum (+)

subNum :: Int -> Int -> State Int Int
subNum = opNum (-)

mulNum :: Int -> Int -> State Int Int
mulNum = opNum (*)

divNum :: Int -> Int -> State Int Int
divNum = opNum div

inc :: Int -> State Int Int
inc = addNum 1

dec :: Int -> State Int Int
dec = flip subNum 1
