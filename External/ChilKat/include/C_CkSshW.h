#ifndef _C_CkSsh_W_H
#define _C_CkSsh_W_H
#include "Chilkat_C.h"

HCkSshW CkSshW_Create(void);
HCkSshW CkSshW_Create2(bool bForMono);
void CkSshW_Dispose(HCkSshW handle);
int CkSshW_getChannelOpenFailCode(HCkSshW cHandle);
void CkSshW_getChannelOpenFailReason(HCkSshW cHandle, HCkStringW retval);
void CkSshW_getClientIdentifier(HCkSshW cHandle, HCkStringW retval);
void CkSshW_putClientIdentifier(HCkSshW cHandle, const wchar_t *newVal);
void CkSshW_getClientIpAddress(HCkSshW cHandle, HCkStringW retval);
void CkSshW_putClientIpAddress(HCkSshW cHandle, const wchar_t *newVal);
int CkSshW_getConnectTimeoutMs(HCkSshW cHandle);
void CkSshW_putConnectTimeoutMs(HCkSshW cHandle, int newVal);
void CkSshW_getDebugLogFilePath(HCkSshW cHandle, HCkStringW retval);
void CkSshW_putDebugLogFilePath(HCkSshW cHandle, const wchar_t *newVal);
int CkSshW_getDisconnectCode(HCkSshW cHandle);
void CkSshW_getDisconnectReason(HCkSshW cHandle, HCkStringW retval);
HCkSshProgressW CkSshW_getEventCallbackObject(HCkSshW cHandle);
void CkSshW_putEventCallbackObject(HCkSshW cHandle, HCkSshProgressW newVal);
void CkSshW_getForceCipher(HCkSshW cHandle, HCkStringW retval);
void CkSshW_putForceCipher(HCkSshW cHandle, const wchar_t *newVal);
int CkSshW_getHeartbeatMs(HCkSshW cHandle);
void CkSshW_putHeartbeatMs(HCkSshW cHandle, int newVal);
void CkSshW_getHostKeyAlg(HCkSshW cHandle, HCkStringW retval);
void CkSshW_putHostKeyAlg(HCkSshW cHandle, const wchar_t *newVal);
void CkSshW_getHostKeyFingerprint(HCkSshW cHandle, HCkStringW retval);
void CkSshW_getHttpProxyAuthMethod(HCkSshW cHandle, HCkStringW retval);
void CkSshW_putHttpProxyAuthMethod(HCkSshW cHandle, const wchar_t *newVal);
void CkSshW_getHttpProxyDomain(HCkSshW cHandle, HCkStringW retval);
void CkSshW_putHttpProxyDomain(HCkSshW cHandle, const wchar_t *newVal);
void CkSshW_getHttpProxyHostname(HCkSshW cHandle, HCkStringW retval);
void CkSshW_putHttpProxyHostname(HCkSshW cHandle, const wchar_t *newVal);
void CkSshW_getHttpProxyPassword(HCkSshW cHandle, HCkStringW retval);
void CkSshW_putHttpProxyPassword(HCkSshW cHandle, const wchar_t *newVal);
int CkSshW_getHttpProxyPort(HCkSshW cHandle);
void CkSshW_putHttpProxyPort(HCkSshW cHandle, int newVal);
void CkSshW_getHttpProxyUsername(HCkSshW cHandle, HCkStringW retval);
void CkSshW_putHttpProxyUsername(HCkSshW cHandle, const wchar_t *newVal);
int CkSshW_getIdleTimeoutMs(HCkSshW cHandle);
void CkSshW_putIdleTimeoutMs(HCkSshW cHandle, int newVal);
BOOL CkSshW_getIsConnected(HCkSshW cHandle);
BOOL CkSshW_getKeepSessionLog(HCkSshW cHandle);
void CkSshW_putKeepSessionLog(HCkSshW cHandle, BOOL newVal);
void CkSshW_getLastErrorHtml(HCkSshW cHandle, HCkStringW retval);
void CkSshW_getLastErrorText(HCkSshW cHandle, HCkStringW retval);
void CkSshW_getLastErrorXml(HCkSshW cHandle, HCkStringW retval);
int CkSshW_getMaxPacketSize(HCkSshW cHandle);
void CkSshW_putMaxPacketSize(HCkSshW cHandle, int newVal);
int CkSshW_getNumOpenChannels(HCkSshW cHandle);
BOOL CkSshW_getPasswordChangeRequested(HCkSshW cHandle);
int CkSshW_getReadTimeoutMs(HCkSshW cHandle);
void CkSshW_putReadTimeoutMs(HCkSshW cHandle, int newVal);
void CkSshW_getSessionLog(HCkSshW cHandle, HCkStringW retval);
int CkSshW_getSoRcvBuf(HCkSshW cHandle);
void CkSshW_putSoRcvBuf(HCkSshW cHandle, int newVal);
int CkSshW_getSoSndBuf(HCkSshW cHandle);
void CkSshW_putSoSndBuf(HCkSshW cHandle, int newVal);
void CkSshW_getSocksHostname(HCkSshW cHandle, HCkStringW retval);
void CkSshW_putSocksHostname(HCkSshW cHandle, const wchar_t *newVal);
void CkSshW_getSocksPassword(HCkSshW cHandle, HCkStringW retval);
void CkSshW_putSocksPassword(HCkSshW cHandle, const wchar_t *newVal);
int CkSshW_getSocksPort(HCkSshW cHandle);
void CkSshW_putSocksPort(HCkSshW cHandle, int newVal);
void CkSshW_getSocksUsername(HCkSshW cHandle, HCkStringW retval);
void CkSshW_putSocksUsername(HCkSshW cHandle, const wchar_t *newVal);
int CkSshW_getSocksVersion(HCkSshW cHandle);
void CkSshW_putSocksVersion(HCkSshW cHandle, int newVal);
BOOL CkSshW_getStderrToStdout(HCkSshW cHandle);
void CkSshW_putStderrToStdout(HCkSshW cHandle, BOOL newVal);
BOOL CkSshW_getTcpNoDelay(HCkSshW cHandle);
void CkSshW_putTcpNoDelay(HCkSshW cHandle, BOOL newVal);
BOOL CkSshW_getVerboseLogging(HCkSshW cHandle);
void CkSshW_putVerboseLogging(HCkSshW cHandle, BOOL newVal);
void CkSshW_getVersion(HCkSshW cHandle, HCkStringW retval);
BOOL CkSshW_AuthenticatePk(HCkSshW cHandle, const wchar_t *username, HCkSshKeyW privateKey);
BOOL CkSshW_AuthenticatePw(HCkSshW cHandle, const wchar_t *login, const wchar_t *password);
BOOL CkSshW_AuthenticatePwPk(HCkSshW cHandle, const wchar_t *username, const wchar_t *password, HCkSshKeyW privateKey);
BOOL CkSshW_ChannelIsOpen(HCkSshW cHandle, int channelNum);
int CkSshW_ChannelPoll(HCkSshW cHandle, int channelNum, int pollTimeoutMs);
int CkSshW_ChannelRead(HCkSshW cHandle, int channelNum);
int CkSshW_ChannelReadAndPoll(HCkSshW cHandle, int channelNum, int pollTimeoutMs);
int CkSshW_ChannelReadAndPoll2(HCkSshW cHandle, int channelNum, int pollTimeoutMs, int maxNumBytes);
BOOL CkSshW_ChannelReceiveToClose(HCkSshW cHandle, int channelNum);
BOOL CkSshW_ChannelReceiveUntilMatch(HCkSshW cHandle, int channelNum, const wchar_t *matchPattern, const wchar_t *charset, BOOL caseSensitive);
BOOL CkSshW_ChannelReceiveUntilMatchN(HCkSshW cHandle, int channelNum, HCkStringArrayW matchPatterns, const wchar_t *charset, BOOL caseSensitive);
BOOL CkSshW_ChannelReceivedClose(HCkSshW cHandle, int channelNum);
BOOL CkSshW_ChannelReceivedEof(HCkSshW cHandle, int channelNum);
BOOL CkSshW_ChannelReceivedExitStatus(HCkSshW cHandle, int channelNum);
BOOL CkSshW_ChannelSendClose(HCkSshW cHandle, int channelNum);
BOOL CkSshW_ChannelSendData(HCkSshW cHandle, int channelNum, HCkByteDataW data);
BOOL CkSshW_ChannelSendEof(HCkSshW cHandle, int channelNum);
BOOL CkSshW_ChannelSendString(HCkSshW cHandle, int channelNum, const wchar_t *strData, const wchar_t *charset);
void CkSshW_ClearTtyModes(HCkSshW cHandle);
BOOL CkSshW_Connect(HCkSshW cHandle, const wchar_t *hostname, int port);
void CkSshW_Disconnect(HCkSshW cHandle);
int CkSshW_GetChannelExitStatus(HCkSshW cHandle, int channelNum);
int CkSshW_GetChannelNumber(HCkSshW cHandle, int index);
BOOL CkSshW_GetChannelType(HCkSshW cHandle, int index, HCkStringW outStr);
BOOL CkSshW_GetReceivedData(HCkSshW cHandle, int channelNum, HCkByteDataW outBytes);
BOOL CkSshW_GetReceivedDataN(HCkSshW cHandle, int channelNum, int numBytes, HCkByteDataW outBytes);
int CkSshW_GetReceivedNumBytes(HCkSshW cHandle, int channelNum);
BOOL CkSshW_GetReceivedStderr(HCkSshW cHandle, int channelNum, HCkByteDataW outBytes);
BOOL CkSshW_GetReceivedText(HCkSshW cHandle, int channelNum, const wchar_t *charset, HCkStringW outStr);
BOOL CkSshW_GetReceivedTextS(HCkSshW cHandle, int channelNum, const wchar_t *substr, const wchar_t *charset, HCkStringW outStr);
int CkSshW_OpenCustomChannel(HCkSshW cHandle, const wchar_t *channelType);
int CkSshW_OpenDirectTcpIpChannel(HCkSshW cHandle, const wchar_t *hostname, int port);
int CkSshW_OpenSessionChannel(HCkSshW cHandle);
BOOL CkSshW_PeekReceivedText(HCkSshW cHandle, int channelNum, const wchar_t *charset, HCkStringW outStr);
BOOL CkSshW_ReKey(HCkSshW cHandle);
BOOL CkSshW_SaveLastError(HCkSshW cHandle, const wchar_t *path);
BOOL CkSshW_SendIgnore(HCkSshW cHandle);
BOOL CkSshW_SendReqExec(HCkSshW cHandle, int channelNum, const wchar_t *command);
BOOL CkSshW_SendReqPty(HCkSshW cHandle, int channelNum, const wchar_t *xTermEnvVar, int widthInChars, int heightInRows, int pixWidth, int pixHeight);
BOOL CkSshW_SendReqSetEnv(HCkSshW cHandle, int channelNum, const wchar_t *name, const wchar_t *value);
BOOL CkSshW_SendReqShell(HCkSshW cHandle, int channelNum);
BOOL CkSshW_SendReqSignal(HCkSshW cHandle, int channelNum, const wchar_t *signalName);
BOOL CkSshW_SendReqSubsystem(HCkSshW cHandle, int channelNum, const wchar_t *subsystemName);
BOOL CkSshW_SendReqWindowChange(HCkSshW cHandle, int channelNum, int widthInChars, int heightInRows, int pixWidth, int pixHeight);
BOOL CkSshW_SendReqX11Forwarding(HCkSshW cHandle, int channelNum, BOOL singleConnection, const wchar_t *authProt, const wchar_t *authCookie, int screenNum);
BOOL CkSshW_SendReqXonXoff(HCkSshW cHandle, int channelNum, BOOL clientCanDo);
BOOL CkSshW_SetTtyMode(HCkSshW cHandle, const wchar_t *name, int value);
BOOL CkSshW_UnlockComponent(HCkSshW cHandle, const wchar_t *unlockCode);
const wchar_t *CkSshW__channelOpenFailReason(HCkSshW cHandle);
const wchar_t *CkSshW__clientIdentifier(HCkSshW cHandle);
const wchar_t *CkSshW__clientIpAddress(HCkSshW cHandle);
const wchar_t *CkSshW__debugLogFilePath(HCkSshW cHandle);
const wchar_t *CkSshW__disconnectReason(HCkSshW cHandle);
const wchar_t *CkSshW__forceCipher(HCkSshW cHandle);
const wchar_t *CkSshW__getChannelType(HCkSshW cHandle, int index);
const wchar_t *CkSshW__getReceivedText(HCkSshW cHandle, int channelNum, const wchar_t *charset);
const wchar_t *CkSshW__getReceivedTextS(HCkSshW cHandle, int channelNum, const wchar_t *substr, const wchar_t *charset);
const wchar_t *CkSshW__hostKeyAlg(HCkSshW cHandle);
const wchar_t *CkSshW__hostKeyFingerprint(HCkSshW cHandle);
const wchar_t *CkSshW__httpProxyAuthMethod(HCkSshW cHandle);
const wchar_t *CkSshW__httpProxyDomain(HCkSshW cHandle);
const wchar_t *CkSshW__httpProxyHostname(HCkSshW cHandle);
const wchar_t *CkSshW__httpProxyPassword(HCkSshW cHandle);
const wchar_t *CkSshW__httpProxyUsername(HCkSshW cHandle);
const wchar_t *CkSshW__lastErrorHtml(HCkSshW cHandle);
const wchar_t *CkSshW__lastErrorText(HCkSshW cHandle);
const wchar_t *CkSshW__lastErrorXml(HCkSshW cHandle);
const wchar_t *CkSshW__peekReceivedText(HCkSshW cHandle, int channelNum, const wchar_t *charset);
const wchar_t *CkSshW__sessionLog(HCkSshW cHandle);
const wchar_t *CkSshW__socksHostname(HCkSshW cHandle);
const wchar_t *CkSshW__socksPassword(HCkSshW cHandle);
const wchar_t *CkSshW__socksUsername(HCkSshW cHandle);
const wchar_t *CkSshW__version(HCkSshW cHandle);
#endif
