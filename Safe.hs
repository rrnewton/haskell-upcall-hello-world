

module Safe where
 
import Foreign.C.Types
import GHC.Conc
 
fibonacci :: Int -> Int
fibonacci n = fibs !! n
    where fibs = 0 : 1 : zipWith (+) fibs (tail fibs)
 
fibonacci_hs :: CInt -> CInt
fibonacci_hs = fromIntegral . fibonacci . fromIntegral
 
foreign export ccall fibonacci_hs :: CInt -> CInt


print_numcaps :: IO ()
print_numcaps =
  do n <- getNumCapabilities
     putStrLn $ "Number of capabilities: "++ show n


foreign export ccall print_numcaps :: IO ()
