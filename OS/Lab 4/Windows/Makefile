stdFlags = -std=c++20

dllDir = dll_sources
dllInclude = ${dllDir}/include
dllSrc = ${dllDir}/src


dllFlags = ${stdFlags} -shared -fPIC -s

dest = ./buildDir

addDllFlags = -L${dest} -lprimes -lsin

WlWindowsFlags = -Wl,-subsystem,windows -Wl,-export-all-symbols
WlWindowsLibFlags = -Wl,--out-implib,

main: doDll
	g++ ${stdFlags} linkedProg.cpp -o ${dest}/linkedProg.exe ${addDllFlags} 
	g++ ${stdFlags} dynamicProg.cpp -o ${dest}/dynamicProg.exe

doDll:
	g++ ${dllFlags} ${WlWindowsFlags} ${WlWindowsLibFlags}${dest}/libsin.lib -I${dllInclude} ${dllSrc}/1SinIntegral.cpp -o ${dest}/libsin.dll
	g++ ${dllFlags} ${WlWindowsFlags} ${WlWindowsLibFlags}${dest}/libprimes.lib -I${dllInclude} ${dllSrc}/3PrimeCounter.cpp -o ${dest}/libprimes.dll
