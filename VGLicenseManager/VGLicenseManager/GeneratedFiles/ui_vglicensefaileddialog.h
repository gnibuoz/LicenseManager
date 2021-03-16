/********************************************************************************
** Form generated from reading UI file 'vglicensefaileddialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VGLICENSEFAILEDDIALOG_H
#define UI_VGLICENSEFAILEDDIALOG_H

#include <QtCore/QDate>
#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_VGLicenseFailedDialog
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *labelTip;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEditCode;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_4;
    QLineEdit *lineEditKey;
    QFrame *frameQRCode;
    QHBoxLayout *horizontalLayout_3;
    QLabel *labelQRC_2;
    QLabel *labelQRC;
    QSpacerItem *horizontalSpacer_2;
    QWidget *widgetExpiration;
    QDateTimeEdit *dateTimeEditExpirationDateTime;
    QLabel *label_2;
    QPushButton *pushButtonGenerateLicenseFile;
    QPushButton *pushButtonGenerateLicenseKey;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButtonApplyLicenseKey;
    QPushButton *pushButton;

    void setupUi(QDialog *VGLicenseFailedDialog)
    {
        if (VGLicenseFailedDialog->objectName().isEmpty())
            VGLicenseFailedDialog->setObjectName(QString::fromUtf8("VGLicenseFailedDialog"));
        VGLicenseFailedDialog->resize(555, 380);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Resource/icon/database.png"), QSize(), QIcon::Normal, QIcon::Off);
        VGLicenseFailedDialog->setWindowIcon(icon);
        verticalLayout = new QVBoxLayout(VGLicenseFailedDialog);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        labelTip = new QLabel(VGLicenseFailedDialog);
        labelTip->setObjectName(QString::fromUtf8("labelTip"));
        QPalette palette;
        QBrush brush(QColor(255, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        QBrush brush1(QColor(120, 120, 120, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        labelTip->setPalette(palette);
        QFont font;
        font.setPointSize(11);
        font.setBold(true);
        font.setWeight(75);
        labelTip->setFont(font);

        verticalLayout->addWidget(labelTip);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(VGLicenseFailedDialog);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        lineEditCode = new QLineEdit(VGLicenseFailedDialog);
        lineEditCode->setObjectName(QString::fromUtf8("lineEditCode"));
        lineEditCode->setReadOnly(false);

        horizontalLayout->addWidget(lineEditCode);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_4 = new QLabel(VGLicenseFailedDialog);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_5->addWidget(label_4);

        lineEditKey = new QLineEdit(VGLicenseFailedDialog);
        lineEditKey->setObjectName(QString::fromUtf8("lineEditKey"));
        lineEditKey->setReadOnly(false);

        horizontalLayout_5->addWidget(lineEditKey);


        verticalLayout->addLayout(horizontalLayout_5);

        frameQRCode = new QFrame(VGLicenseFailedDialog);
        frameQRCode->setObjectName(QString::fromUtf8("frameQRCode"));
        horizontalLayout_3 = new QHBoxLayout(frameQRCode);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        labelQRC_2 = new QLabel(frameQRCode);
        labelQRC_2->setObjectName(QString::fromUtf8("labelQRC_2"));

        horizontalLayout_3->addWidget(labelQRC_2);

        labelQRC = new QLabel(frameQRCode);
        labelQRC->setObjectName(QString::fromUtf8("labelQRC"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(labelQRC->sizePolicy().hasHeightForWidth());
        labelQRC->setSizePolicy(sizePolicy);
        labelQRC->setMinimumSize(QSize(150, 150));
        labelQRC->setMaximumSize(QSize(150, 150));
        labelQRC->setScaledContents(true);

        horizontalLayout_3->addWidget(labelQRC);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);


        verticalLayout->addWidget(frameQRCode);

        widgetExpiration = new QWidget(VGLicenseFailedDialog);
        widgetExpiration->setObjectName(QString::fromUtf8("widgetExpiration"));
        widgetExpiration->setMinimumSize(QSize(0, 80));
        dateTimeEditExpirationDateTime = new QDateTimeEdit(widgetExpiration);
        dateTimeEditExpirationDateTime->setObjectName(QString::fromUtf8("dateTimeEditExpirationDateTime"));
        dateTimeEditExpirationDateTime->setGeometry(QRect(90, 10, 194, 22));
        dateTimeEditExpirationDateTime->setDate(QDate(2021, 2, 1));
        dateTimeEditExpirationDateTime->setCalendarPopup(true);
        label_2 = new QLabel(widgetExpiration);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 10, 54, 12));
        pushButtonGenerateLicenseFile = new QPushButton(widgetExpiration);
        pushButtonGenerateLicenseFile->setObjectName(QString::fromUtf8("pushButtonGenerateLicenseFile"));
        pushButtonGenerateLicenseFile->setGeometry(QRect(230, 50, 80, 23));
        pushButtonGenerateLicenseKey = new QPushButton(widgetExpiration);
        pushButtonGenerateLicenseKey->setObjectName(QString::fromUtf8("pushButtonGenerateLicenseKey"));
        pushButtonGenerateLicenseKey->setGeometry(QRect(360, 50, 75, 23));

        verticalLayout->addWidget(widgetExpiration);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        pushButtonApplyLicenseKey = new QPushButton(VGLicenseFailedDialog);
        pushButtonApplyLicenseKey->setObjectName(QString::fromUtf8("pushButtonApplyLicenseKey"));

        horizontalLayout_2->addWidget(pushButtonApplyLicenseKey);

        pushButton = new QPushButton(VGLicenseFailedDialog);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout_2->addWidget(pushButton);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(VGLicenseFailedDialog);
        QObject::connect(pushButton, SIGNAL(clicked()), VGLicenseFailedDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(VGLicenseFailedDialog);
    } // setupUi

    void retranslateUi(QDialog *VGLicenseFailedDialog)
    {
        VGLicenseFailedDialog->setWindowTitle(QApplication::translate("VGLicenseFailedDialog", "\346\216\210\346\235\203", nullptr));
        labelTip->setText(QApplication::translate("VGLicenseFailedDialog", "\346\227\240\346\263\225\345\234\250\350\277\231\345\217\260\347\224\265\350\204\221\344\270\212\346\211\276\345\210\260\346\234\211\346\225\210\347\232\204\346\216\210\346\235\203\357\274\214\350\257\267\350\201\224\347\263\273\346\234\215\345\212\241\346\217\220\344\276\233\345\225\206,\345\271\266\346\217\220\344\276\233\344\273\245\344\270\213\346\234\272\345\231\250\347\240\201\343\200\202", nullptr));
        label->setText(QApplication::translate("VGLicenseFailedDialog", "\346\234\272\345\231\250\347\240\201:", nullptr));
        lineEditCode->setText(QString());
        label_4->setText(QApplication::translate("VGLicenseFailedDialog", "\345\257\206  \351\222\245:", nullptr));
        lineEditKey->setText(QString());
        labelQRC_2->setText(QApplication::translate("VGLicenseFailedDialog", "\344\272\214\347\273\264\347\240\201:", nullptr));
        labelQRC->setText(QString());
        dateTimeEditExpirationDateTime->setDisplayFormat(QApplication::translate("VGLicenseFailedDialog", "yyyy/MM/dd HH:mm", nullptr));
        label_2->setText(QApplication::translate("VGLicenseFailedDialog", "\346\234\211\346\225\210\346\227\266\351\227\264", nullptr));
        pushButtonGenerateLicenseFile->setText(QApplication::translate("VGLicenseFailedDialog", "\345\257\274\345\207\272\346\216\210\346\235\203\346\226\207\344\273\266", nullptr));
        pushButtonGenerateLicenseKey->setText(QApplication::translate("VGLicenseFailedDialog", "\347\224\237\346\210\220\345\257\206\351\222\245", nullptr));
        pushButtonApplyLicenseKey->setText(QApplication::translate("VGLicenseFailedDialog", "\351\252\214\350\257\201\346\216\210\346\235\203", nullptr));
        pushButton->setText(QApplication::translate("VGLicenseFailedDialog", "\351\200\200\345\207\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class VGLicenseFailedDialog: public Ui_VGLicenseFailedDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VGLICENSEFAILEDDIALOG_H
