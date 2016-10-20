#pragma once
#include <QtGui\qwidget.h>
class QLineEdit;
class QLabel;
class QHBoxLayout;
class QPushButton;
class QVBoxLayout;
class QFrame;
class QMessageBox;

namespace Imgn 
{
	enum{
		ClassNameLabel = 0,
	};

	class ImgnCreateComponent :
		public QWidget
	{
		Q_OBJECT
	public:
		ImgnCreateComponent(QWidget *parent);
		~ImgnCreateComponent();
		
		void Initialize();
		void AddButtons();
		
	private:
		QVBoxLayout* m_Layout;
		QHBoxLayout* classNameLayout;
		
		QLabel* labels[3];
		QLineEdit* className;
		QMessageBox* noClassName;
		QLineEdit* inheritance;

		QHBoxLayout* buttonLayout;
		QPushButton* addButton;
		QPushButton* cancelButton;

		QFrame* meWidget;
	
	private slots:
		void CreateClass();
	};
}


