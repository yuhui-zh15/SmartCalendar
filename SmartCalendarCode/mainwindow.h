#ifndef MAINCALENDARWIDGET_H
#define MAINCALENDARWIDGET_H
#include <QMainWindow>
#include <QGroupBox>
#include <QPushButton>
#include <QLayout>
#include <QLabel>
#include <QComboBox>
#include <QCheckBox>
#include <QDateEdit>
#include <QSlider>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include "calendar.h"
#include "usermanager.h"
#include "classtable.h"

class MainWindow: public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(const QString& username, QWidget* parent = 0);
    ~MainWindow();
    void createPreviewGroupBox();
    void createGeneralOptionGroupBox();
    void createMenuBar();
    void saveSettings();
    void readSettings();
    void beautifyCalendar();

protected:
    void closeEvent(QCloseEvent *event);

private:
    //(0, 0)
    Calendar *m_calendar;
    QGroupBox *m_previewGroupBox;
    QGridLayout *m_previewLayout;
    QPushButton *m_returnTodayButton;
    QPushButton *m_configureButton;
    QPushButton *m_aboutButton;
    QPushButton *m_exitButton;
    //(1, 0)
    QGroupBox* m_generalOptionsGroupBox;
    QGridLayout *m_generalOptionsLayout;
    QLabel* m_localeLabel;
    QComboBox* m_localeComboBox;
    QCheckBox* m_selectionModeCheckBox;
    QCheckBox* m_gridCheckBox;
    QCheckBox* m_navigationBarCheckBox;
    QCheckBox* m_moveAllowCheckBox;
    QCheckBox* m_dragAllowCheckBox;
    QCheckBox* m_opacityCheckBox;
    QSlider* m_opacitySlider;
    QPushButton *m_exportUserDataButton;
    QPushButton *m_importUserDataButton;
    //menuBar
    QMenuBar* m_menuBar;
    QMenu* m_settingMenu;
    QAction* m_moveAllowAction;
    QMenu* m_modeSwitchMenu;
    QAction* m_calendarSwitchAction;
    QAction* m_classTableSwitchAction;

    QString m_userName;
    ClassTable* m_classTable;

protected slots:
    void on_m_configureButton_clicked();
    void on_m_returnTodayButton_clicked();
    void on_m_aboutButton_clicked();
    void on_m_selectionModeCheckBox_clicked();
    void on_m_gridCheckBox_clicked();
    void on_m_navigationBarCheckBox_clicked();
    void on_m_moveAllowCheckBox_clicked();
    void on_m_dragAllowCheckBox_clicked();
    void on_m_opacityCheckBox_clicked();
    void on_m_localeComboBox_currentIndexChanged(int index);
    void on_m_opacitySlider_valueChanged(int value);
    void on_m_moveAllowAction_changed();
    void on_m_exportUserDataButton_clicked();
    void on_m_importUserDataButton_clicked();
    void on_m_calendarSwitchAction_triggered();
    void on_m_classTableSwitch_triggered();

};

#endif
