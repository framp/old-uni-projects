QT       += core gui svg

TEMPLATE = app

SOURCES += main.cpp \
        logic/grid.cpp \
        logic/input.cpp \
        logic/cell.cpp \
        logic/wire.cpp \
        logic/output.cpp \
        logic/inverter.cpp \
        logic/gate.cpp \
        logic/clock.cpp \
        logic/flipflop.cpp \
        logic/vector.cpp \
        logic/base.cpp \
        calculator/calculatorwindow.cpp \
        calculator/calculatorengine.cpp \
        calculator/calculatorgridview.cpp \
        utilities/validator.cpp

HEADERS += logic/grid.h \
        logic/input.h \
        logic/cell.h \
        logic/wire.h \
        logic/output.h \
        logic/inverter.h \
        logic/gate.h \
        logic/clock.h \
        logic/flipflop.h \
        logic/vector.h \
        logic/base.h \
        calculator/calculatorwindow.h \
        calculator/calculatorengine.h \
        calculator/calculatorgridview.h \
        utilities/validator.h \
        utilities/cispointer.h

RESOURCES += \
    svg.qrc

OTHER_FILES += \
    utilities/samples.txt
