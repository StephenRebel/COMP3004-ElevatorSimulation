#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QComboBox>
#include <QPushButton>
#include <QListWidget>
#include <QSpinBox>
#include <QScrollArea>
#include <QVector>
#include <QTextEdit>
#include <QStackedWidget>
#include <QDebug>
#include <QScrollBar>

#include "SimulationController.h"

namespace Ui { class MainWindow; }

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow* ui;
    QVBoxLayout* passengerLayout;
    QWidget* passengerContainer;
    QVector<QWidget*> passengerRows; // Track dynamically created rows

    QWidget* consoleScroll;
    QVBoxLayout* consoleLayout; // Frame for the output console

    SimulationController* controller = nullptr;

    void switchToSimulationPage();  // Function to switch pages in the stacked widget

public slots:
    void onLogMessage(const std::string& message);

// Slots to recieve and manipulation use interaction
private slots:
    void on_safetyCheckbox_stateChanged(int state);
    void updatePassengerRows(int count);
    void onStartClick();
    void onPauseClick();
    void onResumeClick();
    void onStopClick();
    void onResetClick();
    void onExitClick();

    void appendMessageConsole(const std::string& text);
};

#endif // MAINWINDOW_H
