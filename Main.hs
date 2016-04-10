-- | 

module Main where

import Safe
import GHC.Conc
import Control.Concurrent

-- foreign import ccall bounce_back :: IO ()

-- go :: IO 
go name mv =
  do t1 <- myThreadId
     putStrLn $ "Forked haskell thread, "++name++" calling down then back up, tid: "++show t1
     -- bounce_back
     child
     t2 <- myThreadId
     putStrLn $ "Haskell thread, "++name++" returned to Haskell and exiting, tid: "++show t2
     putMVar mv ()     

-- This version does thread creation on the OS side.
main :: IO ()
main =
 do putStrLn "Running Haskell-created threads"
    mv1 <- newEmptyMVar
    mv2 <- newEmptyMVar
    forkOn 0 (go "child1" mv1)
    forkOn 1 (go "child1" mv2)
    takeMVar mv1
    takeMVar mv2

-- hs_dofib :: IO ()
-- hs_dofib = 
--  do putStrLn "Back in Haskell, but calling down to child()"
--     child

-- foreign export ccall hs_dofib :: IO ()

-- Do the batch of upcalls to fib:
foreign import ccall child :: IO ()
