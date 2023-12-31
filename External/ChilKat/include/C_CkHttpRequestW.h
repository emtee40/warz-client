#ifndef _C_CkHttpRequest_W_H
#define _C_CkHttpRequest_W_H
#include "Chilkat_C.h"

HCkHttpRequestW CkHttpRequestW_Create(void);
HCkHttpRequestW CkHttpRequestW_Create2(bool bForMono);
void CkHttpRequestW_Dispose(HCkHttpRequestW handle);
void CkHttpRequestW_getCharset(HCkHttpRequestW cHandle, HCkStringW retval);
void CkHttpRequestW_putCharset(HCkHttpRequestW cHandle, const wchar_t *newVal);
void CkHttpRequestW_getContentType(HCkHttpRequestW cHandle, HCkStringW retval);
void CkHttpRequestW_putContentType(HCkHttpRequestW cHandle, const wchar_t *newVal);
void CkHttpRequestW_getDebugLogFilePath(HCkHttpRequestW cHandle, HCkStringW retval);
void CkHttpRequestW_putDebugLogFilePath(HCkHttpRequestW cHandle, const wchar_t *newVal);
void CkHttpRequestW_getEntireHeader(HCkHttpRequestW cHandle, HCkStringW retval);
void CkHttpRequestW_putEntireHeader(HCkHttpRequestW cHandle, const wchar_t *newVal);
void CkHttpRequestW_getHttpVerb(HCkHttpRequestW cHandle, HCkStringW retval);
void CkHttpRequestW_putHttpVerb(HCkHttpRequestW cHandle, const wchar_t *newVal);
void CkHttpRequestW_getHttpVersion(HCkHttpRequestW cHandle, HCkStringW retval);
void CkHttpRequestW_putHttpVersion(HCkHttpRequestW cHandle, const wchar_t *newVal);
void CkHttpRequestW_getLastErrorHtml(HCkHttpRequestW cHandle, HCkStringW retval);
void CkHttpRequestW_getLastErrorText(HCkHttpRequestW cHandle, HCkStringW retval);
void CkHttpRequestW_getLastErrorXml(HCkHttpRequestW cHandle, HCkStringW retval);
int CkHttpRequestW_getNumHeaderFields(HCkHttpRequestW cHandle);
int CkHttpRequestW_getNumParams(HCkHttpRequestW cHandle);
void CkHttpRequestW_getPath(HCkHttpRequestW cHandle, HCkStringW retval);
void CkHttpRequestW_putPath(HCkHttpRequestW cHandle, const wchar_t *newVal);
BOOL CkHttpRequestW_getSendCharset(HCkHttpRequestW cHandle);
void CkHttpRequestW_putSendCharset(HCkHttpRequestW cHandle, BOOL newVal);
BOOL CkHttpRequestW_getVerboseLogging(HCkHttpRequestW cHandle);
void CkHttpRequestW_putVerboseLogging(HCkHttpRequestW cHandle, BOOL newVal);
void CkHttpRequestW_getVersion(HCkHttpRequestW cHandle, HCkStringW retval);
BOOL CkHttpRequestW_AddBytesForUpload(HCkHttpRequestW cHandle, const wchar_t *name, const wchar_t *filename, HCkByteDataW byteData);
BOOL CkHttpRequestW_AddBytesForUpload2(HCkHttpRequestW cHandle, const wchar_t *name, const wchar_t *filename, HCkByteDataW byteData, const wchar_t *contentType);
BOOL CkHttpRequestW_AddFileForUpload(HCkHttpRequestW cHandle, const wchar_t *name, const wchar_t *path);
BOOL CkHttpRequestW_AddFileForUpload2(HCkHttpRequestW cHandle, const wchar_t *name, const wchar_t *path, const wchar_t *contentType);
void CkHttpRequestW_AddHeader(HCkHttpRequestW cHandle, const wchar_t *name, const wchar_t *value);
void CkHttpRequestW_AddParam(HCkHttpRequestW cHandle, const wchar_t *name, const wchar_t *value);
BOOL CkHttpRequestW_AddStringForUpload(HCkHttpRequestW cHandle, const wchar_t *name, const wchar_t *filename, const wchar_t *strData, const wchar_t *charset);
BOOL CkHttpRequestW_AddStringForUpload2(HCkHttpRequestW cHandle, const wchar_t *name, const wchar_t *filename, const wchar_t *strData, const wchar_t *charset, const wchar_t *contentType);
BOOL CkHttpRequestW_GenerateRequestText(HCkHttpRequestW cHandle, HCkStringW outStr);
BOOL CkHttpRequestW_GetHeaderField(HCkHttpRequestW cHandle, const wchar_t *name, HCkStringW outStr);
BOOL CkHttpRequestW_GetHeaderName(HCkHttpRequestW cHandle, int index, HCkStringW outStr);
BOOL CkHttpRequestW_GetHeaderValue(HCkHttpRequestW cHandle, int index, HCkStringW outStr);
BOOL CkHttpRequestW_GetParam(HCkHttpRequestW cHandle, const wchar_t *name, HCkStringW outStr);
BOOL CkHttpRequestW_GetParamName(HCkHttpRequestW cHandle, int index, HCkStringW outStr);
BOOL CkHttpRequestW_GetParamValue(HCkHttpRequestW cHandle, int index, HCkStringW outStr);
BOOL CkHttpRequestW_GetUrlEncodedParams(HCkHttpRequestW cHandle, HCkStringW outStr);
BOOL CkHttpRequestW_LoadBodyFromBytes(HCkHttpRequestW cHandle, HCkByteDataW binaryData);
BOOL CkHttpRequestW_LoadBodyFromFile(HCkHttpRequestW cHandle, const wchar_t *path);
BOOL CkHttpRequestW_LoadBodyFromString(HCkHttpRequestW cHandle, const wchar_t *bodyStr, const wchar_t *charset);
void CkHttpRequestW_RemoveAllParams(HCkHttpRequestW cHandle);
BOOL CkHttpRequestW_RemoveHeader(HCkHttpRequestW cHandle, const wchar_t *name);
void CkHttpRequestW_RemoveParam(HCkHttpRequestW cHandle, const wchar_t *name);
BOOL CkHttpRequestW_SaveLastError(HCkHttpRequestW cHandle, const wchar_t *path);
void CkHttpRequestW_SetFromUrl(HCkHttpRequestW cHandle, const wchar_t *url);
BOOL CkHttpRequestW_StreamBodyFromFile(HCkHttpRequestW cHandle, const wchar_t *path);
void CkHttpRequestW_UseGet(HCkHttpRequestW cHandle);
void CkHttpRequestW_UseHead(HCkHttpRequestW cHandle);
void CkHttpRequestW_UsePost(HCkHttpRequestW cHandle);
void CkHttpRequestW_UsePostMultipartForm(HCkHttpRequestW cHandle);
void CkHttpRequestW_UsePut(HCkHttpRequestW cHandle);
void CkHttpRequestW_UseUpload(HCkHttpRequestW cHandle);
void CkHttpRequestW_UseUploadPut(HCkHttpRequestW cHandle);
void CkHttpRequestW_UseXmlHttp(HCkHttpRequestW cHandle, const wchar_t *xmlBody);
const wchar_t *CkHttpRequestW__charset(HCkHttpRequestW cHandle);
const wchar_t *CkHttpRequestW__contentType(HCkHttpRequestW cHandle);
const wchar_t *CkHttpRequestW__debugLogFilePath(HCkHttpRequestW cHandle);
const wchar_t *CkHttpRequestW__entireHeader(HCkHttpRequestW cHandle);
const wchar_t *CkHttpRequestW__generateRequestText(HCkHttpRequestW cHandle);
const wchar_t *CkHttpRequestW__getHeaderField(HCkHttpRequestW cHandle, const wchar_t *name);
const wchar_t *CkHttpRequestW__getHeaderName(HCkHttpRequestW cHandle, int index);
const wchar_t *CkHttpRequestW__getHeaderValue(HCkHttpRequestW cHandle, int index);
const wchar_t *CkHttpRequestW__getParam(HCkHttpRequestW cHandle, const wchar_t *name);
const wchar_t *CkHttpRequestW__getParamName(HCkHttpRequestW cHandle, int index);
const wchar_t *CkHttpRequestW__getParamValue(HCkHttpRequestW cHandle, int index);
const wchar_t *CkHttpRequestW__getUrlEncodedParams(HCkHttpRequestW cHandle);
const wchar_t *CkHttpRequestW__httpVerb(HCkHttpRequestW cHandle);
const wchar_t *CkHttpRequestW__httpVersion(HCkHttpRequestW cHandle);
const wchar_t *CkHttpRequestW__lastErrorHtml(HCkHttpRequestW cHandle);
const wchar_t *CkHttpRequestW__lastErrorText(HCkHttpRequestW cHandle);
const wchar_t *CkHttpRequestW__lastErrorXml(HCkHttpRequestW cHandle);
const wchar_t *CkHttpRequestW__path(HCkHttpRequestW cHandle);
const wchar_t *CkHttpRequestW__version(HCkHttpRequestW cHandle);
#endif
