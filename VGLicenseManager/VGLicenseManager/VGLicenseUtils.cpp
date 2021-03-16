#pragma execution_character_set("utf-8")
#include <QtCore/QFile>
#include <QtCore/QTextStream>

#include "QtCore\QString"
#include "QCryptographicHash"
#include "QtCore\QByteArray"
#include "QtCore\QProcess"
#include "QDateTime"
#include "QJsonDocument"
#include "QtCore\QStringList"
//
#include "QJsonObject"

#include "VGLicenseManager/VGLicenseManager.h"

#include "vglicensefaileddialog.h"
#include "QtWidgets/QApplication"

#include "QtCore\QString"
#include "QtCore\QByteArray"
#include "QDateTime"
#include "VGLicenseUtils.h"
#include "QMessageBox"

using namespace VGLicenseManager;

namespace VGLicenseUtils
{
	static void getcpuid(unsigned int CPUInfo[4], unsigned int InfoType)
	{
#if defined(__GNUC__)// GCC
		__cpuid(InfoType, CPUInfo[0], CPUInfo[1], CPUInfo[2], CPUInfo[3]);
#elif defined(_MSC_VER)// MSVC
#if _MSC_VER >= 1400 //VC2005才支持__cpuid
		__cpuid((int*)(void*)CPUInfo, (int)(InfoType));
#else //其他使用getcpuidex
		getcpuidex(CPUInfo, InfoType, 0);
#endif
#endif
	}

	static QString getWMIC(const QString& cmd)
	{
		//获取cpu名称：wmic cpu get Name
		//获取cpu核心数：wmic cpu get NumberOfCores
		//获取cpu线程数：wmic cpu get NumberOfLogicalProcessors
		//查询cpu序列号：wmic cpu get processorid
		//查询主板序列号：wmic baseboard get serialnumber
		//查询BIOS序列号：wmic bios get serialnumber
		//查看硬盘：wmic diskdrive get serialnumber
		QProcess p;
		p.start(cmd);
		p.waitForFinished();

		QString result = QString::fromLocal8Bit(p.readAllStandardOutput());
		QStringList list = cmd.split(" ");
		result = result.remove(list.last(), Qt::CaseInsensitive);
		result = result.replace("\r", "");
		result = result.replace("\n", "");
		result = result.simplified();
		return result;
	}

	static QString getDiskNum()
	{
		return getWMIC("wmic diskdrive where index=0 get serialnumber");
	}

	static QString get_cpuId()
	{
		QString cpu_id = "";
		unsigned int dwBuf[4] = { 0 };
		unsigned long long ret = 0;
		getcpuid(dwBuf, 1);
		ret = dwBuf[3];
		ret = ret << 32;

		QString str0 = QString::number(dwBuf[3], 16).toUpper();
		QString str0_1 = str0.rightJustified(8, '0');//这一句的意思是前面补0，但是我遇到的情况是这里都填满了
		QString str1 = QString::number(dwBuf[0], 16).toUpper();
		QString str1_1 = str1.rightJustified(8, '0');//这里必须在前面补0，否则不会填满数据
													 //cpu_id = cpu_id + QString::number(dwBuf[0], 16).toUpper();
		cpu_id = str0_1 + str1_1;
		return cpu_id;
	}


	QStringList getMachineCode()
	{
		QStringList codeList;

		auto cpuID = get_cpuId();
		auto hello = QString(cpuID + getDiskNum());

		codeList.push_back(QCryptographicHash::hash(hello.toLocal8Bit().toBase64(), QCryptographicHash::Sha3_512).toHex());

		/*for (auto& i : QNetworkInterface::allInterfaces()) {
		codeList << QString(cpuID + i.hardwareAddress()).toLocal8Bit().toHex(':').toBase64();
		}*/

		return codeList;
	}

