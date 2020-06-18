//
//  svkd_typ.h
//  BaiduSDK
//
//  Created by iwall on 2019/8/1.
//  Copyright © 2019 kong. All rights reserved.
//

#ifndef svkd_typ_h
#define svkd_typ_h

// 用户信息
typedef struct STRUCT_PERSONINFO {
    char userName[26];            // Y 用户姓名
    char credentialType[2];       // Y 证件类型 1：居民身份证， 2：其他
    char credentialNum[26];       // Y 证件号码
    char phone[12];               // Y 联系电话
    char email[51];               // N 邮箱
    char address[51];             // N 联系地址
} PERSONINFO;

// 企业信息
typedef struct STRUCT_ENTERPRISEINFO {
    char companyName[51];         // Y 企业名称
    char organizationCode[26];    // Y 组织机构代码
    char taxationNum[26];         // Y 企业税号
    char connectName[26];         // N 联系人
    char connectPhone[12];        // N 联系电话
    char connectEmail[51];        // N 邮箱
    char connectAddress[51];      // N 联系地址
} ENTERPRISEINFO;

// 服务器信息
typedef struct STRUCT_SERVERINFO {
    char domainName[101];         // Y 域名
    char companyName[51];         // Y 服务器名称
    char connectName[26];         // N 联系人
    char connectPhone[12];        // N 联系电话
    char connectEmail[51];        // N 邮箱
    char connectAddress[51];      // N 联系地址
} SERVERINFO;

// 设备信息
typedef struct STRUCT_DEVICEINFO {
    char deviceID[65];            // Y 设备ID
    char manufacturer[26];        // Y 设备制作商
    char deviceVersion[33];       // Y 版本号
    char hwVersion[17];           // Y 设备硬件版本
    char firmwareVersion[65];     // Y 设备固件版本
} DEVICEINFO;

typedef struct STRUCT_USERINFO {
    int userType;                       // Y 用户类型 1-个人用户; 2-企业用户; 3-服务器用户; 4-设备用户;
    union {
        PERSONINFO personInfo;          // 个人用户
        ENTERPRISEINFO enterPersonInfo; // 企业用户
        SERVERINFO serverInfo;          // 服务器用户
        DEVICEINFO deviceInfo;          // 设备用户
    } type;
} USERINFO;

// 证书主体项
typedef struct STRUCT_SUBJECTINFO {
    char country[32];             // Y 国家
    char stateOrProvince[32];     // N 省份
    char locality[32];            // N 地市
    char organization[64];        // N 组织
    char organizationUnit[64];    // N 机构
    char commonName[128];         // Y 用户名称
    char dc1[128];                // N DomainComponent_1
    char dc2[128];                // N DomainComponent_2
    char dc3[128];                // N DomainComponent_3
    char uid[128];                // N userids
} SUBJECTINFO;

typedef enum ENUM_SYMM_ALG {
    SYMM_ALG_SM4_ECB = 0x00000401,
    SYMM_ALG_SM4_CBC,
    SYMM_ALG_SM4_CFB,
    SYMM_ALG_SM4_OFB,
    SYMM_ALG_SM4_CTR,
    SYMM_ALG_AES_ECB = 0x00001401,
    SYMM_ALG_AES_CBC,
    SYMM_ALG_AES_CFB,
    SYMM_ALG_AES_OFB,
    SYMM_ALG_AES_CTR,
    SYMM_ALG_AES_GCM,
    SYMM_ALG_AES_CCM
} SYMM_ALG;

// 算法
typedef enum ENUM_PUBLICKEY_ALG {
    PUBLICKEY_ALG_SM2 = 0,
    PUBLICKEY_ALG_RSA,
    PUBLICKEY_ALG_ECC_P192V1,
    PUBLICKEY_ALG_ECC_P224R1,
    PUBLICKEY_ALG_ECC_P256V1,
    PUBLICKEY_ALG_ECC_P384R1,
    PUBLICKEY_ALG_ECC_P521R1,
} PUBLIC_ALG;

// 签名算法
typedef enum ENUM_SIGN_ALG {
    SIGN_SHA1withRSA,
    SIGN_SHA256withRSA,
    SIGN_SM3withSM2,
    SIGN_SHA1withECDSA,
    SIGN_SHA256withECDSA
} SIGN_ALG;

// 加解密算法
typedef struct STRUCT_SYMMCONTXT {
    void *ctx;
    unsigned char iv[16];
    unsigned char key[32];
    int operationMode;//ECB|CBC
} SYMM_CONTEXT, *PSYMMCONTEXT;

#define SM4_ECB        0x00000401
#define SM4_CBC        0x00000402
#define AES_ECB        0x00001401
#define AES_CBC        0x00001402

#endif /* svkd_typ_h */
