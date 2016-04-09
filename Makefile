
all:
	ghc -c -O Safe.hs
	ghc -threaded --make -no-hs-main -optc-O test.c Safe -o test.exe

	ghc -threaded --make -no-hs-main -optc-O multithreaded.c Safe -o multithreaded.exe

clean:
	rm -f *.o *.hi 
