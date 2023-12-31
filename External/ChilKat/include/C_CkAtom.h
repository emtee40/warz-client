#ifndef _C_CkAtom_H
#define _C_CkAtom_H
#include "Chilkat_C.h"

HCkAtom CkAtom_Create(void);
void CkAtom_Dispose(HCkAtom handle);
void CkAtom_getDebugLogFilePath(HCkAtom cHandle, HCkString retval);
void CkAtom_putDebugLogFilePath(HCkAtom cHandle, const char *newVal);
HCkAtomProgress CkAtom_getEventCallbackObject(HCkAtom cHandle);
void CkAtom_putEventCallbackObject(HCkAtom cHandle, HCkAtomProgress newVal);
void CkAtom_getLastErrorHtml(HCkAtom cHandle, HCkString retval);
void CkAtom_getLastErrorText(HCkAtom cHandle, HCkString retval);
void CkAtom_getLastErrorXml(HCkAtom cHandle, HCkString retval);
int CkAtom_getNumEntries(HCkAtom cHandle);
BOOL CkAtom_getUtf8(HCkAtom cHandle);
void CkAtom_putUtf8(HCkAtom cHandle, BOOL newVal);
BOOL CkAtom_getVerboseLogging(HCkAtom cHandle);
void CkAtom_putVerboseLogging(HCkAtom cHandle, BOOL newVal);
void CkAtom_getVersion(HCkAtom cHandle, HCkString retval);
int CkAtom_AddElement(HCkAtom cHandle, const char *tag, const char *value);
int CkAtom_AddElementDate(HCkAtom cHandle, const char *tag, SYSTEMTIME *dateTime);
int CkAtom_AddElementDateStr(HCkAtom cHandle, const char *tag, const char *dateTimeStr);
int CkAtom_AddElementDt(HCkAtom cHandle, const char *tag, HCkDateTime dateTime);
int CkAtom_AddElementHtml(HCkAtom cHandle, const char *tag, const char *htmlStr);
int CkAtom_AddElementXHtml(HCkAtom cHandle, const char *tag, const char *xmlStr);
int CkAtom_AddElementXml(HCkAtom cHandle, const char *tag, const char *xmlStr);
void CkAtom_AddEntry(HCkAtom cHandle, const char *xmlStr);
void CkAtom_AddLink(HCkAtom cHandle, const char *rel, const char *href, const char *title, const char *typ);
void CkAtom_AddPerson(HCkAtom cHandle, const char *tag, const char *name, const char *uri, const char *email);
void CkAtom_DeleteElement(HCkAtom cHandle, const char *tag, int index);
void CkAtom_DeleteElementAttr(HCkAtom cHandle, const char *tag, int index, const char *attrName);
void CkAtom_DeletePerson(HCkAtom cHandle, const char *tag, int index);
BOOL CkAtom_DownloadAtom(HCkAtom cHandle, const char *url);
BOOL CkAtom_GetElement(HCkAtom cHandle, const char *tag, int index, HCkString outStr);
BOOL CkAtom_GetElementAttr(HCkAtom cHandle, const char *tag, int index, const char *attrName, HCkString outStr);
int CkAtom_GetElementCount(HCkAtom cHandle, const char *tag);
BOOL CkAtom_GetElementDate(HCkAtom cHandle, const char *tag, int index, SYSTEMTIME *outSysTime);
BOOL CkAtom_GetElementDateStr(HCkAtom cHandle, const char *tag, int index, HCkString outStr);
HCkDateTime CkAtom_GetElementDt(HCkAtom cHandle, const char *tag, int index);
HCkAtom CkAtom_GetEntry(HCkAtom cHandle, int index);
BOOL CkAtom_GetLinkHref(HCkAtom cHandle, const char *relName, HCkString outStr);
BOOL CkAtom_GetPersonInfo(HCkAtom cHandle, const char *tag, int index, const char *tag2, HCkString outStr);
BOOL CkAtom_GetTopAttr(HCkAtom cHandle, const char *attrName, HCkString outStr);
BOOL CkAtom_HasElement(HCkAtom cHandle, const char *tag);
BOOL CkAtom_LoadXml(HCkAtom cHandle, const char *xmlStr);
void CkAtom_NewEntry(HCkAtom cHandle);
void CkAtom_NewFeed(HCkAtom cHandle);
BOOL CkAtom_SaveLastError(HCkAtom cHandle, const char *path);
void CkAtom_SetElementAttr(HCkAtom cHandle, const char *tag, int index, const char *attrName, const char *attrValue);
void CkAtom_SetTopAttr(HCkAtom cHandle, const char *attrName, const char *value);
BOOL CkAtom_ToXmlString(HCkAtom cHandle, HCkString outStr);
void CkAtom_UpdateElement(HCkAtom cHandle, const char *tag, int index, const char *value);
void CkAtom_UpdateElementDate(HCkAtom cHandle, const char *tag, int index, SYSTEMTIME *dateTime);
void CkAtom_UpdateElementDateStr(HCkAtom cHandle, const char *tag, int index, const char *dateTimeStr);
void CkAtom_UpdateElementDt(HCkAtom cHandle, const char *tag, int index, HCkDateTime dateTime);
void CkAtom_UpdateElementHtml(HCkAtom cHandle, const char *tag, int index, const char *htmlStr);
void CkAtom_UpdateElementXHtml(HCkAtom cHandle, const char *tag, int index, const char *xmlStr);
void CkAtom_UpdateElementXml(HCkAtom cHandle, const char *tag, int index, const char *xmlStr);
void CkAtom_UpdatePerson(HCkAtom cHandle, const char *tag, int index, const char *name, const char *uri, const char *email);
const char *CkAtom_debugLogFilePath(HCkAtom cHandle);
const char *CkAtom_getElement(HCkAtom cHandle, const char *tag, int index);
const char *CkAtom_getElementAttr(HCkAtom cHandle, const char *tag, int index, const char *attrName);
const char *CkAtom_getElementDateStr(HCkAtom cHandle, const char *tag, int index);
const char *CkAtom_getLinkHref(HCkAtom cHandle, const char *relName);
const char *CkAtom_getPersonInfo(HCkAtom cHandle, const char *tag, int index, const char *tag2);
const char *CkAtom_getTopAttr(HCkAtom cHandle, const char *attrName);
const char *CkAtom_lastErrorHtml(HCkAtom cHandle);
const char *CkAtom_lastErrorText(HCkAtom cHandle);
const char *CkAtom_lastErrorXml(HCkAtom cHandle);
const char *CkAtom_toXmlString(HCkAtom cHandle);
const char *CkAtom_version(HCkAtom cHandle);
#endif
