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
/// @param islog 是否显示 LOG，默认不显示
int IW_CA_Log(BOOL islog);

/// 获取设备指纹
NSString *IW_CA_DeviceID();

/// 获取 SDK 版本信息
NSString *IW_CA_SDKVersion();

/// SDK 初始化 License
/// @param license lincense
int IW_CA_RegisterLicense(NSString *license);

/// 初始化 SDK
/// @param path 初始化路径
/// @param deviceID 设备指纹
int IW_CA_InitSDK(NSString *path, NSString *deviceID);

/// 初始化 证书
/// @param ocsps ocsps 证书数组
/// @param certs certs 证书数组
int IW_CA_InitCerts(NSArray *ocsps, NSArray *certs);

/// 生成 CSR 公钥
/// @param userID 用户标识
/// @param pin    用户 PIN
/// @param publicAlgType 算法类型
/// @param moduleLen     模长
NSString *IW_CA_GenerateApplyCerByCSR(NSString *userID, NSString *pin,
                                      PUBLIC_ALG publicAlgType, int moduleLen,
                                      SUBJECTINFO *subjectInfo);

/// 请求证书
/// @param userID  用户标识
/// @param urlPath 请求地址
/// @param params  请求参数
int IW_CA_RequestCertificate(NSString *userID,
                             NSString *urlPath,
                             NSDictionary *params);

/// 导入证书
/// @param userID 用户标识
/// @param cert   用户证书
int IW_CA_ImportCertificate(NSString *userID, NSString *cert);

/// 导出证书
/// @param userID 用户标识
NSString *IW_CA_ExportCertificate(NSString *userID);

/// 签名
/// @param userID 用户标识
/// @param pin    用户 PIN
/// @param msg    待签名原文
/// @param signAlgType 签名算法
NSData *IW_CA_Sign(NSString *userID,
                   NSString *pin,
                   NSData   *msg,
                   SIGN_ALG signAlgType);

/// 验签
/// @param msg         签名原文
/// @param signature   签名长度
/// @param signAlgType 签名算法
int IW_CA_VerifyByCertificate(NSData *msg,
                              NSData *signature,
                              NSString *certificate,
                              SIGN_ALG signAlgType);


/// 导入 P12 证书
/// @param path     证书路径
/// @param password 证书密码
/// @param userID   用户 ID
/// @param pin      用户 PIN 码
int IW_CA_ImportP12Certificate(NSString *path,
                               NSString *password,
                               NSString *userID,
                               NSString *pin);


/// 修改用户 PIN 码
/// @param userID 用户ID
/// @param oldPIN 原 PIN 码
/// @param newPIN 新 PIN 码
int IW_CA_ModifyUserPIN(NSString *userID, NSString *oldPIN, NSString *newPIN);


/// 解锁PIN
/// @param userID 用户ID
int IW_CA_UnLockPIN(NSString *userID);


/// SM3 摘要算法
/// @param src 待摘要数据
NSData *IW_CA_SM3(NSData *src);

/// CMAC 摘要算法
/// @param key 密钥
/// @param src 待摘要数据
NSData *IW_CA_CMAC(NSData *key, NSData *src);

#pragma mark - 对称加密

/// 生成对称密钥
/// @param keylen 对称密钥长度
NSData *IW_CA_GenSymmKey(NSInteger keylen);

/// 对称加密
/// @param mode 对称加密模式（ECB，CBC，CFB，OFB，CTR）
/// @param key  对称密钥
/// @param iv   向量
/// @param enc  加密 / 解密
/// @param src  待加密数据
NSData *IW_CA_SymmCompute(SYMM_ALG mode,
                          NSData *key,
                          NSData *iv,
                          int enc,
                          NSData *src);

/// 对称加密
/// @param mode 对称加密模式（ECB，CBC，CFB，OFB，CTR）
///             AES 算法额外支持 GCM, CCM 模式
/// @param key  对称密钥
/// @param iv   向量
/// @param enc  加密 / 解密
/// @param src  待加密数据
NSData *IW_CA_SymmCompute_Ex(SYMM_ALG mode,
                             NSData *key,
                             NSData *iv,
                             NSData *add,
                             int enc,
                             NSData *src);

#pragma mark - 非对称加密
/// 非对称加密
/// @param certificate 公钥证书
/// @param plain       待加密数据
NSData *IW_CA_ASymmEncrypt(NSString *certificate,
                           NSData *plain);

/// 非对称解密
/// @param userID  用户 ID
/// @param pin     用户 PIN 码
/// @param cipher  待解密数据
NSData *IW_CA_ASymmDecrypt(NSString *userID,
                           NSString *pin,
                           NSData *cipher);

#pragma mark - 证书校验

/// OCSP 证书校验
/// @param certs  待校验证书
/// @param status 证书状态
int IW_CA_CertsCheckWithOCSP(NSArray *certs, NSMutableArray *status);


/// CRL 证书校验
/// @param certs 待校验证书
/// @param crls  待校验 CRL
/// @param status 证书状态
int IW_CA_CertsCheckWithCRLS(NSArray *certs, NSArray *crls, NSMutableArray *status);


/// 移除证书，软盾文件
/// @param userID 用户 ID
int IW_CA_RemoveFiles(NSString *userID);


/// 安全存储文件
/// @param fileID 文件 ID
/// @param data   待存储数据
int IW_CA_WriteFile(NSString *fileID, NSData *data);


/// 读取安全存储文件
/// @param fileID 文件 ID
NSData *IW_CA_ReadFile(NSString *fileID);


/// 删除安全存储文件
/// @param fileID 文件ID
int IW_CA_DeleteFile(NSString * fileID);


/// ECDHE 算法
/// @param certificate 公钥证书
/// @param sharePubKey 公钥
/// @param secret_x sec x
/// @param secret_y sec y
int IW_CA_ECDHETransmitterGenSK(NSString *certificate,
                                NSData *_Nullable *_Nullable sharePubKey,
                                NSData *_Nullable *_Nullable secret_x,
                                NSData *_Nullable *_Nullable secret_y);

/// ECDHE 算法
/// @param userID 用户标识
/// @param pin    PIN 码
/// @param sharePubKey 公钥
/// @param secret_x  sec x
/// @param secret_y  sec y
int IW_CA_ECDHEReceiverGenSK(NSString *userID,
                             NSString *pin,
                             NSData   *sharePubKey,
                             NSData   *_Nullable *_Nullable secret_x,
                             NSData   *_Nullable *_Nullable secret_y);
@end

NS_ASSUME_NONNULL_END
