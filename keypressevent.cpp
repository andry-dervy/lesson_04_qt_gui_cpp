
#include "keypressevent.h"
#include <QKeyEvent>

KeyPressEvent::KeyPressEvent(QObject *parent) : QObject(parent)
{

}

bool KeyPressEvent::eventFilter(QObject* obj, QEvent* event)
{
    if (event->type() == QEvent::KeyPress)
    {
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);

        if(keyEvent == nullptr) return false;

        auto hotKey = std::make_pair(keyEvent->key(), keyEvent->modifiers());

        auto hk_newFile = hotkeys.find(eTYPE_HOTKEY::NewFile);
        if(hk_newFile != hotkeys.end())
        {
            if(hk_newFile->second == hotKey)
                emit newFile();
        }
        else if(keyEvent->matches(QKeySequence::StandardKey::New))
        {
            emit newFile();
        }

        auto hk_openFile = hotkeys.find(eTYPE_HOTKEY::OpenFile);
        if(hk_openFile != hotkeys.end())
        {
            if(hk_openFile->second == hotKey)
                emit openFile();
        }
        else if(keyEvent->matches(QKeySequence::StandardKey::Open))
        {
            emit openFile();
        }

        auto hk_saveFile = hotkeys.find(eTYPE_HOTKEY::SaveFile);
        if(hk_saveFile != hotkeys.end())
        {
            if(hk_saveFile->second == hotKey)
                emit saveFile();
        }
        else if(keyEvent->matches(QKeySequence::StandardKey::Save))
        {
            emit saveFile();
        }

        auto hk_Quit = hotkeys.find(eTYPE_HOTKEY::Quit);
        if(hk_Quit != hotkeys.end())
        {
            if(hk_Quit->second == hotKey)
                emit quit();
        }
        else if(keyEvent->matches(QKeySequence::StandardKey::Quit))
        {
            emit quit();
        }
        return true;
    }
    if (event->type() == QEvent::KeyRelease) return true;
    return QObject::eventFilter(obj, event);
}

void KeyPressEvent::setHotKey(eTYPE_HOTKEY typeHotKey,std::pair<int,Qt::KeyboardModifiers>& p)
{
    auto itr = hotkeys.find(typeHotKey);
    if(itr != hotkeys.end()) hotkeys.erase(itr);
    hotkeys.insert({typeHotKey,p});
}