	static const uint16_t crc16tab[256] = {
		0x0000,0x1021,0x2042,0x3063,0x4084,0x50a5,0x60c6,0x70e7,
		0x8108,0x9129,0xa14a,0xb16b,0xc18c,0xd1ad,0xe1ce,0xf1ef,
		0x1231,0x0210,0x3273,0x2252,0x52b5,0x4294,0x72f7,0x62d6,
		0x9339,0x8318,0xb37b,0xa35a,0xd3bd,0xc39c,0xf3ff,0xe3de,
		0x2462,0x3443,0x0420,0x1401,0x64e6,0x74c7,0x44a4,0x5485,
		0xa56a,0xb54b,0x8528,0x9509,0xe5ee,0xf5cf,0xc5ac,0xd58d,
		0x3653,0x2672,0x1611,0x0630,0x76d7,0x66f6,0x5695,0x46b4,
		0xb75b,0xa77a,0x9719,0x8738,0xf7df,0xe7fe,0xd79d,0xc7bc,
		0x48c4,0x58e5,0x6886,0x78a7,0x0840,0x1861,0x2802,0x3823,
		0xc9cc,0xd9ed,0xe98e,0xf9af,0x8948,0x9969,0xa90a,0xb92b,
		0x5af5,0x4ad4,0x7ab7,0x6a96,0x1a71,0x0a50,0x3a33,0x2a12,
		0xdbfd,0xcbdc,0xfbbf,0xeb9e,0x9b79,0x8b58,0xbb3b,0xab1a,
		0x6ca6,0x7c87,0x4ce4,0x5cc5,0x2c22,0x3c03,0x0c60,0x1c41,
		0xedae,0xfd8f,0xcdec,0xddcd,0xad2a,0xbd0b,0x8d68,0x9d49,
		0x7e97,0x6eb6,0x5ed5,0x4ef4,0x3e13,0x2e32,0x1e51,0x0e70,
		0xff9f,0xefbe,0xdfdd,0xcffc,0xbf1b,0xaf3a,0x9f59,0x8f78,
		0x9188,0x81a9,0xb1ca,0xa1eb,0xd10c,0xc12d,0xf14e,0xe16f,
		0x1080,0x00a1,0x30c2,0x20e3,0x5004,0x4025,0x7046,0x6067,
		0x83b9,0x9398,0xa3fb,0xb3da,0xc33d,0xd31c,0xe37f,0xf35e,
		0x02b1,0x1290,0x22f3,0x32d2,0x4235,0x5214,0x6277,0x7256,
		0xb5ea,0xa5cb,0x95a8,0x8589,0xf56e,0xe54f,0xd52c,0xc50d,
		0x34e2,0x24c3,0x14a0,0x0481,0x7466,0x6447,0x5424,0x4405,
		0xa7db,0xb7fa,0x8799,0x97b8,0xe75f,0xf77e,0xc71d,0xd73c,
		0x26d3,0x36f2,0x0691,0x16b0,0x6657,0x7676,0x4615,0x5634,
		0xd94c,0xc96d,0xf90e,0xe92f,0x99c8,0x89e9,0xb98a,0xa9ab,
		0x5844,0x4865,0x7806,0x6827,0x18c0,0x08e1,0x3882,0x28a3,
		0xcb7d,0xdb5c,0xeb3f,0xfb1e,0x8bf9,0x9bd8,0xabbb,0xbb9a,
		0x4a75,0x5a54,0x6a37,0x7a16,0x0af1,0x1ad0,0x2ab3,0x3a92,
		0xfd2e,0xed0f,0xdd6c,0xcd4d,0xbdaa,0xad8b,0x9de8,0x8dc9,
		0x7c26,0x6c07,0x5c64,0x4c45,0x3ca2,0x2c83,0x1ce0,0x0cc1,
		0xef1f,0xff3e,0xcf5d,0xdf7c,0xaf9b,0xbfba,0x8fd9,0x9ff8,
		0x6e17,0x7e36,0x4e55,0x5e74,0x2e93,0x3eb2,0x0ed1,0x1ef0
	};

	uint16_t crc16old(const char *buf, int len) {
		int counter;
		uint16_t crc = 0;
		for (counter = 0; counter < len; counter++)
			crc = (crc << 8) ^ crc16tab[((crc >> 8) ^ *buf++) & 0x00FF];
		return crc;
	}

