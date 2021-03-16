#pragma once

#include <QDialog>
namespace Ui { class VGLicenseFailedDialog; };

class VGLicenseFailedDialog : public QDialog
{
	Q_OBJECT

public:
	VGLicenseFailedDialog(bool generate = false ,QWidget *parent = Q_NULLPTR);
	~VGLicenseFailedDialog();

	void setHideQRcode(bool hide);


private:
	Ui::VGLicenseFailedDialog *ui;
};
