#include "mainwindow.h"
#include <QLocale>
#include <QDebug>
#include <QMessageBox>
#include <QCoreApplication>
#include <QWidget>
#include <QSettings>
#include <QEvent>
#include <QCloseEvent>
#include <QFileDialog>
#include <QToolButton>
#include <QTranslator>
#include <QDir>
#include <classtable.h>

MainWindow::MainWindow(const QString& username, QWidget *parent): QMainWindow(parent) {
    QDir::setCurrent(QCoreApplication::applicationDirPath());
    m_userName = username;


    QWidget *centralWidget = new QWidget(this);
    QGridLayout *mainLayout = new QGridLayout;
    createPreviewGroupBox();
    createGeneralOptionGroupBox();
    createMenuBar();
    beautifyCalendar();

    mainLayout->addWidget(m_previewGroupBox, 0, 0);
    mainLayout->addWidget(m_generalOptionsGroupBox, 1, 0);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);
    setWindowTitle("SmartCalendar");
    resize(QSize(1024, 768));

    readSettings();
    UserManager *usermanager = new UserManager(m_userName, m_calendar);
    usermanager->readUserData();
}

MainWindow::~MainWindow() {

}

void MainWindow::beautifyCalendar() {
    QFile qssFile(":/calendarwidget.qss");
    qssFile.open(QFile::ReadOnly);
    if (qssFile.isOpen()) {
        QString qss = QLatin1String(qssFile.readAll());
        m_calendar->setStyleSheet(qss);
        qssFile.close();
    }
    QToolButton *leftButton = m_calendar->findChild<QToolButton*>(QLatin1String("qt_calendar_prevmonth"));
    leftButton->setIcon(QIcon(":/img/leftbutton.png"));
    QToolButton *rightButton = m_calendar->findChild<QToolButton*>(QLatin1String("qt_calendar_nextmonth"));
    rightButton->setIcon(QIcon(":/img/rightbutton.png"));
}

void MainWindow::closeEvent(QCloseEvent *event) {
    QMessageBox msgBox;
    msgBox.setText(tr("Do you want to save user data?"));
    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Cancel | QMessageBox::Discard);
    msgBox.setDefaultButton(QMessageBox::Save);
    int ret = msgBox.exec();
    UserManager *usermanager;
    switch (ret) {
    case QMessageBox::Save:
        usermanager = new UserManager(m_userName, m_calendar);
        usermanager->saveUserData();
        saveSettings();
        event->accept();
        break;
    case QMessageBox::Discard:
        event->accept();
        break;
    case QMessageBox::Cancel:
        event->ignore();
        break;
    }
}

void MainWindow::saveSettings() {
    QSettings settings("Yuhui Inc.", m_userName.toStdString().c_str());
    settings.setValue("GridLayout", m_gridCheckBox->isChecked());
    settings.setValue("NavigationBar", m_navigationBarCheckBox->isChecked());
    settings.setValue("SelectionMode", m_selectionModeCheckBox->isChecked());
    settings.setValue("Locale", m_localeComboBox->currentIndex());
    settings.setValue("AllowMove", m_moveAllowAction->isChecked());
    settings.setValue("AllowDrag", m_dragAllowCheckBox->isChecked());
    settings.setValue("IsOpacity", m_opacityCheckBox->isChecked());
    settings.setValue("Opacity", m_opacitySlider->value());
    settings.setValue("CalendarLocale", m_calendar->locale());
}

