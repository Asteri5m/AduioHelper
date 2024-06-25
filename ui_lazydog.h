/********************************************************************************
** Form generated from reading UI file 'lazydog.ui'
**
** Created by: Qt User Interface Compiler version 6.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LAZYDOG_H
#define UI_LAZYDOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QKeySequenceEdit>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LazyDog
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QTextBrowser *debugBrowser;
    QTabWidget *mainWidget;
    QWidget *tab_process;
    QGridLayout *gridLayout_2;
    QTableView *tableView_process;
    QComboBox *comboBox_add;
    QPushButton *pushButton_renew;
    QPushButton *pushButton_add;
    QSpacerItem *horizontalSpacer;
    QWidget *tab_monitor;
    QGridLayout *gridLayout_3;
    QPushButton *pushButton_change;
    QTableView *tableView_monitor;
    QPushButton *pushButton_delete;
    QComboBox *comboBox_change;
    QSpacerItem *horizontalSpacer_2;
    QWidget *tab_seting;
    QGridLayout *gridLayout_4;
    QGroupBox *groupBox_mode;
    QGridLayout *gridLayout_5;
    QRadioButton *radioButton_window;
    QRadioButton *radioButton_process;
    QToolButton *toolButton_modehelp;
    QPushButton *pushButton_about;
    QSpacerItem *verticalSpacer;
    QPushButton *pushButton_checknew;
    QFrame *line_2;
    QSpacerItem *horizontalSpacer_3;
    QFrame *line;
    QFrame *line_3;
    QGroupBox *groupBox_keys;
    QGridLayout *gridLayout_6;
    QLabel *label_3;
    QLabel *label_2;
    QKeySequenceEdit *keySequenceEdit_start;
    QLabel *label;
    QLabel *label_4;
    QKeySequenceEdit *keySequenceEdit_changemode;
    QKeySequenceEdit *keySequenceEdit_changeup;
    QKeySequenceEdit *keySequenceEdit_changedown;
    QGroupBox *groupBox_default;
    QGridLayout *gridLayout_7;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QCheckBox *checkBox_autostart;
    QCheckBox *checkBox_adminstart;
    QCheckBox *checkBox_defaultdevice;
    QToolButton *toolButton_defaulthelp;
    QComboBox *comboBox_defaultdevice;
    QSpacerItem *horizontalSpacer_4;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_2;
    QCheckBox *checkBox_autohidden;
    QCheckBox *checkBox_changemsg;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout_3;
    QCheckBox *checkBox_autochecknew;

    void setupUi(QMainWindow *LazyDog)
    {
        if (LazyDog->objectName().isEmpty())
            LazyDog->setObjectName("LazyDog");
        LazyDog->setWindowModality(Qt::NonModal);
        LazyDog->setEnabled(true);
        LazyDog->resize(500, 600);
        LazyDog->setMinimumSize(QSize(300, 400));
        LazyDog->setContextMenuPolicy(Qt::DefaultContextMenu);
        LazyDog->setInputMethodHints(Qt::ImhDigitsOnly);
        LazyDog->setAnimated(true);
        LazyDog->setDocumentMode(false);
        LazyDog->setDockNestingEnabled(false);
        LazyDog->setDockOptions(QMainWindow::AllowTabbedDocks|QMainWindow::AnimatedDocks);
        centralwidget = new QWidget(LazyDog);
        centralwidget->setObjectName("centralwidget");
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        debugBrowser = new QTextBrowser(centralwidget);
        debugBrowser->setObjectName("debugBrowser");
        debugBrowser->setMinimumSize(QSize(0, 130));
        debugBrowser->setMaximumSize(QSize(16777215, 130));
        QFont font;
        font.setFamilies({QString::fromUtf8("Microsoft YaHei")});
        debugBrowser->setFont(font);
        debugBrowser->setStyleSheet(QString::fromUtf8(""));
        debugBrowser->setReadOnly(true);

        gridLayout->addWidget(debugBrowser, 1, 0, 1, 1);

        mainWidget = new QTabWidget(centralwidget);
        mainWidget->setObjectName("mainWidget");
        mainWidget->setStyleSheet(QString::fromUtf8(""));
        tab_process = new QWidget();
        tab_process->setObjectName("tab_process");
        gridLayout_2 = new QGridLayout(tab_process);
        gridLayout_2->setObjectName("gridLayout_2");
        tableView_process = new QTableView(tab_process);
        tableView_process->setObjectName("tableView_process");

        gridLayout_2->addWidget(tableView_process, 0, 0, 1, 5);

        comboBox_add = new QComboBox(tab_process);
        comboBox_add->setObjectName("comboBox_add");

        gridLayout_2->addWidget(comboBox_add, 1, 0, 1, 1);

        pushButton_renew = new QPushButton(tab_process);
        pushButton_renew->setObjectName("pushButton_renew");

        gridLayout_2->addWidget(pushButton_renew, 1, 3, 1, 1);

        pushButton_add = new QPushButton(tab_process);
        pushButton_add->setObjectName("pushButton_add");

        gridLayout_2->addWidget(pushButton_add, 1, 4, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 1, 2, 1, 1);

        mainWidget->addTab(tab_process, QString());
        tab_monitor = new QWidget();
        tab_monitor->setObjectName("tab_monitor");
        gridLayout_3 = new QGridLayout(tab_monitor);
        gridLayout_3->setObjectName("gridLayout_3");
        pushButton_change = new QPushButton(tab_monitor);
        pushButton_change->setObjectName("pushButton_change");

        gridLayout_3->addWidget(pushButton_change, 1, 4, 1, 2);

        tableView_monitor = new QTableView(tab_monitor);
        tableView_monitor->setObjectName("tableView_monitor");

        gridLayout_3->addWidget(tableView_monitor, 0, 0, 1, 8);

        pushButton_delete = new QPushButton(tab_monitor);
        pushButton_delete->setObjectName("pushButton_delete");

        gridLayout_3->addWidget(pushButton_delete, 1, 6, 1, 2);

        comboBox_change = new QComboBox(tab_monitor);
        comboBox_change->setObjectName("comboBox_change");

        gridLayout_3->addWidget(comboBox_change, 1, 0, 1, 2);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_2, 1, 3, 1, 1);

        mainWidget->addTab(tab_monitor, QString());
        tab_seting = new QWidget();
        tab_seting->setObjectName("tab_seting");
        gridLayout_4 = new QGridLayout(tab_seting);
        gridLayout_4->setObjectName("gridLayout_4");
        groupBox_mode = new QGroupBox(tab_seting);
        groupBox_mode->setObjectName("groupBox_mode");
        gridLayout_5 = new QGridLayout(groupBox_mode);
        gridLayout_5->setObjectName("gridLayout_5");
        radioButton_window = new QRadioButton(groupBox_mode);
        radioButton_window->setObjectName("radioButton_window");

        gridLayout_5->addWidget(radioButton_window, 0, 1, 1, 1);

        radioButton_process = new QRadioButton(groupBox_mode);
        radioButton_process->setObjectName("radioButton_process");

        gridLayout_5->addWidget(radioButton_process, 0, 0, 1, 1);

        toolButton_modehelp = new QToolButton(groupBox_mode);
        toolButton_modehelp->setObjectName("toolButton_modehelp");

        gridLayout_5->addWidget(toolButton_modehelp, 0, 2, 1, 1);


        gridLayout_4->addWidget(groupBox_mode, 8, 0, 1, 7);

        pushButton_about = new QPushButton(tab_seting);
        pushButton_about->setObjectName("pushButton_about");

        gridLayout_4->addWidget(pushButton_about, 15, 6, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_4->addItem(verticalSpacer, 14, 0, 1, 7);

        pushButton_checknew = new QPushButton(tab_seting);
        pushButton_checknew->setObjectName("pushButton_checknew");

        gridLayout_4->addWidget(pushButton_checknew, 15, 0, 1, 1);

        line_2 = new QFrame(tab_seting);
        line_2->setObjectName("line_2");
        line_2->setFrameShape(QFrame::Shape::HLine);
        line_2->setFrameShadow(QFrame::Shadow::Sunken);

        gridLayout_4->addWidget(line_2, 9, 0, 1, 7);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_3, 15, 1, 1, 5);

        line = new QFrame(tab_seting);
        line->setObjectName("line");
        line->setFrameShape(QFrame::Shape::HLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);

        gridLayout_4->addWidget(line, 7, 0, 1, 7);

        line_3 = new QFrame(tab_seting);
        line_3->setObjectName("line_3");
        line_3->setFrameShape(QFrame::Shape::HLine);
        line_3->setFrameShadow(QFrame::Shadow::Sunken);

        gridLayout_4->addWidget(line_3, 11, 0, 1, 7);

        groupBox_keys = new QGroupBox(tab_seting);
        groupBox_keys->setObjectName("groupBox_keys");
        gridLayout_6 = new QGridLayout(groupBox_keys);
        gridLayout_6->setObjectName("gridLayout_6");
        label_3 = new QLabel(groupBox_keys);
        label_3->setObjectName("label_3");

        gridLayout_6->addWidget(label_3, 2, 0, 1, 1);

        label_2 = new QLabel(groupBox_keys);
        label_2->setObjectName("label_2");

        gridLayout_6->addWidget(label_2, 1, 0, 1, 1);

        keySequenceEdit_start = new QKeySequenceEdit(groupBox_keys);
        keySequenceEdit_start->setObjectName("keySequenceEdit_start");
        keySequenceEdit_start->setClearButtonEnabled(true);

        gridLayout_6->addWidget(keySequenceEdit_start, 0, 2, 1, 1);

        label = new QLabel(groupBox_keys);
        label->setObjectName("label");

        gridLayout_6->addWidget(label, 0, 0, 1, 1);

        label_4 = new QLabel(groupBox_keys);
        label_4->setObjectName("label_4");

        gridLayout_6->addWidget(label_4, 3, 0, 1, 1);

        keySequenceEdit_changemode = new QKeySequenceEdit(groupBox_keys);
        keySequenceEdit_changemode->setObjectName("keySequenceEdit_changemode");
        keySequenceEdit_changemode->setClearButtonEnabled(true);

        gridLayout_6->addWidget(keySequenceEdit_changemode, 1, 2, 1, 1);

        keySequenceEdit_changeup = new QKeySequenceEdit(groupBox_keys);
        keySequenceEdit_changeup->setObjectName("keySequenceEdit_changeup");
        keySequenceEdit_changeup->setClearButtonEnabled(true);

        gridLayout_6->addWidget(keySequenceEdit_changeup, 2, 2, 1, 1);

        keySequenceEdit_changedown = new QKeySequenceEdit(groupBox_keys);
        keySequenceEdit_changedown->setObjectName("keySequenceEdit_changedown");
        keySequenceEdit_changedown->setClearButtonEnabled(true);

        gridLayout_6->addWidget(keySequenceEdit_changedown, 3, 2, 1, 1);


        gridLayout_4->addWidget(groupBox_keys, 10, 0, 1, 7);

        groupBox_default = new QGroupBox(tab_seting);
        groupBox_default->setObjectName("groupBox_default");
        gridLayout_7 = new QGridLayout(groupBox_default);
        gridLayout_7->setObjectName("gridLayout_7");
        widget = new QWidget(groupBox_default);
        widget->setObjectName("widget");
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        checkBox_autostart = new QCheckBox(widget);
        checkBox_autostart->setObjectName("checkBox_autostart");
        checkBox_autostart->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout->addWidget(checkBox_autostart);

        checkBox_adminstart = new QCheckBox(widget);
        checkBox_adminstart->setObjectName("checkBox_adminstart");

        horizontalLayout->addWidget(checkBox_adminstart);


        gridLayout_7->addWidget(widget, 0, 0, 1, 5);

        checkBox_defaultdevice = new QCheckBox(groupBox_default);
        checkBox_defaultdevice->setObjectName("checkBox_defaultdevice");

        gridLayout_7->addWidget(checkBox_defaultdevice, 7, 0, 1, 1);

        toolButton_defaulthelp = new QToolButton(groupBox_default);
        toolButton_defaulthelp->setObjectName("toolButton_defaulthelp");

        gridLayout_7->addWidget(toolButton_defaulthelp, 7, 2, 1, 1);

        comboBox_defaultdevice = new QComboBox(groupBox_default);
        comboBox_defaultdevice->setObjectName("comboBox_defaultdevice");

        gridLayout_7->addWidget(comboBox_defaultdevice, 7, 1, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_7->addItem(horizontalSpacer_4, 7, 3, 1, 2);

        widget_2 = new QWidget(groupBox_default);
        widget_2->setObjectName("widget_2");
        horizontalLayout_2 = new QHBoxLayout(widget_2);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        checkBox_autohidden = new QCheckBox(widget_2);
        checkBox_autohidden->setObjectName("checkBox_autohidden");

        horizontalLayout_2->addWidget(checkBox_autohidden);

        checkBox_changemsg = new QCheckBox(widget_2);
        checkBox_changemsg->setObjectName("checkBox_changemsg");

        horizontalLayout_2->addWidget(checkBox_changemsg);


        gridLayout_7->addWidget(widget_2, 2, 0, 1, 5);

        widget_3 = new QWidget(groupBox_default);
        widget_3->setObjectName("widget_3");
        horizontalLayout_3 = new QHBoxLayout(widget_3);
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        checkBox_autochecknew = new QCheckBox(widget_3);
        checkBox_autochecknew->setObjectName("checkBox_autochecknew");

        horizontalLayout_3->addWidget(checkBox_autochecknew);


        gridLayout_7->addWidget(widget_3, 6, 0, 1, 5);


        gridLayout_4->addWidget(groupBox_default, 1, 0, 2, 7);

        mainWidget->addTab(tab_seting, QString());

        gridLayout->addWidget(mainWidget, 0, 0, 1, 1);

        LazyDog->setCentralWidget(centralwidget);

        retranslateUi(LazyDog);

        mainWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(LazyDog);
    } // setupUi

    void retranslateUi(QMainWindow *LazyDog)
    {
        LazyDog->setWindowTitle(QCoreApplication::translate("LazyDog", "LazyDogTools", nullptr));
        pushButton_renew->setText(QCoreApplication::translate("LazyDog", " \345\210\267\346\226\260\345\210\227\350\241\250", nullptr));
        pushButton_add->setText(QCoreApplication::translate("LazyDog", "\346\267\273\345\212\240\347\273\221\345\256\232", nullptr));
        mainWidget->setTabText(mainWidget->indexOf(tab_process), QCoreApplication::translate("LazyDog", "\345\267\262\346\211\223\345\274\200\350\277\233\347\250\213", nullptr));
        pushButton_change->setText(QCoreApplication::translate("LazyDog", "\346\233\264\346\224\271\347\273\221\345\256\232", nullptr));
        pushButton_delete->setText(QCoreApplication::translate("LazyDog", "\345\217\226\346\266\210\347\273\221\345\256\232", nullptr));
        mainWidget->setTabText(mainWidget->indexOf(tab_monitor), QCoreApplication::translate("LazyDog", "\345\267\262\347\273\221\345\256\232\350\277\233\347\250\213", nullptr));
        groupBox_mode->setTitle(QCoreApplication::translate("LazyDog", "\346\250\241\345\274\217", nullptr));
        radioButton_window->setText(QCoreApplication::translate("LazyDog", "\347\252\227\345\217\243\346\250\241\345\274\217", nullptr));
        radioButton_process->setText(QCoreApplication::translate("LazyDog", "\350\277\233\347\250\213\346\250\241\345\274\217", nullptr));
#if QT_CONFIG(tooltip)
        toolButton_modehelp->setToolTip(QCoreApplication::translate("LazyDog", "<html><head/><body><p>\350\277\233\347\250\213\346\250\241\345\274\217\357\274\232\346\240\271\346\215\256<span style=\" color:#aa0000;\">\344\273\273\345\212\241\347\232\204\345\220\257\345\212\250\351\241\272\345\272\217</span>\350\277\233\350\241\214\345\210\207\346\215\242\350\256\276\345\244\207</p><p>\347\252\227\345\217\243\346\250\241\345\274\217\357\274\232\346\240\271\346\215\256<span style=\" color:#aa0000;\">\345\275\223\345\211\215\346\264\273\345\212\250\347\232\204\347\252\227\345\217\243</span>\350\277\233\350\241\214\345\210\207\346\215\242\350\256\276\345\244\207</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        toolButton_modehelp->setText(QCoreApplication::translate("LazyDog", "?", nullptr));
        pushButton_about->setText(QCoreApplication::translate("LazyDog", "\345\205\263\344\272\216", nullptr));
        pushButton_checknew->setText(QCoreApplication::translate("LazyDog", "\346\243\200\346\237\245\346\233\264\346\226\260", nullptr));
        groupBox_keys->setTitle(QCoreApplication::translate("LazyDog", "\345\277\253\346\215\267\351\224\256", nullptr));
        label_3->setText(QCoreApplication::translate("LazyDog", "\345\210\207\346\215\242\344\270\212\344\270\200\344\270\252\350\256\276\345\244\207", nullptr));
        label_2->setText(QCoreApplication::translate("LazyDog", "\345\210\207\346\215\242\346\250\241\345\274\217", nullptr));
        label->setText(QCoreApplication::translate("LazyDog", "\345\274\200\345\220\257/\345\205\263\351\227\255\345\212\237\350\203\275", nullptr));
        label_4->setText(QCoreApplication::translate("LazyDog", "\345\210\207\346\215\242\344\270\213\344\270\200\344\270\252\350\256\276\345\244\207", nullptr));
        groupBox_default->setTitle(QCoreApplication::translate("LazyDog", "\351\246\226\351\200\211\351\241\271", nullptr));
        checkBox_autostart->setText(QCoreApplication::translate("LazyDog", "\345\274\200\346\234\272\350\207\252\345\220\257\345\212\250", nullptr));
        checkBox_adminstart->setText(QCoreApplication::translate("LazyDog", "\347\256\241\347\220\206\345\221\230\346\250\241\345\274\217\345\220\257\345\212\250", nullptr));
        checkBox_defaultdevice->setText(QCoreApplication::translate("LazyDog", "\351\273\230\350\256\244\350\256\276\345\244\207", nullptr));
#if QT_CONFIG(tooltip)
        toolButton_defaulthelp->setToolTip(QCoreApplication::translate("LazyDog", "\345\275\223\346\262\241\346\234\211\345\214\271\351\205\215\345\210\260\344\273\273\344\275\225\347\273\221\345\256\232\347\232\204\350\277\233\347\250\213\346\227\266\357\274\214\345\210\207\345\233\236\345\210\260\351\273\230\350\256\244\350\256\276\345\244\207", nullptr));
#endif // QT_CONFIG(tooltip)
        toolButton_defaulthelp->setText(QCoreApplication::translate("LazyDog", "?", nullptr));
        checkBox_autohidden->setText(QCoreApplication::translate("LazyDog", "\345\220\257\345\212\250\350\207\252\345\212\250\351\232\220\350\227\217", nullptr));
        checkBox_changemsg->setText(QCoreApplication::translate("LazyDog", "\345\210\207\346\215\242\346\227\266\351\200\232\347\237\245", nullptr));
        checkBox_autochecknew->setText(QCoreApplication::translate("LazyDog", "\350\207\252\345\212\250\346\233\264\346\226\260", nullptr));
        mainWidget->setTabText(mainWidget->indexOf(tab_seting), QCoreApplication::translate("LazyDog", "\350\256\276\347\275\256", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LazyDog: public Ui_LazyDog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LAZYDOG_H
