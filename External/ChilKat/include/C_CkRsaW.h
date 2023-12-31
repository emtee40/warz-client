#ifndef _C_CkRsa_W_H
#define _C_CkRsa_W_H
#include "Chilkat_C.h"

HCkRsaW CkRsaW_Create(void);
HCkRsaW CkRsaW_Create2(bool bForMono);
void CkRsaW_Dispose(HCkRsaW handle);
void CkRsaW_getCharset(HCkRsaW cHandle, HCkStringW retval);
void CkRsaW_putCharset(HCkRsaW cHandle, const wchar_t *newVal);
void CkRsaW_getDebugLogFilePath(HCkRsaW cHandle, HCkStringW retval);
void CkRsaW_putDebugLogFilePath(HCkRsaW cHandle, const wchar_t *newVal);
void CkRsaW_getEncodingMode(HCkRsaW cHandle, HCkStringW retval);
void CkRsaW_putEncodingMode(HCkRsaW cHandle, const wchar_t *newVal);
void CkRsaW_getLastErrorHtml(HCkRsaW cHandle, HCkStringW retval);
void CkRsaW_getLastErrorText(HCkRsaW cHandle, HCkStringW retval);
void CkRsaW_getLastErrorXml(HCkRsaW cHandle, HCkStringW retval);
BOOL CkRsaW_getLittleEndian(HCkRsaW cHandle);
void CkRsaW_putLittleEndian(HCkRsaW cHandle, BOOL newVal);
BOOL CkRsaW_getNoUnpad(HCkRsaW cHandle);
void CkRsaW_putNoUnpad(HCkRsaW cHandle, BOOL newVal);
long CkRsaW_getNumBits(HCkRsaW cHandle);
BOOL CkRsaW_getOaepPadding(HCkRsaW cHandle);
void CkRsaW_putOaepPadding(HCkRsaW cHandle, BOOL newVal);
BOOL CkRsaW_getVerboseLogging(HCkRsaW cHandle);
void CkRsaW_putVerboseLogging(HCkRsaW cHandle, BOOL newVal);
void CkRsaW_getVersion(HCkRsaW cHandle, HCkStringW retval);
BOOL CkRsaW_DecryptBytes(HCkRsaW cHandle, HCkByteDataW bData, BOOL bUsePrivateKey, HCkByteDataW outData);
BOOL CkRsaW_DecryptBytesENC(HCkRsaW cHandle, const wchar_t *str, BOOL bUsePrivateKey, HCkByteDataW outData);
BOOL CkRsaW_DecryptString(HCkRsaW cHandle, HCkByteDataW bData, BOOL bUsePrivateKey, HCkStringW outStr);
BOOL CkRsaW_DecryptStringENC(HCkRsaW cHandle, const wchar_t *str, BOOL bUsePrivateKey, HCkStringW outStr);
BOOL CkRsaW_EncryptBytes(HCkRsaW cHandle, HCkByteDataW bData, BOOL bUsePrivateKey, HCkByteDataW outData);
BOOL CkRsaW_EncryptBytesENC(HCkRsaW cHandle, HCkByteDataW bData, BOOL bUsePrivateKey, HCkStringW outStr);
BOOL CkRsaW_EncryptString(HCkRsaW cHandle, const wchar_t *str, BOOL bUsePrivateKey, HCkByteDataW outData);
BOOL CkRsaW_EncryptStringENC(HCkRsaW cHandle, const wchar_t *str, BOOL bUsePrivateKey, HCkStringW outStr);
BOOL CkRsaW_ExportPrivateKey(HCkRsaW cHandle, HCkStringW outStr);
BOOL CkRsaW_ExportPublicKey(HCkRsaW cHandle, HCkStringW outStr);
BOOL CkRsaW_GenerateKey(HCkRsaW cHandle, int numBits);
BOOL CkRsaW_ImportPrivateKey(HCkRsaW cHandle, const wchar_t *strXml);
BOOL CkRsaW_ImportPublicKey(HCkRsaW cHandle, const wchar_t *strXml);
BOOL CkRsaW_OpenSslSignBytes(HCkRsaW cHandle, HCkByteDataW data, HCkByteDataW outBytes);
BOOL CkRsaW_OpenSslSignBytesENC(HCkRsaW cHandle, HCkByteDataW data, HCkStringW outStr);
BOOL CkRsaW_OpenSslSignString(HCkRsaW cHandle, const wchar_t *str, HCkByteDataW outBytes);
BOOL CkRsaW_OpenSslSignStringENC(HCkRsaW cHandle, const wchar_t *str, HCkStringW outStr);
BOOL CkRsaW_OpenSslVerifyBytes(HCkRsaW cHandle, HCkByteDataW signature, HCkByteDataW outBytes);
BOOL CkRsaW_OpenSslVerifyBytesENC(HCkRsaW cHandle, const wchar_t *str, HCkByteDataW outBytes);
BOOL CkRsaW_OpenSslVerifyString(HCkRsaW cHandle, HCkByteDataW data, HCkStringW outStr);
BOOL CkRsaW_OpenSslVerifyStringENC(HCkRsaW cHandle, const wchar_t *str, HCkStringW outStr);
BOOL CkRsaW_SaveLastError(HCkRsaW cHandle, const wchar_t *path);
BOOL CkRsaW_SignBytes(HCkRsaW cHandle, HCkByteDataW bData, const wchar_t *hashAlg, HCkByteDataW outData);
BOOL CkRsaW_SignBytesENC(HCkRsaW cHandle, HCkByteDataW bData, const wchar_t *hashAlg, HCkStringW outStr);
BOOL CkRsaW_SignHash(HCkRsaW cHandle, HCkByteDataW hashBytes, const wchar_t *hashAlg, HCkByteDataW outBytes);
BOOL CkRsaW_SignHashENC(HCkRsaW cHandle, const wchar_t *encodedHash, const wchar_t *hashAlg, HCkStringW outStr);
BOOL CkRsaW_SignString(HCkRsaW cHandle, const wchar_t *str, const wchar_t *hashAlg, HCkByteDataW outData);
BOOL CkRsaW_SignStringENC(HCkRsaW cHandle, const wchar_t *str, const wchar_t *hashAlg, HCkStringW outStr);
BOOL CkRsaW_SnkToXml(HCkRsaW cHandle, const wchar_t *snkPath, HCkStringW outStr);
BOOL CkRsaW_UnlockComponent(HCkRsaW cHandle, const wchar_t *unlockCode);
BOOL CkRsaW_VerifyBytes(HCkRsaW cHandle, HCkByteDataW bData, const wchar_t *hashAlg, HCkByteDataW sigData);
BOOL CkRsaW_VerifyBytesENC(HCkRsaW cHandle, HCkByteDataW bData, const wchar_t *hashAlg, const wchar_t *encodedSig);
BOOL CkRsaW_VerifyHash(HCkRsaW cHandle, HCkByteDataW hashBytes, const wchar_t *hashAlg, HCkByteDataW sigBytes);
BOOL CkRsaW_VerifyHashENC(HCkRsaW cHandle, const wchar_t *encodedHash, const wchar_t *hashAlg, const wchar_t *encodedSig);
BOOL CkRsaW_VerifyPrivateKey(HCkRsaW cHandle, const wchar_t *xml);
BOOL CkRsaW_VerifyString(HCkRsaW cHandle, const wchar_t *str, const wchar_t *hashAlg, HCkByteDataW sigData);
BOOL CkRsaW_VerifyStringENC(HCkRsaW cHandle, const wchar_t *str, const wchar_t *hashAlg, const wchar_t *sig);
const wchar_t *CkRsaW__charset(HCkRsaW cHandle);
const wchar_t *CkRsaW__debugLogFilePath(HCkRsaW cHandle);
const wchar_t *CkRsaW__decryptString(HCkRsaW cHandle, HCkByteDataW bData, BOOL bUsePrivateKey);
const wchar_t *CkRsaW__decryptStringENC(HCkRsaW cHandle, const wchar_t *str, BOOL bUsePrivateKey);
const wchar_t *CkRsaW__encodingMode(HCkRsaW cHandle);
const wchar_t *CkRsaW__encryptBytesENC(HCkRsaW cHandle, HCkByteDataW bData, BOOL bUsePrivateKey);
const wchar_t *CkRsaW__encryptStringENC(HCkRsaW cHandle, const wchar_t *str, BOOL bUsePrivateKey);
const wchar_t *CkRsaW__exportPrivateKey(HCkRsaW cHandle);
const wchar_t *CkRsaW__exportPublicKey(HCkRsaW cHandle);
const wchar_t *CkRsaW__lastErrorHtml(HCkRsaW cHandle);
const wchar_t *CkRsaW__lastErrorText(HCkRsaW cHandle);
const wchar_t *CkRsaW__lastErrorXml(HCkRsaW cHandle);
const wchar_t *CkRsaW__openSslSignBytesENC(HCkRsaW cHandle, HCkByteDataW data);
const wchar_t *CkRsaW__openSslSignStringENC(HCkRsaW cHandle, const wchar_t *str);
const wchar_t *CkRsaW__openSslVerifyString(HCkRsaW cHandle, HCkByteDataW data);
const wchar_t *CkRsaW__openSslVerifyStringENC(HCkRsaW cHandle, const wchar_t *str);
const wchar_t *CkRsaW__signBytesENC(HCkRsaW cHandle, HCkByteDataW bData, const wchar_t *hashAlg);
const wchar_t *CkRsaW__signHashENC(HCkRsaW cHandle, const wchar_t *encodedHash, const wchar_t *hashAlg);
const wchar_t *CkRsaW__signStringENC(HCkRsaW cHandle, const wchar_t *str, const wchar_t *hashAlg);
const wchar_t *CkRsaW__snkToXml(HCkRsaW cHandle, const wchar_t *snkPath);
const wchar_t *CkRsaW__version(HCkRsaW cHandle);
#endif
