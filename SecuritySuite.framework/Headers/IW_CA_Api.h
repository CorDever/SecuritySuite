//
//  GL_CA_Api.h
//  BDCA_iOS
//
//  Created by kong on 2020/5/11.
//  Copyright © 2020 kong. All rights reserved.
//

#import <Foundation/Foundation.h>
#include "svkd_typ.h"

NS_ASSUME_NONNULL_BEGIN

@interface IW_CA_Api : NSObject


/// 显示 LOG
/// @param islog [IN] 是否显示 LOG，默认不显示
int IW_CA_Log(BOOL islog);

/// 获取设备指纹
/// @return 设备指纹信息
NSString *IW_CA_DeviceID();

/// 获取 SDK 版本信息
/// @return 版本信息
NSString *IW_CA_SDKVersion();

/// SDK 初始化 License
/// @param license [IN] lincense
/// @return 0 success, other error no.
int IW_CA_RegisterLicense(NSString *license);

/// 初始化 SDK
/// @param path          [IN] 初始化路径
/// @param deviceID      [IN] 设备指纹
/// @return 0 success, other error no.
int IW_CA_InitSDK(NSString *path, NSString *deviceID);

/// 初始化 证书
/// @param ocsps         [IN] OCSP 证书数组
/// @param certs         [IN] CA 证书数组
/// @return 0 success, other error no.
int IW_CA_InitCerts(NSArray *ocsps, NSArray *certs);

/// 生成 CSR 公钥
/// @param userID        [IN] 用户标识
/// @param pin           [IN] 用户 PIN
/// @param publicAlgType [IN] 算法类型
/// @param moduleLen     [IN] 模长
/// @param subjectInfo   [IN] SUBJECTINFO 信息
/// @param csr           [OUT] CSR Data
/// @return 0 success, other error no.
int IW_CA_GenerateApplyCerByCSR(NSString *userID,
                                NSString *pin,
                                PUBLIC_ALG publicAlgType,
                                int moduleLen,
                                SUBJECTINFO *subjectInfo,
                                NSData *_Nonnull *_Nonnull csr);

/// 请求证书
/// @param userID        [IN] 用户标识
/// @param urlPath       [IN] 请求地址
/// @param params        [IN] 请求参数
/// @return 0 success, other error no.
int IW_CA_RequestCertificate(NSString *userID,
                             NSString *urlPath,
                             NSDictionary *params);

/// 导入证书
/// @param userID        [IN] 用户标识
/// @param cert          [IN] 用户证书
/// @return 0 success, other error no.
int IW_CA_ImportCertificate(NSString *userID, NSData *cert);

/// 导出证书
/// @param userID        [IN] 用户标识
/// @param cert          [OUT] 证书信息
/// @return 公钥证书
int IW_CA_ExportCertificate(NSString *userID,
                            NSData *_Nonnull *_Nonnull cert);

/// 签名
/// @param userID        [IN] 用户标识
/// @param pin           [IN] 用户 PIN
/// @param msg           [IN] 待签名原文
/// @param signAlgType   [IN] 签名算法
/// @param sign          [OUT] 签名值
/// @return 签名数据
int IW_CA_Sign(NSString *userID,
               NSString *pin,
               NSData   *msg,
               SIGN_ALG signAlgType,
               NSData *_Nonnull *_Nonnull sign);

/// 验签
/// @param msg           [IN] 签名原文
/// @param signature     [IN] 签名
/// @param certificate   [IN] 公钥证书
/// @param signAlgType   [IN] 签名算法
/// @param isPass        [OUT] if 1 verify success, 0 verify fail
/// @return 0 success, other error no.
int IW_CA_VerifyByCertificate(NSData *msg,
                              NSData *signature,
                              NSData *certificate,
                              SIGN_ALG signAlgType,
                              int *isPass);

/// 导入 P12 证书
/// @param path          [IN] 证书路径
/// @param password      [IN] 证书密码
/// @param userID        [IN] 用户ID
/// @param pin           [IN] 用户PIN码
/// @return 0 success, other error no.
int IW_CA_ImportP12Certificate(NSString *path,
                               NSString *password,
                               NSString *userID,
                               NSString *pin);

/// 修改用户 PIN 码
/// @param userID        [IN] 用户ID
/// @param oldPIN        [IN] 原 PIN 码
/// @param newPIN        [IN] 新 PIN 码
/// @return 0 success, other error no.
int IW_CA_ModifyUserPIN(NSString *userID, NSString *oldPIN, NSString *newPIN);


/// 解锁PIN
/// @param userID        [IN] 用户ID
/// @return 0 success, other error no.
int IW_CA_UnLockPIN(NSString *userID);


/// SM3 摘要算法
/// @param src           [IN] 待摘要数据
/// @return SM3 摘要数据
NSData *IW_CA_SM3(NSData *src);

