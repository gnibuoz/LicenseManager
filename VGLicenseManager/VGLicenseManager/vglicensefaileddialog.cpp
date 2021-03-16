#pragma execution_character_set("utf-8")
#include "vglicensefaileddialog.h"
#include "ui_vglicensefaileddialog.h"


#include "QR_Encode.h"
#include "QImage"
#include "QFileDialog"
#include "VGLicenseUtils.h"
#include "QMessageBox"
#include "QDateTime"

VGLicenseFailedDialog::VGLicenseFailedDialog(bool generate /*= false */, QWidget *parent)
	: QDialog(parent)
{
	ui = new Ui::VGLicenseFailedDialog();
	ui->setupUi(this);

	if (generate)
	{
		ui->labelTip->setVisible(false);
	}
	else
	{
		ui->widgetExpiration->setVisible(false);
	}

#if 0
	connect(ui->pushButtonGenerateLicenseFile, &QPushButton::clicked, [this]() {
		auto path =  QFileDialog::getSaveFileName(this, "License File", "license.lic", "License(*.lic)");
		if (path.isEmpty()) return;
		VGLicenseUtils::generateLicense(ui->lineEditCode->text(),path);
	});

	connect(ui->pushButtonGenerateLicenseKey, &QPushButton::clicked, [this]() {
		ui->lineEditKey->setText(VGLicenseUtils::crypt(ui->lineEditCode->text(),QDate(2021,1,1)));
	});
#endif

	connect(ui->pushButtonApplyLicenseKey, &QPushButton::clicked, [this]() {
		auto key = ui->lineEditKey->text().toLocal8Bit();
		
		bool valid = false;
		
		auto licenseInfo = VGLicenseUtils::validationLicenseCode(key);
		QDate date(licenseInfo.expiration.year, licenseInfo.expiration.month, licenseInfo.expiration.day);

		if (licenseInfo.isValid())
		{
			valid = true;

			QMessageBox::information(this, "提示", QString("授权成功!"));// .arg(date.toString("yyyy年MM月dd日")));

			QFile license("license.lic");
			license.open(QFile::WriteOnly | QFile::Text);
			license.write(key);
			license.close();

			accept();
		}
		else
		{
			VGLicenseUtils::showLicenseError(licenseInfo);
			return;
		}
	});

	connect(ui->lineEditCode, &QLineEdit::textChanged, [this](const QString& text) {
		int levelIndex = 1;
		int versionIndex = 0;
		bool bExtent = true;
		int maskIndex = -1;
		CQR_Encode m_QREncode;

		auto m_bDataEncoded = m_QREncode.EncodeData(levelIndex, versionIndex,
			bExtent, maskIndex, text.toLocal8Bit().data());

		if (!m_bDataEncoded) return;

		// 创建二维码图片
		auto m_EncodeImageSize = m_QREncode.m_nSymbleSize + (QR_MARGIN * 2);
		QImage encode_image(m_EncodeImageSize, m_EncodeImageSize, QImage::Format_Mono);
		encode_image.fill(1);

		// 生成二维码图片
		for (int i = 0; i < m_QREncode.m_nSymbleSize; ++i)
		{
			for (int j = 0; j < m_QREncode.m_nSymbleSize; ++j)
			{
				if (m_QREncode.m_byModuleData[i][j])
					encode_image.setPixel(i + QR_MARGIN, j + QR_MARGIN, 0);
			}
		}

		// 显示二维码图片
		ui->labelQRC->setPixmap(QPixmap::fromImage(encode_image.scaledToWidth(ui->labelQRC->width(), Qt::SmoothTransformation)));

	});

	auto mmm = VGLicenseUtils::getMachineCode();
	ui->lineEditCode->setText(mmm[0]);
}

VGLicenseFailedDialog::~VGLicenseFailedDialog()
{
	delete ui;
}

void VGLicenseFailedDialog::setHideQRcode(bool hide)
{
	ui->frameQRCode->setHidden(hide);

	setMinimumWidth(500);
	resize(sizeHint());
}