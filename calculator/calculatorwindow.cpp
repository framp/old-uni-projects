#include "calculator/calculatorwindow.h"

CalculatorWindow::CalculatorWindow(QWidget *parent) :
    QMainWindow(parent), rightOperator(false)
{
    resize(800,400);
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *area = new QVBoxLayout(centralWidget);
    QSplitter *display = new QSplitter(centralWidget);
    QWidget *headContainer = new QWidget();
    QVBoxLayout *head = new QVBoxLayout();
    history = new QTableWidget(0, 2, centralWidget);
    history->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    history->verticalHeader()->hide();
    history->setAlternatingRowColors(true);
    QHBoxLayout *currentLayout = new QHBoxLayout();
    current = new QPlainTextEdit(centralWidget);
    QFontMetrics m(current->font());
    current->setFixedHeight(2 * m.lineSpacing()+15);
    current->setReadOnly(true);
    current->setDisabled(false);
    clearButton = new QPushButton(centralWidget);
    clearButton->setFixedHeight(2 * m.lineSpacing()+15);
    clearButton->setFixedWidth(50);
    currentLayout->addWidget(current);
    currentLayout->addWidget(clearButton);
    input = new QPlainTextEdit(centralWidget);
    input->setFixedHeight(2 * m.lineSpacing()+15);
    input->setMaximumBlockCount(2);
    input->setFocus();
    head->addWidget(history);
    head->addLayout(currentLayout);
    head->addWidget(input);
    headContainer->setLayout(head);

    gridView = new CalculatorGridView(centralWidget);
    display->addWidget(headContainer);
    display->addWidget(gridView);
    display->setSizes(QList<int>() << 1 << 1 );

    QHBoxLayout *keyboard = new QHBoxLayout();
    QGridLayout *objects = new QGridLayout();
    gridButton = new QPushButton(centralWidget);
    vectorButton = new QPushButton(centralWidget);
    wireButton = new QPushButton(centralWidget);
    inputButton = new QPushButton(centralWidget);
    outputButton = new QPushButton(centralWidget);
    inverterButton = new QPushButton(centralWidget);
    gateButton = new QPushButton(centralWidget);
    clockButton = new QPushButton(centralWidget);
    flipflopButton = new QPushButton(centralWidget);
    objects->addWidget(gridButton, 1, 0);
    objects->addWidget(vectorButton, 1, 1);
    objects->addWidget(wireButton, 1, 2);
    objects->addWidget(inputButton, 3, 0);
    objects->addWidget(outputButton, 3, 1);
    objects->addWidget(inverterButton, 3, 2);
    objects->addWidget(gateButton, 5, 0);
    objects->addWidget(clockButton, 5, 1);
    objects->addWidget(flipflopButton, 5, 2);

    spacer = new QSpacerItem(10, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

    QGridLayout *operators = new QGridLayout();
    tickButton = new QPushButton(centralWidget);
    resetButton = new QPushButton(centralWidget);
    addButton = new QPushButton(centralWidget);
    subButton = new QPushButton(centralWidget);
    insertButton = new QPushButton(centralWidget);
    removeButton = new QPushButton(centralWidget);
    andButton = new QPushButton(centralWidget);
    orButton = new QPushButton(centralWidget);
    notButton = new QPushButton(centralWidget);
    resultButton = new QPushButton(centralWidget);
    operators->addWidget(tickButton, 0, 0);
    operators->addWidget(resetButton, 0, 2);
    operators->addWidget(addButton, 1, 0);
    operators->addWidget(subButton, 1, 2);
    operators->addWidget(insertButton, 2, 0);
    operators->addWidget(removeButton, 2, 2);
    operators->addWidget(andButton, 3, 0);
    operators->addWidget(orButton, 3, 2);
    operators->addWidget(notButton, 4, 0);
    operators->addWidget(resultButton, 4, 2);
    keyboard->addLayout(objects);
    keyboard->addItem(spacer);
    keyboard->addLayout(operators);
    area->addWidget(display);
    area->addLayout(keyboard);

    connect(history, SIGNAL(cellClicked(int, int)), this, SLOT(cellClicked(int, int)));
    connect(clearButton, SIGNAL(clicked()), this, SLOT(clearClicked()));
    connect(input, SIGNAL(textChanged()), this, SLOT(parseInput()));

    connect(gridButton, SIGNAL(clicked()), this, SLOT(clickedGrid()));
    connect(vectorButton, SIGNAL(clicked()), this, SLOT(clickedVector()));
    connect(wireButton, SIGNAL(clicked()), this, SLOT(clickedWire()));
    connect(inputButton, SIGNAL(clicked()), this, SLOT(clickedInput()));
    connect(outputButton, SIGNAL(clicked()), this, SLOT(clickedOutput()));
    connect(inverterButton, SIGNAL(clicked()), this, SLOT(clickedInverter()));
    connect(gateButton, SIGNAL(clicked()), this, SLOT(clickedGate()));
    connect(clockButton, SIGNAL(clicked()), this, SLOT(clickedClock()));
    connect(flipflopButton, SIGNAL(clicked()), this, SLOT(clickedFlipFlop()));

    connect(tickButton, SIGNAL(clicked()), this, SLOT(clickedTick()));
    connect(resetButton, SIGNAL(clicked()), this, SLOT(clickedReset()));
    connect(addButton, SIGNAL(clicked()), this, SLOT(clickedAdd()));
    connect(subButton, SIGNAL(clicked()), this, SLOT(clickedSub()));
    connect(andButton, SIGNAL(clicked()), this, SLOT(clickedAnd()));
    connect(orButton, SIGNAL(clicked()), this, SLOT(clickedOr()));
    connect(notButton, SIGNAL(clicked()), this, SLOT(clickedNot()));
    connect(insertButton, SIGNAL(clicked()), this, SLOT(clickedInsert()));
    connect(removeButton, SIGNAL(clicked()), this, SLOT(clickedRemove()));
    connect(resultButton, SIGNAL(clicked()), this, SLOT(clickedResult()));

    setWindowTitle("Logic Circuits");
    clearButton->setText("X");
    gridButton->setText("Grid");
    vectorButton->setText("Vector");
    wireButton->setText("Wire");
    QStringList columns = QStringList("Operation") << "Result";
    history->setHorizontalHeaderLabels(columns);
    inputButton->setText("Input");
    outputButton->setText("Output");
    inverterButton->setText("Inverter");
    gateButton->setText("Gate");
    clockButton->setText("Clock");
    flipflopButton->setText("Flip Flop");
    tickButton->setText("Tick");
    resetButton->setText("Reset");
    resultButton->setText("=");
    addButton->setText("+");
    subButton->setText("-");
    insertButton->setText("<<");
    removeButton->setText(">>");
    andButton->setText("&&");
    orButton->setText("|");
    notButton->setText("!");

    engine = new CalculatorEngine();

    parseInput();
}

void CalculatorWindow::operation(const QString &op, int n)
{
    string expression = input->toPlainText().trimmed().toStdString(),
           error = "";
    if (expression.length()>0) {
        string added = engine->addObject(expression, error);
        if (error!="") {
            showError(QString::fromStdString(error));
            return;
        }
        current->setPlainText(current->toPlainText() + QString::fromStdString(added) + " ");
    }
    bool operatorSet = false;
    if (!engine->isReady()) {
        if (engine->setOperator(op.toStdString(), n)) {
            operatorSet = true;
            current->setPlainText(current->toPlainText() + " " + op + " ");
            input->setPlainText("");
        }
    }
    if (engine->isReady()) {
        CISpointer<Base> result = engine->computeResult(error);
        gridView->render(result);
        string resultString = result->toString();
        engine->clear();
        if (error!="")
            resultString = error;
        historyInsert(current->toPlainText(), QString::fromStdString(resultString));
        if (error!="") {
            showError(QString::fromStdString(error));

            input->setPlainText("");
            current->setPlainText("");
            return;
        }
        if (n==1) {
            input->setPlainText(QString::fromStdString(resultString));
            current->setPlainText("");
        } else {
            input->setPlainText("");
            string added = engine->addObject(resultString, error);
            if (error!="") {
                current->setPlainText("");
                showError(QString::fromStdString(error));
                return;
            }
            current->setPlainText(QString::fromStdString(added));
        }
        if (!operatorSet)
            operation(op, n);
    }
}

void CalculatorWindow::showError(const QString &error)
{
    statusBar()->showMessage("Error: " + error);
}

void CalculatorWindow::historyInsert(const QString &operation, const QString &result)
{
    if (operation[operation.length()-1]=='=')
        return;
    history->insertRow(history->rowCount());
    history->setItem(history->rowCount()-1, 0, new QTableWidgetItem(operation));
    history->setItem(history->rowCount()-1, 1, new QTableWidgetItem(result));
    history->resizeRowToContents(history->rowCount()-1);
    history->scrollToBottom();

}

void CalculatorWindow::parseInput()
{
    QString type = QString::fromStdString(
                       engine->getType(input->toPlainText().toStdString())
                   );
    statusBar()->showMessage("Type: " + type);
}


void CalculatorWindow::cellClicked(int r, int c)
{
    if (input->toPlainText()=="" && c==1)
        input->setPlainText(history->item(r,c)->text());
}

void CalculatorWindow::clearClicked()
{
    current->setPlainText("");
    engine->clear();
}

void CalculatorWindow::clickedGrid()
{
    input->setPlainText("[10,10,0,[]]");
}
void CalculatorWindow::clickedVector()
{
    input->setPlainText("Vector(0,0)");
}
void CalculatorWindow::clickedWire()
{
    input->setPlainText("Wire(" + gridView->selected() + ",0)");
}
void CalculatorWindow::clickedInput()
{
    input->setPlainText("Input(" + gridView->selected() + ",1)");
}
void CalculatorWindow::clickedOutput()
{
    input->setPlainText("Output(" + gridView->selected() + ",0)");
}
void CalculatorWindow::clickedInverter()
{
    input->setPlainText("Inverter(" + gridView->selected() + ",0)");
}
void CalculatorWindow::clickedGate()
{
    input->setPlainText("Gate(" + gridView->selected() + ",0,&)");
}
void CalculatorWindow::clickedClock()
{
    input->setPlainText("Clock(" + gridView->selected() + ",0,0,0)");
}
void CalculatorWindow::clickedFlipFlop()
{
    input->setPlainText("FlipFlop(" + gridView->selected() + ",0)");
}

void CalculatorWindow::clickedTick()
{
    operation("TICK", 1);
}
void CalculatorWindow::clickedReset()
{
    operation("RESET", 1);
}
void CalculatorWindow::clickedResult()
{
    operation("=", 1);
}
void CalculatorWindow::clickedAdd()
{
    operation("+", 2);
}
void CalculatorWindow::clickedSub()
{
    operation("-", 2);
}
void CalculatorWindow::clickedInsert()
{
    operation("<<", 2);
}
void CalculatorWindow::clickedRemove()
{
    operation(">>", 2);
}
void CalculatorWindow::clickedAnd()
{
    operation("&", 2);
}
void CalculatorWindow::clickedOr()
{
    operation("|", 2);
}
void CalculatorWindow::clickedNot()
{
    operation("!", 1);
}

CalculatorWindow::~CalculatorWindow()
{
    delete engine;
}
