/****************************************************************************
**
** Copyright (C) 2011 Research In Motion Limited
**
** This file is part of the plugins of the Qt Toolkit.
**
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
****************************************************************************/

#ifndef QBBSCREEN_H
#define QBBSCREEN_H

#include <QtGui/QPlatformScreen>
#include <QByteArray>

#include <screen/screen.h>

QT_BEGIN_NAMESPACE

class QBBWindow;

class QBBScreen : public QPlatformScreen
{
public:
    static QList<QPlatformScreen *> screens() { return sScreens; }
    static void createDisplays(screen_context_t context);
    static void destroyDisplays();
    static QBBScreen* primaryDisplay() { return static_cast<QBBScreen*>(sScreens.at(0)); }

    virtual QRect geometry() const { return mCurrentGeometry; }
    virtual QRect availableGeometry() const;
    virtual int depth() const { return 32; }
    virtual QImage::Format format() const { return QImage::Format_RGB32; }
    virtual QSize physicalSize() const { return mCurrentPhysicalSize; }

    int rotation() const { return mCurrentRotation; }
    void setRotation(int rotation);

    screen_display_t nativeDisplay() const { return mDisplay; }
    screen_context_t nativeContext() const { return mContext; }
    const char *windowGroupName() const { return mWindowGroupName.constData(); }

    /* Window heirarchy management */
    static void addWindow(QBBWindow* child);
    static void removeWindow(QBBWindow* child);
    static void raiseWindow(QBBWindow* window);
    static void lowerWindow(QBBWindow* window);
    static void updateHierarchy();

private:
    QBBScreen(screen_context_t context, screen_display_t display);
    virtual ~QBBScreen();

    screen_context_t mContext;
    screen_display_t mDisplay;
    screen_window_t mAppWindow;
    QByteArray mWindowGroupName;

    int mStartRotation;
    int mCurrentRotation;
    QSize mStartPhysicalSize;
    QSize mCurrentPhysicalSize;
    QRect mStartGeometry;
    QRect mCurrentGeometry;
    static QList<QBBWindow*> sChildren;

    static bool orthogonal(int rotation1, int rotation2);
    static QList<QPlatformScreen *> sScreens;
};

QT_END_NAMESPACE

#endif // QBBSCREEN_H
