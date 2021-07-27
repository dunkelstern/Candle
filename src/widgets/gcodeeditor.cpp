
#include "gcodeeditor.h"

#include <math.h>
#include <QList>
#include <QFile>
#include <qcolor.h>



GCodeEditor::GCodeEditor(QWidget *parent) :
    QsciScintilla(parent),
    currentLineBackgroundColor(QColorConstants::Yellow) {
    setReadOnly(true);

    indicatorDefine(QsciScintilla::FullBoxIndicator, CURRENT_LINE_INDICATOR);
    setIndicatorForegroundColor(currentLineBackgroundColor,	CURRENT_LINE_INDICATOR);
    setIndicatorDrawUnder(true, CURRENT_LINE_INDICATOR);

    connect(this, &QsciScintilla::linesChanged, this, [this]() { ensureSingleLineIndicator(CURRENT_LINE_INDICATOR); });
}

bool GCodeEditor::openFile(QString fileName) {
   QFile fp(fileName);
   if(!fp.open(QIODevice::ReadOnly)) {
       return false;
   }
   
   read(&fp);

   int maxDigits = int(log10(lines() + 1)) + 2;
   setMarginWidth(0, QString(maxDigits, '9'));

   return true;
}

bool GCodeEditor::saveFile(QString fileName) {
   QFile fp(fileName);
   if(!fp.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
       return false;
   }
   
   write(&fp);

   return true;
}


QList<QString> GCodeEditor::textLines() const {
   QList<QString> result;

   for(int i = 0 ; i < lines() ; i++) {
       result.append(text(i));
   }

   return result;
}

/**
 * @brief Sets the current line
 *
 * Sets the current line. This makes sure the current line is visible and highlighted.
 */
void GCodeEditor::setCurrentLine(int line) {
    if(line < lines()) {
        setFirstVisibleLine(line - 5 > 0 ? line - 5 : 0); // Make sure the current line is visible on the screen
        removeIndicatorRanges(CURRENT_LINE_INDICATOR);
        setIndicatorOnLine(CURRENT_LINE_INDICATOR, line);
    }
}

/**
 * @brief Ensure that and indicator spans exactly one line, adjust it if needed
 *
 * This iterates over the indicator ranges of a given indicator and makes sure that it spans exactly from the start to the end of a line. If it doesn't, it adjusts it so that it spans the line that the beginning of the range is in.
 *
 * @param[in] indicator_number The indicator to be adjusted.
 */
// number of lines changed, 
void GCodeEditor::ensureSingleLineIndicator(int indicator_number) {
    forAllIndicatorRanges(indicator_number, [indicator_number, this](int start, int end) -> bool {
        // line numbers and character index from the start of the line for both start and end of the range
        int start_line, start_index;
        int end_line, end_index;
        
        lineIndexFromPosition(start, &start_line, &start_index);
        lineIndexFromPosition(end - 1, &end_line, &end_index);

        // re-do the indicator range if the indicator no longer corresponds to exactly one line:
        if(start_line != end_line or // start and end are on different lines
            start_index != 0 or // start is not at the beginning of the line
            end_index != lastLinePos(end_line) // end is not at the end of the line
            ) {

            clearIndicatorRange(indicator_number, start, end);
            setIndicatorOnLine(indicator_number, start_line);
        }
        return false;
    });

}


/**
 * @brief Call indicatorStart
 *
 * Calls the low level scintilla function SCI_INDICATORSTART.
 */
int GCodeEditor::indicatorStart(int indicator_number, int pos) {
    return SendScintilla(SCI_INDICATORSTART, indicator_number, pos);
}

/**
 * @brief Call indicatorEnd
 *
 * Calls the low level scintilla function SCI_INDICATOREND.
 */
int GCodeEditor::indicatorEnd(int indicator_number, int pos) {
    return SendScintilla(SCI_INDICATOREND, indicator_number, pos);
}

/**
 * @brief Call indicatorAllOnFor
 *
 * Calls the low level scintilla function SCI_INDICATORALLONFOR which is used for iterating over indicator ranges.
 */
int GCodeEditor::indicatorAllOnFor(int pos) {
    return SendScintilla(SCI_INDICATORALLONFOR, pos);
}

/**
 * @brief Remove all indicator ranges belonging to a given indicator
 *
 * @param[in] indicator_number The indicator to remove all ranges for
 */
void GCodeEditor::removeIndicatorRanges(int indicator_number) {
    forAllIndicatorRanges(indicator_number, [indicator_number, this](int start, int end) -> bool {
        clearIndicatorRange(indicator_number, start, end);
        
        return false;
    });
}

/**
 * @brief Add an indicator to a line
 *
 * If the line does not exit, do nothing.
 *
 * @param[in] indicator_number The indicator to set
 * @param[in] line The line to set it on
 */
void GCodeEditor::setIndicatorOnLine(int indicator_number, int line) {
    int lastpos = lastLinePos(line);
    if(lastpos >= 0) {
        fillIndicatorRange(line, 0, line, lastpos, indicator_number);
    }
}

/**
 * @brief Remove an indicator from a range of characters
 *
 * @param[in] indicator_number The indicator to remove
 * @param[in] start The byte position of the start of the range to remove
 * @param[in] end The byte position of the end of the range to remove
 */
void GCodeEditor::clearIndicatorRange(int indicator_number, int start, int end) {
    SendScintilla(SCI_SETINDICATORCURRENT, indicator_number);
    SendScintilla(SCI_INDICATORCLEARRANGE, start, end - start);
}

/**
 * @brief Iterator over all ranges of a given indicator
 *
 * @param[in] indicator_number The indicator whose ranges to iterate over
 * @param[in] func The function(int start, int end) to call with the start and end byte positions of each range
 */
void GCodeEditor::forAllIndicatorRanges(int indicator_number, std::function<bool(int, int)> func) {

    int textLength = length();
    int bitmapFlag = (1 << indicator_number);

    int startPos = 0;
    int endPos = 0;

    do {
        startPos = indicatorStart(indicator_number, endPos);
        endPos = indicatorEnd(indicator_number, startPos);

        // Is this range filled with our indicator?
        int bitmap = indicatorAllOnFor(startPos);
        int filled = ((bitmapFlag & bitmap) == bitmapFlag);
        if (filled) {
            // Do stuff with indicator range
            bool done = func(startPos, endPos);
            if(done)
                break;
        }
    } while (endPos != 0 && endPos < textLength);
}

/**
 * @brief Return the byte position of the last character on a line
 *
 * @param[in] line The line number
 * @returns The byte position of the last character on the line or -1 if there is no such line
 */
int GCodeEditor::lastLinePos(int line) const {
    int len = lineLength(line);
    return len > 0 ? len - 1 : len;
}
