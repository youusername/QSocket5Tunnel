﻿/**
  Based on http://saju.net.in/code/misc/openssl_aes.c.txt example

  public domain

  Author Ruslan Salikhov <ruslansalihov /at/ gmail.com>
**/

#ifndef OpensslAES_H
#define OpensslAES_H

#include <QByteArray>
#include <openssl/evp.h>

class OpensslAES
{
public:

    enum Mode
    {
        ModeCbc = 0,
        ModeCfb = 1, // CFB128
        ModeEcb = 2,
        ModeOfb = 3
    };

    enum Type
    {
        TypeAes128 = 0,
        TypeAes192 = 1,
        TypeAes256 = 2
    };

    OpensslAES(const QByteArray &secretKey = "dushibaiyu",
                  const QByteArray &salt = "www.dushibaiyu.com",
                  Type m_type = TypeAes256,
                  Mode m_mode = ModeCbc );
    ~OpensslAES();

    QByteArray encrypt(const QByteArray &plainData);

    QByteArray decrypt(const QByteArray &cipherData);

    bool isValid() const;

    Type type() const;

    Mode mode() const;

    int blockSize() const;

private:
    bool init(const QByteArray &keyData,
              const QByteArray &saltData);

    const EVP_CIPHER *getEvpCipher() const;

    int calcBlockSize() const;

    bool m_isValid;

    Type m_type;
    Mode m_mode;

    int m_blockSize;

    /* "opaque" encryption, decryption ctx structures that libcrypto uses to record
     * status of enc/dec operations */
    EVP_CIPHER_CTX *m_encoder;
    EVP_CIPHER_CTX *m_decoder;
};

#endif // OpensslAES_H
