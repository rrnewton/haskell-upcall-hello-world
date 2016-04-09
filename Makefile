
all:
	ghc -c -O Safe.hs
	ghc --make -no-hs-main -optc-O test.c Safe -o test.exe

	ghc --make -no-hs-main -optc-O multithreaded.c Safe -o multithreaded.exe
