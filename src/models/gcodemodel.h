#if !defined(GCODEMODEL_H)
#define GCODEMODEL_H

#include "../widgets/gcodeeditor.h"
#include "../parser/gcodeparser.h"


class GCodeModel {
public:
    struct GCodeItem
    {
        enum States { Nothing, InQueue, Sent, Processed, Skipped };

        QString command;
        char state;
        QString response;
        int line;
        QStringList args;
    };
    
    GCodeModel();
    void setEditor(GCodeEditor *editor);
    bool openFile(QString fileName);
    bool saveFile(QString fileName);

    int lines() const;
    QString command(int line) const;
    int gpCommandNumber(int line) const;
    QList<QString> args(int line) const;

    void setState(int line, GCodeItem::States state);
    void setResponse(int line, QString response);
    void setArgs(int line, QList<QString> args);

    void setCurrentLine(int line);

    GcodeParser* getGCodeParser();
private:
    void rebuildModel();

    
    GCodeEditor *editor;
    GcodeParser gp;
    QVector<GCodeItem> items;
};

#endif
