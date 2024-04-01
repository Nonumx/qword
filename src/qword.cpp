#include "qword.h"
#include <QDebug>
#include <QFileInfo>

const QString kWordApplication = "Word.Application";

// 从第一列开始 非0
constexpr int kTableColBegin = 1;
// 表格从第二行开始 第一行是表头
constexpr int kTableRowBegin = 2;

QWord::QWord(QObject *parent)
    : QAxObject(kWordApplication, parent), m_activeDoc(nullptr),
      m_currentBookmark(nullptr)
{
}

QWord::QWord(const QString &path, QObject *parent) : QWord(parent)
{
    Open(path);
}

bool QWord::Open(const QString &path)
{
    if (!QFileInfo::exists(path))
    {
        return false;
    }

    m_path = path;

    auto *documents = querySubObject("Documents");
    if (!documents)
    {
        return false;
    }

    documents->dynamicCall("Add(QString)", path);
    m_activeDoc = querySubObject("ActiveDocument");

    return m_activeDoc != nullptr;
}

void QWord::Save(QString save_as)
{
    if (save_as.isEmpty())
    {
        save_as = m_path;
    }
    m_activeDoc->dynamicCall("SaveAs(QString)", save_as);
    m_activeDoc->dynamicCall("Close(boolean)", true);
    dynamicCall("Quit(void)");
}

QAxObject *QWord::SelectCurrentBookmark()
{
    if (!m_currentBookmark)
    {
        return nullptr;
    }

    m_currentBookmark->dynamicCall("Select(void)");

    auto *selection = querySubObject("Selection");

    if (!selection)
    {
        return nullptr;
    }

    return selection;
}

QWord &QWord::operator[](const QString &bookmark)
{
    m_currentBookmark = m_activeDoc->querySubObject("Bookmarks(QString)", bookmark);
    if (!m_currentBookmark)
    {
        qWarning() << "Bookmark" << bookmark << "does not exists";
    }
    return *this;
}

QWord &QWord::operator=(const QString &content)
{
    auto *selection = SelectCurrentBookmark();

    if (!selection)
    {
        return *this;
    }

    selection->dynamicCall("TypeText(QString)", content);

    return *this;
}

QWord &QWord::operator=(const QWordTable &table)
{
    auto *selection = SelectCurrentBookmark();

    if (!selection)
    {
        return *this;
    }

    // 水平居中
    selection->querySubObject("ParagraphFormat")->dynamicCall("Alignment", "wdAlignParagraphCenter");

    auto row = table.GetRowCount();
    auto column = table.GetColumnCount();
    QAxObject *range = selection->querySubObject("Range");
    QAxObject *tables = m_activeDoc->querySubObject("Tables");
    // 新建表格对象 row行数据+1（表头）
    QAxObject *table_obj = tables->querySubObject("Add(QVariant,int,int)", range->asVariant(), row + 1, column);

    // 表格自动拉伸列 0固定  1根据内容调整  2 根据窗口调整
    table_obj->dynamicCall("AutoFitBehavior(WdAutoFitBehavior)", 2);

    const auto &horizontal_headers = table.GetHorizontalHeaders();

    // 表头赋值填充
    for (int i = 0; i < column; i++)
    {
        if (auto *header_cell = table_obj->querySubObject("Cell(int,int)", kTableColBegin, i + 1))
        {
            if (auto *range_cell = header_cell->querySubObject("Range"))
            {
                // 设置这一格的文本
                range_cell->dynamicCall("SetText(QString)", horizontal_headers[i]);
                // 加粗
                range_cell->dynamicCall("SetBold(int)", 1);
            }
        }
    }

    // 表格填充
    for (int i = 0; i < row; i++)
    {
        const auto &row_content = table.GetRow(i);
        for (int j = 0; j < column; j++)
        {
            // 指定某行 某列的数据单元
            if (auto *data_cell = table_obj->querySubObject("Cell(int,int)", i + kTableRowBegin, j + kTableColBegin))
            {
                data_cell->dynamicCall("Select(void)");
                if (auto *data_range = data_cell->querySubObject("Range"))
                {
                    // 填充文本
                    data_range->setProperty("Text", row_content[j]);
                    // 设置字体
                    if (auto *font_obj = data_range->querySubObject("Font"))
                    {
                        font_obj->setProperty("Size", 10);
                        font_obj->setProperty("Name", "Times New Roman");
                    }
                }
            }
        }
    }

    return *this;
}