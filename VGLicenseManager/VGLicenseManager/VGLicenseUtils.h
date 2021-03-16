#pragma once

#include "QtCore\QString"
#include "QtCore\QByteArray"
#include "VGLicenseManager\VGLicenseManager.h"

class QDate;

namespace VGLicenseUtils
{
	/**
	* 获取机器码
	*/
	QStringList getMachineCode();

	/**
	 * 加密函数
	 */
	QByteArray crypt(const QString& input);

	QByteArray crypt(const QString& input, const QDate& expiration);

	/**
	 * 根据机器码生成license文件
	 */
	QByteArray generateLicense(const QString& code, const QString& path = "");

	/**
	* 根据机器码生成license文件
	*/
	QByteArray generateLicense(const QString& code, const QDate& expiration, const QString& path = "");

	/**
	* 检查license码是否正确
	*/
	VGLicenseManager::LicenseInfo validationLicenseCode(const QByteArray& license_code);

	/**
	* 检查license code是否有效
	*/
	VGLicenseManager::LicenseInfo validationLicenseFile(const QString& licenseFile = "license.lic");

	void showLicenseError(const VGLicenseManager::LicenseInfo& license);
};