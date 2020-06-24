# 修改日志

[20200624]
- version:1.3.4
- OC 层接口，指针的指针均以 `_Nonnull` 修饰。
- 更新接口注释文字说明。
- 修改 IW_CA_GenerateApplyCerByCSR OC 层调用接口，csr  以指针的指针形式返回，接口返回状态码。
- 修改 IW_CA_ExportCertificate     OC 层调用接口，cert 以指针的指针形式返回，接口返回状态码。
- 修改 IW_CA_Sign                  OC 层调用接口，sign 以指针的指针形式返回，接口返回状态码。
- 修改 IW_CA_VerifyByCertificate   OC 层调用接口，isPass 验签结果以指针形式返回，接口返回状态码。
- 修改 IW_CA_SymmCompute           OC 层调用接口，结果数据以指针的指针形式返回，接口返回状态码。
- 修改 IW_CA_SymmCompute_Ex        OC 层调用接口，结果数据以指针的指针形式返回，接口返回状态码。
- 修改 IW_CA_ASymmEncrypt          OC 层调用接口，结果数据以指针的指针形式返回，接口返回状态码。
- 修改 IW_CA_ASymmDecrypt          OC 层调用接口，结果数据以指针的指针形式返回，接口返回状态码。
- 修改 IW_CA_ReadFile              OC 层调用接口，结果数据以指针的指针形式返回，接口返回状态码。
- 增加 IW_CA_GenerateECCTemporaryKeyPair 生成临时密钥对接口，接口返回状态码。
- 修改 IW_CA_ECDHEReceiverGenSK    接口，接口返回状态码。
- 增加 IW_CA_DestroyTempEccKeyPair 临时密钥对销毁接口，接口返回状态码。
