#pragma once
#ifndef APPLICATION_H
#define	APPLICATION_H

import std;
#include <QApplication>

class Application {
public:
	Application() = delete; // 禁止默认构造函数
	Application(int argc, char* argv[]) {
		QApplication app(argc, argv);
		m_app = std::move(app);
	}

	QApplication& getApp() {
		return m_app;
	}

private:
	QApplication m_app;
};

#endif