void MainWindow::readSettings() {
    QSettings settings("Yuhui Inc.", m_userName.toStdString().c_str());

    if(settings.contains("GridLayout")) m_gridCheckBox->setChecked(settings.value("GridLayout").toBool());
    if(settings.contains("NavigationBar")) m_navigationBarCheckBox->setChecked(settings.value("NavigationBar").toBool());
    if(settings.contains("SelectionMode")) m_selectionModeCheckBox->setChecked(settings.value("SelectionMode").toBool());
    if(settings.contains("CalendarLocale")) m_calendar->setLocale(settings.value("CalendarLocale").toLocale());
    if(settings.contains("Locale")) m_localeComboBox->setCurrentIndex(settings.value("Locale").toInt());
    if(settings.contains("AllowMove")) m_moveAllowAction->setChecked(settings.value("AllowMove").toBool());
    if(settings.contains("AllowDrag")) m_dragAllowCheckBox->setChecked(settings.value("AllowDrag").toBool());
    if(settings.contains("IsOpacity")) m_opacityCheckBox->setChecked(settings.value("IsOpacity").toBool());
    if(settings.contains("Opacity")) m_opacitySlider->setValue(settings.value("Opacity").toInt());
    emit(m_gridCheckBox->clicked());
    emit(m_selectionModeCheckBox->clicked());
    emit(m_navigationBarCheckBox->clicked());
    emit(m_moveAllowAction->changed());
    emit(m_dragAllowCheckBox->clicked());
    emit(m_opacityCheckBox->clicked());
}

void MainWindow::createMenuBar() {
    m_menuBar = new QMenuBar(this);
    m_settingMenu = new QMenu(tr("SetFixed"));
    m_moveAllowAction = new QAction(tr("Allow Move"), 0);
    m_moveAllowAction->setCheckable(true);
    m_settingMenu->addAction(m_moveAllowAction);
    m_menuBar->addMenu(m_settingMenu);
    m_moveAllowAction->setChecked(true);
    connect(m_moveAllowAction, SIGNAL(changed()), this, SLOT(on_m_moveAllowAction_changed()));
    m_modeSwitchMenu = new QMenu(tr("Switch Mode"));
    m_calendarSwitchAction = new QAction(tr("Calendar Mode"), 0);
    m_classTableSwitchAction = new QAction(tr("Class Table Mode"), 0);
    m_modeSwitchMenu->addAction(m_calendarSwitchAction);
    connect(m_calendarSwitchAction, SIGNAL(triggered()), this, SLOT(on_m_calendarSwitchAction_triggered()));
    m_modeSwitchMenu->addAction(m_classTableSwitchAction);
    connect(m_classTableSwitchAction, SIGNAL(triggered()), this, SLOT(on_m_classTableSwitch_triggered()));
    m_menuBar->addMenu(m_modeSwitchMenu);
    m_calendarSwitchAction->setDisabled(true);
}

void MainWindow::createPreviewGroupBox() {
    m_previewGroupBox = new QGroupBox(tr("Calendar"));
    m_previewLayout = new QGridLayout;
    m_calendar = new Calendar(m_userName);
    connect(m_calendar, SIGNAL(activated(QDate)), m_calendar, SLOT(addNote(QDate)));
    m_previewLayout->addWidget(m_calendar, 0, 0);
    m_previewGroupBox->setLayout(m_previewLayout);
    m_returnTodayButton = new QPushButton(tr("Today"));
    connect(m_returnTodayButton, SIGNAL(clicked()), this, SLOT(on_m_returnTodayButton_clicked()));
    m_configureButton = new QPushButton(tr("Settings"));
    connect(m_configureButton, SIGNAL(clicked()), this, SLOT(on_m_configureButton_clicked()));
    m_aboutButton = new QPushButton(tr("About"));
    connect(m_aboutButton, SIGNAL(clicked()), this, SLOT(on_m_aboutButton_clicked()));
    m_exitButton = new QPushButton(tr("Quit"));
    connect(m_exitButton, SIGNAL(clicked()), this, SLOT(close()));
    m_exitButton->setIcon(QIcon(":/img/close.png"));
    m_aboutButton->setIcon(QIcon(":/img/author.png"));
    m_returnTodayButton->setIcon(QIcon(":/img/today.png"));
    m_configureButton->setIcon(QIcon(":/img/setting.png"));

    QHBoxLayout *previewButtonLayout = new QHBoxLayout;
    previewButtonLayout->addWidget(m_exitButton);
    previewButtonLayout->addStretch();
    previewButtonLayout->addWidget(m_returnTodayButton);
    previewButtonLayout->addWidget(m_configureButton);
    previewButtonLayout->addWidget(m_aboutButton);
    m_previewLayout->addLayout(previewButtonLayout, 1, 0);
}

