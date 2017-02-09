#include "CBFilesButton.h"
#include "dirent.h"
#include "Qt\qdir.h"
#include "QtGui\QLabel"
#include "QtGui\qevent.h"
#include "Qt\qurl.h"
#include "Qt\qapplication.h"
#include <string.h>
#include "ImgnMimeData.h"

CBFilesButton::CBFilesButton(dirent * Entry,std::string FilePath) : FolderButton(false)
{
	fileType = "";
	filePath = FilePath;
	entry = Entry;
	Initialize();
}

CBFilesButton::~CBFilesButton()
{
	
}

void CBFilesButton::Initialize()
{

	QIcon icon;
	if (entry->d_type == DT_DIR)
	{
		//Is Folder
		pixmap.load("../EngineData/Icons/Folder.png");
		icon.addPixmap(pixmap);
	}
	else if (entry->d_type == DT_REG)
	{
		GetFileData();
		if (fileType == "txt")
		{
			pixmap.load("../EngineData/Icons/Txt.png");
			icon.addPixmap(pixmap);
		}
		else if (fileType == "imgnasset")
		{
			pixmap.load("../EngineData/Icons/ImgnAsset.png");
			icon.addPixmap(pixmap);
		}
		else if (fileType == "png")
		{
			pixmap.load("../EngineData/Icons/Image.png");
			icon.addPixmap(pixmap);
		}
		else if (fileType == "bmp")
		{
			pixmap.load("../EngineData/Icons/Image.png");
			icon.addPixmap(pixmap);
		}
		else
		{
			pixmap.load("../EngineData/Icons/Txt.png");
			icon.addPixmap(pixmap);
		}
	}
	else
	{
		setText("No Icon");
	}

	setIcon(icon);
	FolderButton::setIconSize(QSize(48, 48));
	FolderButton::setObjectName("FilesButton");
	FolderButton::setFixedSize(48, 48);
	FolderButton::sizePolicy().setHorizontalPolicy(QSizePolicy::Expanding);
}

void CBFilesButton::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
		startPos = event->pos();
	FolderButton::mousePressEvent(event);
}

void CBFilesButton::mouseMoveEvent(QMouseEvent *event)
{
	if (event->buttons() & Qt::LeftButton) {
		int distance = (event->pos() - startPos).manhattanLength();
		if (distance >= QApplication::startDragDistance())
			PerformDrag();
	}
	FolderButton::mouseMoveEvent(event);
}

void CBFilesButton::dragEnterEvent(QDragEnterEvent *event)
{

}

void CBFilesButton::dragMoveEvent(QDragMoveEvent *event)
{
	/*ProjectListWidget *source =
		qobject_cast<ProjectListWidget *>(event->source());
	if (source && source != this) {
		event->setDropAction(Qt::MoveAction);
		event->accept();
	}*/
}

void CBFilesButton::dropEvent(QDropEvent *event)
{

}

void CBFilesButton::GetFileData()
{
	char* cFileType = 0;
	char* cFileName = 0;
	
	for (unsigned i = 0; i < entry->d_namlen; i++)
	{	
		if (entry->d_name[i] == '.')
		{
			cFileName = new char[i + 1];
			strncpy(cFileName, entry->d_name, i);
			cFileName[i] = 0;
			i++;
			cFileType = new char[entry->d_namlen - i + 1];
			strcpy_s(cFileType, entry->d_namlen - i + 1, entry->d_name + i);
			break;
		}
	}
	if (cFileType && cFileName)
	{
		fileName = cFileName;
		fileType = cFileType;
		delete cFileType;
		delete cFileName;
	}
}

void CBFilesButton::PerformDrag()
{
	ImgnMimeData *mimeData = new ImgnMimeData;
	mimeData->Extension(fileType);
	mimeData->FileName(fileName);
	mimeData->SetFilePath(filePath);

	QDrag *drag = new QDrag(static_cast<QWidget*>(this));
	drag->setMimeData(mimeData);
	drag->setPixmap(pixmap);
	drag->exec(Qt::MoveAction);
}
