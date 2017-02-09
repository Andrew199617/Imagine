#pragma once
#include "FolderButton.h"
#include "QtGui\qlistwidget.h"
struct dirent;
//FolderButton
class CBFilesButton : public FolderButton
{
public:
	CBFilesButton(dirent* Entry,std::string FilePath);
	~CBFilesButton();

protected:
	void Initialize();

protected:
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void dragEnterEvent(QDragEnterEvent *event);
	void dragMoveEvent(QDragMoveEvent *event);
	void dropEvent(QDropEvent *event);

private:
	void GetFileData();
	void PerformDrag();

private:
	QPoint startPos;
	QPixmap pixmap;
	dirent* entry;
	std::string fileName;
	std::string fileType;
	std::string filePath;

	static CBFilesButton* currentlyPressedFile;
};

