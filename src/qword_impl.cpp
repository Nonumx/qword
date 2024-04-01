#include "qword_impl.h"

QAxObject *QWordImpl::SelectCurrentBookmark()
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