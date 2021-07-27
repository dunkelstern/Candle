#include "gcodemodel.h"

GCodeModel::GCodeModel() {}

void GCodeModel::setEditor(GCodeEditor *editor) {
    this->editor = editor;
}

bool GCodeModel::openFile(QString fileName) {
    if(editor->openFile(fileName)) {
        rebuildModel();
        return true;
    }
    return false;
}

bool GCodeModel::saveFile(QString fileName) {
    return editor->saveFile(fileName);
}

void GCodeModel::rebuildModel() {
    // Prepare parser
    /*
    gp.setTraverseSpeed(m_settings->rapidSpeed());
    if (m_codeDrawer->getIgnoreZ())
        gp.reset(QVector3D(qQNaN(), qQNaN(), 0));
    */
    QString command;
    QString stripped;
    QString trimmed;
    QList<QString> args;

    items.clear();
    items.reserve(lines());

    for(int i = 0 ; i < lines() ; i++) {
        command = this->editor->text(i);

        // Trim command
        trimmed = command.trimmed();

        GCodeItem item;
        if (!trimmed.isEmpty()) {
            // Split command
            stripped = GcodePreprocessorUtils::removeComment(command);
            args = GcodePreprocessorUtils::splitCommand(stripped);

//            PointSegment *ps = gp.addCommand(args);
            gp.addCommand(args);

    //        if (ps && (qIsNaN(ps->point()->x()) || qIsNaN(ps->point()->y()) || qIsNaN(ps->point()->z())))
    //                   qDebug() << "nan point segment added:" << *ps->point();

            
            item.command = trimmed;
            item.state = GCodeItem::InQueue;
            item.line = gp.getCommandNumber();
            item.args = args;
        } else {
            item.command = QString();
            item.state = GCodeItem::Nothing;
            item.line = i;
            item.args = QStringList();
        }
        items.append(item);
        /*
                if (progress.isVisible() && (data.count() % PROGRESSSTEP == 0))
        { progress.setValue(progress.maximum() - data.count());
                    qApp->processEvents();
                    if (progress.wasCanceled()) break;
                }
        */        
    }

    
}

int GCodeModel::lines() const {
    int l = editor->lines();
    if(l < 10 && editor->text().trimmed() == "") {
        return 0;
    } else {
        return l;
    }
}

QString GCodeModel::command(int line) const {
    return items[line].command;
}

int GCodeModel::gpCommandNumber(int line) const {
    return items[line].line;
}

QList<QString> GCodeModel::args(int line) const {
    return items[line].args;
}


void GCodeModel::setState(int line, GCodeItem::States state) {
    if(line < editor->lines()) {
        items[line].state = state;
    }
}

void GCodeModel::setResponse(int line, QString response) {
    if(line < editor->lines()) {
        items[line].response = response;
    }
}

void GCodeModel::setArgs(int line, QList<QString> args) {
    if(line < editor->lines()) {
        items[line].args = args;
    }
}



void GCodeModel::setCurrentLine(int line) {
    editor->setCurrentLine(line);
}

GcodeParser* GCodeModel::getGCodeParser() {
    return &gp;
}
