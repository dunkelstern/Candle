#if !defined(GCODEEDITOR_H)
#define GCODEEDITOR_H

#include <functional>

#include "Qsci/qsciscintilla.h"

class GCodeEditor : public QsciScintilla {
    Q_OBJECT

    static constexpr int CURRENT_LINE_INDICATOR = 8;
    
    QColor currentLineBackgroundColor;
    
public:
    GCodeEditor(QWidget *parent=0);

    bool openFile(QString fileName);
    bool saveFile(QString fileName);
    QList<QString> textLines() const;
    void setCurrentLine(int line);

private slots:
    void ensureSingleLineIndicator(int indicator_number);

private:

    int indicatorStart(int indicator_number, int pos);
    int indicatorEnd(int indicator_number, int pos);
    int indicatorAllOnFor(int pos);
    void removeIndicatorRanges(int indicator_number);
    void setIndicatorOnLine(int indicator_number, int line);
    void clearIndicatorRange(int indicator_number, int start, int end);
    void forAllIndicatorRanges(int indicator_number, std::function<bool(int, int)> func);

    int lastLinePos(int line) const;
};

#endif