void MainWindow::createGeneralOptionGroupBox() {
    m_generalOptionsGroupBox = new QGroupBox(tr("General Options"));
    m_generalOptionsLayout = new QGridLayout;
    m_localeComboBox = new QComboBox;
    int curLocaleIndex = -1;
    int index = 0;
    for (int lang = QLocale::C; lang <= QLocale::LastLanguage; ++lang) {
        QLocale::Language language = static_cast<QLocale::Language>(lang);
        QList<QLocale::Country> countries = QLocale::countriesForLanguage(language);
        for (int i = 0; i < countries.count(); ++i) {
            QLocale::Country country = countries.at(i);
            QString label = QLocale::languageToString(language);
            label += QLatin1Char('/');
            label += QLocale::countryToString(country);
            QLocale _locale(language, country);
            if (this->locale().language() == language && this->locale().country() == country) {
                curLocaleIndex = index;
            }
            m_localeComboBox->addItem(label, _locale);
            ++index;
        }
        if (curLocaleIndex != -1) {
            m_localeComboBox->setCurrentIndex(curLocaleIndex);
        }
    }
    m_localeLabel = new QLabel(tr("Language: "));
    m_localeLabel->setBuddy(m_localeComboBox);
    connect(m_localeComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(on_m_localeComboBox_currentIndexChanged(int)));
    QHBoxLayout *languageOptionLayout = new QHBoxLayout;
    languageOptionLayout->addWidget(m_localeLabel);
    languageOptionLayout->addStretch();
    languageOptionLayout->addWidget(m_localeComboBox);
    m_generalOptionsLayout->addLayout(languageOptionLayout, 0, 0);

    m_selectionModeCheckBox = new QCheckBox(tr("Allow Choice"));
    m_selectionModeCheckBox->setChecked(true);
    connect(m_selectionModeCheckBox, SIGNAL(clicked()), this, SLOT(on_m_selectionModeCheckBox_clicked()));
    m_gridCheckBox = new QCheckBox(tr("Show Grid"));
    m_gridCheckBox->setChecked(true);
    connect(m_gridCheckBox, SIGNAL(clicked()), this, SLOT(on_m_gridCheckBox_clicked()));
    m_navigationBarCheckBox = new QCheckBox(tr("Show Navigation Bar"));
    m_navigationBarCheckBox->setChecked(true);
    connect(m_navigationBarCheckBox, SIGNAL(clicked()), this, SLOT(on_m_navigationBarCheckBox_clicked()));
    QHBoxLayout *optionCheckBoxLayout = new QHBoxLayout;
    optionCheckBoxLayout->addWidget(m_selectionModeCheckBox);
    optionCheckBoxLayout->addWidget(m_gridCheckBox);
    optionCheckBoxLayout->addWidget(m_navigationBarCheckBox);
    m_generalOptionsLayout->addLayout(optionCheckBoxLayout, 1, 0);
    m_moveAllowCheckBox = new QCheckBox(tr("Allow Move"));
    m_moveAllowCheckBox->setChecked(true);
    connect(m_moveAllowCheckBox, SIGNAL(clicked()), this, SLOT(on_m_moveAllowCheckBox_clicked()));
    m_dragAllowCheckBox = new QCheckBox(tr("Allow File Drag"));
    m_dragAllowCheckBox->setChecked(true);
    connect(m_dragAllowCheckBox, SIGNAL(clicked()), this, SLOT(on_m_dragAllowCheckBox_clicked()));
    m_opacityCheckBox = new QCheckBox(tr("Set Opacity"));
    connect(m_opacityCheckBox, SIGNAL(clicked()), this, SLOT(on_m_opacityCheckBox_clicked()));
    m_opacitySlider = new QSlider(Qt::Horizontal);
    m_opacitySlider->setMaximum(100);
    m_opacitySlider->setMinimum(20);
    m_opacitySlider->setValue(80);
    connect(m_opacitySlider, SIGNAL(valueChanged(int)), this, SLOT(on_m_opacitySlider_valueChanged(int)));
    QHBoxLayout *optionCheckBoxLayout2 = new QHBoxLayout;
    optionCheckBoxLayout2->addWidget(m_moveAllowCheckBox);
    optionCheckBoxLayout2->addWidget(m_dragAllowCheckBox);
    optionCheckBoxLayout2->addWidget(m_opacityCheckBox);
    m_generalOptionsLayout->addLayout(optionCheckBoxLayout2, 2, 0);
    QHBoxLayout *opacitySliderBoxLayout = new QHBoxLayout;
    m_exportUserDataButton = new QPushButton(tr("Export"));
    m_exportUserDataButton->setIcon(QIcon(":/img/export.png"));
    connect(m_exportUserDataButton, SIGNAL(clicked()), this, SLOT(on_m_exportUserDataButton_clicked()));
    m_importUserDataButton = new QPushButton(tr("Import"));
    m_importUserDataButton->setIcon(QIcon(":/img/import.png"));
    connect(m_importUserDataButton, SIGNAL(clicked()), this, SLOT(on_m_importUserDataButton_clicked()));
    opacitySliderBoxLayout->addWidget(m_importUserDataButton);
    opacitySliderBoxLayout->addWidget(m_exportUserDataButton);
    opacitySliderBoxLayout->addStretch();
    opacitySliderBoxLayout->addWidget(m_opacitySlider);
    m_opacitySlider->setVisible(false);
    m_generalOptionsLayout->addLayout(opacitySliderBoxLayout, 3, 0);
    m_generalOptionsGroupBox->setLayout(m_generalOptionsLayout);
    m_generalOptionsGroupBox->setHidden(true);
}

