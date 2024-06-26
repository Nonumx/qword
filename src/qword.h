#pragma once

#include <QtCore>
#include <memory>

#if defined(QWORD_LIB)
#define QWORD_EXPORT __declspec(dllexport)
#else
#define QWORD_EXPORT __declspec(dllimport)
#endif

struct QWordTable
{
    QStringList m_horizontalHeaders;
    QList<QStringList> m_content;

    QStringList GetHorizontalHeaders() const { return m_horizontalHeaders; }
    void SetHorizontalHeaders(const QStringList &horizontal_headers) { m_horizontalHeaders = horizontal_headers; }

    void SetContent(const QList<QStringList> &content)
    {
        for (const auto &row : content)
        {
            if (row.size() != m_horizontalHeaders.size())
            {
                // 列数与表头不一致，不进行表内容设置
                return;
            }
        }
        m_content = content;
    }

    void AddRow(const QStringList &row)
    {
        if (row.size() != m_horizontalHeaders.size())
        {
            return;
        }
        m_content.push_back(row);
    }
    QStringList GetRow(int index) const { return m_content[index]; }

    int GetRowCount() const { return m_content.size(); }
    int GetColumnCount() const { return m_horizontalHeaders.size(); }
};

struct QWordImpl;

class QWORD_EXPORT QWord
{
  public:
    QWord();
    explicit QWord(const QString &path);

    bool Open(const QString &path);
    void Save(QString save_as = QString());

    QWord &operator[](const QString &bookmark);
    QWord &operator=(const QString &content);
    QWord &operator=(const QWordTable &table);

  private:
    std::shared_ptr<QWordImpl> m_impl;
    QString m_path;
};