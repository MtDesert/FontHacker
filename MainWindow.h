#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include<QMainWindow>
#include"Widget_BitmapFont.h"
#include"ui_MainWindow.h"

#include<QFont>
#include<QImage>
#include<QPainter>
#include<QFontDialog>

class MainWindow:public QMainWindow,private Ui::MainWindow{
	Q_OBJECT
public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

	QFontDialog fontDialog;//字体选择对话框,用于调整字体
	Widget_BitmapFont widgetBitmapFont;//显示字体效果的控件
public slots:
	void on_action_BitmapFontSize_triggered();
	void on_action_FontSelect_triggered();

	void on_fontDialog_currentFontChanged(QFont);
	void on_fontDialog_fontSelected(QFont);
protected:
	void keyReleaseEvent(QKeyEvent*);
	void closeEvent(QCloseEvent*);
};
#endif // MAINWINDOW_H