void MainWindow::on_m_configureButton_clicked() {
    if (m_generalOptionsGroupBox->isHidden()) {
        m_generalOptionsGroupBox->setHidden(false);
    }
    else {
        m_generalOptionsGroupBox->setHidden(true);
    }
}

void MainWindow::on_m_localeComboBox_currentIndexChanged(int index)
{
    QLocale newLocale(m_localeComboBox->itemData(index).toLocale());
    if(m_calendar->locale() != newLocale) {
        m_calendar->setLocale(newLocale);
        UserManager *usermanager = new UserManager(m_userName, m_calendar);
        usermanager->saveUserData();
        saveSettings();
        qApp->exit(233);
    }
}

void MainWindow::on_m_returnTodayButton_clicked() {
    m_calendar->setSelectedDate(QDate::currentDate());
}

void MainWindow::on_m_aboutButton_clicked() {
    QMessageBox::information(this, tr("Author"), tr("Designed By Zhang Yuhui.\nHints:\n双击对话框添加当日事件\n可以将文件拖入对应的日期格子内\n可以从当日文件列表中拖出文件\n"));
}

void MainWindow::on_m_selectionModeCheckBox_clicked() {
    if (m_selectionModeCheckBox->isChecked()) {
        m_calendar->setSelectionMode(Calendar::SingleSelection);
    }
    else {
        m_calendar->setSelectionMode(Calendar::NoSelection);
    }
}

void MainWindow::on_m_gridCheckBox_clicked() {
    if (m_gridCheckBox->isChecked()) {
        m_calendar->setGridVisible(true);
    }
    else {
        m_calendar->setGridVisible(false);
    }
}

void MainWindow::on_m_navigationBarCheckBox_clicked() {
    if (m_navigationBarCheckBox->isChecked()) {
        m_calendar->setNavigationBarVisible(true);
    }
    else {
        m_calendar->setNavigationBarVisible(false);
    }
}