	uint16_t crc16(const char* buffer, int len)
	{
		const uint16_t crctab16[] = {
			0X0000, 0X1189, 0X2312, 0X329B, 0X4624, 0X57AD, 0X6536, 0X74BF,
				0X8C48, 0X9DC1, 0XAF5A, 0XBED3, 0XCA6C, 0XDBE5, 0XE97E, 0XF8F7,
				0X1081, 0X0108, 0X3393, 0X221A, 0X56A5, 0X472C, 0X75B7, 0X643E,
				0X9CC9, 0X8D40, 0XBFDB, 0XAE52, 0XDAED, 0XCB64, 0XF9FF, 0XE876,
				0X2102, 0X308B, 0X0210, 0X1399, 0X6726, 0X76AF, 0X4434, 0X55BD,
				0XAD4A, 0XBCC3, 0X8E58, 0X9FD1, 0XEB6E, 0XFAE7, 0XC87C, 0XD9F5,
				0X3183, 0X200A, 0X1291, 0X0318, 0X77A7, 0X662E, 0X54B5, 0X453C,
				0XBDCB, 0XAC42, 0X9ED9, 0X8F50, 0XFBEF, 0XEA66, 0XD8FD, 0XC974,
				0X4204, 0X538D, 0X6116, 0X709F, 0X0420, 0X15A9, 0X2732, 0X36BB,
				0XCE4C, 0XDFC5, 0XED5E, 0XFCD7, 0X8868, 0X99E1, 0XAB7A, 0XBAF3,
				0X5285, 0X430C, 0X7197, 0X601E, 0X14A1, 0X0528, 0X37B3, 0X263A,
				0XDECD, 0XCF44, 0XFDDF, 0XEC56, 0X98E9, 0X8960, 0XBBFB, 0XAA72,
				0X6306, 0X728F, 0X4014, 0X519D, 0X2522, 0X34AB, 0X0630, 0X17B9,
				0XEF4E, 0XFEC7, 0XCC5C, 0XDDD5, 0XA96A, 0XB8E3, 0X8A78, 0X9BF1,
				0X7387, 0X620E, 0X5095, 0X411C, 0X35A3, 0X242A, 0X16B1, 0X0738,
				0XFFCF, 0XEE46, 0XDCDD, 0XCD54, 0XB9EB, 0XA862, 0X9AF9, 0X8B70,
				0X8408, 0X9581, 0XA71A, 0XB693, 0XC22C, 0XD3A5, 0XE13E, 0XF0B7,
				0X0840, 0X19C9, 0X2B52, 0X3ADB, 0X4E64, 0X5FED, 0X6D76, 0X7CFF,
				0X9489, 0X8500, 0XB79B, 0XA612, 0XD2AD, 0XC324, 0XF1BF, 0XE036,
				0X18C1, 0X0948, 0X3BD3, 0X2A5A, 0X5EE5, 0X4F6C, 0X7DF7, 0X6C7E,
				0XA50A, 0XB483, 0X8618, 0X9791, 0XE32E, 0XF2A7, 0XC03C, 0XD1B5,
				0X2942, 0X38CB, 0X0A50, 0X1BD9, 0X6F66, 0X7EEF, 0X4C74, 0X5DFD,
				0XB58B, 0XA402, 0X9699, 0X8710, 0XF3AF, 0XE226, 0XD0BD, 0XC134,
				0X39C3, 0X284A, 0X1AD1, 0X0B58, 0X7FE7, 0X6E6E, 0X5CF5, 0X4D7C,
				0XC60C, 0XD785, 0XE51E, 0XF497, 0X8028, 0X91A1, 0XA33A, 0XB2B3,
				0X4A44, 0X5BCD, 0X6956, 0X78DF, 0X0C60, 0X1DE9, 0X2F72, 0X3EFB,
				0XD68D, 0XC704, 0XF59F, 0XE416, 0X90A9, 0X8120, 0XB3BB, 0XA232,
				0X5AC5, 0X4B4C, 0X79D7, 0X685E, 0X1CE1, 0X0D68, 0X3FF3, 0X2E7A,
				0XE70E, 0XF687, 0XC41C, 0XD595, 0XA12A, 0XB0A3, 0X8238, 0X93B1,
				0X6B46, 0X7ACF, 0X4854, 0X59DD, 0X2D62, 0X3CEB, 0X0E70, 0X1FF9,
				0XF78F, 0XE606, 0XD49D, 0XC514, 0XB1AB, 0XA022, 0X92B9, 0X8330,
				0X7BC7, 0X6A4E, 0X58D5, 0X495C, 0X3DE3, 0X2C6A, 0X1EF1, 0X0F78,
		};

		auto res = 0x0ffff;

		uint16_t crc = 0;
		for (auto counter = 0; counter < len; counter++)
		{
			auto b = buffer[counter];
			res = ((res >> 8) & 0x0ff) ^ crctab16[(res ^ b) & 0xff];
		}
		return (~res) & 0x0ffff;
	}

