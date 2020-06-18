/*****************************************************************
 * CA
 * 2019-06-10
 * IWALL
 * com.i-wall.cn
 *****************************************************************/

#ifndef svkdapi_h
#define svkdapi_h

#include <stdio.h>
#include "svkd_typ.h"
#include <string>
#include <map>

using namespace std;

#define DEVICECONTROL_EXPORTS

#ifdef _WIN32
#ifdef DEVICECONTROL_EXPORTS
#define DEVCTRLDLL __declspec(dllexport)
#else
#define DEVCTRLDLL __declspec(dllimport)
#endif
#else
#define DEVCTRLDLL
#endif

#ifdef __cplusplus
extern "C" {
#endif


/*****************************************************************
 * Function: IW_SDKVersion
 * Description: 获取当前 SDK 版本信息
 * @return 版本号
*****************************************************************/
DEVCTRLDLL const char *IW_SDKVersion();

/*****************************************************************
 * Function: IW_RegisterLicense
 * Description: 注册 License 信息
 * @return 注册结果
*****************************************************************/
DEVCTRLDLL int IW_RegisterLicense(const char *info,
                                  const char *license);

/*****************************************************************
 * Function: IW_InitSDKCA
 * Description: 初始化SDK
 * @param path            [IN] 文件存储路径（密钥文件，证书文件）
 * @param deviceId        [IN] 设备指纹 id
 * @return 操作结果：0 成功
*****************************************************************/
DEVCTRLDLL int IW_InitSDK(const char* path,
                          const char* deviceId);

/*****************************************************************
 * Function: IW_InitCerts
 * Description: 初始化设置证书
 * 如采用 OCSP 校验证书方式，则需导入 OCSP_ROOT_CERT OCSP_SUB_CERT
 * 如采用 CRL  校验证书链， 则需导入CA_ROOT_CERT CA_SUB_CERT
 * @param ocsps   [IN] OCSP 服务器证书
 * @param onum    [IN] OCSP 服务器证书个数
 * @param certs   [IN] CA 证书
 * @param cnum    [IN] CA 证书个数
 * @return 操作结果：0 成功
*****************************************************************/
DEVCTRLDLL int IW_InitCerts(const char *ocsps[], int onum,
                            const char *certs[], int cnum);

/*****************************************************************
 * Function: IW_GenerateKey
 * Description: 生成 Der 编码公钥
 * @param userID         [IN] 用户标识
 * @param pin            [IN] PIN 码
 * @param publicAlgType  [IN] 算法类型
 * @param moduleLen      [IN] 模长
 * @param der            [OUT] 公钥
 * @param derLen         [OUT] 公钥长度
 * @return 操作结果：0 成功
 *****************************************************************/
DEVCTRLDLL int IW_GenerateApplyCerByDER(char* userID, char* pin,
                                        PUBLIC_ALG publicAlgType, int moduleLen,
                                        unsigned char* der, unsigned int* derLen);

/*****************************************************************
 * Function: IW_GenerateApplyCerByCSR
 * Description: 生成 Der 编码公钥
 * @param userID         [IN] 用户标识
 * @param pin            [IN] PIN 码
 * @param publicAlgType  [IN] 算法类型
 * @param moduleLen      [IN] 模长
 * @param subjectInfo    [IN] 证书信息
 * @param csr            [OUT] 公钥
 * @param csrLen         [OUT] 公钥长度
 * @return 操作结果：0 成功
 *****************************************************************/
DEVCTRLDLL int IW_GenerateApplyCerByCSR(char* userID, char* pin,
                                        PUBLIC_ALG publicAlgType, int moduleLen,
                                        SUBJECTINFO* subjectInfo,
                                        unsigned char* csr, unsigned int* csrLen);


/*****************************************************************
 * Function: IW_RequestCertificate
 * Description: 申请证书
 * @param userID         [IN] 用户标识
 * @param urlPath        [IN] 请求路径
 * @param params         [IN] 请求 参数
 * @param resbody        [OUT] 请求结果 json 数据
 * @param success        [OUT] 请求结果 状态值
 * @param result         [OUT] 请求结果 状态字符串
 * @return 操作结果：0 成功
 *****************************************************************/
DEVCTRLDLL int IW_RequestCertificate(string userID,
                                     string urlPath,
                                     map<string, string> params,
                                     string resbody,
                                     int* success,
                                     string& result);

/*****************************************************************
 * Function: IW_RequestP12Certificate
 * Description: 生成 Der 编码公钥
 * @param userID         [IN] 用户标识
 * @param path           [IN] 路径
 * @param params         [IN] 请求 参数
 * @param resbody        [OUT] 请求结果 json 数据
 * @param success        [OUT] 请求结果 状态值
 * @param result         [OUT] 请求结果 状态字符串
 * @return 操作结果：0 成功
 *****************************************************************/
DEVCTRLDLL int IW_RequestP12Certificate(string userID,
                                        string path,
                                        map<string, string> params,
                                        string pin,
                                        string resbody,
                                        int* success,
                                        string& result);

/*****************************************************************
 * Function: IW_ImportCertificate
 * Description: 导入证书并分散
 * @param userID             [IN] 用户标识
 * @param cert               [IN] 证书
 * @param certlen            [IN] 证书长度
 * @return 操作结果：0 成功
 *****************************************************************/
DEVCTRLDLL int IW_ImportCertificate(char* userID, unsigned char* cert, unsigned int certlen);

/*****************************************************************
 * Function: IW_ExportCertificate
 * Description: 导出证书
 * @param userID             [IN]  用户标识
 * @param cert               [OUT] 证书
 * @param certlen            [OUT] 证书长度
 * @return 操作结果：0 成功
 *****************************************************************/
DEVCTRLDLL int IW_ExportCertificate(char* userID, unsigned char* cert, unsigned int* certlen);

/*****************************************************************
 * Function: IW_Sign
 * Description: 签名算法
 * @param userID         [IN]  用户标识
 * @param pin            [IN]  PIN 码
 * @param msg            [IN]  签名原文
 * @param msgLen         [IN]  签名长度
 * @param signature      [OUT] 签名
 * @param signatureLen   [OUT] 签名长度
 * @param signAlgType    [IN]  签名算法类型
 * @return 操作结果：0 成功
 *****************************************************************/
DEVCTRLDLL int IW_Sign(char* userID, char* pin,
                       unsigned char* msg, unsigned int msgLen,
                       unsigned char* signature, unsigned int* signatureLen,
                       SIGN_ALG signAlgType);

/*****************************************************************
 * Function: IW_Verify
 * Description: 验签算法
 * @param msg            [IN]  签名原文
 * @param msgLen         [IN]  签名长度
 * @param signature      [IN]  签名
 * @param signatureLen   [IN]  签名长度
 * @param certificate    [IN]  证书（X509）
 * @param certificateLen [IN]  证书长度
 * @param signAlgType    [IN]  签名 hash 算法
 * @param isPassed       [OUT] 1 成功，0 失败
 * @return 操作结果：0 成功
 *****************************************************************/
DEVCTRLDLL int IW_VerifyByCertificate(unsigned char* msg, unsigned int msgLen,
                                      unsigned char* signature, unsigned int signatureLen,
                                      unsigned char* certificate, unsigned int certificateLen,
                                      SIGN_ALG signAlgType,
                                      int* isPassed);

/*****************************************************************
 * Function: IW_ImportP12Certificate
 * Description: 导入 P12 证书
 * @param cerPath        [IN]  证书路径
 * @param password       [IN]  P12 证书密码
 * @param userID         [IN]  用户标识
 * @param pin            [IN]  PIN 码
 * @return 操作结果：0 成功
 *****************************************************************/
DEVCTRLDLL int IW_ImportP12Certificate(const char* cerPath, const char* password,
                                       char* userID, char* pin);


/*****************************************************************
 * Function: IW_ModifyUserPIN
 * Description: 修改用户PIN码
 * @param userID          [IN]  用户ID
 * @param oldPIN          [IN]  原PIN码
 * @param newPIN          [IN]  新PIN码
 * @return 操作结果：0 成功
 *****************************************************************/
DEVCTRLDLL int IW_ModifyUserPIN(char* userID, char* oldPIN, char* newPIN);

/*****************************************************************
 * Function: IW_UnLockPIN
 * Description: 解锁用户PIN码
 * @param userID          [IN]  容器标识
 * @return 操作结果：0 成功
 *****************************************************************/
DEVCTRLDLL int IW_UnLockPIN(char* userID);

/*****************************************************************
 * Function: IW_Base64_Encode
 * Description: Base64 Encode
 * @param src             [IN]  待编码数据
 * @param slen            [IN]  待编码数据长度
 * @param dst             [OUT] 编码数据
 * @param dlen            [OUT] 编码数据长度
 * @return 操作结果：0 成功
 *****************************************************************/
DEVCTRLDLL int IW_Base64_Encode(const unsigned char* src, unsigned int slen,
                                unsigned char* dst, unsigned int* dlen);

/*****************************************************************
 * Function: IW_BASE64_Decode
 * Description: Base64 Decode
 * @param src             [IN]  待解码
 * @param slen            [IN]  待解密数据长度
 * @param dst             [OUT] 解码数据
 * @param dlen            [OUT] 解码数据长度
 * @return 操作结果：0 成功
 *****************************************************************/
DEVCTRLDLL int IW_Base64_Decode(const unsigned char* src, unsigned int slen,
                                unsigned char* dst, unsigned int* dlen);

/*****************************************************************
 * Function: IW_SM3
 * Description: SM3 摘要算法
 * @param data             [IN]  待摘要数据
 * @param len              [IN]  待摘要数据长度
 * @param digest           [OUT] 摘要数据
 * @param digestLen        [OUT] 摘要数据长度
 * @return 操作结果：0 成功
 *****************************************************************/
DEVCTRLDLL int IW_SM3(const unsigned char* data, unsigned int len,
                      unsigned char* digest, unsigned int* digestLen);

/*****************************************************************
 * Function: IW_CMAC
 * Description: CMAC 摘要算法
 * @param key              [IN]  CMAC key
 * @param keylen           [IN]  密钥长度：16, 24, 32
 * @param src              [IN]  待摘要数据
 * @param slen             [IN]  待摘要数据长度
 * @param digest           [OUT] 摘要数据
 * @param digestLen        [OUT] 摘要数据长度
 * @return 操作结果：0 成功
 *****************************************************************/
DEVCTRLDLL int IW_CMAC(const unsigned char* key,  int keylen,
                       const unsigned char* src,  int slen,
                       unsigned char* digest,  int *digestlen);

/*****************************************************************
 * Function: IW_SymmInit
 * Description: 初始化
 * SM4 默认密钥长度为16字节
 * AES 128, 192, 256 密钥长度分别为： 16字节，24字节，32字节
 * 密钥长度不足时，补0x00
 * @param ctx              [IN]  SYMM CONTEXT
 * @param mode             [IN]  解密模式 SM4_ECB, SM4_CBC, AES_ECB, AES_CBC
 * @param key              [IN]  解密密钥
 * @param keylen           [IN]  密钥长度
 * @param iv               [IN]  偏移量（CBC 模式需传偏移量）
 * @param enc              [IN]  enc:1 , dec: 0
 * @return 操作结果：0 成功
 *****************************************************************/
DEVCTRLDLL int IW_SymmInit(SYMM_CONTEXT* ctx, int mode,
                           const unsigned char* key, unsigned int keylen,
                           const unsigned char* iv, int enc);

/*****************************************************************
 * Function: IW_SymmUpdate
 * Description: Update
 * @param ctx             [IN]  SYMM CONTEXT
 * @param in              [IN]  待加密数据/待解密数据
 * @param inlen           [IN]  待加密数据长度/待解密数据长度
 * @param out             [OUT] 加密/解密后数据
 * @param outlen          [OUT] 加密/解密后数据长度
 * @return 操作结果：0 成功
 *****************************************************************/
DEVCTRLDLL int IW_SymmUpdate(SYMM_CONTEXT* ctx,
                             const unsigned char* in, unsigned int inlen,
                             unsigned char* out, unsigned int* outlen);

/*****************************************************************
 * Function: IW_SymmFinal
 * Description: Finial
 * @param ctx             [IN] SYMM CONTEXT
 * @param in              [IN/OUT] 加密/解密数据
 * @param inlen           [IN/OUT] 加密/解密数据长度
 * @return 操作结果：0 成功
 *****************************************************************/
DEVCTRLDLL int IW_SymmFinal(SYMM_CONTEXT* ctx,
                            unsigned char* in, unsigned int* inlen);

/*****************************************************************
 * Function: IW_SymmCompute
 * Description: 对称加密算法（ECB，CBC，CFB，OFB，CTR）
 * @param mode            [IN] SYMM_ALG 算法类型
 * @param key             [IN] 密钥
 * @param keylen          [IN] 密钥长度
 * @param iv              [IN] 偏移向量
 * @param in              [IN] 待加密/解密数据
 * @param inlen           [IN] 待加密/解密数据长度
 * @param out             [OUT] 密文/明文数据
 * @param outlen          [OUT] 密文/明文数据长度
 * @return 操作结果：0 成功
 *****************************************************************/
DEVCTRLDLL int IW_SymmCompute(SYMM_ALG mode,
                              const unsigned char* key, int keylen,
                              const unsigned char* iv, int enc,
                              const unsigned char* in, int inlen,
                              unsigned char* out, int* outlen);

/*****************************************************************
 * Function: IW_ASymmEncrypt
 * Description: 非对称加密
 * Function: IW_SymmCompute_ex
 * Description: 对称加密算法（ECB，CBC，CFB，OFB，CTR）
 *              AES 算法增加 GCM CCM 模式支持
 * @param mode            [IN] SYMM_ALG 算法类型
 * @param key             [IN] 密钥
 * @param keylen          [IN] 密钥长度
 * @param iv              [IN] iv / nonce
 * @param ivlen           [IN] ivlen / noncelen
 * @param in              [IN] 待加密/解密数据
 * @param inlen           [IN] 待加密/解密数据长度
 * @param tag             [IN/OUT] GCM/CCM tag
 * @param out             [OUT] 密文/明文数据
 * @param outlen          [OUT] 密文/明文数据长度
 * @return 操作结果：0 成功
 *****************************************************************/
DEVCTRLDLL int IW_SymmCompute_ex(SYMM_ALG mode, int enc,
                                 const unsigned char* key, int keylen,
                                 const unsigned char* iv,  int ivlen,
                                 const unsigned char* add, int addlen,
                                 const unsigned char* in,  int inlen,
                                 unsigned char* out, int* outlen);

/*****************************************************************
 * Function: IW_ASymmEncrypt
 * Description: 非对称加密（ECB，CBC，CFB，OFB，CTR，GCM，CCM）
 * @param certificate     [IN]  编码公钥证书 (DER, PEM)
 * @param certificateLen  [IN]  编码公钥证书长度
 * @param msg             [IN]  待加密数据
 * @param msglen          [IN]  待加密数据长度
 * @param cipher          [OUT] 密文数据
 * @param cipherlen       [OUT] 密文数据长度
 * @return 操作结果：0 成功
 *****************************************************************/
DEVCTRLDLL int IW_ASymmEncrypt(const unsigned char* certificate, int certificateLen,
                               const unsigned char* msg, int msglen,
                               unsigned char* cipher, int* cipherlen);

/*****************************************************************
 * Function: IW_ASymmEncrypt
 * Description: 非对称解密
 * SM4 默认密钥长度为16字节
 * AES 128, 192, 256 密钥长度分别为： 16字节，24字节，32字节
 * 密钥长度不足时，补0x00
 * @param userID          [IN]  用户ID
 * @param pin             [IN]  用户PIN
 * @param cipher          [IN]  密文数据
 * @param cipherlen       [IN]  密文数据长度
 * @param plain           [IN]  明文数据
 * @param plainlen        [IN]  明文数据长度
 * @return 操作结果：0 成功
*****************************************************************/
DEVCTRLDLL int IW_ASymmDecrypt(const char* userID,
                               const char* pin,
                               const unsigned char* cipher, int cipherlen,
                               unsigned char* plain, int* plainlen);

/*****************************************************************
 * Function: IW_CertsCheckWithOCSP
 * Description: 通过 OCSP 校验证书
 * @param certs           [IN]  证书值
 * @param cnum            [IN]  证书数量
 * @param status          [OUT] 对应证书状态 0 为正常
 * @return 操作结果：0 成功
*****************************************************************/
DEVCTRLDLL int IW_CertsCheckWithOCSP(const char* certs[], const int cnum,
                                     int status[]);

/*****************************************************************
 * Function: IW_CertsCheckWithCrls
 * Description: 通过 CRL 校验证书
 * @param certs           [IN]  证书值
 * @param cnum            [IN]  证书数量
 * @param crls            [IN]  吊销证书值
 * @param lnum            [IN]  吊销证书数量
 * @param status          [OUT] 对应证书状态 0 为正常
 * @return 操作结果：0 成功
*****************************************************************/
DEVCTRLDLL int IW_CertsCheckWithCrls(const char* certs[], const int cnum,
                                     const char* crls[], const int lnum,
                                     int status[]);

/*****************************************************************
 * Function: IW_GenSymmKey
 * Description: 生成对称密钥
 * @param key             [OUT]  密钥
 * @param keylen          [IN]   密钥长度
 * @return 操作结果：0 成功
*****************************************************************/
DEVCTRLDLL int IW_GenSymmKey(unsigned char* key, unsigned int keylen);

/*****************************************************************
 * Function: IW_RemoveFiles
 * Description: 移除证书文件（移除软盾文件，用户证书，CSR等）
 * @param userID          [IN]   用户ID
 * @return 操作结果：0 成功
*****************************************************************/
DEVCTRLDLL int IW_RemoveFiles(char* userID);

/*****************************************************************
 * Function: IW_WriteFile
 * Description: 安全存储文件（文件长度小于 128 字节）
 * @param fileID          [IN]  文件标识
 * @param buffer          [IN]  待存储数据
 * @param bufferlen       [IN]  待存储数据长度
 * @return 操作结果：0 成功
*****************************************************************/
DEVCTRLDLL int IW_WriteFile(char *fileID, unsigned char *buffer, unsigned int bufferlen);

/*****************************************************************
 * Function: IW_ReadFile
 * Description: 读取文件
 * @param fileID          [IN]  文件标识
 * @param buffer          [OUT] 读取数据
 * @param bufferlen       [OUT] 读取数据长度
 * @return 操作结果：0 成功
*****************************************************************/
DEVCTRLDLL int IW_ReadFile(char *fileID, unsigned char *buffer, unsigned int* bufferlen);

/*****************************************************************
 * Function: IW_DeleteFile
 * Description: 删除文件
 * @param fileID          [IN]  文件标识
 * @return 操作结果：0 成功
*****************************************************************/
DEVCTRLDLL int IW_DeleteFile(char *fileID);

/*****************************************************************
 * Function: IW_DeleteFile
 * Description: 删除文件
 * @param fileID          [IN]  文件标识
 * @param fileLen         [OUT] 文件长度
 * @return 操作结果：0 成功
*****************************************************************/
DEVCTRLDLL int IW_ReadFileLen(char *fileID, unsigned int *fileLen);

/*****************************************************************
 * Function: IW_ECDHETransmitterGenSK
 * Description: ECDHE 发送方生成公钥，计算会话密钥
 * @param publicKey       [IN]  公钥
 * @param publicKeyLen    [IN]  公钥长度
 * @param sharePubKey     [OUT] 分享公钥
 * @param sharePubKeyLen  [OUT] 分享公钥长度
 * @param sKey            [OUT] 会话密钥
 * @param sKeyLen         [OUT] 会话密钥长度
 * @return 操作结果：0 成功
*****************************************************************/
DEVCTRLDLL int IW_ECDHETransmitterGenSK(const unsigned char *certificate, int certificateLen,
                                        unsigned char *sharePubKey, int *sharePubKeyLen,
                                        unsigned char *skey_x, int *xlen,
                                        unsigned char *skey_y, int *ylen);

/*****************************************************************
 * Function: IW_ECDHEReceiverGenSK
 * Description: ECDHE 接收方计算会话密钥
 * @param userID          [IN]  用户 ID
 * @param pin             [IN]  PIN 码
 * @param sharePubKey     [IN]  分享公钥
 * @param sharePubKeyLen  [IN]  分享公钥长度
 * @param sKey            [OUT] 会话密钥
 * @param sKeyLen         [OUT] 会话密钥长度
 * @return 操作结果：0 成功
*****************************************************************/
DEVCTRLDLL int IW_ECDHEReceiverGenSK(const char *userID, char *pin,
                                     unsigned char *sharePubKey, int sharePubKeyLen,
                                     unsigned char *skey_x, int *xlen,
                                     unsigned char *skey_y, int *ylen);

/*****************************************************************
 * Function: IW_UnInitSDK
 * Description: SDK 释放资源
 * @return 操作结果：0 成功
*****************************************************************/
DEVCTRLDLL int IW_UnInitSDK();

#ifdef __cplusplus
}
#endif // __cplusplus
#endif /* svkdapi_h */
