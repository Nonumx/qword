# qword
使用ActiveQt操作Word模板生成报告

## 使用方法

```c++
// 必须在QApplication中使用（QCoreApplication不行）
QApplication app(argc, argv);

// 在中文版本Windows操作系统中
// 可能需要QStringLiteral("D:/模板.docx")
// 来兼容MSVC编译器使用GBK字符集编译的情况
QWord word(R"(D:\模板.docx)");

word["Bookmark1"] = "abcabc";

QWordTable table1;
table1.SetHorizontalHeaders({"Col1", "Col2", "Col3"});
table1.SetContent({
    {"aaa", "aaa", "aaa"},
    {"bbb", "bbb", "bbb"},
    {"ccc", "ccc", "ccc"},
});

word["BoookmarkTable1"] = table1;

word.Save(R"(D:\生成报告.docx)");
```