
all:
	ghc -c -O Safe.hs
	ghc -threaded --make -no-hs-main -optc-O test.c Safe -o test.exe
	ghc -threaded --make -no-hs-main -optc-O multithreaded.c Safe -o multithreaded.exe
	$(MAKE) haskell_first.exe

haskell_first.exe:
	ghc -c -O Main.hs
	ghc -threaded --make -optc-O shared.c Safe Main -o haskell_first.exe
#	ghc -threaded --make -optc-O haskell_first.c Safe Main -o haskell_first.exe

clean:
	rm -f *.o *.hi *.exe *_stub.h
