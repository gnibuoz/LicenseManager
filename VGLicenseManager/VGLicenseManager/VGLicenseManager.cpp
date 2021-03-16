#pragma execution_character_set("utf-8")
#include "VGLicenseManager/VGLicenseManager.h"

#include "VGLicenseUtils.h"
#include "vglicensefaileddialog.h"
#include "QApplication"
#include "QMessageBox"

using namespace VGLicenseUtils;

namespace VGLicenseManager
{
	VG_LICENSE_MANAGER_API LicenseInfo checkLicense()
	{
		auto lic = validationLicenseFile();
		if ( !lic.isValid() )
		{
			VGLicenseUtils::showLicenseError(lic);

			VGLicenseFailedDialog dia(false);
			if (dia.exec() != QDialog::Accepted)
			{
				qApp->quit();
				exit(-1);
			}
		}

		return lic;
	}
};
