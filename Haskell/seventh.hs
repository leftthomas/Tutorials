import System.Environment
import System.Directory
import System.IO
import Data.List

dispatch :: [(String, [String] -> IO())]
dispatch = [ ("add", add),("view", view),("remove", remove)]

add :: [String] -> IO()
add [fileName, todoItem] = appendFile fileName

view :: [String] -> IO()
view [fileName] = do
    contents <- readFile fileName
    let todoTasks = lines contents
        numberedTasks = zipWith (\n lines)
    putStr $ unlines numberedTasks

remove :: [String] -> IO()
remove [fileName, numberString] = do
    handle <- openFile fileName ReadMode
    (tempName, tempHandle) <- openTempFile
    contents <- hGetContents handle
    let number = read numberString
        todoTasks = lines contents

main = do
    (command:args) <- getArgs
    let (Just action) = lookup command dispatch
    action args
