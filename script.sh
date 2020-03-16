rm ms.exe
rm tc.exe
g++ mainserver.cpp -pthread -o ms.exe
g++ clienttest.cpp  -pthread -o tc.exe