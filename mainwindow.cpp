#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // Create container for passenger inputs, allows adding rows and removing dynamically maintaining layout.
    passengerContainer = new QWidget(this);
    passengerLayout = new QVBoxLayout(passengerContainer);
    passengerContainer->setLayout(passengerLayout);

    // Wrap the layout in a scrollable area
    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(passengerContainer);
    ui->passengerEditorFrame->layout()->addWidget(scrollArea);

    // Get the console setup
    consoleScroll = new QWidget(ui->consoleScrollArea);
    consoleLayout = new QVBoxLayout(consoleScroll);
    consoleScroll->setLayout(consoleLayout);

    ui->consoleScrollArea->setWidgetResizable(true); // Figure out this stupid scrolling console later, I don't know why but it won't scroll just squeeze everythig and is a piece of trash.
    ui->consoleScrollArea->setWidget(consoleScroll);

    // Connect passengersInput QSpinBox to update function
    connect(ui->passengersInput, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &MainWindow::updatePassengerRows);

    // Connect start button to onStartClick function
    connect(ui->startButton, &QPushButton::clicked, this, &MainWindow::onStartClick);

    // Conect pause button
    connect(ui->pauseButton, &QPushButton::clicked, this, &MainWindow::onPauseClick);
    connect(ui->resumeButton, &QPushButton::clicked, this, &MainWindow::onResumeClick);
    connect(ui->stopButton, &QPushButton::clicked, this, &MainWindow::onStopClick);
    connect(ui->resetButton, &QPushButton::clicked, this, &MainWindow::onResetClick);
    connect(ui->exitButton, &QPushButton::clicked, this, &MainWindow::onExitClick);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::appendMessageConsole(const std::string& text) {
    QLabel* newMessage = new QLabel(QString::fromStdString(text));
    newMessage->setWordWrap(true);

    consoleLayout->addWidget(newMessage);
}

void MainWindow::onLogMessage(const std::string& message) {
    appendMessageConsole(message);
}

void MainWindow::on_safetyCheckbox_stateChanged(int state)
{
    // Enable/disable the safety event planner section based on checkbox state
    ui->safetyFrame->setEnabled(state == Qt::Checked);
}

void MainWindow::updatePassengerRows(int count)
{
    // Remove excess rows if passengersInput decreased
    while (passengerRows.size() > count) {
        QWidget *rowWidget = passengerRows.takeLast();
        passengerLayout->removeWidget(rowWidget);
        delete rowWidget;
    }

    // Add new rows if passengersInput increased
    while (passengerRows.size() < count) {
        QWidget *rowWidget = new QWidget(this);
        QHBoxLayout *rowLayout = new QHBoxLayout(rowWidget);

        // Passenger label
        int passengerIndex = passengerRows.size() + 1;
        QLabel *label = new QLabel(QString("Passenger %1").arg(passengerIndex), rowWidget);

        // JSON Input to define passenger behaviour
        QTextEdit *jsonInput = new QTextEdit(rowWidget);
        jsonInput->setPlaceholderText("Enter JSON here...");

        rowLayout->addWidget(label);
        rowLayout->addWidget(jsonInput);
        rowWidget->setLayout(rowLayout);

        // Store reference and add to UI
        passengerRows.append(rowWidget);
        passengerLayout->addWidget(rowWidget);
    }
}

void MainWindow::onStartClick() {
    // Collect input from the UI and pass to simulation creator
    int numFloors = ui->floorsInput->value();
    int numElevators = ui->elevatorsInput->value();
    int numPassengers = ui->passengersInput->value();

    // Passenger JSON collection
    std::vector<std::string> passengersJson;
    for (QWidget* rowWidget : passengerRows) {
        QTextEdit* jsonInput = rowWidget->findChild<QTextEdit*>();
        if (jsonInput) {
            passengersJson.push_back(jsonInput->toPlainText().toStdString());
        }
    }

    // Get controller, will validate passed data in here returning a controller or nullptr in fail
    controller = SimulationController::createController(numFloors, numElevators, numPassengers, passengersJson);
    if (controller) {
        connect(controller, &SimulationController::logToConsoleSignal, this, &MainWindow::onLogMessage);
        // Successfully created controller, now switch to the simulation page
        switchToSimulationPage();
        controller->startSimulation();
    } else {
        qInfo("Error: Creating the simulation controller failed.");
    }
}

void MainWindow::switchToSimulationPage() {
    // Switch to the second page in the stacked widget (simulation page)
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::onPauseClick() {
    ui->resumeButton->setEnabled(true);
    ui->pauseButton->setDisabled(true);

    controller->pauseSimulation();
}

void MainWindow::onResumeClick() {
    ui->resumeButton->setDisabled(true);
    ui->pauseButton->setEnabled(true);

    controller->resumeSimulation();
}

void MainWindow::onStopClick() {
    ui->resumeButton->setDisabled(true);
    ui->pauseButton->setDisabled(true);
    ui->exitButton->setEnabled(true);
    ui->resetButton->setEnabled(true);

    // Implement some controller stop or pause
}

void MainWindow::onResetClick() {

}

void MainWindow::onExitClick() {
    exit(0);
}
