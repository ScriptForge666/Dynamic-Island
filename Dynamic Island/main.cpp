#include "SystemTray.h"
#include <QQmlApplicationEngine>
#include <QQuickWindow>
#include <QPainterPath>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QApplication>

int main(int argc, char *argv[])
{
#if defined(Q_OS_WIN) && QT_VERSION_CHECK(5, 6, 0) <= QT_VERSION && QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QApplication app(argc, argv);

    QSystemTrayIcon trayIcon;

    trayIcon.setIcon(QIcon(":/photo/icon.png")); // 使用资源文件或本地图片
    trayIcon.setToolTip("Dynamic Island");
    // 可选：添加右键菜单
    QMenu menu;
    QAction quitAction("退出", &app);
    QObject::connect(&quitAction, &QAction::triggered, &app, &QApplication::quit);
    menu.addAction(&quitAction);
    trayIcon.setContextMenu(&menu);
    trayIcon.show();
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

    if (!engine.rootObjects().isEmpty()) {
        QQuickWindow *window = qobject_cast<QQuickWindow *>(engine.rootObjects().first());
        
        if (window) {
            auto updateMask = [window, &engine]() {
                int w = window->width();
                int h = window->height();
                QPainterPath path;
                QObject* root = engine.rootObjects().first();
                bool isExpanded = root->property("isExpanded").toBool();
                int expendedradiusSize = root->property("expendedradiusSize").toInt();
                if(isExpanded) {
					path.addRoundedRect(0, 0, w, h, expendedradiusSize, expendedradiusSize);
                }
                else {
                    // 收缩状态，使用圆角矩形遮罩
                    path.addRoundedRect(0, 0, w, h, h / 2, h / 2);
                }
                QRegion mask = QRegion(path.toFillPolygon().toPolygon());
                window->setMask(mask);
            };
            QObject::connect(window, &QQuickWindow::widthChanged, window, updateMask);
            QObject::connect(window, &QQuickWindow::heightChanged, window, updateMask);
            // 主动调用一次，确保初始就有遮罩
            QMetaObject::invokeMethod(window, [updateMask]() { updateMask(); }, Qt::QueuedConnection);
        }
    }

	return app.exec();
}
