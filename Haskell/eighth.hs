--import Prelude hiding(Maybe, Noting, Just)

main = print $ maternalGrandfather "son2"

data Maybe_ a = Just_ a | Nothing_ String
                 deriving(Show)

instance Monad Maybe_ where
  --return :: a -> Maybe_ a
  return x = Just_ x

  --(>>=)::(Maybe_ a)->(a->Maybe_ b)->Maybe_ b
  (>>=)(Just_ x) f = f x
  (>>=)(Nothing_ s) f = Nothing_ $ s

type Person = String

father::Person->Maybe_ Person
father son = case son of
  "son1"->return "father1"
  "son2"->return "father2"