	QByteArray crypt(const QString& input, const QDate& expiration)
	{
		auto code_12 = crypt(input);

		bool ok = false;
		auto number = code_12.toLongLong(&ok, 16);

		auto day = QDate(2021, 1, 1).daysTo(expiration);
		if (day < 0)
			day = 0;

		unsigned short dayUS = std::min(day, long long(65535));
		auto hexDaysValid = QString::number(dayUS, 16).toUpper();
		while (hexDaysValid.size() < 4)
			hexDaysValid.prepend('0');

		auto code_date = code_12 + hexDaysValid.toLocal8Bit();

		auto crc_16 = crc16(code_date.data(), code_date.size());
		auto crc16Bytearray = QString::number(crc_16, 16).toLocal8Bit();
		while (crc16Bytearray.size() < 4)
			crc16Bytearray.prepend('0');

		// crcHigh2 + code12 + days4 + crcLow2
		auto licenseCode = crc16Bytearray.mid(0, 2) + code_date + crc16Bytearray.mid(2, 2);
		return licenseCode.toUpper();
	}

	QByteArray crypt(const QString& input)
	{
		// QByteArray bytePwdMd5 = QCryptographicHash::hash(, QCryptographicHash::Md5);

		auto lower = input.toLower();
		auto local8bit = lower.toLocal8Bit();
		auto hex = local8bit.toHex();
		auto md5 = QCryptographicHash::hash(hex, QCryptographicHash::Md5).toHex();

		auto base64 = md5.toBase64();
		auto base64_base_64 = base64.toBase64();
		auto base_64_hex = base64_base_64.toHex();

#if 0
#ifdef _WIN64
		QString path("x64.txt");
#else
		QString path("x86.txt");
#endif // _WIN64
		QFile file(path);

		QJsonObject json{
			{ "input", QString(input) },
			{ "local8bit", QString(local8bit) },
			{ "hex", QString(hex) },
			{ "md5", QString(md5) },
			{ "base64", QString(base64) },
			{ "base64_base_64", QString(base64_base_64) },
			{ "base_64_hex", QString(base_64_hex) },
		};
		if (file.open(QFile::WriteOnly | QFile::Text))
		{
			QJsonDocument doc;
			doc.setObject(json);
			QTextStream s(&file);
			s.setCodec("utf-8");
			s << doc.toJson(QJsonDocument::Indented);
			s.flush();
		}

		auto base_64_hex_compress = qCompress(base_64_hex, 9);

		auto testStr = qCompress(QString("e2NvZGU6J3ppYXdua2RpaGduZWwnLHQ6MjAyMDEyMzAscHJvZHVjdDonRGFtYWdlU29sdmVyJ30=").toLocal8Bit(), 9);

		auto md5compress = qCompress(QCryptographicHash::hash(hex, QCryptographicHash::Md5), 9);

		QByteArray datetime("20201230");

		base_64_hex.mid(2, 10);
#endif

		//FB8112B5;
		return base_64_hex.mid(0, 12).toUpper();
	}

