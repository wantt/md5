#include<stdio.h>
#include  <string.h>
#include <openssl/sha.h>

void OPENSSL_cleanse(void *ptr, size_t len)
{
    memset(ptr, 0, len);
}


int upgUtlGetFileSha256Checksum(const char *filePath,char *mdStr)
{
    SHA256_CTX shaCtx;
    int   readLen = 0;
    FILE    *fp = NULL;
    char    dataBuf[512] = {0};
    int mdIdx = 0;
    unsigned char fileMd[32];
    fp = fopen(filePath, "ro");
    if (NULL == fp)
    {
       return -1;
    }

    SHA256_Init(&shaCtx);
    while ((readLen = fread(dataBuf, 1, 512, fp)) > 0)
    {
        SHA256_Update(&shaCtx, dataBuf, readLen);
        memset(dataBuf, 0, sizeof(dataBuf));
    }
    SHA256_Final(fileMd, &shaCtx);
    OPENSSL_cleanse(&shaCtx, sizeof(shaCtx));

    fclose(fp);

    for (mdIdx = 0; mdIdx < 32; mdIdx++)
    {
        sprintf(mdStr + (2 * mdIdx), "%02x", fileMd[mdIdx]);
    }

    return 0;
}

int main(int argc ,char* argv[]){
    char filemd[64];
    upgUtlGetFileSha256Checksum(argv[1],filemd);
    for(int i=0;i<64;i++){
    printf("%c",filemd[i]);}
    printf("\n");
    return 0;
}
