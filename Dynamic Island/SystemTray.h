#pragma once
#ifndef SYSTEMTRAY_H
#define SYSTEMTRAY_H

#include <QApplication>
#include <QSystemTrayIcon>
#include <QMenu>

class SystemTray {
public:
	SystemTray() = delete; // 禁止默认构造函数
	SystemTray(QApplication& app) {
		m_trayIcon.setIcon(QIcon(":/photo/icon.png")); // 使用资源文件或本地图片
		m_trayIcon.setToolTip("Dynamic Island");
		// 可选：添加右键菜单
		QMenu menu;
		QAction quitAction("退出", &app);
		QObject::connect(&quitAction, &QAction::triggered, &app, &QApplication::quit);
		menu.addAction(&quitAction);
		m_trayIcon.setContextMenu(&menu);
		m_trayIcon.show();
	}
	QSystemTrayIcon& getTrayIcon() {
		return m_trayIcon;
	}
private:
	QSystemTrayIcon m_trayIcon;
};

#endif