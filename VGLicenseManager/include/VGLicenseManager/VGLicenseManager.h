#pragma once

#include "Export"
#include <string>

namespace VGLicenseManager
{
	struct LicenseInfo {

		enum Status {
			NoError = 0,				// 无错误
			Expired,					// 过期
			MachineCodeMismatch,		// 机器码不匹配
			CodeError,					// 授权错误
			LicenseInvalid,				// 授权无效
			Invalid,					// 未初始化
			Other						// 其它错误
		};

		std::string machineCode;		// 机器码
		std::string licenseCode;		// 授权码

		struct Date
		{
			unsigned short year{0};			// 年
			unsigned char month{0};			// 月
			unsigned char day{0};			// 日
		};

		Date expiration;				// 过期时间

		bool isValid() const { return status == NoError; }

		Status status{ Invalid };
	};

	/**
	 * 检查授权是否有有效的授权
	 */
	VG_LICENSE_MANAGER_API LicenseInfo checkLicense();
};