	QByteArray generateLicense(const QString& code, const QString& path /*= ""*/)
	{
		struct LicenseInfo
		{
			QByteArray machineCode;				// 机器码
			QDateTime expirationDatetime;		// 过期时间
		};

		auto licenseCode = crypt(code);

		QFile license(path);
		if (license.open(QFile::WriteOnly | QFile::Text))
		{
			license.write(licenseCode);
			//license.write(info.expirationDatetime);
			license.close();
		}

		return licenseCode;
	}

	QByteArray generateLicense(const QString& code, const QDate& expiration, const QString& path /*= ""*/)
	{
		struct LicenseInfo
		{
			QByteArray machineCode;				// 机器码
			QDateTime expirationDatetime;		// 过期时间
		};

		auto licenseCode = crypt(code, expiration);

		QFile license(path);
		if (license.open(QFile::WriteOnly | QFile::Text))
		{
			license.write(licenseCode);
			//license.write(info.expirationDatetime);
			license.close();
		}

		return licenseCode;
	}

	VGLicenseManager::LicenseInfo validationLicenseCode(const QByteArray& license_code)
	{
		LicenseInfo license;

		auto licenseCode = QString(license_code).trimmed().remove("-").toLocal8Bit();

		license.licenseCode = licenseCode.toStdString();

		if (licenseCode.size() == 12)
		{
			// deprecated license 12 byte
			return license;
			bool flag = false;
			for (auto& code : getMachineCode())
			{
				if (crypt(code) == licenseCode)
				{
					flag = true;
					break;
				}
			}
			return license;
		}
		// 包含时间信息的版本
		else if (licenseCode.size() == 20)
		{
			auto crc16Value = licenseCode.mid(0, 2) + licenseCode.mid(18, 2);
			auto computedCrc_16 = crc16(licenseCode.mid(2, 16).data(), 16);

			bool ok;
			auto codeCRC16 = crc16Value.toInt(&ok, 16);
			if (!ok || codeCRC16 != computedCrc_16)
			{
				license.status = LicenseInfo::LicenseInvalid;
				return license;
			}

			auto licenseCode12 = licenseCode.mid(2, 12);
			bool machineValid = false;
			for (auto& code : getMachineCode())	 // 检查机器码
			{
				if (crypt(code) == licenseCode12)
				{
					license.machineCode = code.toStdString();
					machineValid = true;
					break;
				}
			}

			if (!machineValid)
			{
				license.status = LicenseInfo::MachineCodeMismatch;
				return license;
			}

			auto days = licenseCode.mid(14, 4).toUShort(&ok, 16);
			if (!ok)
			{
				license.status = LicenseInfo::LicenseInvalid;
				return license;
			}

			auto expiration = QDate(2021, 1, 1).addDays(days);
			license.expiration.year = expiration.year();
			license.expiration.month = expiration.month();
			license.expiration.day = expiration.day();

			if (QDate::currentDate().daysTo(expiration) >= 0)
				license.status = LicenseInfo::NoError;
			else
				license.status = LicenseInfo::Expired;

			return license;
		}
		return license;
	}

	VGLicenseManager::LicenseInfo validationLicenseFile(const QString& licenseFile)
	{
		QFile file(licenseFile);
		file.open(QFile::ReadOnly | QFile::Text);
		auto licenseCode = file.readAll();
		file.close();

		return validationLicenseCode(licenseCode);
	}

	void showLicenseError(const VGLicenseManager::LicenseInfo& license)
	{
		using namespace VGLicenseManager;

		LicenseInfo::Status status;
		static QHash<LicenseInfo::Status, QString> info{
			{ LicenseInfo::Expired,"授权已过期，请联系软件提供商。" },
			{ LicenseInfo::MachineCodeMismatch,"机器码不匹配，授权错误，请联系软件提供商。" },
			{ LicenseInfo::CodeError,"授权码错误，请联系软件提供商。" },
			{ LicenseInfo::LicenseInvalid,"授权无效，请联系软件提供商。" },
			{ LicenseInfo::Invalid,"无法找到授权，请联系软件提供商。" },
			{ LicenseInfo::Other,"其它授权错误，请联系软件提供商。" },
		};
		if ( !license.isValid() )
			QMessageBox::warning(0, "错误", info.value(license.status));
	}

};