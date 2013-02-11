#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle(tr("GScribo"));

    initGraphicsRegion();
    initTextRegion();
    initXmlWidget();
    initPageWidget();
    initToolBar();
    initMenuBar();

    connectWidgets();
    connectShortcuts();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initGraphicsRegion()
{
    // Cache backgroud to speed up its repaint.
    graphicsView.setCacheMode(QGraphicsView::CacheBackground);
    graphicsView.setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
    graphicsView.setScene(&scene);

    setCentralWidget(&graphicsView);
}

void MainWindow::initPageWidget()
{
    dockPages.setWindowTitle(tr("Pages"));
    dockPages.setFeatures(QDockWidget::DockWidgetClosable);
    dockPages.setMaximumWidth(190);
    dockPages.setMinimumWidth(190);
    dockPages.setWidget(&pagesWidget);

    addDockWidget(Qt::LeftDockWidgetArea, &dockPages);
}

void MainWindow::initXmlWidget()
{
    dockXml.setWindowTitle(tr("Xml"));
    dockXml.setFeatures(QDockWidget::DockWidgetClosable);
    dockXml.setWidget(&xmlWidget);

    addDockWidget(Qt::BottomDockWidgetArea, &dockXml);
}

void MainWindow::initTextRegion()
{
    dockText.setWindowTitle(tr("Text"));
    dockText.setAllowedAreas(Qt::AllDockWidgetAreas);
    dockText.setFeatures(QDockWidget::DockWidgetFloatable | QDockWidget::DockWidgetMovable);
    dockText.setWidget(&textEdit);

    addDockWidget(Qt::RightDockWidgetArea, &dockText);
    dockText.hide();
}

void MainWindow::initToolBar()
{
    QAction *open = ui->mainToolBar->addAction(tr("Open"));
    connect(open, SIGNAL(triggered()), this, SLOT(onOpen()));

    QAction *segment = ui->mainToolBar->addAction(tr("Segment"));
    connect(segment, SIGNAL(triggered()), this, SLOT(onSegment()));

    QAction *del = ui->mainToolBar->addAction(tr("Delete"));
    connect(del, SIGNAL(triggered()), &pagesWidget, SLOT(removeSelection()));
}

void MainWindow::initMenuBar()
{
    QAction *preferences = ui->menuBar->addAction(tr("Preferences"));
    connect(preferences, SIGNAL(triggered()), SLOT(onPreferences()));
}

void MainWindow::onFileChanged(const QString &filename, const QPixmap &pixmap)
{
    // If it's not the current scene.
    if(scene.backgroundPath() != filename)
    {
        QString xmlPath = Xml::getPath(filename);
        // Check if the xml file exists to draw data in the scene.
        if(QFile(xmlPath).exists())
        {
            xml.load(xmlPath);
            scene.changeScene(filename, pixmap, xml.graphicItem());
            xmlWidget.changeView(xml.treeItem());
        }
        else
            scene.changeScene(filename, pixmap);
    }
}

void MainWindow::onOpen()
{
    QStringList paths = QFileDialog::getOpenFileNames(this, "Open Image(s)", QDir::homePath(), "Images (*.png *.jpg *.ppm *.bmp)");

    if(paths.count() > 0)
    {
        QString path = paths[0];
        QPixmap pixmap(path);

        pagesWidget.addPixmap(path, pixmap);

        // If more than one file, we store it in the page widget.
        for(int i = 1; i < paths.count(); i++)
        {
            path = paths[i];
            pixmap.load(path);
            pagesWidget.addPixmap(path, pixmap);
        }

        onFileChanged(path, pixmap);
    }
}

void MainWindow::onSegment()
{
    if(scene.backgroundPath() != "")
    {
        QStringList filenames;

        if(!pagesWidget.isVisible())
            filenames << scene.backgroundPath();
        else
            filenames = pagesWidget.filenames();

        // Run segmentation of page(s).
        progressDialog.reset();
        runner.start_demat(filenames);
    }
}

void MainWindow::onXmlSaved(const QString& filename)
{
    xml.load(filename);
    xmlWidget.changeView(xml.treeItem());
    scene.addPolygonItem(xml.graphicItem());
}

void MainWindow::onPreferences()
{
    PreferencesDialog *preferenceDialog = new PreferencesDialog(this);
    preferenceDialog->show();
}

void MainWindow::connectWidgets()
{
    // If double click on a picture of the page widget -> draw it on background scene.
    connect(&pagesWidget, SIGNAL(sceneChanged(QString,QPixmap)), this, SLOT(onFileChanged(QString,QPixmap)));

    // Connect scene selection with xml tree and vice versa.
    connect(&scene, SIGNAL(selectTreeItems(QList<QTreeWidgetItem*>)), &xmlWidget, SLOT(selectItems(QList<QTreeWidgetItem*>)));
    connect(&xmlWidget, SIGNAL(selectGraphicalItem(PolygonItem*)), &scene, SLOT(selectItem(PolygonItem*)));
    connect(&pagesWidget, SIGNAL(removeTreeSelection()), &xmlWidget, SLOT(clear()));

    connect(&runner, SIGNAL(progress()), &progressDialog, SLOT(run()));
    connect(&runner, SIGNAL(new_progress_max_value(int)), &progressDialog, SLOT(setMaximum(int)));
    connect(&runner, SIGNAL(new_progress_label(QString)), &progressDialog, SLOT(setLabelText(QString)));
    connect(&runner, SIGNAL(finished()), &progressDialog, SLOT(close()));
    connect(&runner, SIGNAL(xml_saved(QString)), this, SLOT(onXmlSaved(QString)));
}

void MainWindow::connectShortcuts()
{
    QShortcut *del = new QShortcut(Qt::Key_Delete, &pagesWidget);
    connect(del, SIGNAL(activated()), &pagesWidget, SLOT(removeSelection()));
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type())
    {
        case QEvent::LanguageChange:
            ui->retranslateUi(this);
            break;
        default:
            break;
    }
}
