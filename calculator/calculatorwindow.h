#ifndef CALCULATORWINDOW_H
#define CALCULATORWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QSplitter>
#include <QtGui/QGraphicsView>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QTableWidget>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include <QtGui/QStatusBar>
#include "calculator/calculatorengine.h"
#include "calculator/calculatorgridview.h"

class CalculatorWindow : public QMainWindow
{
    Q_OBJECT

public:
    CalculatorWindow(QWidget *parent = 0);
    ~CalculatorWindow();

private:
    bool rightOperator;
    void operation(const QString &, int);
    void showError(const QString &);
    void historyInsert(const QString &, const QString &);

private slots:
    void parseInput();
    void cellClicked(int, int);
    void clearClicked();

    void clickedGrid();
    void clickedVector();
    void clickedWire();
    void clickedInput();
    void clickedOutput();
    void clickedInverter();
    void clickedGate();
    void clickedClock();
    void clickedFlipFlop();

    void clickedTick();
    void clickedReset();
    void clickedAdd();
    void clickedSub();
    void clickedAnd();
    void clickedOr();
    void clickedNot();
    void clickedInsert();
    void clickedRemove();
    void clickedResult();

private:
    QTableWidget *history;
    QPlainTextEdit *current;
    QPushButton *clearButton;
    QPlainTextEdit *input;
    CalculatorGridView *gridView;
    QPushButton *gridButton;
    QPushButton *vectorButton;
    QPushButton *wireButton;
    QPushButton *inputButton;
    QPushButton *outputButton;
    QPushButton *inverterButton;
    QPushButton *gateButton;
    QPushButton *clockButton;
    QPushButton *flipflopButton;
    QSpacerItem *spacer;
    QPushButton *tickButton;
    QPushButton *resetButton;
    QPushButton *addButton;
    QPushButton *subButton;
    QPushButton *insertButton;
    QPushButton *removeButton;
    QPushButton *andButton;
    QPushButton *orButton;
    QPushButton *notButton;
    QPushButton *resultButton;
    CalculatorEngine *engine;

};

#endif // CALCULATORWINDOW_H
