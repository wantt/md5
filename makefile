main:
	g++ md5.c -o md5 -lssl -lcrypto
clean:
	rm -rf md5  
