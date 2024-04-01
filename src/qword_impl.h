#pragma once

#include <QAxObject>

const QString kWordApplication = "Word.Application";

struct QWordImpl : public QAxObject
{
    QWordImpl() : QAxObject(kWordApplication) {}
    QAxObject *SelectCurrentBookmark();

    QAxObject *m_activeDoc{};
    QAxObject *m_currentBookmark{};

  private:
    Q_OBJECT
};