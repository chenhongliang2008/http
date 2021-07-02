class KMD5
{
public:
	/* Data structure for MD5 (Message Digest) computation */
	typedef struct {
		unsigned int i[2];                   /* Number of _bits_ handled mod 2^64 */
		unsigned int buf[4];                                    /* Scratch buffer */
		unsigned char in[64];                              /* Input buffer */
		unsigned char digest[16];     /* Actual digest after MD5Final call */
	} MD5_CTX;

	void MD5_Transform(unsigned int *buf, unsigned int *in);

	void MD5Init(MD5_CTX *mdContext, unsigned long pseudoRandomNumber = 0);
	void MD5Update(MD5_CTX *mdContext, unsigned char *inBuf, unsigned int inLen);
	void MD5Final(MD5_CTX *mdContext);

	//	���㻺�������ݵ�MD5ֵ, ����16λhw_int8Sֵ
	int MD5Hash(unsigned char * buffer, int bufferLen, unsigned char md5Value[16]);
	int MD5HashFile(const char * path, unsigned char md5Value[16]);

	//	��hw_int8[16] ת����16����32λ�ַ���
	int Byte16ToChar32(unsigned char bytes[16], char str[33]);
	int Byte16ToChar16(unsigned char bytes[16], char str[17]);

private:
	int				m_nPrgCount;
	bool			m_bFinal;
};