/// CMAC 摘要算法
/// @param key           [IN] 密钥
/// @param src           [IN] 待摘要数据
/// @return CMAC 摘要数据
NSData *IW_CA_CMAC(NSData *key, NSData *src);

#pragma mark - 对称加密

/// 生成对称密钥
/// @param keylen        [IN] 对称密钥长度
/// @return 对称密钥数据
NSData *IW_CA_GenSymmKey(NSInteger keylen);

/// 对称加密
/// @param mode          [IN] 对称加密模式（ECB，CBC，CFB，OFB，CTR）
/// @param key           [IN] 对称密钥
/// @param iv            [IN] 向量
/// @param enc           [IN] 加密/解密
/// @param src           [IN] 待加密数据
/// @param cipher        [OUT] 密文数据
/// @return 0 success, other error no.
int IW_CA_SymmCompute(SYMM_ALG mode,
                      NSData *key,
                      NSData *iv,
                      int enc,
                      NSData *src,
                      NSData *_Nonnull *_Nonnull cipher);

/// 对称加密
/// @param mode          [IN] 对称加密模式（ECB，CBC，CFB，OFB，CTR）
///                           AES 算法额外支持 GCM, CCM 模式
/// @param key           [IN] 对称密钥
/// @param iv            [IN] 向量
/// @param add           [IN] 附加值
/// @param enc           [IN] 加密/解密
/// @param src           [IN] 待加密数据
/// @param cipher        [OUT] 密文数据
/// @return 0 success, other error no.
int IW_CA_SymmCompute_Ex(SYMM_ALG mode,
                         NSData *key,
                         NSData *iv,
                         NSData *add,
                         int enc,
                         NSData *src,
                         NSData *_Nonnull *_Nonnull cipher);

#pragma mark - 非对称加密
/// 非对称加密
/// @param certificate   [IN] 公钥证书
/// @param plain         [IN] 待加密数据
/// @param cipher        [OUT] 密文数据
/// @return 0 success, other error no.
int IW_CA_ASymmEncrypt(NSData *certificate,
                       NSData *plain,
                       NSData *_Nonnull *_Nonnull cipher);

/// 非对称解密
/// @param userID        [IN] 用户 ID
/// @param pin           [IN] 用户 PIN 码
/// @param cipher        [IN] 待解密数据
/// @param plain         [OUT] 解密数据
/// @return 0 success, other error no.
int IW_CA_ASymmDecrypt(NSString *userID,
                       NSString *pin,
                       NSData *cipher,
                       NSData *_Nonnull *_Nonnull plain);

#pragma mark - 证书校验

/// OCSP 证书校验
/// @param certs         [IN] 待校验证书
/// @param status        [IN/OUT] 证书状态
/// @return 0 success, other error no.
int IW_CA_CertsCheckWithOCSP(NSArray *certs,
                             NSMutableArray *status);


/// CRL 证书校验
/// @param certs         [IN] 待校验证书
/// @param crls          [IN] 待校验 CRL
/// @param status        [IN/OUT] 证书状态
/// @return 0 success, other error no.
int IW_CA_CertsCheckWithCRLS(NSArray *certs,
                             NSArray *crls,
                             NSMutableArray *status);


/// 移除证书，软盾文件
/// @param userID        [IN] 用户 ID
/// @return 0 success, other error no.
int IW_CA_RemoveFiles(NSString *userID);


/// 安全存储文件
/// @param fileID        [IN] 文件 ID
/// @param data          [IN] 待存储数据
/// @return 0 success, other error no.
int IW_CA_WriteFile(NSString *fileID,
                    NSData *data);


/// 读取安全存储文件
/// @param fileID        [IN] 文件 ID
/// @param data          [OUT] 读取数据
/// @return 0 success, other error no.
int IW_CA_ReadFile(NSString *fileID,
                   NSData *_Nonnull *_Nonnull data);

/// 删除安全存储文件
/// @param fileID        [IN] 文件ID
/// @return 0 success, other error no.
int IW_CA_DeleteFile(NSString * fileID);


/// 生成临时公私钥对接口
/// @param type          [IN] 公钥数据类型
/// @param pKey          [OUT] DER 编码公钥
/// @return 0 success, other error no.
int IW_CA_GenerateECCTemporaryKeyPair(PUBLIC_ALG type,
                                      NSData *_Nonnull *_Nonnull pKey);

/// 销毁临时公私钥对接口
int IW_CA_DestroyTempEccKeyPair();

/// ECDHE 算法
/// @param pubKey        [IN] 公钥
/// @param secret_x      [OUT] secret x
/// @param secret_y      [OUT] secret y
/// @return 0 success, other error no.
int IW_CA_ECDHEReceiverGenSK(NSData *pubKey,
                             NSData *_Nonnull *_Nonnull secret_x,
                             NSData *_Nonnull *_Nonnull secret_y);
@end

NS_ASSUME_NONNULL_END
