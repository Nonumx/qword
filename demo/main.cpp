#include "qword.h"
#include <QApplication>
#include <QTimer>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QWord word(R"(D:\NewProjects\qword\demo\模型标定报告.docx)");

    word["ArgumentList"] = "abc";

    word["ExperimentName"] = "";
    word["ExperimentResultName"] = "";
    word["SimulationSetting"] = "";

    // word["ArgumentData"] = QWordTable();

    word["EvalDataPath"] = "";

    // word["ArgumentEval"] = QWordTable();

    // word["EvalValue"] = QWordTable();

    // word["EvalResult"] = QWordTable();

    word.Save(R"(D:\NewProjects\qword\demo\模型标定报告_生成.docx)");

    return QApplication::exec();
}