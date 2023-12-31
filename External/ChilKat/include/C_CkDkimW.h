#ifndef _C_CkDkim_W_H
#define _C_CkDkim_W_H
#include "Chilkat_C.h"

HCkDkimW CkDkimW_Create(void);
HCkDkimW CkDkimW_Create2(bool bForMono);
void CkDkimW_Dispose(HCkDkimW handle);
void CkDkimW_getDebugLogFilePath(HCkDkimW cHandle, HCkStringW retval);
void CkDkimW_putDebugLogFilePath(HCkDkimW cHandle, const wchar_t *newVal);
void CkDkimW_getDkimAlg(HCkDkimW cHandle, HCkStringW retval);
void CkDkimW_putDkimAlg(HCkDkimW cHandle, const wchar_t *newVal);
int CkDkimW_getDkimBodyLengthCount(HCkDkimW cHandle);
void CkDkimW_putDkimBodyLengthCount(HCkDkimW cHandle, int newVal);
void CkDkimW_getDkimCanon(HCkDkimW cHandle, HCkStringW retval);
void CkDkimW_putDkimCanon(HCkDkimW cHandle, const wchar_t *newVal);
void CkDkimW_getDkimDomain(HCkDkimW cHandle, HCkStringW retval);
void CkDkimW_putDkimDomain(HCkDkimW cHandle, const wchar_t *newVal);
void CkDkimW_getDkimHeaders(HCkDkimW cHandle, HCkStringW retval);
void CkDkimW_putDkimHeaders(HCkDkimW cHandle, const wchar_t *newVal);
void CkDkimW_getDkimSelector(HCkDkimW cHandle, HCkStringW retval);
void CkDkimW_putDkimSelector(HCkDkimW cHandle, const wchar_t *newVal);
void CkDkimW_getDomainKeyAlg(HCkDkimW cHandle, HCkStringW retval);
void CkDkimW_putDomainKeyAlg(HCkDkimW cHandle, const wchar_t *newVal);
void CkDkimW_getDomainKeyCanon(HCkDkimW cHandle, HCkStringW retval);
void CkDkimW_putDomainKeyCanon(HCkDkimW cHandle, const wchar_t *newVal);
void CkDkimW_getDomainKeyDomain(HCkDkimW cHandle, HCkStringW retval);
void CkDkimW_putDomainKeyDomain(HCkDkimW cHandle, const wchar_t *newVal);
void CkDkimW_getDomainKeyHeaders(HCkDkimW cHandle, HCkStringW retval);
void CkDkimW_putDomainKeyHeaders(HCkDkimW cHandle, const wchar_t *newVal);
void CkDkimW_getDomainKeySelector(HCkDkimW cHandle, HCkStringW retval);
void CkDkimW_putDomainKeySelector(HCkDkimW cHandle, const wchar_t *newVal);
HCkDkimProgressW CkDkimW_getEventCallbackObject(HCkDkimW cHandle);
void CkDkimW_putEventCallbackObject(HCkDkimW cHandle, HCkDkimProgressW newVal);
void CkDkimW_getLastErrorHtml(HCkDkimW cHandle, HCkStringW retval);
void CkDkimW_getLastErrorText(HCkDkimW cHandle, HCkStringW retval);
void CkDkimW_getLastErrorXml(HCkDkimW cHandle, HCkStringW retval);
BOOL CkDkimW_getVerboseLogging(HCkDkimW cHandle);
void CkDkimW_putVerboseLogging(HCkDkimW cHandle, BOOL newVal);
void CkDkimW_getVersion(HCkDkimW cHandle, HCkStringW retval);
BOOL CkDkimW_AddDkimSignature(HCkDkimW cHandle, HCkByteDataW mimeIn, HCkByteDataW outBytes);
BOOL CkDkimW_AddDomainKeySignature(HCkDkimW cHandle, HCkByteDataW mimeIn, HCkByteDataW outBytes);
BOOL CkDkimW_LoadDkimPk(HCkDkimW cHandle, const wchar_t *privateKey, const wchar_t *optionalPassword);
BOOL CkDkimW_LoadDkimPkBytes(HCkDkimW cHandle, HCkByteDataW privateKeyDer, const wchar_t *optionalPassword);
BOOL CkDkimW_LoadDkimPkFile(HCkDkimW cHandle, const wchar_t *privateKeyFilepath, const wchar_t *optionalPassword);
BOOL CkDkimW_LoadDomainKeyPk(HCkDkimW cHandle, const wchar_t *privateKey, const wchar_t *optionalPassword);
BOOL CkDkimW_LoadDomainKeyPkBytes(HCkDkimW cHandle, HCkByteDataW privateKeyDer, const wchar_t *optionalPassword);
BOOL CkDkimW_LoadDomainKeyPkFile(HCkDkimW cHandle, const wchar_t *privateKeyFilepath, const wchar_t *optionalPassword);
BOOL CkDkimW_LoadPublicKey(HCkDkimW cHandle, const wchar_t *selector, const wchar_t *domain, const wchar_t *publicKey);
BOOL CkDkimW_LoadPublicKeyFile(HCkDkimW cHandle, const wchar_t *selector, const wchar_t *domain, const wchar_t *publicKeyFilepath);
int CkDkimW_NumDkimSignatures(HCkDkimW cHandle, HCkByteDataW mimeData);
int CkDkimW_NumDomainKeySignatures(HCkDkimW cHandle, HCkByteDataW mimeData);
BOOL CkDkimW_PrefetchPublicKey(HCkDkimW cHandle, const wchar_t *selector, const wchar_t *domain);
BOOL CkDkimW_SaveLastError(HCkDkimW cHandle, const wchar_t *path);
BOOL CkDkimW_UnlockComponent(HCkDkimW cHandle, const wchar_t *unlockCode);
BOOL CkDkimW_VerifyDkimSignature(HCkDkimW cHandle, int sigIdx, HCkByteDataW mimeData);
BOOL CkDkimW_VerifyDomainKeySignature(HCkDkimW cHandle, int sigIdx, HCkByteDataW mimeData);
const wchar_t *CkDkimW__debugLogFilePath(HCkDkimW cHandle);
const wchar_t *CkDkimW__dkimAlg(HCkDkimW cHandle);
const wchar_t *CkDkimW__dkimCanon(HCkDkimW cHandle);
const wchar_t *CkDkimW__dkimDomain(HCkDkimW cHandle);
const wchar_t *CkDkimW__dkimHeaders(HCkDkimW cHandle);
const wchar_t *CkDkimW__dkimSelector(HCkDkimW cHandle);
const wchar_t *CkDkimW__domainKeyAlg(HCkDkimW cHandle);
const wchar_t *CkDkimW__domainKeyCanon(HCkDkimW cHandle);
const wchar_t *CkDkimW__domainKeyDomain(HCkDkimW cHandle);
const wchar_t *CkDkimW__domainKeyHeaders(HCkDkimW cHandle);
const wchar_t *CkDkimW__domainKeySelector(HCkDkimW cHandle);
const wchar_t *CkDkimW__lastErrorHtml(HCkDkimW cHandle);
const wchar_t *CkDkimW__lastErrorText(HCkDkimW cHandle);
const wchar_t *CkDkimW__lastErrorXml(HCkDkimW cHandle);
const wchar_t *CkDkimW__version(HCkDkimW cHandle);
#endif