void MainWindow::on_m_moveAllowCheckBox_clicked() {
    if (m_moveAllowCheckBox->isChecked()) {
        setWindowFlags(Qt::Widget);
        show();
    }
    else {
        setWindowFlags(Qt::FramelessWindowHint | Qt::WindowTransparentForInput);
        show();
    }
}

void MainWindow::on_m_dragAllowCheckBox_clicked() {
    m_calendar->setAcceptDrops(m_dragAllowCheckBox->isChecked());
}

void MainWindow::on_m_opacityCheckBox_clicked() {
    if (m_opacityCheckBox->isChecked()) {
        m_opacitySlider->setVisible(true);
        setWindowOpacity((double)m_opacitySlider->value()/100);
    }
    else {
        m_opacitySlider->setVisible(false);
        setWindowOpacity(1);
    }
}

void MainWindow::on_m_opacitySlider_valueChanged(int value) {
    setWindowOpacity((double)value/100);
}

void MainWindow::on_m_moveAllowAction_changed() {
    if (m_moveAllowAction->isChecked()) {
        setWindowFlags(Qt::Widget);
        show();
    }
    else {
        setWindowFlags(Qt::FramelessWindowHint | Qt::WindowTransparentForInput);
        show();
    }
}

void MainWindow::on_m_exportUserDataButton_clicked() {
    UserManager *userManager = new UserManager(m_userName, m_calendar);
    userManager->saveUserData();
    QString dirPath = QFileDialog::getExistingDirectory();
    if(dirPath.length() == 0) {
        QMessageBox::information(this, tr("Error"), tr("Please choose directory!"));
        return;
    }
    QFile *qFile = new QFile;
    qFile->remove(dirPath + "/" + m_userName + "_files.ini");
    qFile->copy(m_userName + "_files.ini", dirPath + "/" + m_userName + "_files.ini");
    qFile->remove(dirPath + "/" + m_userName + "_colors.ini");
    qFile->copy(m_userName + "_colors.ini", dirPath + "/" + m_userName + "_colors.ini");
    qFile->remove(dirPath + "/" + m_userName + "_things.ini");
    qFile->copy(m_userName + "_things.ini", dirPath + "/" + m_userName + "_things.ini");
    delete qFile;
    QMessageBox::information(this, tr("Export"), tr("Export Completely"));
}

void MainWindow::on_m_importUserDataButton_clicked() {
    QString dirPath = QFileDialog::getExistingDirectory();
    if(dirPath.length() == 0) {
        QMessageBox::information(this, tr("Error"), tr("Please choose directory!"));
        return;
    }
    QFile *qFile = new QFile;
    qFile->remove(m_userName + "_files.ini");
    qFile->copy(dirPath + "/" + m_userName + "_files.ini", m_userName + "_files.ini");
    qFile->remove(m_userName + "_colors.ini");
    qFile->copy(dirPath + "/" + m_userName + "_colors.ini", m_userName + "_colors.ini");
    qFile->remove(m_userName + "_things.ini");
    qFile->copy(dirPath + "/" + m_userName + "_things.ini", m_userName + "_things.ini");
    delete qFile;
    UserManager *userManager = new UserManager(m_userName, m_calendar);
    userManager->readUserData();
    QMessageBox::information(this, tr("Import"), tr("Import Completely"));
}

void MainWindow::on_m_calendarSwitchAction_triggered() {
    this->show();
    m_classTable->hide();
    m_classTableSwitchAction->setEnabled(true);
    m_calendarSwitchAction->setDisabled(true);
}

void MainWindow::on_m_classTableSwitch_triggered() {
    m_classTable = new ClassTable();
    m_classTable->show();
    this->hide();
    m_classTable->show();
    m_calendarSwitchAction->setEnabled(true);
    m_classTableSwitchAction->setDisabled(true);
}
